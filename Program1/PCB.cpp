#include "PCB.h"
#include <iostream>
#include <fstream>
using namespace std;

void PCB::operator=(const PCB& b){
			this->ID = b.ID;
			this->priority = b.priority;
      this->processState = b.processState;
		}

PCB::PCB(int pid, int prio) {
  this->ID = pid;
  this->priority = prio;
  this->processState = NEW;
}

PCB::PCB(){}

PCB::~PCB(){}

void PCB::setPrio(int prio) {
  priority = prio;
}

void PCB::setID(int pid) {
  ID = pid;
}

void PCB::setState(State procState) {
  processState = procState; 
}

int PCB::getPrio(){
  return priority;
}

State PCB::getState(){
  return processState;
}

int PCB::getID(){
  return ID;
}