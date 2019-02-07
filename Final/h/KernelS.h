#ifndef KERNELS_H_
#define KERNELS_H_


class Queue;
class TimeQueue;
class AllSemap;
typedef unsigned int Time;
class KernelSem
{
private:
	int value;
public:
	KernelSem(int init);
	~KernelSem();
	void block(Time maxTimeToWait);
	void deblock();
	int getValue();
	void inc();
	void dec();
    static AllSemap * allSemap;
    Queue * waitQueue;
    TimeQueue* timeQueue;



};

#endif