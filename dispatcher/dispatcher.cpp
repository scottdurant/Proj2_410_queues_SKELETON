#include "../includes_usr/constants.h"
#include "../includes_usr/dispatcher.h"
#include "../includes_usr/file_io.h"
#include "../includes_usr/joblist.h"
#include "../includes_usr/logger_single_thread.h"
#include <queue>

PCB runningPCB;
std::queue<PCB> ready_Q;
std::queue<PCB> blocked_Q;

// clears ready_Q and blocked_Q these are queues of PCB structures,
// initializes runningPCB to default values in constants (see PCB structure)
void dispatcher::init() {
	std::queue<PCB> emptyQueue;
	// clear ready_Q and blocked_Q
	ready_Q.swap(emptyQueue);
	blocked_Q.swap(emptyQueue);

	// set runningPCB to default values
	runningPCB.process_number = UNINITIALIZED;
	runningPCB.start_time = UNINITIALIZED;
	runningPCB.cpu_time = UNINITIALIZED;
	runningPCB.io_time = UNINITIALIZED;
}

//used for testing, return a copy of runningPCB
PCB dispatcher::getCurrentJob() {
	return runningPCB;
}

//add a job to the ready queue
void dispatcher::addJob(PCB &myPCB) {
	ready_Q.push(myPCB);
}

//interrupt can be either;
//a switch process interrupt in which case the function performs the appropriate tasks and returns PCB_SWITCHED_PROCESSES
//or a io_complete interrupt in which case it pulls ALL processes off of the blockedQ and returns either PCB_MOVED_FROM_BLOCKED_TO_READY (if there were any)
//or PCB_BLOCKED_QUEUE_EMPTY if there were none.
int dispatcher::processInterrupt(int interrupt) {
	return NO_JOBS;
}

//see flowchart
int dispatcher::doTick() {
	return NO_JOBS;
}
