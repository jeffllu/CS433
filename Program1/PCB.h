#include <iostream>
#include <fstream>
using namespace std;

enum State{ NEW=1, READY=2, RUNNING=3, WAITING=4, TERMINATED=5 };

class PCB{
  private:
    int ID = 0;
    int priority = 0;
    State processState = NEW;
  public:
    PCB(int pid, int prio);
    PCB();
    ~PCB();
    void setPrio(int prio);
    void setState(State procState);
    void setID(int pid);
    int getPrio();
    State getState();
    int getID();
		void operator=(const PCB& b);
};