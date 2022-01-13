#include <stdlib.h> /* required for rand_r(...) */
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <unistd.h>
#include<iostream>
#include "buffer.h" //buffer

buffer_item buffer[BUFFER_SIZE];
int in = 0;
int out = 0;
int counter;//counter

int insert_item(buffer_item item);//insert method
int remove_item(buffer_item *item);// remove method
void *producer(void *param); //manage producer thread
void *consumer(void *param);  //manage consumer thread

pthread_mutex_t mutex;//create mutex lock
sem_t empty;//create semaphore
sem_t full;//create semaphore

pthread_attr_t attr;// Thread attribute

int insert_item(buffer_item item) {
/* insert item into buffer return 0 if successful, otherwise
return -1 indicating an error condition */

//TODO: handle if array is empty
  if (counter < BUFFER_SIZE)
  {    
    buffer[in] = item;
    in = (in+1) % BUFFER_SIZE;
    counter++;
   std::cout<<"item: " << item <<" inserted by a producer \n";
    return 0;
  }
  else
  {
    std::cout<<"Error on inserting \n"<<std::endl;
    return -1;
  }
}

int remove_item(buffer_item *item) {
/* remove an object from buffer placing it in item
return 0 if successful, otherwise return -1 indicating an error condition */

//TODO handle if array if empty
if(counter > 0)
{
  *item = buffer[out];
  out = (out+1)%BUFFER_SIZE;  
  counter--; //counter decreases
  std::cout<<"item: "<<*item <<" removed by consumer" <<std::endl;
  return 0;
  }
  else
  {
    std::cout<<"Error on removing"<<std::endl;
    return -1;
  }
}
void display()
{
  int k = 0;
	std::cout << "The current content of the buffer is [ ";
  //checks the buffer to print out elements inside
	for (int i = out; k < counter; i = (i + 1) % BUFFER_SIZE ) 
  {
		std::cout << buffer[i] << " ";
    k++;
  }
    std::cout << "]"<<std::endl;
  
}
void *producer(void *param)
{
  int t= 0;
 
  buffer_item item;
  while (true) 
  {
      /* sleep for a random period of time */
      t = rand()% 5;
      usleep(t);
      /* generate a random number */
      item = rand() % 100;
      //insert item to the buffer
      sem_wait(&empty);                   //decrements empty semaphore if empty > 0
      pthread_mutex_lock(&mutex);         //acquires mutex lock
    
      if (insert_item(item))
      {
        std::cout<<("report error condition on producer/inserting \n");
      }
      else
      {
      display();
      }
      pthread_mutex_unlock(&mutex);       //releases mutex lock
      sem_post(&full);
      
    }
}

void *consumer(void *param)
{
  buffer_item item;
  while (true)
  {
    /* sleep for a random period of time */
    int t = rand()%5;
    usleep(t);
    //Block on a semaphore count
    sem_wait(&full);                   //adquiere semaphores
    pthread_mutex_lock(&mutex);         //acquires mutex lock


    if (remove_item(&item))
    {      
    std::cout<<"report error condition on removing/consumer"<<std::endl;
    }
    else
    {
      display();//go through the buffer and prints
      
    }
      pthread_mutex_unlock(&mutex); //release mutex lock
      sem_post(&empty);  
    
  }
}

int main(int argc, char *argv[]) {
std::cout << "Course: CS433 (Operating Systems)" << std::endl;
std::cout << "Description : Producer-Consumer problem" << std::endl;
std::cout << "=================================================================\n" ;
/* 1. Get command line arguments argv[1],argv[2],argv[3] */
int sleep = atoi(argv[1]);
int produce = atoi(argv[2]);
int consume = atoi(argv[3]);
/* 2. Initialize buffer */
pthread_mutex_init(&mutex, NULL);         //initializes mutex
/*create semaphores*/
sem_init(&full, 0, 0);			            	// full initialized to 0
sem_init(&empty, 0, BUFFER_SIZE);			  	// empty initialized to 0

/* 3. Create producer thread(s) */
pthread_t pTID [produce];
for (int i = 0; i < produce; i++)
{
  pthread_attr_init(&attr);
  pthread_create(&pTID[i], &attr, producer, NULL);  
}
/* 4. Create consumer thread(s) */
pthread_t cTID [consume];
for (int i = 0; i < consume; i++)
{
  pthread_attr_init(&attr);
	pthread_create(&cTID[i], &attr, consumer, NULL);
}
/* 5. Sleep */
usleep(sleep);
/* 6. Exit */
exit(0);
}