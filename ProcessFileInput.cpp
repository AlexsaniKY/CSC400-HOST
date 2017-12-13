#include "ProcessFileInput.h"

#include <iostream>


using namespace std;

		ProcessFileInput::ProcessFileInput(){}
		ProcessFileInput::~ProcessFileInput(){}

		bool ProcessFileInput::open(string filename){
			if (!(inputliststream = fopen(filename.c_str(), "r"))) { // open it
				cout << " could not open dispatch list file:" << filename;
				return false;
			}
			return true;
		}

		bool ProcessFileInput::eof(){
			return feof(inputliststream);
		}

		PcbPtr ProcessFileInput::next(){
			PcbPtr process = createnullPcb();
			if (fscanf(inputliststream,"%d, %d, %d, %d, %d, %d, %d, %d",
					&(process->arrivaltime), &(process->priority),
					&(process->remainingcputime), &(process->mbytes),
					&(process->req.printers), &(process->req.scanners),
					&(process->req.modems), &(process->req.cds)) != 8) {
				free(process);
				return NULL;
			}
			process->status = PCB_INITIALIZED;
			return process;
		}