//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Mar 30 10:04:20 2023 by ROOT version 6.26/06
// from TTree tree/Muon Tree
// found on file: Feb_2_2023_weekend.root
//////////////////////////////////////////////////////////

#ifndef TreeToCSV_h
#define TreeToCSV_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TString.h>
#include <TSystem.h>

// Header file for the classes stored in the TTree if any.

class TreeToCSV {
    public :
	TTree          *fChain;   //!pointer to the analyzed TTree or TChain
	Int_t           fCurrent; //!current Tree number in a TChain
	TString		filename;

	// Fixed size dimensions of array or collections stored in the TTree if any.

	// Declaration of leaf types
	Short_t         ADC_1_0;
	Short_t         ADC_1_1;
	Short_t         ADC_1_2;
	Short_t         ADC_1_3;
	Short_t         ADC_1_4;
	Short_t         ADC_1_5;
	Short_t         ADC_1_6;
	Short_t         ADC_1_7;
	Short_t         ADC_1_8;
	Short_t         ADC_1_9;
	Short_t         ADC_1_10;
	Short_t         ADC_1_11;
	Short_t         ADC_2_0;
	Short_t         ADC_2_1;
	Short_t         ADC_2_2;
	Short_t         ADC_2_3;
	Short_t         ADC_2_4;
	Short_t         ADC_2_5;
	Short_t         ADC_2_6;
	Short_t         ADC_2_7;
	Short_t         ADC_2_8;
	Short_t         ADC_2_9;
	Short_t         ADC_2_10;
	Short_t         ADC_2_11;
	Short_t         STDC_8_0;
	Short_t         STDC_8_1;
	Short_t         STDC_8_2;
	Short_t         STDC_8_3;
	Short_t         STDC_8_4;
	Short_t         STDC_8_5;
	Short_t         STDC_8_6;
	Short_t         STDC_8_7;
	Short_t         STDC_8_8;
	Short_t         STDC_8_9;
	Short_t         STDC_8_10;
	Short_t         STDC_8_11;
	Short_t         STDC_8_12;
	Short_t         STDC_8_13;
	Short_t         STDC_8_14;
	Short_t         STDC_8_15;
	Short_t         STDC_8_SUM;
	Short_t         FTDC_9_0;
	Short_t         FTDC_9_1;
	Short_t         FTDC_9_2;
	Short_t         FTDC_9_3;
	Short_t         FTDC_9_4;
	Short_t         FTDC_9_5;
	Short_t         FTDC_9_6;
	Short_t         FTDC_9_7;

	// List of branches
	TBranch        *b_ADC_1_0;   //!
	TBranch        *b_ADC_1_1;   //!
	TBranch        *b_ADC_1_2;   //!
	TBranch        *b_ADC_1_3;   //!
	TBranch        *b_ADC_1_4;   //!
	TBranch        *b_ADC_1_5;   //!
	TBranch        *b_ADC_1_6;   //!
	TBranch        *b_ADC_1_7;   //!
	TBranch        *b_ADC_1_8;   //!
	TBranch        *b_ADC_1_9;   //!
	TBranch        *b_ADC_1_10;   //!
	TBranch        *b_ADC_1_11;   //!
	TBranch        *b_ADC_2_0;   //!
	TBranch        *b_ADC_2_1;   //!
	TBranch        *b_ADC_2_2;   //!
	TBranch        *b_ADC_2_3;   //!
	TBranch        *b_ADC_2_4;   //!
	TBranch        *b_ADC_2_5;   //!
	TBranch        *b_ADC_2_6;   //!
	TBranch        *b_ADC_2_7;   //!
	TBranch        *b_ADC_2_8;   //!
	TBranch        *b_ADC_2_9;   //!
	TBranch        *b_ADC_2_10;   //!
	TBranch        *b_ADC_2_11;   //!
	TBranch        *b_STDC_8_0;   //!
	TBranch        *b_STDC_8_1;   //!
	TBranch        *b_STDC_8_2;   //!
	TBranch        *b_STDC_8_3;   //!
	TBranch        *b_STDC_8_4;   //!
	TBranch        *b_STDC_8_5;   //!
	TBranch        *b_STDC_8_6;   //!
	TBranch        *b_STDC_8_7;   //!
	TBranch        *b_STDC_8_8;   //!
	TBranch        *b_STDC_8_9;   //!
	TBranch        *b_STDC_8_10;   //!
	TBranch        *b_STDC_8_11;   //!
	TBranch        *b_STDC_8_12;   //!
	TBranch        *b_STDC_8_13;   //!
	TBranch        *b_STDC_8_14;   //!
	TBranch        *b_STDC_8_15;   //!
	TBranch        *b_STDC_8_SUM;   //!
	TBranch        *b_FTDC_9_0;   //!
	TBranch        *b_FTDC_9_1;   //!
	TBranch        *b_FTDC_9_2;   //!
	TBranch        *b_FTDC_9_3;   //!
	TBranch        *b_FTDC_9_4;   //!
	TBranch        *b_FTDC_9_5;   //!
	TBranch        *b_FTDC_9_6;   //!
	TBranch        *b_FTDC_9_7;   //!

	TreeToCSV(TTree *tree=0);
	TreeToCSV(char *filename);
	virtual ~TreeToCSV();
	virtual Int_t    Cut(Long64_t entry);
	virtual Int_t    GetEntry(Long64_t entry);
	virtual Long64_t LoadTree(Long64_t entry);
	virtual void     Init(TTree *tree);
	virtual void     Loop(bool write_all=false);
	virtual Bool_t   Notify();
	virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef TreeToCSV_cxx
TreeToCSV::TreeToCSV(TTree *tree) : fChain(0) 
{
    // if parameter tree is not specified (or zero), connect the file
    // used to generate this class and read the Tree.
    if (tree == 0) {
	TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("weekend 3-30 use-tdc-15.root");
	if (!f || !f->IsOpen()) {
	    f = new TFile("weekend 3-30 use-tdc-15.root");
	}
	f->GetObject("tree",tree);

    }
    Init(tree);
}

TreeToCSV::TreeToCSV(char *fname) : fChain(0), filename(fname)
{
    // if argument is a filename, connect the file
    // and take the tree from it

    TFile* f = new TFile(filename.Data(), "READ");
    TTree* tree = nullptr;
    if (!f || !f->IsOpen()) {
	std::cout << "Could not open file " << filename.Data() << " ! Quitting ROOT!\n";
    }
    else {
	f->GetObject("tree",tree);
    }

    Init(tree);
}

TreeToCSV::~TreeToCSV()
{
    if (!fChain) return;
    delete fChain->GetCurrentFile();
}

Int_t TreeToCSV::GetEntry(Long64_t entry)
{
    // Read contents of entry.
    if (!fChain) return 0;
    return fChain->GetEntry(entry);
}
Long64_t TreeToCSV::LoadTree(Long64_t entry)
{
    // Set the environment to read one entry
    if (!fChain) return -5;
    Long64_t centry = fChain->LoadTree(entry);
    if (centry < 0) return centry;
    if (fChain->GetTreeNumber() != fCurrent) {
	fCurrent = fChain->GetTreeNumber();
	Notify();
    }
    return centry;
}

void TreeToCSV::Init(TTree *tree)
{
    // The Init() function is called when the selector needs to initialize
    // a new tree or chain. Typically here the branch addresses and branch
    // pointers of the tree will be set.
    // It is normally not necessary to make changes to the generated
    // code, but the routine can be extended by the user if needed.
    // Init() will be called many times when running on PROOF
    // (once per file to be processed).

    // Set branch addresses and branch pointers
    if (!tree) return;
    fChain = tree;
    fCurrent = -1;
    fChain->SetMakeClass(1);

    fChain->SetBranchAddress("ADC_1_0", &ADC_1_0, &b_ADC_1_0);
    fChain->SetBranchAddress("ADC_1_1", &ADC_1_1, &b_ADC_1_1);
    fChain->SetBranchAddress("ADC_1_2", &ADC_1_2, &b_ADC_1_2);
    fChain->SetBranchAddress("ADC_1_3", &ADC_1_3, &b_ADC_1_3);
    fChain->SetBranchAddress("ADC_1_4", &ADC_1_4, &b_ADC_1_4);
    fChain->SetBranchAddress("ADC_1_5", &ADC_1_5, &b_ADC_1_5);
    fChain->SetBranchAddress("ADC_1_6", &ADC_1_6, &b_ADC_1_6);
    fChain->SetBranchAddress("ADC_1_7", &ADC_1_7, &b_ADC_1_7);
    fChain->SetBranchAddress("ADC_1_8", &ADC_1_8, &b_ADC_1_8);
    fChain->SetBranchAddress("ADC_1_9", &ADC_1_9, &b_ADC_1_9);
    fChain->SetBranchAddress("ADC_1_10", &ADC_1_10, &b_ADC_1_10);
    fChain->SetBranchAddress("ADC_1_11", &ADC_1_11, &b_ADC_1_11);
    fChain->SetBranchAddress("ADC_2_0", &ADC_2_0, &b_ADC_2_0);
    fChain->SetBranchAddress("ADC_2_1", &ADC_2_1, &b_ADC_2_1);
    fChain->SetBranchAddress("ADC_2_2", &ADC_2_2, &b_ADC_2_2);
    fChain->SetBranchAddress("ADC_2_3", &ADC_2_3, &b_ADC_2_3);
    fChain->SetBranchAddress("ADC_2_4", &ADC_2_4, &b_ADC_2_4);
    fChain->SetBranchAddress("ADC_2_5", &ADC_2_5, &b_ADC_2_5);
    fChain->SetBranchAddress("ADC_2_6", &ADC_2_6, &b_ADC_2_6);
    fChain->SetBranchAddress("ADC_2_7", &ADC_2_7, &b_ADC_2_7);
    fChain->SetBranchAddress("ADC_2_8", &ADC_2_8, &b_ADC_2_8);
    fChain->SetBranchAddress("ADC_2_9", &ADC_2_9, &b_ADC_2_9);
    fChain->SetBranchAddress("ADC_2_10", &ADC_2_10, &b_ADC_2_10);
    fChain->SetBranchAddress("ADC_2_11", &ADC_2_11, &b_ADC_2_11);
    fChain->SetBranchAddress("STDC_8_0", &STDC_8_0, &b_STDC_8_0);
    fChain->SetBranchAddress("STDC_8_1", &STDC_8_1, &b_STDC_8_1);
    fChain->SetBranchAddress("STDC_8_2", &STDC_8_2, &b_STDC_8_2);
    fChain->SetBranchAddress("STDC_8_3", &STDC_8_3, &b_STDC_8_3);
    fChain->SetBranchAddress("STDC_8_4", &STDC_8_4, &b_STDC_8_4);
    fChain->SetBranchAddress("STDC_8_5", &STDC_8_5, &b_STDC_8_5);
    fChain->SetBranchAddress("STDC_8_6", &STDC_8_6, &b_STDC_8_6);
    fChain->SetBranchAddress("STDC_8_7", &STDC_8_7, &b_STDC_8_7);
    fChain->SetBranchAddress("STDC_8_8", &STDC_8_8, &b_STDC_8_8);
    fChain->SetBranchAddress("STDC_8_9", &STDC_8_9, &b_STDC_8_9);
    fChain->SetBranchAddress("STDC_8_10", &STDC_8_10, &b_STDC_8_10);
    fChain->SetBranchAddress("STDC_8_11", &STDC_8_11, &b_STDC_8_11);
    fChain->SetBranchAddress("STDC_8_12", &STDC_8_12, &b_STDC_8_12);
    fChain->SetBranchAddress("STDC_8_13", &STDC_8_13, &b_STDC_8_13);
    fChain->SetBranchAddress("STDC_8_14", &STDC_8_14, &b_STDC_8_14);
    fChain->SetBranchAddress("STDC_8_15", &STDC_8_15, &b_STDC_8_15);
    fChain->SetBranchAddress("STDC_8_SUM", &STDC_8_SUM, &b_STDC_8_SUM);
    fChain->SetBranchAddress("FTDC_9_0", &FTDC_9_0, &b_FTDC_9_0);
    fChain->SetBranchAddress("FTDC_9_1", &FTDC_9_1, &b_FTDC_9_1);
    fChain->SetBranchAddress("FTDC_9_2", &FTDC_9_2, &b_FTDC_9_2);
    fChain->SetBranchAddress("FTDC_9_3", &FTDC_9_3, &b_FTDC_9_3);
    fChain->SetBranchAddress("FTDC_9_4", &FTDC_9_4, &b_FTDC_9_4);
    fChain->SetBranchAddress("FTDC_9_5", &FTDC_9_5, &b_FTDC_9_5);
    fChain->SetBranchAddress("FTDC_9_6", &FTDC_9_6, &b_FTDC_9_6);
    fChain->SetBranchAddress("FTDC_9_7", &FTDC_9_7, &b_FTDC_9_7);
    Notify();
}

Bool_t TreeToCSV::Notify()
{
    // The Notify() function is called when a new file is opened. This
    // can be either for a new TTree in a TChain or when when a new TTree
    // is started when using PROOF. It is normally not necessary to make changes
    // to the generated code, but the routine can be extended by the
    // user if needed. The return value is currently not used.

    return kTRUE;
}

void TreeToCSV::Show(Long64_t entry)
{
    // Print contents of entry.
    // If entry is not specified, print current entry
    if (!fChain) return;
    fChain->Show(entry);
}
Int_t TreeToCSV::Cut(Long64_t entry)
{
    // This function may be called from Loop.
    // returns  1 if entry is accepted.
    // returns -1 otherwise.
    return 1;
}
#endif // #ifdef TreeToCSV_cxx
