/**
 * @file SharedData.cpp
 * Implementation for SharedData class
 *
 * @brief 
 *
 * @author Yakov Kulinich 
 * @version 1.0
 */

#include "SharedData.h"

#include <stdio.h>

#include <TTree.h>
#include <TFile.h>
#include <TH1.h>
#include <TSystem.h>
#include <TCanvas.h>

#include <iostream>


//--------------------------------
//          SharedData
//--------------------------------

SharedData :: SharedData() {
  m_fout = NULL;
  m_tree = new TTree("tree","Muon Tree");
  m_tree->SetAutoSave(1000000); 
}

SharedData :: ~SharedData() {
  delete m_tree;
  delete m_fout;
}

void SharedData :: Finalize() {
  m_tree->Write();
  for( auto& psh1 : m_m_hists ) psh1.second->Write();

  m_fout->Close();
}
