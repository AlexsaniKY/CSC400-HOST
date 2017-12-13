#include "Dispatcher.h"
#include <cstdio>

using namespace std;

Dispatcher::Dispatcher()
{
}


Dispatcher::~Dispatcher()
{
}

void Dispatcher::addToInitQueue(PcbPtr process){
	printPcb(process, stdout);
	input_queue = enqPcb(input_queue, process);

}
