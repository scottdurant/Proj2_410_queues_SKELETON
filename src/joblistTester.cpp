/*
 * fileio.cpp
 *
 *  Created on: Sep 16, 2017
 *      Author: keith
 */

//============================================================================
// Name        : Proj1_410.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
//============================================================================

#include <iostream>
#include "../includes_usr/file_io.h"
#include "../includes_usr/joblist.h"
//defaults
const char* 		SOURCE_FILE = "sampleruns/2_noIO_testdata.txt";
const char* 		BOGUS_FILE = "BOGUS.txt";
const char*		 	RESULTS_FILE = "results.txt";
using namespace std;

int main() {
	int total_points = 100; //assumme success
	int iRet = FAIL;

	//verify return COULD_NOT_OPEN_FILE
/*	iRet = loadData(BOGUS_FILE);
	if (iRet != COULD_NOT_OPEN_FILE){
		total_points =total_points-10;
		cout<<"-10 failed to return COULD_NOT_OPEN_FILE on bogus file"<<endl;
	}
	else
		cout<<"Success 1"<<endl;*/


	iRet = joblist::init(BOGUS_FILE);
	if (iRet != COULD_NOT_OPEN_FILE){
			total_points =total_points-10;
			cout<<"-10 failed to return COULD_NOT_OPEN_FILE on bogus file"<<endl;
		}
		else
			cout<<"Success 1"<<endl;

	//load data
	iRet = joblist::init(SOURCE_FILE);  // NOTE: init will also sort by START_TIME
	if (iRet != SUCCESS){
		total_points =total_points-10;
		cout<<"-10 failed to return SUCCESS on correct file"<<endl;
	}
	else
		cout<<"Success 2"<<endl;


	//get the next one in line
	PCB myPCB = joblist::getNextJob();
	if (myPCB.process_number!=2 || myPCB.start_time !=1 ||myPCB.cpu_time !=8 || myPCB.io_time !=0 ){
		total_points =total_points-20;
		cout<<"-20 failed getnext after sort, expected 2,1,8,0 got "<<std::to_string(myPCB.process_number) <<","<<std::to_string(myPCB.start_time)<<","<<std::to_string(myPCB.cpu_time)<<", "<<std::to_string(myPCB.io_time)<<endl;
	}
	else
		cout<<"Success 3"<<endl;

	// do tick not correct time
	iRet = joblist::doTick(3);
	if(iRet != WAITING_TO_ADD_JOB_TO_DISPATCHER){
		cout<<"-20 failed doTick, expected WAITING_TO_ADD_JOBS_TO_DISPATCHER, got"<<iRet<<endl;
	} else {
		cout<<"Success 4"<<endl;
	}

	// do tick correct time
	iRet = joblist::doTick(10);
	if(iRet != ADD_JOB_TO_DISPATCHER){
		cout<<"-20 failed doTick, expected ADD_JOB_TO_DISPATCHER, got"<<iRet<<endl;
	} else {
		cout<<"Success 5"<<endl;
	}


	//get the next one in line
	myPCB = joblist::getNextJob();
	if (myPCB.process_number!=1 || myPCB.start_time !=10 ||myPCB.cpu_time !=7 || myPCB.io_time != 0){
		total_points =total_points-20;
		cout<<"-20 failed getnext, expected 1,10,7,0 got "<<std::to_string(myPCB.process_number) <<","<<std::to_string(myPCB.start_time)<<","<<std::to_string(myPCB.cpu_time)<<","<<std::to_string(myPCB.io_time)<<endl;
	}
		else
		cout<<"Success 6"<<endl;


	// myVector should be empty now
	iRet = joblist::doTick(0);
	if(iRet != NO_JOBS){
		cout<<"-20 failed doTick, expected NO_JOBS, got "<<iRet<<endl;
	} else {
		cout <<"Success 7"<<endl;
	}



	return iRet;
}


