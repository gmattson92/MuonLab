#ifndef PHILLIPS2249W_H
#define PHILLIPS2249W_H

#include "Common.h"
#include "GenericModule.h"

/**
   @brief  Phillips2249W (TDC) class. Inherits from Module.
   Mostly the same except for reading data. It has
   a default read command which.
*/
class Phillips2249W : public GenericModule{

 public:
  /**
     @brief Overloaded constructor for Phillips2249W.
     
     @param param1 Module name
     @param param2 Number of channels in this module    
     @param param3 Slot number of this module in CAMAC
  */
  Phillips2249W( std::string, int, int ); 

  /**
     @brief Default destructor for Phillips2249W
   */
  virtual ~Phillips2249W();

  /**
     @brief Function adds output for a Phillips2249W
  */
  virtual void AddOutput ();

  /**
     @brief Function reads data from a Phillips2249W
     
     @param param1 Address where module's data beings
  */
  virtual void ReadData( short* p );

  /**
     @brief Function to fill histograms for a Phillips2249W
  */
  virtual void FillHistograms();

 private:
  short m_tdcsum;

  TH1*  m_h_tdcsum;
};

#endif
