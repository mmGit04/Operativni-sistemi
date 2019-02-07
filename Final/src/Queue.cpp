

#include "pcb.h"
#include "Thread.h"
#include "Queue.h"
#include "timer.h"


void Queue::put(PCB* pcb) {
  lockFleg=0;
  Elem *curr=first;
  if (curr==0)
  	first=last=new Elem(pcb);
  else 
  {
  	last->next=new Elem(pcb);
  	last=last->next;
  }
  length++;
  lockFleg=1;
}
Queue::Queue()
{
	first =0;
	last=0;
	length=0;
}
Queue :: ~Queue()
{
	lockFleg=0;
	Elem * tem=first;
	while( first != 0)
	{
		tem = first;
		first = first->next;
		delete tem;
		length--;
	}
	lockFleg=1;
}

int Queue::getLength() const {
	return length;
}

PCB* Queue::get() {
	
	if( first == 0 )  return 0;
	lockFleg=0;
	length--;
	Elem* temp = first;
	first = first->next;
	if (first == 0)
		last = 0;
	lockFleg=1;
	return temp->pcb;
}

void Queue::remove(PCB * pcb)
{   lockFleg=0;
	Elem * pred=0; Elem * tek=first;
	while(tek!=0 && tek->pcb!=pcb)
	{
		pred=tek; tek=tek->next;
	}
	if (pred==0) first=first->next;
	else pred->next=tek->next;
	lockFleg=1;
}
PCB* Queue ::get(int id)
{   lockFleg=0;
	for (Elem * tek=first;tek!=0;tek=tek->next){
		if (tek->pcb->id==id) { lockFleg=1;return tek->pcb;}
	}
	lockFleg=1;
	return 0;
}
PCB* Queue ::index(int i)
{   lockFleg=0;
	int j=0;
	Elem *tek=0;
	for (tek=first;j!=i && tek!=0;tek=tek->next);
	lockFleg=1;
	return tek->pcb;
}




