#include "KernelS.h"
#include "Queue.h"
#include "TimeQueu.h"
#include "AllSemap.h"
#include "timer.h"

AllSemap::AllSemap()
{
	first=0;
}
 
AllSemap::~AllSemap()
{
	Elem * curr=first;
	while(curr)
	{
		Elem * old=curr;
		curr=curr->next;
		delete old;
	}
	first=0;

}
void AllSemap::add(KernelSem * _elem)
{
	lockFleg=0;
	first=new Elem(_elem,first);
	lockFleg=1;
}
void AllSemap::remove(KernelSem* _elem)
{
	Elem * curr=first,*prev=0;
	while(curr)
	{
		if (curr->elem !=_elem){
			prev=curr;
			curr=curr->next;
		}
		else {
			curr=curr->next;
			if (prev==0) first=curr;
			else prev->next=curr;
			break;
		}
	}
}


void AllSemap::updateAllSemap()
{
	Elem* curr=first;
	while(curr)
	{ 
	  KernelSem* tem=curr->elem;
      tem->timeQueue->decreaseTime();
      tem->timeQueue->remove(tem);
	  curr=curr->next;
	}
}





