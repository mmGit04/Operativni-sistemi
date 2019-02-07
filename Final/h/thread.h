

#ifndef THREAD_H_
#define THREAD_H_



typedef unsigned long StackSize;
const StackSize defaultStackSize = 4096;
typedef unsigned int Time; 
const Time defaultTimeSlice = 2; 
typedef int ID;
class PCB; 
class Thread {
	public:
		void start();
		void waitToComplete();
		virtual ~Thread();
		ID getId();
		static ID getRunningId();
		static Thread * getThreadById(ID id);
	protected:
		friend class PCB;
		friend class IdleThread;
		Thread (StackSize stackSize = defaultStackSize, Time timeSlice =
		defaultTimeSlice);
		virtual void run() {}
	private:
		PCB* myPCB;
};


void dispatch();
#endif 
