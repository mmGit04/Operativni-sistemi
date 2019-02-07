
#ifndef ALLSEMAP_H_
#define ALLSEMAP_H_


class AllSemap
{
private:
	struct Elem
	{ 
		KernelSem * elem;
        Elem * next;
        Elem(KernelSem* _elem):elem(_elem),next(0){}
		Elem(KernelSem* _elem,Elem * _next):elem(_elem),next(_next){}
	};
	Elem * first;
public:
	AllSemap();
	~AllSemap();
	void add (KernelSem * _elem);
	void remove(KernelSem* _elem);
	void updateAllSemap();

        
};
#endif