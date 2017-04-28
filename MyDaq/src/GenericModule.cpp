/**
 * @file GenericModule.cpp
 * Implementation for GenericModule class
 *
 * @brief 
 *
 * @author Yakov Kulinich 
 * @version 1.0
 */

#include "GenericModule.h"
#include "SharedData.h"

#include <stdio.h>

#include <TTree.h>
#include <TFile.h>
#include <TH1.h>
#include <TSystem.h>
#include <TCanvas.h>

#include <iostream>

//--------------------------------
//            GenericModule
//--------------------------------

GenericModule :: GenericModule() {
  m_moduleName = "NONE"; m_nChannels = 0; m_slotNumber = 0; m_dataBank = NULL; m_readCommand = 0;
}

GenericModule :: GenericModule( std::string moduleName, int nChannels, int slotNumber, int readCommand, int nDigitsData ) {  
  m_moduleName  = moduleName;
  m_nChannels   = nChannels;
  m_slotNumber  = slotNumber;
  m_readCommand = readCommand;
  m_nDigitsData = nDigitsData;
  m_dataBank    = new short[nChannels];
}

GenericModule :: ~GenericModule(){
  delete [] m_dataBank; 
  m_dataBank = NULL;
}

void GenericModule :: RegisterSharedData( SharedData* sd ) {
  m_sd = sd;
}

/**
   Adds series of read commands to stack.
   These depend on module's slot number and read command.
   Stop bits (16) are added before and after the commands.
 */
void GenericModule :: AddClearingReadToStack( std::vector<long>& stack ){
  stack.push_back( Q_STOP_BIT );  
  for( int i = 0; i < m_nChannels; i++ ){
    stack.push_back( CreateSimpleCommand( m_slotNumber, i, m_readCommand) );
  }
  stack.push_back( CreateSimpleCommand( m_slotNumber, 0, 9 ) ); // N,0,9 (N,A,F)
  stack.push_back( Q_STOP_BIT );   
}

/**
   CAMAC Commands are constructed as follows.
   command = N*512 + A*32  + F
   equivalent to
   command = N*2^9 + A*2^5 + F
 */
long GenericModule :: CreateSimpleCommand( int N, int A, int F){
  return ( N<<9 ) + ( A<<5 ) + F;
}


/**
   Add output for this module. This means adding branches
   to the tree and creating histograms.

   For basic module, we assume a 10 bit module even though its a 12
   bit data word. (Front 2 bits are for?)
   10 bit module means 0-1024 channels.
*/
void GenericModule :: AddOutput(){
  char name [128];
  
  for( int ch = 0; ch < m_nChannels; ch++){
    sprintf( name, "h_%s_%d_%d",  m_moduleName.c_str(), m_slotNumber, ch );  
    m_hists.push_back( new TH1F( name, name, m_nDigitsData + 10 , 0, m_nDigitsData + 10 ) );
    m_sd->GetHists()[ name ] = m_hists.back();

    sprintf( name, "%s_%d_%d",  m_moduleName.c_str(), m_slotNumber, ch );  
    m_sd->GetTree()->Branch( name, &m_dataBank[ch] );
  }
}


/**
   For a simple module the data is simple. We read the 
   word and the data is that!

   p is going to point at first actual data member.
   This is the first channel in most modules. First data
   member is next item after the Q_STOP_BIT.
 */
void GenericModule :: ReadData( short* p ){
  for( int i = 0; i < m_nChannels; i++ ){
    m_dataBank[i] = *(p + i);
  }
}

/**
   Here we just go and fill histograms based on our 
   data bank information. 

   These histograms are for monitoring, so if the value
   is 0 or m_nDigitsData we dont fill (so we only see useful info).

   One can then compare total number of events to number of entries 
   in the histogram to see how well the module is working.
 */
void GenericModule :: FillHistograms(){
 for( int ch = 0; ch < m_nChannels; ch++){
   short data = m_dataBank[ch];
   if( data > 0 && data < m_nDigitsData) 
     m_hists.at(ch)->Fill( m_dataBank[ch] );
 }
}

void GenericModule :: Print() { 
  std::cerr << m_moduleName << " with " 
	    << m_nChannels  << " channels in " 
	    << m_slotNumber << " slot number." << std::endl; 
}
