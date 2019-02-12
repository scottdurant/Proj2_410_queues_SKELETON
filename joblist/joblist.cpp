#include <iostream>
#include "../includes_usr/constants.h"
#include "../includes_usr/dispatcher.h"
#include "../includes_usr/file_io.h"
#include "../includes_usr/joblist.h"

//assumme the worst
bool joblistHasJobs = false;

// loads data from filename and sorts
// it by job start time
int joblist::init(const char* filename) {
	int iRet = loadData(filename);
	if(iRet == COULD_NOT_OPEN_FILE){
		return COULD_NOT_OPEN_FILE;
	}

	sortData(SORT_ORDER::START_TIME);
	return SUCCESS;
}

//gets next job from file_IO
PCB joblist::getNextJob() {
	return getNext();
}


// if no jobs in vector managed by file_io return NO_JOBS
// otherwise see if its time to load a process by comparing current tick
// to the next process in lines start_time.
// If its time to load return ADD_JOB_TO_DISPATCHER
// if not return WAITING_TO_ADD_JOB_TO_DISPATCHER
int joblist::doTick(int currentTick) {
	if(size() == 0){
		return NO_JOBS;
	}

	int nextStartTime = peekNextStartTime();

	if (currentTick == nextStartTime){
		return ADD_JOB_TO_DISPATCHER;
	}

	return WAITING_TO_ADD_JOB_TO_DISPATCHER;
}

