#pragma once
class Dispatcher
{
	PcbPtr input_queue;
public:
	Dispatcher();
	~Dispatcher();
	void addToInitQueue(PcbPtr);
};

