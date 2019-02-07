

#include <iostream.h>
#include "pcb.h"
#include "timer.h"
#include"thread.h"
#include <dos.h>
#include "usermain.h"


void main(int argc,char **argv)
{
	PCB::mainPCB = new PCB(defaultStackSize, 0, 0);
	PCB::runningPCB = PCB::mainPCB;
	PCB::runningPCB->state = BLOCKED;
	UserMain *usermain=new UserMain(argc,argv);
	usermain->start();
	inic();
	dispatch();
	restore();
}


