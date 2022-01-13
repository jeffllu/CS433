#include "ReadyQueue.h"
#include <iostream>
#include <fstream>
#include <array>
using namespace std;
/*
1) add processes 15, 6, 23, 39 and 8 to 𝑞1. Display the content of 𝑞1
2) remove the process with the highest priority from 𝑞1 and display 𝑞1.
3) add processes 47, 1, 37 and 5 into 𝑞1, and display 𝑞1.
4) remove the process with the highest priority from 𝑞1 and display 𝑞1.
5) add processes 43, 17, 32, 12 and 19 to 𝑞1 and display 𝑞1
6) One by one remove the process with the highest priority from the queue 𝑞1 and
display the queue after each removal
*/

int main() {
  cout << "This is a priority queue taking in proccesses represented by PCB" << endl;
  ReadyQueue q1;
  PCB obj15(15,15);
  PCB obj6(6,6); 
  PCB obj23(23,23); 
  PCB obj39(39,39);
  PCB obj8(8,8);
  PCB obj47(47,47); PCB obj1(1,1); PCB obj37(37,37); PCB obj5(5,5);
  PCB obj43(43,43); PCB obj17(17,17); PCB obj32(32,32);
  PCB obj12(12, 12); PCB obj19(19,19);
  
  q1.addPCB(obj15);
  q1.addPCB(obj6);
  q1.addPCB(obj23);
  q1.addPCB(obj39); 
  q1.addPCB(obj8);
  q1.display();

  cout << "Removing" << endl;
  q1.removePCB();
  q1.display();

  q1.addPCB(obj47);
  q1.addPCB(obj1);
  q1.addPCB(obj37);
  q1.addPCB(obj5);

  q1.display();

  cout << "Removing" << endl;
  q1.removePCB();
  q1.display();

  //add processes 43, 17, 32, 12 and 19 to 𝑞1 and display 𝑞1

  q1.addPCB(obj43);
  q1.addPCB(obj17);
  q1.addPCB(obj32);
  q1.addPCB(obj12);
  q1.addPCB(obj19);

  q1.display();

	while (q1.size() != 0){
		cout << "Removing" << endl;
  	q1.removePCB();
  	q1.display();
	}

	 //Second Test
   
	 	 cout<< "\n" << "second test"<<endl;
	//creating 100 PCB objects with random priorities
	ReadyQueue q2;
	const int SIZE = 100;
	int id = 1;

	while(q2.size() != SIZE){
		int prio = rand() % 50 +1;
		PCB pcb = PCB(id,prio);
		q2.addPCB(pcb);
		id++;
	}
	q2.display();

	//randomely adding or removing objects a million times
	for (int i = 0; i< 1000000; i++ ){
		int r = rand() % 2+1;
		if(r== 1){ //if random number is 1, creatre new PCb and add it to queue
			id++;
			PCB pcb = PCB(id,rand() % 50 +1);
			q2.addPCB(pcb);
		}else if(q2.size() != 0){
			q2.removePCB();
		}
	}
	q2.display();

	


}