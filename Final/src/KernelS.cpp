#include "KernelS.h"
#include "Queue.h"
#include "timeQueu.h"
#include "AllSemap.h"
#include "timer.h"
#include "pcb.h"
#include "thread.h"
#include "schedule.h"

AllSemap* KernelSem::allSemap=new AllSemap();

KernelSem::KernelSem(int init)
{
  value=init;
  allSemap->add(this);
  lockFleg=0;
  waitQueue=new Queue();
  timeQueue=new TimeQueue();
  lockFleg=1;
}
KernelSem::~KernelSem()
{
	allSemap->remove(this);
}

void KernelSem::inc()
{
	value++;
}

void KernelSem::dec()
{
	value--;
}

int KernelSem::getValue()
{
	return value;
}

void KernelSem::block(Time maxTimeToWait)
{ 
	waitQueue->put(PCB::runningPCB);
	timeQueue->add(PCB::runningPCB, maxTimeToWait);
	PCB::runningPCB->state=BLOCKED;
	dispatch();

}

void KernelSem::deblock()
{  
    PCB* tem=waitQueue->get();
    timeQueue->remove(tem);
    tem->state=READY;
    tem->free=1;
    Scheduler::put(tem);
}






