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
//a switch process interrupt (1) in which case the function performs the appropriate tasks and returns PCB_SWITCHED_PROCESSES
//or a io_complete interrupt (0) in which case it pulls ALL processes off of the blockedQ and returns either PCB_MOVED_FROM_BLOCKED_TO_READY (if there were any)
//or PCB_BLOCKED_QUEUE_EMPTY if there were none.
int dispatcher::processInterrupt(int interrupt) {
	if (interrupt == SWITCH_PROCESS) {
		//////////  timeslice interrupt  //////////
		if (ready_Q.empty() && blocked_Q.empty()) {
			return NO_JOBS;
		}

		if (ready_Q.empty() && !blocked_Q.empty()) {
			return BLOCKED_JOBS;
		}

		// there are jobs to switch to
		PCB tmpPCB = ready_Q.front();

		if (runningPCB.cpu_time != UNINITIALIZED
				&& runningPCB.io_time != UNINITIALIZED
				&& runningPCB.process_number != UNINITIALIZED
				&& runningPCB.start_time != UNINITIALIZED) {

			ready_Q.push(runningPCB);
			runningPCB = tmpPCB;
			return PCB_SWITCHED_PROCESSES;
		}


		} else if (interrupt == IO_COMPLETE) {
			//////////  io complete interrupt  //////////

			if (!blocked_Q.empty()) {
				// add all jobs in blocked_Q back to ready_Q if there are any
				int blocked_QSize = blocked_Q.size();
				for (int i = 0; i < blocked_QSize; i++) {
					ready_Q.push(blocked_Q.front());
				}
				return PCB_MOVED_FROM_BLOCKED_TO_READY;
			} else {
				// no jobs on blocked_Q
				return PCB_BLOCKED_QUEUE_EMPTY;
			}

		} else {
			return PCB_UNIMPLEMENTED;
		}

		return NO_JOBS;
	}

//see flowchart
int dispatcher::doTick() {
	int returnVal = FAIL;
	// is there a runningPCB?
	if (runningPCB.cpu_time != UNINITIALIZED
			&& runningPCB.io_time != UNINITIALIZED
			&& runningPCB.process_number != UNINITIALIZED
			&& runningPCB.start_time != UNINITIALIZED) {
		// subtract 1 from cpu time
		runningPCB.cpu_time = runningPCB.cpu_time - 1;

		// is current job finished?
		if (runningPCB.cpu_time == 0) {

			// does runningPCB make a blocking IO call?
			if (runningPCB.io_time == 1) {
				blocked_Q.push(runningPCB);
				returnVal = PCB_ADDED_TO_BLOCKED_QUEUE;

				// mark runningPCB as invalid
				runningPCB.cpu_time = UNINITIALIZED;
				runningPCB.io_time = UNINITIALIZED;
				runningPCB.process_number = UNINITIALIZED;
				runningPCB.start_time = UNINITIALIZED;

			} else {
				///// runningPCB does NOT make blocking IO call /////
				returnVal = PCB_FINISHED;

				// unload or make runningPCB invalid
				runningPCB.cpu_time = UNINITIALIZED;
				runningPCB.io_time = UNINITIALIZED;
				runningPCB.process_number = UNINITIALIZED;
				runningPCB.start_time = UNINITIALIZED;
			}
		} else {
			///// current job NOT finished /////
			return PCB_CPUTIME_DECREMENTED;
		}
	} else {
		//////////// there is NOT a runningPCB ////////////////
		// Is ready_Q empty?
		if (ready_Q.empty()) {
			if (blocked_Q.empty()) {
				// both queues are empty, return NO_JOBS
				return NO_JOBS;
			}
			// just ready_Q is empty
			return BLOCKED_JOBS;
		} else {     ///// ready_Q NOT empty //////
			// load a job into runningPCB
			runningPCB = ready_Q.front();// is this right???????????????????????????
			ready_Q.pop();// remove the next element?
			return PCB_MOVED_FROM_READY_TO_RUNNING;
		}
	}

	return returnVal;
}
