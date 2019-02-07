#include "usermain.h"
#include "timer.h"
#include "schedule.h"
#include "pcb.h"
#include "iostream.h"'
#include "semaphor.h"
#include "user.h"

UserMain::UserMain(int _argc, char** _argv):Thread(defaultStackSize,1)
{
	argc=_argc;
	argv=_argv;
}
void UserMain::run()
{
	userMain(argc,argv);
	lockFleg=0;
	Scheduler::put(PCB::mainPCB);
	lockFleg=1;
	
}
