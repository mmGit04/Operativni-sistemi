#include "timer.h"
#include "Semaphor.h"
#include "KernelS.h"
#include "pcb.h"
#include "thread.h"
Semaphore::Semaphore(int init)
{ 
	lockFleg=0;
	myImpl=new KernelSem(init);
	lockFleg=1;
}
Semaphore::~Semaphore()
{
	delete myImpl;
}
int Semaphore::wait(Time maxTimeToWait)
{
	asm pushf
	asm cli 
	
	myImpl->dec();
	if (myImpl->getValue() < 0) 
	{
        myImpl->block(maxTimeToWait);
		dispatch();
		asm popf
		return PCB::runningPCB->free;
	}
	else
	{
		asm popf
		return 2;
	}
}
void Semaphore::signal()
{
	asm pushf
	asm cli 
	
	if(myImpl->getValue()<0)
	{
      myImpl->deblock();
	}
	myImpl->inc();
	asm popf
	
}

int Semaphore::val()const{
	return myImpl->getValue();
}