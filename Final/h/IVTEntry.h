#ifndef _IVTENTRY_H_
#define _IVTENTRY_H_

typedef  void interrupt (*Routine)(...);
typedef unsigned char IVTNo;
class KernelEv;
class IVTEntry
{
public:
	static IVTEntry* array[256];
	IVTNo ivtNo;
	
public:
	IVTEntry(IVTNo _ivtNo,Routine intRoutine);
	~IVTEntry();
	static IVTEntry* get(IVTNo _ivtNo);
	KernelEv * myEvent;
	Routine oldRoutine;
};

#endif 