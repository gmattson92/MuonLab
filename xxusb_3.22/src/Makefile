# basic makefile

.LIBPATTERNS ="'lib%.so lib%.a' "

CXX             = g++
RM		= rm -f

LDLIBS		= -lusb
INCLUDEDIRS 	= -I./../include/

CXXFLAGS      	= -Wall -fPIC

LDFLAGS		= -shared

SOURCES =  libxxusb.c
OBJECTS =  $(SOURCES:.c=.o)
LIB     =  libxx_usb.so

library: 
	$(CXX) $(CXXFLAGS) $(INCLUDEDIRS) -c $(SOURCES)
	$(LD)  $(LDFLAGS) $(LDLIBS) $(INCLUDEDIRS) $(OBJECTS) -o $(LIB)  
	@chmod 755 $(LIB)
	cp $(LIB) ./../lib
	@echo "Done"

clean:
	$(RM) $(OBJECTS) $(LIB)

