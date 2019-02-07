#include "timeQueu.h"
# include "Queue.h"
# include "KernelS.h"
#include "PCB.h"
#include "schedule.h"

TimeQueue::TimeQueue()
{
	first=0;
}
TimeQueue::~TimeQueue()
{
	Elem* curr=first;
	while(curr)
	{
		Elem* old=curr;
		curr=curr->next;
		delete old;
	}
	first=0;
}
void TimeQueue::add(PCB* _pcb,int time)

{
	if (first==0) 
		first=new Elem(_pcb,time); 
	else
	{
		Elem* curr=first,*prev=0;
		while((curr)&& (curr->waitTime<=time))
		{
			prev=curr;curr=curr->next;
		}
		Elem * tem = new Elem(_pcb,time,curr);
		if (prev==0) first=tem;
		else prev->next=tem;
	}
}


void TimeQueue::remove(KernelSem * _kersem)
{
	Elem* curr=first;
	while((curr)&& (curr->waitTime==0))
	{
		curr->elem->state=READY;
		
		_kersem->waitQueue->remove(curr->elem);
		Scheduler::put(curr->elem);
		curr->elem->free=0;
		first=first->next;
		delete curr;
		curr=first;
	}
}

void TimeQueue::decreaseTime()
{
	Elem* curr=first;
	while(curr)
	{
		curr->waitTime--;
		curr=curr->next;
	}
}

void TimeQueue::remove(PCB* _pcb)
{
	Elem * curr=first,*prev=0;
	while((curr) && (curr->elem!=_pcb))
	{
		prev=curr;
		curr=curr->next;
	}
	if (curr)
	{   
		Elem* old=curr;
		curr=curr->next;
		delete old;
		if (prev==0) first=curr;
		else prev->next=curr;
	}
}







