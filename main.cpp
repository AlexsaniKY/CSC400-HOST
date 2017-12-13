#include "Dispatcher.h"
#include "pcb.h"

using namespace std;

Dispatcher dis;

int main() {

	if (!(inputliststream = fopen(inputfile, "r"))) { // open it
          SysErrMsg("could not open dispatch list file:", inputfile);
          exit(2);
    }

    while (!feof(inputliststream)) {  // put processes into input_queue
        process = createnullPcb();
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