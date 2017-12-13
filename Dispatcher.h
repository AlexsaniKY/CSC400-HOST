#pragma once

#include "pcb.h"


class Dispatcher
{
	PcbPtr input_queue;
public:
	Dispatcher();
	~Dispatcher();
	void addToInitQueue(PcbPtr process);
};

