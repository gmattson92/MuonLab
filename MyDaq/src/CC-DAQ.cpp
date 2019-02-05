#include "MyDaq.h"

#include "GenericModule.h"
#include "Phillips2249W.h"

#include <TApplication.h>

int main (int argc,  char *argv[])
{
  MyDaq* daq = new MyDaq();
  
  // Add  ADC module with 12 channels to slot 1. Has 10 bit output
  daq->AddModule( new GenericModule(  "ADC", 12, 1, 2, 1024) );
  // Add  ADC module with 12 channels to slot 2. Has 10 bit output
  daq->AddModule( new GenericModule(  "ADC", 12, 2, 2, 1024) );
  // Add STDC module with 16 channels to slot 8. Has 12 bit output
  daq->AddModule( new Phillips2249W( "STDC", 16, 8         ) ); 
  // Add FTDC module with  8 channels to slot 9. Has 11 bit output
  daq->AddModule( new GenericModule( "FTDC", 8,  9, 2, 2048) );

  daq->Run();

  return 0;
}

