#include "process.h"
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
using namespace std;

int main() {
  cout << "CS433 Assignment 3" << endl;
  cout << "Authors: Jeff Lu, Jeff Melton and Miguel Morales" << endl;
  cout << "Program starts here" << endl;
	
	//locate file
  ifstream fin;
	string s;
	cout << "please input file name: ";
	cin>> s;
	fin.open(s);
	 //initializing process variables for pulling from file
  int timequantum = 10;
  string processname = "";
  int prio = 0;
  int burstime = 0;
  string number;
  Process newProc;
  string str;
	//vector for containing all processes
  vector<Process> processes;

	//pulls information about processes from file and inserts into processes vector
  while(getline(fin, str)) {
    istringstream newstr(str);
    getline(newstr, processname, ',');
    getline(newstr, number, ',');
    prio = stoi(number);
		newProc.ProcessName = processname;
    newProc.priority = prio;
    getline(newstr, number, ',');
    burstime = stoi(number);
    newProc.time = burstime;
    cout << processname << " " << prio << " " << burstime << endl;

    processes.push_back(newProc);
  }
		//begining of sjf sort
    for(int i = 0; i < processes.size(); i++) {
      int high = processes[i].time;
      int pos = i;
		// checks if next process is smaller and swaps processes if so
      for(int j = i+1; j < processes.size(); j++) {
        if(processes[j].time < processes[i].time){
          high = processes[j].time;
          pos = j;
        }
      }
      Process temp = processes[i];
      processes[i] = processes[pos];
      processes[pos] = temp;
  }
  
  float waiting = 0;
  float turnaround = 0;

	//outputs sjf Scheduled processes and displayes turnaround and waiting times at each process
  for(int i = 0; i < processes.size(); i++) {
    	turnaround = turnaround + processes[i].time;
    	if (i > 0) {
     		waiting = waiting + processes[i-1].time;
    	}
    	cout << "Process: " << processes[i].ProcessName << " Priority: " << processes[i].priority << " Time: " << processes[i].time << endl;
    	processes[i].turnaround = turnaround;
    	processes[i].waiting = waiting;
  	}
  	for(int i = 0; i < processes.size(); i++) {
    	cout << processes[i].ProcessName << " Turnaround Time: " << processes[i].turnaround << " Waiting Time: " << processes[i].waiting << endl;
  	}
    cout << endl;
    cout<< "Average turn arround time ="<< turnaround/processes.size() <<","<< "Average waiting time = "<<waiting/processes.size()<<endl;
  cout << endl;
}