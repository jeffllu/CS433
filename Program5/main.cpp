#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include "pagetable.h"
#include <string>
#include <chrono>
#include <algorithm> 
#include <iterator> 
using namespace std;
 
// Check if an integer is power of 2
bool isPowerOfTwo(unsigned int x)
{
	/* First x in the below expression is for the case when x is 0 */
	return x && (!(x & (x - 1)));
}

int main(int argc, char* argv[]) {
	//Print basic information about the program
	std::cout << "=================================================================" << std::endl;
	std::cout << "CS 433 Programming assignment 5" << std::endl;
	std::cout << "Date: xx/xx/20xx" << std::endl;
	std::cout << "Course: CS433 (Operating Systems)" << std::endl;
	std::cout << "Description : Program to simulate different page replacement algorithms" << std::endl;
	std::cout << "=================================================================\n" << std::endl;

	if (argc < 3) {
		// user does not enter enough parameters
		std::cout << "You have entered too few parameters to run the program.  You must enter" << std::endl
			<< "two command-line arguments:" << std::endl
			<< " - page size (in bytes): between 256 and 8192, inclusive" << std::endl
			<< " - physical memory size (in megabytes): between 4 and 64, inclusive" << std::endl;
		exit(1);
	}
	
	// Page size and Physical memory size 
	// Their values should be read from command-line arguments, and always a power of 2
	unsigned int page_size = atoi(argv[1]);
	if(!isPowerOfTwo(page_size))
	{
		std::cout << "You have entered an invalid parameter for page size (bytes)" << std::endl
			<< "  (must be an power of 2 between 256 and 8192, inclusive)." << std::endl;
		return 1;
	}
	unsigned int phys_mem_size = atoi(argv[2]) << 20; // convert from MB to bytes
	if(!isPowerOfTwo(phys_mem_size))
	{
		std::cout << "You have entered an invalid parameter for physical memory size (MB)" << std::endl
			<< "  (must be an even integer between 4 and 64, inclusive)." << std::endl;
		return 1;
	}

	// calculate number of pages and frames;
	int logic_mem_bits = 27;		// 27-bit logical memory (128 MB logical memory assumed by the assignment)
	int phys_mem_bits = std::log2(phys_mem_size);		// Num of bits for physical memory addresses, calculated from physical memory size, e.g. 24 bits for 16 MB memory
	int page_offset_bits = std::log2(page_size);				// Num of bits for page offset, calculated from page size, e.g. 12 bits for 4096 byte page
	// Number of pages in logical memory = 2^(logic_mem_bits - page_bit)
	int num_pages = 1 << (logic_mem_bits - page_offset_bits);
	// Number of free frames in physical memory = 2^(phys_mem_bits - page_offset_bits)
	int num_frames = 1 << (phys_mem_bits - page_offset_bits);
	
	std::cout << "Page size = " << page_size << " bytes" << std::endl;
	std::cout << "Physical Memory size = " << phys_mem_size << " bytes" << std::endl;
	std::cout << "Number of pages = " << num_pages << std::endl; 
	std::cout << "Number of physical frames = " << num_frames << std::endl;

	// Test 1: Read and simulate the small list of logical addresses from the input file "small_refs.txt"
	std::cout <<"\n================================Test 1=============================================\n";
	// TODO: Add your code here for test 1 that prints out logical page #, frame # and whether page fault for each logical address
  int page,counter,address,isfault,frame,fault_num;
  int arr[100]; //array to hold page numbers
  counter = 0;
  isfault = 0;
  fault_num = 0;
  //PageEntry* victim;
  std::vector<PageEntry*> table;
  std::vector<PageEntry*>::iterator i;
  std::fstream file("small_refs.txt");
  int r = 0;
  int currFrame = 0;
  int second[400000];
  while (file >> address) //repeatedly grap addresses from small_refs
  { 
    counter++; //counter for references
    page = (int) address/page_size; //calculate page
    PageTable tablet(num_pages);
    bool exists = find(begin(arr), end(arr), page) != end(arr);
    if(exists == true) {//see if page already exists
      isfault = 0; //if it already exists then there isn't a page fault
    } else {
      isfault = 1; //otherwise there is a page fault
      fault_num++; //increase fault count
      second[page] = currFrame;  
      currFrame++;
      if(tablet.total < tablet.used) { //if there are still frames
        tablet.paging[page].frame_num = tablet.total;
        tablet.total++; 
      }
      if(tablet.total > tablet.used) { //no more frames so replacement would be needed
          r++;
      }
    }
    arr[counter] = page; //append page into the array
    PageEntry p; 
    table.push_back(&p);  
    frame++; 
    std::cout << "Logical address:" << address << "pagenumber:" << page << "frame number:" << second[page] <<"page fault:" << isfault << std::endl;
  }     
   
  std:: cout<<"References: "<<counter<<endl; 
  cout << "Faults: " << fault_num << endl;
  cout << "Replacements: " << r << endl;
	
 
  
	file.close();
  
	int pNumber;
	// Test 2: Read and simulate the large list of logical addresses from the input file "large_refs.txt"
  int addr;
  
	std::cout <<"\n================================Test 2==================================================\n";
	//FOR SIMULATING FIFO REPLACEMENT
	cout << "************Simulate FIFO Replacement************" << endl;
	auto start = chrono::steady_clock::now();//keep track of time
  ifstream fin;
	fin.open("large_refs.txt");//open large_refs
	PageTable newPage(num_pages); //create new table with size of number of pages
	newPage.used = num_frames; 
	vector<int> v; //vector to hold page numbers
		fin >> addr; //getting address
		while(fin){
		pNumber = addr/page_size; //calculate page number
		if(newPage.paging[pNumber].frame_num == -1) 
			{//-1 means a page fault has occured
			newPage.paging[pNumber].pagefault = true;//set fault to true
			newPage.faults++; //increment faults
      if(newPage.total < newPage.used) { //if there are still pages then save address
        newPage.paging[pNumber].frame_num = newPage.total;
        newPage.total++;
        v.push_back(pNumber);
      }
      else{ //replace pages because there aren't any spares
        int frameLocation = v[0]; 
				v.erase(v.begin()); //erase at beginning
				int freeFrame = newPage.paging[frameLocation].frame_num;
        newPage.paging[frameLocation].frame_num = -1;
        newPage.paging[pNumber].frame_num = freeFrame;
				v.push_back(pNumber);
				newPage.replacements++;
      }
		}
		else{
			newPage.paging[pNumber].pagefault = false; //no page fault
		}
		newPage.references++; //get new address and increase references
		fin >> addr;
	}
	fin.close(); 
  
  auto end = chrono::steady_clock::now();
  double elapsed_time_ns = double(chrono::duration_cast <chrono::nanoseconds> (end-start).count()); 
  cout << "Number of references: " << newPage.references << endl;
	cout << "Number of page faults: " << newPage.faults << endl;
	cout << "Number of page replacements: " << newPage.replacements << endl;
  cout << "Elapsed time = " << elapsed_time_ns/1e9 << " seconds" << endl;

	//FOR SIMULATING RANDOM REPLACEMENT
	cout << "************Simulate Random Replacement************" << endl;
  auto start2 = chrono::steady_clock::now();//keep track of time
	ifstream fin2;
	fin2.open("large_refs.txt"); //open large_refs
  PageTable newPage2(num_pages); //create new table with size of number of pages
	newPage2.used = num_frames; 
  vector<int> v2;  //vector to hold page numbers
		fin2 >> addr; //getting address
		while(fin2) 
		{
		pNumber = addr/page_size; //calculate page number
		if(newPage2.paging[pNumber].frame_num == -1)
      {//-1 means a page fault has occured
			newPage2.paging[pNumber].pagefault = true;//set fault to true
			newPage2.faults++;//increment faults
      if(newPage2.total < newPage2.used) {//if there are still pages then save address 
        newPage2.paging[pNumber].frame_num = newPage2.total;
        newPage2.total++; 
        v2.push_back(pNumber); 
      } 
			else{//replace pages because there aren't any spares
				int max = newPage2.total;
        srand(time(NULL)); //create random number
				int randNum = rand()%max;  
				int frameLocation = v2[randNum];
				v2.erase(v2.begin() + randNum); //erase at the randomly selected area
				int freeFrame = newPage2.paging[frameLocation].frame_num;
        newPage2.paging[frameLocation].frame_num = -1;
				newPage2.paging[pNumber].frame_num = freeFrame;
				v2.push_back(pNumber); 
				newPage2.replacements++; 
			}
		}
		else{
			newPage2.paging[pNumber].pagefault = false; //no page fault
		}
		newPage2.references++;//get new address and increase references
		fin2 >> addr;
	}
	fin2.close(); 
  auto end2 = chrono::steady_clock::now(); //get time again
  double elapsed_time_ns2 = double(chrono::duration_cast <chrono::nanoseconds> (end2-start2).count()); //calculate time
  
	cout << "Number of references: " << newPage2.references << endl;
	cout << "Number of page faults: " << newPage2.faults << endl;
	cout << "Number of page replacements: " << newPage2.replacements << endl;
  cout << "Elapsed time = " << elapsed_time_ns2/1e9 << " seconds" << endl;

	//FOR SIMULATION LRU REPLACEMENT
	cout << "************Simulate LRU Replacement************" << endl;
  auto starttt = chrono::steady_clock::now(); //get time
  ifstream fin3;
	fin3.open("large_refs.txt"); //open large refs
	PageTable newPage3(num_pages);//create new table with size of number of pages
	newPage3.used = num_frames; 
	vector<int> v3;//vector to hold page numbers
  int x = 0;
		fin3 >> addr;
		while(fin3)//getting address
		{
		pNumber = addr/page_size;//calculate page number
		if(newPage3.paging[pNumber].frame_num == -1){//-1 means a page fault has occured
			newPage3.paging[pNumber].pagefault = true;//set fault to true
			newPage3.faults++;//increment faults
      if(newPage3.total < newPage3.used) {//if there are still pages then save address
        newPage3.paging[pNumber].frame_num = newPage3.total;
        newPage3.total++;
        v3.push_back(pNumber);
      }
      else {//replace pages because there aren't any spares
        x = v3.size() - 1; //this is probably wrong, but this is attempt to find least recently used by fetching the last element in vector
        int frameLocation = v3[x];
				v3.erase(v3.begin() + x);  //delete at least recently used
				int freeFrame = newPage3.paging[frameLocation].frame_num;
        newPage3.paging[frameLocation].frame_num = -1;
				newPage3.paging[pNumber].frame_num = freeFrame;
				v3.push_back(pNumber);
				newPage3.replacements++;
       }  
		}
		else{
			newPage3.paging[pNumber].pagefault = false; //no page fault
		}
		newPage3.references++; //get new address and increase references
		fin3 >> addr; 
		}
	fin3.close(); 
  auto enddd = chrono::steady_clock::now();//timestamp
  double elapsed_time_nsss = double(chrono::duration_cast <chrono::nanoseconds> (enddd-starttt).count());//calculate elapsed time
  cout << "Number of references: " << newPage3.references << endl;
	cout << "Number of page faults: " << newPage3.faults << endl;
	cout << "Number of page replacements: " << newPage3.replacements << endl;
  cout << "Elapsed time = " << elapsed_time_nsss/1e9 << " seconds" << endl;

	return 0;
}