#ifndef SHAREDDATA_H
#define SHAREDDATA_H

#include "Common.h"

/**
   @brief This class is made so that all modules can
   connect to a common database that can only be created
   from MyDaq. 
   This way, all modules can add to the tree,
   and add their histograms to a common collection.
   At the end, this tree and histograms will be written to file.
 */
class SharedData{
  
  friend class MyDaq;

 private:
  /**
     @brief Default destructor for SharedData
  */
  SharedData();
  /**
     @brief Default destructor for SharedData
  */
  ~SharedData();

  /**
     @brief Function to finalize and write all data to file.
  */
  void Finalize();
 
  TFile* m_fout;
  TTree* m_tree;
 
  std::map< std::string, TH1* > m_m_hists;

 public: 
  /**
     @brief Getter for output file
  */
  TFile* GetFout(){ return m_fout; }
  /**
     @brief Getter for ttree
  */
  TTree* GetTree(){ return m_tree; }
  
  /**
     @brief Getter for map of string to histos
  */
  std::map< std::string, TH1* >& GetHists()
    { return m_m_hists; } 

  /**
     @brief Setter for output file
  */
  void   SetFout( TFile* f ){ m_fout = f; }

};

#endif 
