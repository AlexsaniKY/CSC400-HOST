#include "Dispatcher.h"
#include "pcb.h"
#include <iostream>

using namespace std;

Dispatcher dis;

int main(int argc, char *argv[]) {
	char * inputfile;             // job dispatch file
	FILE * inputliststream;

	if (argc == 2) inputfile = argv[1];
	else cout << argv[0];

	if (!(inputliststream = fopen(inputfile, "r"))) { // open it
		cout << "could not open dispatch list file:" << inputfile;
		exit(2);
	}

	while (!feof(inputliststream)) {  // put processes into input_queue
		PcbPtr process = createnullPcb();
		if (fscanf(inputliststream,"%d, %d, %d, %d, %d, %d, %d, %d",
				&(process->arrivaltime), &(process->priority),
				&(process->remainingcputime), &(process->mbytes),
				&(process->req.printers), &(process->req.scanners),
				&(process->req.modems), &(process->req.cds)) != 8) {
			free(process);
		continue;
		}
		process->status = PCB_INITIALIZED;

		dis.addToInitQueue(process);
	}


}