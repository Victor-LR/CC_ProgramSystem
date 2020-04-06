all: 
	g++ -Wall -std=c++14 -pthread -c cc_main.cpp
	g++ -Wall -pthread cc_main.o -o cc_main.exe

