

#ifndef TIMER_H_
#define TIMER_H_


extern volatile unsigned int lockFleg;
extern volatile unsigned int explicitDispatch;
void interrupt timer();
void inic();
void restore();
#endif 
