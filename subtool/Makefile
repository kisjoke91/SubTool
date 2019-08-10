COMPILER=g++

all: subtool

subtool: main.o ChaosCommonLibrary.o subtool.o
	$(COMPILER) main.o ChaosCommonLibrary.o subtool.o -o subtool

main.o: main.cpp
	$(COMPILER) -c main.cpp

ChaosCommonLibrary.o: ChaosCommonLibrary.cpp
	$(COMPILER) -c ChaosCommonLibrary.cpp

subtool.o: subtool.cpp
	$(COMPILER) -c subtool.cpp

clean:
	rm -r main.o ChaosCommonLibrary.o subtool.o subtool
