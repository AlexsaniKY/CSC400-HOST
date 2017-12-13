#include "ProcessFileInput.h"

#include <iostream>
#include <exception>


using namespace std;

		bool ProcessFileInput::open(string filename){
			if (!(inputliststream = fopen(filename.c_str(), "r"))) { // open it
				cout << " could not open dispatch list file:" << filename;
				return false;
			}
			return true;
		}

		bool ProcessFileInput::hasNext(){
			return !feof(inputliststream);
		}

		PcbPtr ProcessFileInput::next(){
			PcbPtr process = createnullPcb();
			if (fscanf(inputliststream,"%d, %d, %d, %d, %d, %d, %d, %d",
					&(process->arrivaltime), &(process->priority),
					&(process->remainingcputime), &(process->mbytes),
					&(process->req.printers), &(process->req.scanners),
					&(process->req.modems), &(process->req.cds)) != 8) {
				free(process);
				throw ios_base::failure("could not retrieve next process");
			}
		process->status = PCB_INITIALIZED;
		return process;
		}