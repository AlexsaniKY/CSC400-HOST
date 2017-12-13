#include "Dispatcher.h"
#include <iostream.h>


Dispatcher::Dispatcher()
{
}


Dispatcher::~Dispatcher()
{
}

void Dispatcher::addToInitQueue(PcbPtr process){
	printPcb(process, cout);

}
