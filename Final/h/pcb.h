
#ifndef PCB_H_
#define PCB_H_


enum State{
	READY,RUNNING,BLOCKED,DONE
};

class Queue;
class Thread;
typedef unsigned int Time;
typedef unsigned long StackSize;
typedef int ID;
class PCB
{
public:
	unsigned int* stack;
	unsigned sp,bp,ss;
	StackSize stackSize;
	int free;
	Time timeSlice;
	Thread* myThread;
	State state;
	int started; 
	ID id;
	static ID generatorID;
	static Queue * exists; 
	Queue * wait;
	static PCB* runningPCB;
	static PCB* mainPCB;
	static  void wrapper();
	PCB(unsigned long stackSize_, Time timeSlice_,Thread* myThread_);
	~PCB();
	void createStack();
	friend class IdleThread;
};



#endif 
