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

}
