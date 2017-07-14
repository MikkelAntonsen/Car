CC=g++


CPPFLAGS += -I$(CPPUTEST_HOME)/include
CXXFLAGS += -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorNewMacros.h
CFLAGS += -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorMallocMacros.h
LD_LIBRARIES = -L$(CPPUTEST_HOME)/lib -lCppUTest -lCppUTestExt

CFLAGS += $(INCLUDES) -O -Wall -Wno-c++14-compat

all: src/main.cpp src/serial-lib.cpp tests/AllTests.cpp
	$(CC) -c src/serial-lib.cpp
	ar rvs serial-lib.a serial-lib.o
	$(CC) -o raspberry_main src/main.cpp serial-lib.a
	$(CC) -o AllTests tests/AllTests.cpp $(CPPFLAGS) $(CXXFLAGS) $(CFLAGS) $(LD_LIBRARIES)

clean:
	rm *.o *.a AllTests
