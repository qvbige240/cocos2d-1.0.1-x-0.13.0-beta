CC      = i686-linux-gcc
CXX     = i686-linux-g++
TARGET	= HelloWorld
CCFLAGS = -Wall -g -O2 
CXXFLAGS = -Wall -g -O2 
VISIBILITY = 

INCLUDES = -I../../cocos2dx/platform/third_party/linux \
            -I../../cocos2dx/include \
            -I../../cocos2dx \
            -I../../cocos2dx/platform \
            -I../../CocosDenshion/include \
            -I../Classes/ \
            -I/opt/timesys/linux/6.2/i686-std/rfs/usr/include \
            -I../../lib/__install_sdl/include

DEFINES = -DLINUX

OBJECTS = ./main.o \
        ../Classes/AppDelegate.o \
        ../Classes/HelloWorldScene.o 

STATICLIBS =  
#SHAREDLIBS = -L../../lib/linux/Debug -lcocos2d -lrt -lz -lcocosdenshion -Wl,-rpath,../../lib/linux/Debug/
SHAREDLIBS = -L../../lib/linux/Debug \
		-L../../lib/__install_sdl/lib \
		-L../../lib/xserver \
		-lcocos2d -lSDL -lGL -lXext -lXxf86vm -ldrm -lXau -lXdmcp -lX11 -lcocosdenshion -lrt -lz \
		-Wl,-rpath,../../lib/linux/Debug \
		-Wl,-rpath,../../lib/xserver

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
