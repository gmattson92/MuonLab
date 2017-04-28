#ifndef COMMON_H
#define COMMON_H

#include <vector>
#include <map>
#include <string>

#define CONTINUATION_BIT  (0x8000)  // 15th bit = 32768
#define LONG_MODE_BIT     (0x4000)  // 14th bit = 16384
#define ADDRESS_SCAN_BIT  (0x0020)  // 5th  bit = 32
#define Q_STOP_BIT        (0x0010)  // 4th  bit = 16

#define STACK_END_MARKER  (0xFFFF)
#define MODULE_END_MARKER (0xDDDD)

#define MAX_STACK_SIZE    (256)

class TTree;
class TFile;
class TH1;
class TF1; 
class TApplication;

class MyDaq;
class SharedData;
class Module;
class Phillips_2249W;
class MyDaq;
class MyMainFrame;

#endif
