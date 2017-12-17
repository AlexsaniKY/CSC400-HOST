#include "Dispatcher.h"
#include <cstdio>
#include <iostream>

using namespace std;

Dispatcher::Dispatcher()
{
	systime = 0;
}


Dispatcher::~Dispatcher()
{
}

unsigned int Dispatcher::getTime(){return systime;}

PcbPtr Dispatcher::pop_next(PcbPtr pcb){
	PcbPtr next = pcb->next;
	//if this was the last item in the list, return null
	if(!next) return NULL;
	//next exists, check for the one afterwards
	PcbPtr next_next = next->next;
	//if the next pointer is the last in the list, popping is trivial
	if(!next_next){
		pcb->next = NULL;
		return next;
	}
	//we have all three list items, reroute the first to the third
	pcb->next = next_next;
	//unlink the middle pcb
	next->next = NULL;
	//and return it
	return next;
}

//add process to init queue.  Jobs that are queued but not arrived will be in this queue.
//Jobs are required to arrive in arrival order to have defined behavior.
void Dispatcher::addToInitQueue(PcbPtr process){
	printPcb(process, stdout);
	input_queue = enqPcb(input_queue, process);
}

//Queues up all jobs from the New Process Queue into the appropriate RT/User feedback Queues
//provided the resources required by the process is available.
void Dispatcher::queueJobs(){
	PcbPtr p = new_queue;
	PcbPtr previous = NULL;
	PcbPtr next = NULL;
	MemoryBlock* m;

	//for each process in new_queue
	while(p){
		switch(p->priority){
			//if real-time
			case RT_PRIORITY:
				cout << "retrieving memory" << endl;
				m = memory.get_block(p->mbytes);
				cout << m << endl;
				//if a block was available
				if(m){
					cout << "memory selected" << endl;
					//give it to p
					p->mblock = m;
					cout << "m assigned to p" << endl;
					//remove p from the list
					next = p->next;
					if(previous) pop_next(previous);
					cout << "p removed from new_queue" << endl;
					//add it to the RT ready queue
					if(!job_queues[RT]) job_queues[RT] = p;
					else job_queues[RT] = enqPcb(job_queues[RT], p);
					cout << "p moved to job queue" << endl;
					//set up the next link
					//if(previous) p = previous->next;
					p = next;
					//clean up
					m = NULL;
					sleep(.1);
					continue;
				}
				break;
			
		}

		previous = p;
		p = p->next;
	}
}

//Initializes Processes into the New Process Queue if they have "arrived"
void Dispatcher::initializeProcesses(){
	PcbPtr p;
	//while input queue not empty and process not scheduled for future
	while(input_queue && input_queue->arrivaltime <= systime){
		//remove from input queue
		p = deqPcb(&input_queue);
		//add to new process queue
		new_queue = enqPcb(new_queue, p);
	}
}

//Whether the Dispatcher still has jobs, whether initialized or not
bool Dispatcher::hasJobs(){
	return (
		input_queue
		|| new_queue
		|| job_queues[RT]
		|| job_queues[US1]
		|| job_queues[US2]
		|| job_queues[US3]
	);
}

//test method to print the queue of processes not yet prepared into the ready state
void Dispatcher::printQueue(PcbPtr Queue){
	PcbPtr p = Queue;
	while(p) {
		printPcb(p, stdout);
		p = p->next;
		}
}

void Dispatcher::printAllQueues(){
	cout << "Process not initialized:" << endl;
	printQueue(input_queue);
	cout << "New Processes not Ready:" << endl;
	printQueue(new_queue);
	cout << "Real Time Processes:" << endl;
	printQueue(job_queues[RT]);
	cout << "User Processes Priority 1:" << endl;
	printQueue(job_queues[US1]);
	cout << "User Processes Priority 2:" << endl;
	printQueue(job_queues[US2]);
	cout << "User Processes Priority 3:" << endl;
	printQueue(job_queues[US3]);
	cout << endl;
}

//Run the Dispatcher. Available processes will be scheduled, ran,
//and afterwards if necessary, preempted and requeued.
//
//Notable exceptions: Real Time Processes will run to completion.
//User Processes will not preempt until other processes exist in the job queue.
void Dispatcher::run(){
	sleep(1);
	systime += 1;
}