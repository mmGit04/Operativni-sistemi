
#ifndef QUEUE_H_
#define QUEUE_H_


class PCB;

class Elem {
public:
	PCB* pcb;
	Elem *next;
	Elem(PCB *_pcb):pcb(_pcb),next(0){}
};
class Queue {
public:
      int getLength() const;
      void put(PCB* pcb);
      PCB* get();
      Queue();
      ~Queue();
      void remove(PCB * pcb);
      PCB* get(int id);
      PCB* index(int i);

private:
      Elem* first;
      Elem* last;
      int length;

};




#endif /* QUEUE_H_ */
