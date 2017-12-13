#include "Dispatcher.h"
#include <iostream>


Dispatcher::Dispatcher()
{
}


Dispatcher::~Dispatcher()
{
}

void Dispatcher::addToInitQueue(PcbPtr process){
	printPcb(process, cout);

}
