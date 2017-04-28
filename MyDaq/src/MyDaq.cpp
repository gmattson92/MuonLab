/**
 * @file MyDaq.cpp
 * Implementation for MyDaq class
 *
 * @brief 
 *
 * @author Yakov Kulinich 
 * @version 1.0
 */

#include "MyDaq.h"
#include "Module.h"
#include "SharedData.h"
#include "MyMainFrame.h"

#include <stdio.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

#include <TTree.h>
#include <TFile.h>
#include <TH1.h>
#include <TSystem.h>
#include <TCanvas.h>

#include <TApplication.h>
#include <TGClient.h>

#include <iostream>

static const int STACK_VERBOSE = 0;

//--------------------------------
//            MyDaq
//--------------------------------

/**
   Adds a module to the collection of MyDaq's modules.
   MyDaq, who is the only one that can make SharedData,
   lets the modules know about the shared data by passing
   them a copy of the pointer.
 */
MyDaq :: MyDaq () {
  m_sd = new SharedData();
  m_nWordsExpectedPerEvent = 0;
  
  m_t_app = NULL;
  m_t_daq = NULL;

  m_start_flag = false;
  m_stop_flag  = false;
} 

MyDaq :: ~MyDaq() { 
  delete m_sd; 

  delete m_t_app;
  delete m_t_daq;

  delete m_theApp;
  delete m_myMainFrame;

  m_sd = NULL;
}

void MyDaq :: AddModule( Module* module ) { 
  m_modules.push_back( module ); 
  module->RegisterSharedData( m_sd );
} 

void MyDaq :: PrintInfo(){
  std::cerr << "Firmware ID           : " << m_firmware_id << std::endl;
  std::cerr << "Available modules are : \n" << std::endl;
  for( auto& module : m_modules ) module->Print();
}

/**
   Here the DAQ is initialized, stack loaded, and running started.
   At the end of the run, output is finalized and the program exits.
 */
int MyDaq :: Run(){
  std::cerr << "\n     MyDaq :: Run\n" << std::endl;

  if( !InitializeCAMAC() ) return 0; 
  PrintInfo();
  if( !PrepareAndLoadStack() ) return 0;
  InitializeModulesOutput();

  m_theApp      = new TApplication("App", NULL, NULL);
  m_myMainFrame = new MyMainFrame( gClient->GetRoot(), 400, 400, this);
  
  m_t_app = new std::thread( [this] { m_theApp->Run( kTRUE ); } );

  while( !m_start_flag && !m_stop_flag ) continue;
  
  if( m_start_flag && !m_stop_flag ){
    InitializeDAQ();
    m_t_daq = new std::thread( [this] { TakeData(); } );  

    // We have a start, and we join the threads, now MyDaq::Run waits until both threads finish
    m_t_app->join();               
    m_t_daq->join();           
  }
  else if( !m_start_flag && m_stop_flag ){
    std::cerr << "\nNever started DAQ. Quitting!" << std::endl;
    return 0;
  }
  
  // Both threads are done, we can finalize (write output and quit).
  Finalize();
 
  return 1;
}

/**
   First, attempt to find a cc-usb device. If it is found,
   and it responds, try to open/connect to it.

   Once all this is successful, the device handle, which is a hook
   from our device to this code, is used throughout the program in 
   function calls that go to cc-usb.

   Some read, write, clear, inhibit calls are tested 

   Also, the trigger delay (100 us) and buffer size (4k) are set.
 */
int MyDaq :: InitializeCAMAC(){
  std::cerr << "\n     MyDaq :: InitializeCAMAC\n" << std::endl;

  int   CamQ, CamX;       // X, Q dataway info, D is dummy
  long  CamD;             // Dummy for CAMAC_read which shouldnt read anything

  std::cerr << "Finding XX_USB devices and opening first one found" << std::endl;;
  
  //Find XX_USB devices and open the first one found
  xxusb_devices_find(devices);
  dev = devices[0].usbdev;
  if( dev <= 0 ){
    std::cerr << "\n\nDevice not xxusb\n\n" << std::endl;
    return 0;
  }
  udev = xxusb_device_open(dev); 
  if(!udev)  {
    std::cerr << "\n\nFailedto Open CC_USB \n\n" << std::endl;
    return 0;
  }
  else{
    std::cerr << "Found   XX_USB device" << std::endl;;
    CAMAC_read( udev, 25, 0, 0, &m_firmware_id, &CamQ, &CamX);
  }

  std::cerr << "\nTesting data lines...." << std::endl;
  
  short ret = -1;

  // Fix this up ??
  ret = CAMAC_Z(udev);
  if( ret > 0 ) ret = CAMAC_I(udev, true);
  if( ret > 0 ) ret = CAMAC_write(udev, 1, 0, 16, 0xa,&CamQ, &CamX);
  if( ret > 0 ) ret = CAMAC_read(udev, 1, 0, 0, &CamD,&CamQ, &CamX);
  if( ret > 0 ) ret = CAMAC_C(udev);
  if( ret > 0 ) ret = CAMAC_I(udev, false);
  if( ret > 0 ) ret = CAMAC_Z(udev);
  
  if( ret <= 0 ) { 
    std::cerr << "Some data lines didnt work" << std::endl;
    return 0;
  }

  std::cerr << "Done testing data lines....\n" << std::endl;;

  // Define Trigger to be Crate Trigger (L1) 
  CAMAC_write( udev, 25, 9, 16, 0x0, &CamQ, &CamX );
  // Define Trigger Delay to 100us. Bits 0 to 15 in Delay Register N(25) A(2) F(16)
  ret = CAMAC_write(udev, 25, 2, 16, 0x64,&CamQ, &CamX);
 
  // Set buffer size to 4k BuffOpt in Global Mode register N(25) A(1) F(16)
  ret = CAMAC_write(udev, 25, 1, 16, 0x02,&CamQ, &CamX);
 
  return 1;
}

/**
   Prepare the stack. Loop through the modules in this DAQ
   And add their clearing read commands to stack. Commands
   are preceeded and followed by q-stop bits. Q-stop bit also 
   added after first element of stack. Final marker word added at bottom.

   Stack is then written to the cc-usb, and read for verification.
 */
int MyDaq :: PrepareAndLoadStack(){
  std::cerr << "\n     MyDaq :: PrepareAndLoadStack\n" << std::endl;

  // prepare stack and load to CC-USB
  std::vector< long > writeStack; // leave this dynamic, easier 
  long readStack[MAX_STACK_SIZE]; // max stack size = 256 for now

  writeStack.push_back(0);
  writeStack.push_back( Q_STOP_BIT );   

  for( auto& module : m_modules ){ // Loop over all modules
    module->AddClearingReadToStack( writeStack );
  }

  // End Marker
  writeStack.push_back( STACK_END_MARKER  );	       // marker = ffff
 
  long nStackCommands = writeStack.size() - 1;
  writeStack[0]       = nStackCommands;  

  // Load stack into CC-USB
  short nBytesSent = xxusb_stack_write(udev, 2, &(writeStack[0]) );
  // verify stack
  short nBytesRecieved = xxusb_stack_read(udev, 2, readStack);
  long nReadStackCommands = readStack[0];

  if( nStackCommands != nReadStackCommands ||
      (nBytesSent - 2 - nBytesRecieved) != 0 ){
    std::cerr << "Something wrong with stack " << std::cerr;
    return 0;
  }

  if( STACK_VERBOSE){
    std::cerr << "Stack Size = " << nStackCommands << std::endl;
    std::cerr << " WRITE STACK" << std::endl;
    for( int i = 0; i < nStackCommands; i++){
      std::cerr << i << " command = " << writeStack[i] << std::endl;
    }
    
    std::cerr << " VERIFY STACK" << std::endl;
    for( int i = 0; i < nReadStackCommands; i++){
      std::cerr << i << " command = " << readStack[i] << std::endl;
    } 
    std::cerr << "Verified Stack Size = " << nStackCommands << std::endl;
  }
  
  short ret = xxusb_stack_execute(udev, &(writeStack[0]) );
  std::cerr << ret << "  Stack executed once" << std::endl;

  return 1;
}

void MyDaq :: InitializeModulesOutput(){
  std::cerr << "\n     MyDaq :: InitializeModulesOutput\n" << std::endl;

  for( auto& module : m_modules ) {
    module->AddOutput();
    m_nWordsExpectedPerEvent += (module->GetNchannels() + 1);
  }
  // one for first word (nwords expected)
  // and one for negative one at end 
  m_nWordsExpectedPerEvent += 2; 

  std::cerr << "Number of words expected per even is " << m_nWordsExpectedPerEvent << std::endl;
}

/**
   Function to start acquisition ( write to xxusb register )
   Also create output filename based on either user input
   or default (output.root).
 */

void MyDaq :: InitializeDAQ(){
  //  START DAQ
  xxusb_register_write(udev, 1, 0x1); // start acquisition
  
  // got a start, inform that we are begining reading
  std::cerr << "Switch to DAQ & Reading data\n" << std::endl;
  std::cerr << "Output Filename = " << m_fout_name.Data()  << std::endl;
  m_sd->SetFout( new TFile( m_fout_name.Data(),"RECREATE") );
}

/**
   Main loop for reading data from CC-USB.
   Once we enter daq mode, we start taking data continuously.
   The crate will write out only when its buffer is full.

   The main GUI application and the TakeData() run on separate threads
   and there are some flags that the GUI application controls which
   indicate in TakeData() when to start and when to stop.

   These flags are atomic variables so there should not be any lock problems.
 */

void MyDaq :: TakeData() {
  std::cerr << "\n     MyDaq :: TakeData\n" << std::endl;

  short ret = -1;

  short dataStream[100000]; 
  long  wordsReturned = 0; 
  long  bytesReturned = 0;
  int   nLoopsRead    = 0;

  unsigned int nModules = m_modules.size();

  int loop = 0;
  int totalEvents = 0;

  while(true){ 
    bytesReturned = xxusb_bulk_read(udev, dataStream, 2056, 100);	// use for32-bit data
    wordsReturned = bytesReturned / 2;
    if( bytesReturned > 0 ) {
      int nEvents = (dataStream[0] & 0xffff);
      totalEvents += nEvents;
      printf("Events in loop %i : %i   bytesReturned : %ld    totalEvents : %d\n", loop, nEvents, bytesReturned, totalEvents);
      nLoopsRead++;

      // Check if number of recieved words in the packet matches how much
      // we expect for a given number of events (dataStream[0] element)
      if( (m_nWordsExpectedPerEvent * nEvents + 2 ) != wordsReturned ){
	std::cerr << "Bad Packet - Dropping" << std::endl;
	continue;
      }

      // We have recieved our data packet, we know number of data lines
      // and we know number of events in that packet.
      // [0] element in package is number of events. We set
      // out data pointer to look there
      short* dataPtr = dataStream;

      // Check to see if we have a a -1 (trailer last event), -1, 0. (End of packet) 
      // at the end of the packet. If we do, we can consider the packet 
      // to probably be correct. additional checks to be performed 
      // on per-event basis
      if( *( dataPtr +  m_nWordsExpectedPerEvent * nEvents ) == -1 && 
	  *( dataPtr +  m_nWordsExpectedPerEvent * nEvents + 1)     == -1 && 
	  *( dataPtr +  m_nWordsExpectedPerEvent * nEvents + 2) ==  0) { 
	// !!! GOOD PACKET !!!

	// First event in packet...
	//W
	// Now we set our dataPtr to look at [1] element.
	// This is the number of data in our event.
	// This includes a Q_STOP_BIT for every module, and a -1 trailer, 
	// plus number of channels in every module. 
	// 
	// I.e. for one 12 channel ADC and 16 channel TDC we expect
	// 12 + 1 + 16 + 1 + 1 (for -1) = 31 words
	dataPtr++; 

	// we know we have a good packet...
	// but are all the events inside good?
	// so far assume yes
	bool isBadEvent = false;

	// START EVENT LOOP.
	// should now be looking at dataStream[1] 
	for( int ev = 0; ev < nEvents; ev++ ){
	  if( isBadEvent ) break;
	  // At the beginning of every event, the dataPtr should be looking at 
	  // the first element of the event, which is number of words expected.
	  // 
	  // Check if m_nWordsExpectedPerEvent - 1 matches what we read
	  // the Minus one because the number which tells us how many words there are
	  // is also a word in the event.
	  //
	  // I.e. for our example of one ADC and one TDC we expect 32 words per event,
	  // so we echeck if *dataPtr is equal to 32 - 1 = 31
	  if( *( dataPtr ) == ( m_nWordsExpectedPerEvent - 1)   &&
	      *( dataPtr +  m_nWordsExpectedPerEvent - 1) == -1 && 
	      *( dataPtr + 1 ) == Q_STOP_BIT ){ 
	    // !!! GOOD EVENT !!!
	   
	    // dataPtr should now jump to zeroth data element
	    // of zeroth module
	    dataPtr += 2; 
	 
	    for( unsigned int moduleNumber = 0; moduleNumber < nModules; moduleNumber++){
	      m_modules[ moduleNumber ]->ReadData( dataPtr );
	     
	      dataPtr += m_modules[ moduleNumber ]->GetNchannels();
	      dataPtr++; 
	    }
	  } // END GOOD EVENT
	  else{ 
	    std::cerr << "Bad Event " << ev << " - Dropping" << std::endl;
	    isBadEvent = true;
	  }

	  // m_dataBanks are filled, now lets 
	  // fill ROOT Tree and histos.
	  ProcessDataIntoROOT();
	} // END EVENT LOOP
      }
      else{
	std::cerr << "Bad Packet - Dropping" << std::endl;
	continue;
      }
    }

    if( m_stop_flag ){
      std::cerr << "\n\nFinishing Run!" << std::endl;
      std::cerr << "Took " << totalEvents << " Events\n\n" << std::endl;
      break;
    }    
    loop ++;
  }

  // leave DAQ mode
  xxusb_register_write(udev, 1, 0x0);

  // CLEAN UP!!
  // drain all data from fifo
  ret=1;
  loop = 0;
  while(ret > 0) {
    ret = xxusb_bulk_read(udev, dataStream, 2048, 100);
    if(ret > 0){
      printf("drain loops: %i (result %i)\n", loop, ret);
      loop++;
      if (loop > 100) ret=0;
    }
  }

  xxusb_register_write(udev, 1, 0x0);
}


/**
   Done on a per-event basis
   This function processes each modules m_dataBank to add 
   information to ROOT Tree and histos.
   
   This can be added onto later, or a function such as 
   ProcessDataIntoBinary can be added. Also, if in the future
   a user wants to add additional branches to the ROOT tree,
   they can do it here. 

   ReadData should be left alone, as it 
   does the most basic thing.
 */
void MyDaq :: ProcessDataIntoROOT(){
  for( auto& module : m_modules ) module->FillHistograms();
  m_sd->m_tree->Fill();
}

void MyDaq :: Finalize() {
  std::cerr << "\n     MyDaq :: Finalize \n" << std::endl;

  m_sd->Finalize();
}
