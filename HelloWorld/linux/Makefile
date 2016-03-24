CC      = gcc
CXX     = g++
TARGET	= HelloWorld
CCFLAGS = -Wall -g -O2 
CXXFLAGS = -Wall -g -O2 
VISIBILITY = 

WORK_PATH = ../../..
COCOS_PATH = $(WORK_PATH)/cocos2d-1.0.1-x-0.13.0-beta
INSTALL_PATH = $(WORK_PATH)/../pc/final

INCLUDES = -I$(COCOS_PATH)/cocos2dx/platform/third_party/linux \
            -I$(COCOS_PATH)/cocos2dx/include \
            -I$(COCOS_PATH)/cocos2dx \
            -I$(COCOS_PATH)/cocos2dx/platform \
            -I$(COCOS_PATH)/CocosDenshion/include \
            -I$(INSTALL_PATH)/include \
            -I../Classes/

DEFINES = -DLINUX

OBJECTS = ./main.o \
        ../Classes/AppDelegate.o \
        ../Classes/HelloWorldScene.o 

STATICLIBS =  
SHAREDLIBS = -L$(COCOS_PATH)/lib/linux/Debug -L$(INSTALL_PATH)/lib/ -lcocos2d -lglfw -lGL -lrt -lz -lcocosdenshion -Wl,-rpath,$(COCOS_PATH)/lib/linux/Debug/,-rpath,$(INSTALL_PATH)/lib/

#$(shell ../../build-linux.sh $<)
####### Build rules
$(TARGET): $(OBJECTS) 
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(OBJECTS) -o $(TARGET) $(SHAREDLIBS) $(STATICLIBS)
	
####### Compile
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@

%.o: %.c
	$(CC) $(CCFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@
		
clean: 
	rm -f $(OBJECTS) $(TARGET) core
