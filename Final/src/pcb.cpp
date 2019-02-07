
#include "pcb.h"
#include "thread.h"
#include <dos.h>
#include "Queue.h"
#include "timer.h"
#include "SCHEDULE.H"
#include <iostream.h>


Queue * PCB::exists=new Queue ();
PCB* PCB::runningPCB = 0;
ID PCB::generatorID = 0;
PCB* PCB::mainPCB = 0;
PCB::PCB(unsigned long stackSize_, Time timeSlice_,Thread* myThread_)
{
	stackSize = stackSize_;
	timeSlice = timeSlice_;
	myThread = myThread_;
	stack=0;
	started = 0;
	state = READY;
	id = generatorID++;
	createStack();
	PCB::exists->put(this);
	lockFleg=0;
	wait=new Queue();
	lockFleg=1;
}



void PCB::wrapper()
{
	runningPCB->myThread->run();
	PCB* temp;
	while(PCB::runningPCB->wait->getLength()>0)
	{
		temp = PCB::runningPCB->wait->get();
		temp->state = READY;
		Scheduler::put(temp);
	}
	runningPCB->state = DONE;
	dispatch();
}


void PCB::createStack()
{
	int stackElemNum = stackSize/sizeof(unsigned);
	stack = new unsigned[stackElemNum];
	stack[stackElemNum - 1] =0x200;
	stack[stackElemNum - 2] =FP_SEG(wrapper);
	stack[stackElemNum - 3] =FP_OFF(wrapper);
	sp = FP_OFF(stack + stackElemNum - 12);
	ss = FP_SEG(stack + stackElemNum - 12);
	bp=sp;
}



PCB::~PCB()
{
	lockFleg=0;
	delete stack;
	delete wait;
	lockFleg=1;
	exists->remove(this);

}


