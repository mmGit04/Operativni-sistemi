#ifndef _EVENT_H_
#define _EVENT_H_


#include "kernelev.h"
#include "ivtentry.h"
class IVTEntry;
typedef unsigned char IVTNo;
class KernelEv;
class Event {
public:
    Event (IVTNo ivtNo);
    ~Event ();
    void wait ();
protected:
    friend class KernelEv;
    void signal(); 
private:
    KernelEv* myImpl;
};
#define PREPAREENTRY(num, callold)\
void interrupt inter##num(...);\
IVTEntry newEntry##num(num,inter##num);\
void interrupt inter##num(...)\
{\
if (newEntry##num.myEvent!=0)\
	newEntry##num.myEvent->signal();\
if (callold==1 && newEntry##num.oldRoutine)\
	newEntry##num.oldRoutine();\
}

#endif 