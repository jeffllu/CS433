#include <iostream>
#pragma once

// Remember to add comments to your code

// A page table entry
class PageEntry
{
public:
  int address=0;
	// Physical frame number for a given page
	int frame_num=-1;
	// valid bit represents whether a page is in the physical memory
	bool valid=false;
	// dirty bit represents whether a page is changed
	bool dirty=false;
  bool pagefault=false;
  //constructor
  //PageEntry(address);
  int getFrame();
  int getAddress();
  bool isValid();
  bool isDirty();
};


/**
 * \brief A page table is like an array of page entries. The size of the page table should equal to the number of pages in logical memory
 */
class PageTable
{
	// TODO: Add your implementation of the page table here
  int size;
  
  public:
  int total=0;
  int used=0;
  int references=0;
  int faults=0;
  int replacements=0;
  PageEntry* paging;
  int counter;
  std::vector<PageEntry> table;
  PageTable();
  PageTable(int size); 
  int getSize();  
  void Check();
};
