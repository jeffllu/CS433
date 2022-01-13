#include <iostream>
#include <fstream>
#include "PCB.h"
using namespace std;

int const MAX = 100;

class ReadyQueue{
  private: 
    PCB Q[MAX];
    int count;

    void swap(int x, int y);
    void reheapify(); //
    int getSmallerchild(int x);
    void trickleup(); //heapsort
    void trickledown();
    int getParent(int childloc);
    bool even(int x);

  public:
    ReadyQueue();
    ~ReadyQueue();
    void addPCB(PCB x);
    void removePCB();
    int size();
    void display();

};