hostd: main.cpp Dispatcher.cpp Dispatcher.h pcb.c pcb.h Memory.cpp Memory.h ProcessFileInput.cpp ProcessFileInput.h sigtrap.c
	g++ -std=c++11 -Wall -o hostd main.cpp Dispatcher.cpp pcb.c Memory.cpp Memory.h ProcessFileInput.cpp
	g++ -w -o process sigtrap.c