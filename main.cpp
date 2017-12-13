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
		cout << "no file specified";
		exit(2);
	}
	
	if(!input.open(fname)) {
		cout << "error opening file";
		exit(2);
	}

	//initialize processes in file
	while (input.hasNext()){
		//add to dispatcher input queue
		dis.addToInitQueue(input.next());
	}

	dis.queueJobs();
	
	while(dis.hasJobs()){
		dis.initializeProcesses();
		dis.run();
	}

}