#pragma once

#include "pcb.h"


class Dispatcher
{
private:
	enum queue{RT, US1, US2, US3};
	
	PcbPtr input_queue = NULL;
	PcbPtr new_queue = NULL;
	PcbPtr[4] job_queues = {NULL, NULL, NULL, NULL};

	Rsrc available_resources = {4,4,4,4};
	unsigned long systime;
	void printQueue(PcbPtr Queue);
public:
	Dispatcher();
	~Dispatcher();
	void addToInitQueue(PcbPtr process);
	void queueJobs();
	void initializeProcesses();
	void printAllQueues();
	bool hasJobs();
	void run();
};

