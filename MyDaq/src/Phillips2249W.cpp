/**
 * @file Phillips2249W.cpp
 * Implementation for Phillips2249W class
 *
 * @brief 
 *
 * @author Yakov Kulinich 
 * @version 1.0
 */

#include "Phillips2249W.h"
#include "SharedData.h"

#include <stdio.h>

#include <TTree.h>
#include <TFile.h>
#include <TH1.h>
#include <TSystem.h>
#include <TCanvas.h>

#include <iostream>

//--------------------------------
//        Phillips2249W
//--------------------------------

Phillips2249W :: Phillips2249W ( std::string moduleName, int nChannels, int slotNumber ) : 
  GenericModule( moduleName, nChannels, slotNumber, 0, 4095 ){

  m_tdcsum = 0; 
  m_h_tdcsum = NULL;
} 

Phillips2249W :: ~Phillips2249W () {}

/**
   Add output for this Phillips2249W. This means adding branches
   to the tree and creating histograms.

   Phillips TDC data represents a 12 bit TDC so data go from
   0 to 4095 channels.
 */
void Phillips2249W :: AddOutput(){
  char name [128];
  
  // same thing we would do here
  GenericModule::AddOutput(); 

  // This is the "TDC SUM"
  // we need some additional output
  sprintf( name, "h_%s_%d_SUM",  m_moduleName.c_str(), m_slotNumber ); 
  m_h_tdcsum = new TH1F( name, name, m_nDigitsData + 10 , 0, m_nDigitsData + 10 );
  m_sd->GetHists()[ name ] = m_h_tdcsum;

  sprintf( name, "%s_%d_SUM",  m_moduleName.c_str(), m_slotNumber );   
  m_sd->GetTree()->Branch( name, &m_tdcsum );
}

/**
   Phillips TDC data is 16 bit.
   First Front 4 bits (highest bits) are channel number
   Lowests 12 bits are data.

   Also find a non 0 or 4095 value (if it exists)
*/
void Phillips2249W :: ReadData( short* p ){
  int ch, tdcdata;
  short data;

  m_tdcsum = 0;

  for( int i = 0; i < m_nChannels; i++ ){
    data = *(p + i);
    tdcdata = (data & 0x000FFF); 
    ch = (data & 0x00F000)>>12;	    
    m_dataBank[ch] = tdcdata;

    // get a useful tdc value
    if( tdcdata < m_nDigitsData && !m_tdcsum )   
      m_tdcsum = tdcdata;
  }
}


/**
   Fill the TDC histograms for each channel.
   Since it is a Phillips TDC, we have an additional histogram
   of the TDC sum we need to to override the function.

   These histograms are for monitoring, so if the value
   is 0 or m_nDigitsData we dont fill (so we only see useful info).

   One can then compare total number of events to number of entries 
   in the histogram to see how well the module is working.
*/
void Phillips2249W :: FillHistograms(){
  GenericModule::FillHistograms();
  
  // This is the "TDC SUM"
  if( m_tdcsum ) m_h_tdcsum->Fill( m_tdcsum );
}
