
#include "user.h"
#include "pcb.h"
#include "SCHEDULE.h"
#include "timer.h"
#include "idle.h"
#include "semaphor.h"
#include "kernels.h"
#include "allsemap.h"
unsigned oldTimerSEG, oldTimerOFF;
volatile unsigned int counter;
volatile unsigned int tempBP, tempSP, tempSS;
volatile unsigned lockFleg=1, explicitDispatch=0;
IdleThread *idle=new IdleThread(); 
void tick();

void interrupt timer()
{   tick();
	if (PCB::runningPCB->timeSlice != 0 && counter != 0 && explicitDispatch==0) counter--;
	if (!explicitDispatch) 
		KernelSem::allSemap->updateAllSemap();
	if (lockFleg==1)
	{
		if (explicitDispatch || (PCB::runningPCB->timeSlice != 0) && (counter == 0) )
		{

			asm {
				mov tempBP,bp
				mov tempSP, sp
				mov tempSS, ss
			}
			
			PCB::runningPCB->bp = tempBP; PCB::runningPCB->sp = tempSP; PCB::runningPCB->ss = tempSS;
			if (PCB::runningPCB->state == RUNNING)
			{
				PCB::runningPCB->state = READY;
				Scheduler::put(PCB::runningPCB);
			}
			PCB::runningPCB=Scheduler::get();
			if (PCB::runningPCB  == 0)  
				PCB::runningPCB=idle->getPCB();
			
			tempBP = PCB::runningPCB->bp; 
			tempSP = PCB::runningPCB->sp; 
			tempSS = PCB::runningPCB->ss;
			asm{

				mov bp, tempBP
				mov sp, tempSP
				mov ss, tempSS
			}
			
			PCB::runningPCB->state = RUNNING;
			counter = PCB::runningPCB->timeSlice;
		}
	}
	if (explicitDispatch == 0)
	{
		asm int 60h
	}
	explicitDispatch=0;
}

void inic(){
	asm{
	    cli
		push es
		push ax
		mov ax,0
		mov es,ax
		mov ax, word ptr es:0022h
		mov word ptr oldTimerSEG, ax
		mov ax, word ptr es:0020h
		mov word ptr oldTimerOFF, ax
		mov word ptr es:0022h, seg timer
		mov word ptr es:0020h, offset timer
		mov ax, oldTimerSEG
		mov word ptr es:0182h, ax
		mov ax, oldTimerOFF
		mov word ptr es:0180h, ax
		pop ax
		pop es

	}
}



void restore(){
	asm {
		cli
		push es
		push ax
		mov ax,0
		mov es,ax
		mov ax, word ptr oldTimerSEG
		mov word ptr es:0022h, ax
		mov ax, word ptr oldTimerOFF
		mov word ptr es:0020h, ax
		pop ax
		pop es
		sti
	}
}
