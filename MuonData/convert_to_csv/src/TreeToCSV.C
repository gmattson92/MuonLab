#define TreeToCSV_cxx
#include "TreeToCSV.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TString.h>
#include <iostream>
#include <fstream>

void TreeToCSV::Loop(bool write_all=false)
{
    //   In a ROOT session, you can do:
    //      root> .L TreeToCSV.C
    //      root> TreeToCSV t
    //      root> t.GetEntry(12); // Fill t data members with entry number 12
    //      root> t.Show();       // Show values of entry 12
    //      root> t.Show(16);     // Read and show values of entry 16
    //      root> t.Loop();       // Loop on all entries

    std::ofstream outfile;
    // Get output file name automatically from input file name
    /* TFile* infile = fChain->GetCurrentFile(); */
    /* TString fname = (TString)infile->GetName(); */
    /* fname.ReplaceAll("root", "cvs"); */
    /* outfile.open(fname.Data()); */
    filename = TString(gSystem->BaseName(filename.Data()));
    TString outfilename = filename.ReplaceAll(".root", ".csv");
    outfile.open(outfilename.Data());

    // Choose whether to write the ADC and FTDC values
    /* bool write_all = false; */
    if (write_all) {
	outfile << "ADC_1_0,ADC_1_1,ADC_1_2,ADC_1_3,ADC_1_4,ADC_1_5,ADC_1_6,ADC_1_7,ADC_1_8,ADC_1_9,ADC_1_10,ADC_1_11,";
	outfile << "ADC_2_0,ADC_2_1,ADC_2_2,ADC_2_3,ADC_2_4,ADC_2_5,ADC_2_6,ADC_2_7,ADC_2_8,ADC_2_9,ADC_2_10,ADC_2_11,";
	outfile << "FTDC_9_0,FTDC_9_1,FTDC_9_2,FTDC_9_3,FTDC_9_4,FTDC_9_5,FTDC_9_6,FTDC_9_7,";
    }
    outfile << "STDC_8_0,STDC_8_1,STDC_8_2,STDC_8_3,STDC_8_4,STDC_8_5,STDC_8_6,STDC_8_7,";
    outfile << "STDC_8_8,STDC_8_9,STDC_8_10,STDC_8_11,STDC_8_12,STDC_8_13,STDC_8_14,STDC_8_15,STDC_8_SUM\n";

    if (fChain == 0) return;

    Long64_t nentries = fChain->GetEntriesFast();

    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++) { // Begin loop over events
	Long64_t ientry = LoadTree(jentry);
	if (ientry < 0) break;
	nb = fChain->GetEntry(jentry);   nbytes += nb;
	if (jentry % 10000 == 0) std::cout << "Event " << jentry << "\n";

	
	if (write_all) {
	    outfile << Form("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,", 
		    ADC_1_0, ADC_1_1, ADC_1_2, ADC_1_3, ADC_1_4, ADC_1_5, ADC_1_6, ADC_1_7, ADC_1_8, ADC_1_9, ADC_1_10, ADC_1_11);
	    outfile << Form("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,", 
		    ADC_2_0, ADC_2_1, ADC_2_2, ADC_2_3, ADC_2_4, ADC_2_5, ADC_2_6, ADC_2_7, ADC_2_8, ADC_2_9, ADC_2_10, ADC_2_11);
	    outfile << Form("%d,%d,%d,%d,%d,%d,%d,%d,", 
		    FTDC_9_0, FTDC_9_1, FTDC_9_2, FTDC_9_3, FTDC_9_4, FTDC_9_5, FTDC_9_6, FTDC_9_7);
	}
	outfile << Form("%d,%d,%d,%d,%d,%d,%d,%d,", 
		STDC_8_0, STDC_8_1, STDC_8_2, STDC_8_3, STDC_8_4, STDC_8_5, STDC_8_6, STDC_8_7);
	outfile << Form("%d,%d,%d,%d,%d,%d,%d,%d,%d\n", 
		STDC_8_8, STDC_8_9, STDC_8_10, STDC_8_11, STDC_8_12, STDC_8_13, STDC_8_14, STDC_8_15, STDC_8_SUM);

    } // End loop over events
    outfile.close();
}
