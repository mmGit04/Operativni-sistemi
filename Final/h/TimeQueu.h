#ifndef TIMEQUEU_H_
#define TIMEQUEU_H_

class PCB;
class KernelSem;
class TimeQueue
{
private:
	struct Elem
	{
		PCB* elem;
		int waitTime;
		Elem* next;
		Elem (PCB* _elem,int _time): elem(_elem),waitTime(_time),next(0){}
		Elem (PCB* _elem ,int _time,Elem * _next): elem(_elem),waitTime(_time),next(_next){}
	};
	Elem * first ;
public:
	TimeQueue();
	~TimeQueue();
	void add(PCB* _pcb,int time);
	void remove(KernelSem* _kersem);
	void remove(PCB* _pcb);
	void decreaseTime();

};

#endif