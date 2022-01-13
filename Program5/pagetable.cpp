#include <iostream>
#include <vector>
#include <ctime>
#include "pagetable.h"


// TODO: Add your implementation of PageTable
bool PageEntry::isValid()
 {
   return valid;
 }

 bool PageEntry::isDirty()
 {
   return dirty;
 }
 int PageEntry::getAddress()
 {
   return address;
 }

 int PageEntry::getFrame()
 {
   return frame_num;
 }


PageTable::PageTable()
{
  int size;
  int counter;
  std::vector<PageEntry*> table;  
}


PageTable::PageTable(int size)
{ 
  paging = new PageEntry[size]; 
}

 int PageTable::getSize()
 {
   return size;
 }

 void PageTable::Check()
 {
   
   for (int i = 0;i< size; i++)
   {
     std::cout<<"table"<< &table<<std::endl;
   } 
 }
    