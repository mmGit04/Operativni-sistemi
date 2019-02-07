#ifndef _usermain_h_
#define _usermain_h_


#include "thread.h"
int userMain(int,char**);
class UserMain:public Thread  
{
	private:
		int argc;
		char **argv;
	public:
		UserMain(int _argc, char** _argv);
		void run(); 
};




#endif