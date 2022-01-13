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
	//declare process variables for pulliing from file
  int timequantum = 10;
  string processname = "";
  int prio = 0;
  int burstime = 0;
  string number;
  Process newProc;
  string str;
	//create vector for storing processes
  vector<Process> processes;
	//vector for holding processes after RR Scheduling
	vector<Process> RRprocesses;

	//pulls process information from file and stores in processes vector
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

    processes.push_back(newProc);\
	}

	//propmt the user for Time Quantum and store in int tq
	int tq;
	cout << "Please input the time quantum for Round Robin Scheduling: ";
	cin>>tq;

	//sort processes by priority before Round Robin Scheduling
	for(int i = 0; i < processes.size(); i++) {
      int high = processes[i].priority;
      int pos = i;

			//swaps processes in vector when next process has higher priority
      for(int j = i+1; j < processes.size(); j++) {
        if(processes[j].priority > processes[i].priority){
          high = processes[j].priority;
          pos = j;
        }
      }
      Process temp = processes[i];
      processes[i] = processes[pos];
      processes[pos] = temp;
    }
		
		//RR Scheduling implementation
		//loops through processes vector until it is empty
		while(!processes.empty()){

			for(int k = 0; k < processes.size(); k++){
				//checks if current process meets TQ requirement
				if (processes[k].time <= tq){
					//store current Process in newProc
					newProc.ProcessName = processes[k].ProcessName;
					newProc.time = processes[k].time;
					newProc.priority = processes[k].priority;

					//insert newProc into RRprocesses and remove process from processes vector
					RRprocesses.insert(RRprocesses.begin(), newProc);
					processes.erase(processes.begin());
					k--;

				}
				//if burst time is greater than TQ else runs
				else{
					//store current process into new Proc with udjusted burst time
					newProc.ProcessName = processes[k].ProcessName;
					newProc.time = tq;
					newProc.priority = processes[k].priority;

					//insert newProc into RRprocesses
					RRprocesses.insert(RRprocesses.begin(), newProc);

					//adjust remaining burst time for current process in processes vector
					processes[k].time = processes[k].time - tq;

				}
				
			}
		}

		float waiting = 0;
  	float turnaround = 0;

		//outputs Round Robin Scheduled processes and displayes turnaround and waiting times at each process
  	for(int i = 0; i < RRprocesses.size(); i++) {
    	turnaround = turnaround + RRprocesses[i].time;
    	if (i > 0) {
     		waiting = waiting + RRprocesses[i-1].time;
    	}
    	cout << "Process: " << RRprocesses[i].ProcessName << " Priority: " << RRprocesses[i].priority << " Time: " << RRprocesses[i].time << endl;
    	RRprocesses[i].turnaround = turnaround;
    	RRprocesses[i].waiting = waiting;
  	}
  	for(int i = 0; i < RRprocesses.size(); i++) {
    	cout << RRprocesses[i].ProcessName << " Turnaround Time: " << RRprocesses[i].turnaround << " Waiting Time: " << RRprocesses[i].waiting << endl;
  	}
    cout << endl;
    cout<< "Average turn arround time ="<< turnaround/RRprocesses.size() <<","<< "Average waiting time = "<<waiting/RRprocesses.size()<<endl;
	


}