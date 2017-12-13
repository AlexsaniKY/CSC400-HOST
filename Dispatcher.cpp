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

void Dispatcher::queueJobs(){
}

void Dispatcher::initializeProcesses(){}

bool Dispatcher::hasJobs(){return false;}

void Dispatcher::run(){
	PcbPtr p;
	while(p = input_queue->next()) printPcb(p, stdout);

}