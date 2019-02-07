

#include "Timer.h"
#include "pcb.h"
#include "Idle.h"
#include <iostream.h>
#include "SCHEDULE.h"
#include "Queue.h"

IdleThread::IdleThread():Thread(32,0){}

void IdleThread::run()
{
	while(1){
		
		dispatch();
	}
}
PCB* IdleThread::getPCB()
{
	return myPCB;
}




