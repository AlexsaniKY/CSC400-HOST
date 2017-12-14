#include "Dispatcher.h"
#include "ProcessFileInput.h"
#include "pcb.h"
#include <iostream>
#include <string>

using namespace std;

Dispatcher dis;
ProcessFileInput input;

int main(int argc, char *argv[]) {

	string fname;
	//attempt to open input file
	if (argc == 2) fname = argv[1];
	else{
		cout << "no file specified" << endl;
		exit(2);
	}
	
	if(!input.open(fname)) {
		cout << "error opening file" << endl;
		exit(2);
	}

	//initialize processes in file
	while (!input.eof()){
		//add to dispatcher input queue
		PcbPtr process = input.next();
		if(process) dis.addToInitQueue(process);
	}
	
	while(dis.hasJobs()){
		dis.queueJobs();
		dis.initializeProcesses();
		dis.run();
	}

}