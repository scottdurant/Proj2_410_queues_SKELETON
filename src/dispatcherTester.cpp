#include <iostream>
#include "../includes_usr/dispatcher.h"

using namespace std;
/*
int main() {

	int iRet = FAIL;

	// test init
	dispatcher::init();

	PCB testPCB = dispatcher::getCurrentJob();

	if (testPCB.process_number != UNINITIALIZED
			|| testPCB.start_time != UNINITIALIZED
			|| testPCB.cpu_time != UNINITIALIZED
			|| testPCB.io_time != UNINITIALIZED) {
		cout << "failed to initialize runningPCB" << endl;
	} else {
		cout << "Success 1" << endl;
	}

	// runningPCB uninitialized at this point
	iRet = dispatcher::doTick();
	if (iRet != NO_JOBS) {
		cout << "fail, expected NO_JOBS but was: " << iRet << endl;
	} else {
		cout << "Success 2" << endl;
	}

	return 0;
}
*/
