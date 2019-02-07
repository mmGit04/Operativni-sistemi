#include "thread.h"
#include "timer.h"
#include "SCHEDULE.h"
#include "pcb.h"
#include <dos.h>
#include "Queue.h"
#include "stdlib.h"


Thread::Thread (StackSize stackSize, Time timeSlice)
{
	if (stackSize < defaultStackSize) stackSize = defaultStackSize;
	if (stackSize>65535) stackSize=65535;
	lockFleg=0;
	myPCB = new PCB(stackSize,timeSlice,this);
	lockFleg=1;
}


void Thread::start()
{
	if (myPCB->started == 0)
	{
		myPCB->started = 1;
		myPCB->state=READY;
		Scheduler::put(myPCB);
	}
}

void dispatch()
{
	asm pushf
	asm cli
	explicitDispatch = 1;
	asm int 08h
	asm popf
}


void Thread::waitToComplete() 
{
	if (myPCB->started == 1 && myPCB->state != DONE && myPCB != PCB::runningPCB)
	{
		lockFleg=0;
		myPCB->wait->put(PCB::runningPCB);
		PCB::runningPCB->state = BLOCKED;
		lockFleg=1;
		dispatch();
	}
}


Thread::~Thread()
{
	waitToComplete(); 
	lockFleg=0;
	delete myPCB;
	lockFleg=1;
}


ID Thread::getId()
{
	return myPCB->id;
}
ID Thread ::getRunningId()
{
	return PCB::runningPCB->id;
}


Thread * Thread::getThreadById(ID id)
{
	PCB* p=PCB::exists->get(id);
	if (p == 0) return 0;
	return p->myThread;

}


