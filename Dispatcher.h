#pragma once

#include "pcb.h"


class Dispatcher
{
private:
	enum queue{RT, US1, US2, US3};

	PcbPtr input_queue = NULL;
	PcbPtr new_queue = NULL;
	PcbPtr job_queues[4] = {NULL, NULL, NULL, NULL};

	Memory memory = Memory(2048);
	Rsrc available_resources = {4,4,4,4};
	unsigned long systime;
	void printQueue(PcbPtr Queue);
	PcbPtr pop_next(PcbPtr pcb);
	bool isRsrcAvailable(Rsrc reqRes);
	void allocateRsrc(Rsrc res);
	void deallocateRsrc(Rsrc res);
public:
	Dispatcher();
	~Dispatcher();
	unsigned int getTime();
	void addToInitQueue(PcbPtr process);
	void queueJobs();
	void initializeProcesses();
	void printAllQueues();
	bool hasJobs();
	void run();
};

