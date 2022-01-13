#include <iostream>
#include <fstream>
#include "ReadyQueue.h"
using namespace std;



ReadyQueue::ReadyQueue(){
  count = 0;
}

ReadyQueue::~ReadyQueue(){}

void ReadyQueue::addPCB(PCB x){
  if(count < MAX){
		x.setState(READY);
    Q[count] = x;
    count++;
    trickleup();
  }
}

void ReadyQueue::removePCB() {
	Q[0].setState(RUNNING);
  reheapify();
}

void ReadyQueue::display(){
  cout << "Processes in priority queue: " << endl;
  for(int i = 0; i < count-1; i++) {
    cout << "ID: " << Q[i].getID() << " Priority: " << Q[i].getPrio() << endl;
  }
  cout << "ID: " << Q[count-1].getID() << " Priority: " << Q[count-1].getPrio() << endl;
}

int ReadyQueue::size(){
  return count;
}

void ReadyQueue::swap(int x, int y) {
  int a;
  a = x;
  x = y;
  y = a;
}

void ReadyQueue::trickleup(){
  int x = count-1;
  while(x>0) {
    if(Q[x].getPrio() < Q[getParent(x)].getPrio()) {
      PCB temp = Q[x];
      Q[x] = Q[getParent(x)];
      Q[getParent(x)] = temp;
      x = getParent(x);
			
    } else {
      return;
    }
  }
}

void ReadyQueue::trickledown(){
  int x = 0;
  while(x < count-1) {
    if(Q[x].getPrio() > Q[getSmallerchild(x)].getPrio()) {
      PCB temp = Q[x];
      Q[x] = Q[getSmallerchild(x)];
      Q[getSmallerchild(x)] = temp;
      x = getSmallerchild(x);
    } else {
      return;
    }
  }
}

int ReadyQueue::getParent(int childloc) {
  if (even(childloc) ) {
    return ((childloc-2)/2);
  }
  return ((childloc-1)/2);
}

bool ReadyQueue::even(int x) {
  if((x%2) == 0) return true; else return false;
}

void ReadyQueue::reheapify(){
  int x = 0;
  Q[0] = Q[count-1];
  count--;
	trickledown();

}

int ReadyQueue::getSmallerchild(int x) {
  if( Q[2*x+2].getPrio() > Q[2*x+1].getPrio()) {
    return (2*x+1);
  }
  return (2*x+2);
}
