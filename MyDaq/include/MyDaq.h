#ifndef MYDAQ_H
#define MYDAQ_H

#include "Common.h"

#include <libxxusb.h>
#include <thread> 
#include <atomic>

#include <TString.h>

/**
   @brief MyDaq is the main class for the DAQ system.
   It can be though of as the CAMAC crate and controller.
   From here, we do the control of the whole system.
   This class is instanciated by the user, and modules are added
   by the user. The user can then Run the DAQ with the rest of 
   the interface hidden from them.
*/
class MyDaq{
  
  friend class MyMainFrame;

 public:
  /**
     @brief Default constructor for MyDaq.
   */
  MyDaq();

  /**
     @brief Default destructor for MyDaq.
   */
  ~MyDaq();

 public:
  /**
     @brief Function to add modules to MyDaq

     @param param1 Pointer to module being added
   */
  void AddModule( Module* );

  /**
     @brief Main function in MyDaq. Called by user.
  */
  int  Run();                  

 private: 
  /**
     @brief Function to print info about DAQ
  */
  void PrintInfo();        

  /**
     @brief Function to initialize CAMAC
  */
  int InitializeCAMAC();         
  
  /**
     @brief Function to Prepare and load stack into DAQ
  */
  int PrepareAndLoadStack();  

  /**
     @brief Function to Initialize output data for modules
  */
  void InitializeModulesOutput();  

  /**
     @brief Function to initialize DAQ
  */
  void InitializeDAQ();     

  /**
     @brief Function to take data
  */
  void TakeData();  

  /**
     @brief Function processes data bank into ROOT
  */
  void ProcessDataIntoROOT();

  /**
     @brief Function to finalize data taking
  */
  void Finalize();  


 private:
  xxusb_device_type devices[100]; 
  struct usb_device *dev;      // Device
  usb_dev_handle *udev;        // Device Handle 

  /// collection of modules in DAQ
  std::vector< Module* > m_modules;
  long m_firmware_id;
  long m_nWordsExpectedPerEvent;

  /// Pointer to Data Class
  SharedData* m_sd;

  // Application Stuff
  TApplication* m_theApp;   
  MyMainFrame*  m_myMainFrame; 

  TString       m_fout_name;

  // thread things
  std::thread* m_t_app;
  std::thread* m_t_daq;

  std::atomic<bool> m_start_flag;
  std::atomic<bool> m_stop_flag;

 public:
  /**
     @brief Getter for shared data
   */
  SharedData* GetSharedData(){ return m_sd; }
};


#endif
