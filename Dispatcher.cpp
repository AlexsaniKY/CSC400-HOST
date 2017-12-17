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

int Dispatcher::getTime(){return systime;}

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

bool Dispatcher::isRsrcAvailable(Rsrc reqRes){
	return (
		(reqRes.printers <= available_resources.printers) 
		&& (reqRes.scanners <= available_resources.scanners) 
		&& (reqRes.modems <= available_resources.modems) 
		&& (reqRes.cds <= available_resources.cds)
		);
}

void Dispatcher::allocateRsrc(Rsrc res){
	available_resources.printers -= res.printers;
	available_resources.scanners -= res.scanners;
	available_resources.modems -= res.modems;
	available_resources.cds -= res.cds;
}

void Dispatcher::deallocateRsrc(Rsrc res){
	available_resources.printers += res.printers;
	available_resources.scanners += res.scanners;
	available_resources.modems += res.modems;
	available_resources.cds += res.cds;
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
				m = memory.get_block(p->mbytes);
				//if a block was available
				if(m){
					//give it to p
					p->mblock = m;
					//remove p from the list
					next = p->next;
					if(previous) pop_next(previous);
					else {
						new_queue = next;
						p->next = NULL;
					}
					//add it to the RT ready queue
					if(!job_queues[RT]) job_queues[RT] = p;
					else job_queues[RT] = enqPcb(job_queues[RT], p);
					//set up the next link
					p = next;
					//clean up
					m = NULL;
					continue;
				}
				else {
					previous = p;
					p = p->next;
				}
				break;
			//if user process
			default:
				//if resources can be allocated
				if(isRsrcAvailable(p->req)){
					allocateRsrc(p->req);

					next = p->next;

					if(previous) pop_next(previous);
					else {
						new_queue = next;
						p->next = NULL;
					}
					if(!job_queues[p->priority]) job_queues[p->priority] = p;
					else job_queues[p->priority] = enqPcb(job_queues[p->priority], p);
					p = next;
					continue;
				}
				else {
					previous = p;
					p = p->next;
				}
				break;
		}
		//previous = p;
		//p = p->next;
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

bool Dispatcher::hasInputQueue(){
	return input_queue;
}

//Whether the Dispatcher still has jobs, whether initialized or not
bool Dispatcher::hasJobs(){
	return (
		new_queue
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
	//remove a process from the "ready" job queues
	if(job_queues[RT]) running_process = deqPcb(&job_queues[RT]);
	else if(job_queues[US1]) running_process = deqPcb(&job_queues[US1]);
	else if(job_queues[US2]) running_process = deqPcb(&job_queues[US2]);
	else if(job_queues[US3]) running_process = deqPcb(&job_queues[US3]);

	//if there is a running process
	if(running_process) startPcb(running_process);
	else{
		sleep(1);
		systime += 1;
		return;
	}

	if(running_process->priority == RT){
		while(running_process->remainingcputime != 0){
			sleep(1);
			systime += 1;
			running_process->remainingcputime -= 1;
		}
		terminatePcb(running_process);
		running_process = NULL;
		return;
	}

	do{
		sleep(1);
		systime+=1;
	}
	while(!(
		hasJobs() 
		|| (hasInputQueue() 
			&& input_queue->priority <= running_process->priority
			&& input_queue->arrivaltime <= systime ) 
		));
	suspendPcb(running_process);
	running_process->priority += 
		running_process->priority + 1 < 4 
		? 1 : 0;
	job_queues[running_process->priority] = enqPcb(job_queues[running_process->priority], running_process);
}