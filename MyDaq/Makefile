# basic makefile
HERE=$(shell pwd)

CXX             = g++
RM		= rm -rf

INCLUDEDIRS 	= -I$(XXUSBDIR)/include -I./include
LIBDIRS	        = -L$(XXUSBDIR)/lib
LIBS		= -lxx_usb -lm -lusb

CXXFLAGS      	= -g -O2 -Wall `root-config --cflags` 

LDFLAGS         = -O2 `root-config --glibs` -Wl,-rpath=$(XXUSBDIR)/lib

SOURCES         = MyDaq.cpp   MyMainFrame.cpp  GenericModule.cpp  Phillips2249W.cpp  SharedData.cpp  CC-DAQ.cpp
INCLUDES        = MyDaq.h     MyMainFrame.h    GenericModule.h    Phillips2249W.h    SharedData.h    Module.h   Common.h  LinkDef.h  
OBJ             = runMyDaq

SOURCEDIR       = src/
INCLUDEDIR      = include/

CSOURCES        = $(addprefix $(SOURCEDIR),$(SOURCES))
CINCLUDES       = $(addprefix $(INCLUDEDIR),$(INCLUDES))

RUNDIR          = run/

all: $(CSOURCES) $(CINCLUDES) $(SOURCEDIR)MyMainFrameDict.cpp 
	$(CXX) $(CXXFLAGS) $(INCLUDEDIRS) $(CSOURCES) $(SOURCEDIR)MyMainFrameDict.cpp \
	$(LIBDIRS) $(LIBS) $(LDFLAGS) -o $(OBJ) 
	[ -d $(RUNDIR) ] || mkdir $(RUNDIR) 
	mv $(OBJ)  $(RUNDIR)
	[ -f $(RUNDIR)env.sh ] || echo "export XXUSBDIR="$(XXUSBDIR) >> $(RUNDIR)env.sh
	@echo "Done"

$(SOURCEDIR)MyMainFrameDict.cpp: $(SOURCEDIR)MyMainFrame.cpp $(INCLUDEDIR)MyMainFrame.h
	rootcling -f $(SOURCEDIR)MyMainFrameDict.cpp -c $(INCLUDEDIRS) MyMainFrame.h $(INCLUDEDIR)LinkDef.h
	[ -d $(RUNDIR) ] || mkdir $(RUNDIR) 	
	cp $(SOURCEDIR)MyMainFrameDict* $(RUNDIR)

clean:
	$(RM) $(RUNDIR)MyMainFrameDict* $(RUNDIR)$(OBJ)  $(SOURCEDIR)MyMainFrameDict*
