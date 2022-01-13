#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Process{
  public:
    Process();
    string ProcessName;
    int time;
    int priority;
    int waiting;
    int turnaround;    
};