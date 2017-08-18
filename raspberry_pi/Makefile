CC=g++


CPPFLAGS += -I$(CPPUTEST_HOME)/include
CXXFLAGS += -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorNewMacros.h
CFLAGS += -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorMallocMacros.h
LD_LIBRARIES = -L$(CPPUTEST_HOME)/lib -lCppUTest -lCppUTestExt

CFLAGS += $(INCLUDES) -O -std=c++11 -Wall -Wno-c++14-compat

all: src/main.cpp src/serial-lib.cpp tests/AllTests.cpp src/ArduinoInterface.cpp
	$(CC) -o bin/raspberry_main src/main.cpp src/ArduinoInterface.cpp src/serial-lib.cpp $(CFLAGS)
	$(CC) -o bin/AllTests tests/AllTests.cpp src/ArduinoInterface.cpp tests/ArduinoInterfaceTest.cpp $(CPPFLAGS) $(CXXFLAGS) $(CFLAGS) $(LD_LIBRARIES)

clean:
	rm *.o bin/AllTests bin/raspberry_main
