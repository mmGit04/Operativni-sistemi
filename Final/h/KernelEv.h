#ifndef _KERNELEV_H_
#define _KERNELEV_H_
typedef unsigned char IVTNo;
class PCB;
class Event;
class KernelEv
{
public:
	Event * myEvent;
	IVTNo entry;
	PCB* parent;
	int value;
	
	KernelEv(Event * my,IVTNo ivtNo);
	~KernelEv();
	void dec();
	void inc();
	int getValue();
	void signal();
    
   
};







#endif