hostd: main.cpp Dispatcher.cpp Dispatcher.h pcb.c pcb.h Process.cpp Process.h ProcessFileInput.cpp ProcessFileInput.h
	g++ -Wall -o hostd main.cpp Dispatcher.cpp pcb.c Process.cpp ProcessFileInput.cpp