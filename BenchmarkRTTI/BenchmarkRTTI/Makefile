# Project: BenchmarkRTTI

#CPP      = clang++-3.6 -stdlib=libstdc++ -lstdc++ -std=c++11
CPP      = g++ -lstdc++ -std=c++11 
CC       = gcc
OBJ      = BenchmarkRTTI.o timer.o Shapes.o $(RES)
LINKOBJ  = BenchmarkRTTI.o timer.o Shapes.o $(RES)
LIBS     = 
CXXINCS  = 
BIN      = BenchmarkRTTI.exe
CXXFLAGS = -Wall -O1 -DCPP11 $(CXXINCS)
CFLAGS   = -Wall -O1  
RM       = rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before BenchmarkRTTI.exe all-after


clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o "BenchmarkRTTI.exe" $(LIBS)

timer.o: timer.cpp
	$(CPP) -c timer.cpp -o timer.o $(CXXFLAGS)

Shapes.o: Shapes.cpp
	$(CPP) -c Shapes.cpp -o Shapes.o $(CXXFLAGS)

BenchmarkRTTI.o: BenchmarkRTTI.cpp
	$(CPP) -c BenchmarkRTTI.cpp -o BenchmarkRTTI.o $(CXXFLAGS)
