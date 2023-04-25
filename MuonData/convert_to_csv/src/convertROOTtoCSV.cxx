#include "TreeToCSV.C"

int convertROOTtoCSV(char* fname, bool write_all=false) {
    TreeToCSV t(fname);
    if (! t.fChain) return 1;
    t.Loop(write_all);
    return 0;
}
