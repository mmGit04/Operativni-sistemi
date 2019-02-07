

#ifndef IDLE_H_
#define IDLE_H_


#include "thread.h"

class Thread;
class IdleThread: public Thread
{
public:
	IdleThread();
	virtual void run();
	PCB* getPCB();
};



#endif 
