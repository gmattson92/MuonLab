/**
 * @file MyMainFrame.cpp
 * Implementation for MyMainFrame class
 *
 * @brief 
 *
 * @author Yakov Kulinich 
 * @version 1.0
 */

#include "MyMainFrame.h"
#include "SharedData.h"
#include "MyDaq.h"

#include <stdio.h>

#include <TTree.h>
#include <TFile.h>
#include <TH1.h>
#include <TString.h>
#include <TSystem.h>
#include <TCanvas.h>
#include <TApplication.h>

#include <TGClient.h>
#include <TGButton.h>
#include <TGTextEntry.h>
#include <TRootEmbeddedCanvas.h>

#include <TTimer.h>

#include <iostream>

MyMainFrame::MyMainFrame(const TGWindow *p, UInt_t w, UInt_t h, MyDaq* daq) :  
  TGMainFrame(p, w, h), m_daq(daq) {

  // Create canvas widget
  m_fEcanvas = new TRootEmbeddedCanvas("Ecanvas", this, w/2, h);
  AddFrame(m_fEcanvas, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 
					 10,10,10,1));

  // timer handling.
  TCanvas *fCanvas = m_fEcanvas->GetCanvas();

  fCanvas->cd();
  m_daq->GetSharedData()->GetHists()["h_STDC_8_SUM"]->Draw();

  // Create a horizontal frame widget with buttons 
  m_hframe = new TGHorizontalFrame(this,200,40);
 
  m_startB = new TGTextButton( m_hframe,"&Start");
  m_startB->Connect("Clicked()","MyMainFrame",this,"DoStart()");
  m_hframe->AddFrame(m_startB, new TGLayoutHints( kLHintsLeft, 5, 5, 3, 4 ) );

  m_stopB = new TGTextButton( m_hframe,"&Stop");
  m_stopB->Connect("Clicked()","MyMainFrame",this,"DoStop()");
  m_hframe->AddFrame(m_stopB, new TGLayoutHints( kLHintsRight, 5, 5, 3, 4 ) );

  m_fTextEntry = new TGTextEntry( m_hframe, new TGTextBuffer(40));
  m_hframe->AddFrame(m_fTextEntry, new TGLayoutHints( kLHintsLeft, 5, 5, 3, 4 ) );

  AddFrame(m_hframe, new TGLayoutHints( kLHintsCenterX, 2, 2, 2, 2 ) );

  // Set a name to the main frame
  SetWindowName("MUON DAQ");

  // Map all subwindows of main frame
  MapSubwindows();

  // Initialize the layout algorithm
  Resize(GetDefaultSize());

  // Map main frame
  MapWindow();

  // create a timer firing every 100 ms
  fTimer = new TTimer(this, 500);
}

MyMainFrame::~MyMainFrame() {
  // Clean up used widgets: frames, buttons, layout hints
  Cleanup();
}

/**
   Just tells the canvas to refresh 
   whenever the timer fires
 */

Bool_t MyMainFrame::HandleTimer(TTimer *)
{
   // timer handling.
   TCanvas *fCanvas = m_fEcanvas->GetCanvas();

   fCanvas->cd();
   fCanvas->Update();
   fCanvas->Modified();
   fCanvas->Update();

   fTimer->Reset();

  return kTRUE;
}

void MyMainFrame::DoStart() {
  TString nm =  m_fTextEntry->GetBuffer()->GetString();

  if( nm == "" ) 
    m_daq->m_fout_name = (TString)"output.root";
  else 
    m_daq->m_fout_name = (TString)Form("%s.root", nm.Data() );

  fTimer->Reset();
  fTimer->TurnOn();
  
  m_daq->m_start_flag = true;

}

void MyMainFrame::DoStop() {
  m_daq->m_stop_flag = true;

  fTimer->TurnOff();

  gApplication->Terminate(0);
}
