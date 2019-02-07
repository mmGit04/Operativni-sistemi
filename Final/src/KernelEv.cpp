#include "KernelEv.h"
#include "Event.h"
#include "pcb.h"
#include "timer.h"
#include "IVTEntry.h"


KernelEv::KernelEv(Event * my,IVTNo ivtNo)
{  
	myEvent=my;
	entry=ivtNo;
	parent=PCB::runningPCB;
	value=1;
	IVTEntry::get(ivtNo)->myEvent=this;
}
KernelEv::~KernelEv()
{
	IVTEntry::array[entry]=0;
}
void KernelEv::inc()
{
	value=1;
}
void KernelEv::dec()
{
	value=0;
}
int KernelEv::getValue()
{
	return value;
}

void KernelEv::signal(){
	myEvent->signal();
}