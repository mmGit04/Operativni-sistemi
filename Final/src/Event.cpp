#include "Event.h"
#include "timer.h"
#include "pcb.h"

#include "thread.h"
#include "schedule.h"

Event::Event (IVTNo ivtNo)
{   
	lockFleg=0;
	myImpl=new KernelEv(this,ivtNo);
	lockFleg=1;
}
Event::~Event ()
{
	lockFleg=0;
	delete myImpl;
	lockFleg=1;
}

void Event::wait()
{
	asm pushf
	asm cli
	if (PCB::runningPCB==myImpl->parent)
	{
		myImpl->parent->state=BLOCKED;
		myImpl->dec();
		dispatch();
	}
	asm popf
}

void Event::signal()
{
	asm pushf
	asm cli 
	if (myImpl->getValue()==0)
	{
		myImpl->parent->state=READY;
		myImpl->inc();
		Scheduler::put(myImpl->parent);
	}
	asm popf
}
 


