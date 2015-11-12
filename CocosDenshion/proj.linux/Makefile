CC      = i686-linux-gcc
CXX     = i686-linux-g++
TARGET	= libcocosdenshion.so
CCFLAGS = -Wall -g -O2 -fPIC
CXXFLAGS = -Wall -g -O2 -fPIC
VISIBILITY = 

LBITS := $(shell getconf LONG_BIT)
ifeq ($(LBITS),64)
INCLUDES = -I.. \
		-I../include \
		-I../third_party/linux/fmod/lib64/api/inc 
else
INCLUDES = -I.. \
		-I../include \
		-I../../lib/__install_sdl/include \
		-I../third_party/linux/fmod/api/inc 
endif


DEFINES = -DLINUX

OBJECTS =   ../linux/SDLAudioPlayer.o \
            ../linux/SimpleAudioEngine.o \

STATICLIBS = 

ifeq ($(LBITS),64)
SHAREDLIBS_DIR = ../third_party/linux/fmod/lib64/api/lib
SHAREDLIBS = -L$(SHAREDLIBS_DIR) -lfmodex64
else
SHAREDLIBS_DIR = ../third_party/linux/fmod/api/lib
SHAREDLIBS = -L$(SHAREDLIBS_DIR)
endif


####### Build rules
$(TARGET): $(OBJECTS) 
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(OBJECTS) -shared -o $(TARGET) $(SHAREDLIBS) $(STATICLIBS)
	
####### Compile
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@

%.o: %.c
	$(CC) $(CCFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@
		
clean: 
	rm -f $(OBJECTS) $(TARGET) core
