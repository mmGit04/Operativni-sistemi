#include "IVTEntry.h"
#include <dos.h>
IVTEntry* IVTEntry::array[256];


IVTEntry::IVTEntry(IVTNo _ivtNo,Routine intRoutine )
{
	asm pushf
	asm cli
	ivtNo=_ivtNo;
	oldRoutine=getvect(ivtNo);
	setvect(ivtNo,intRoutine);
	myEvent=0;
	array[ivtNo]=this;
    asm popf
}
IVTEntry::~IVTEntry()
{
	asm pushf
	asm cli
	setvect(ivtNo,oldRoutine);
	asm popf;
}

IVTEntry* IVTEntry::get(IVTNo _ivtNo)
{
	return array[_ivtNo];
  
}
