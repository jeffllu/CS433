#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <bits/stdc++.h>
#include <vector>
#include <iostream>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
//#include <cstring>

using namespace std;
#define MAX_LINE 80 /* The maximum length command */

class Shell
{  
  public:
  void parse(char input[], char* args[]);
  void saveCommand(char args[]);
  void execCommand(char* args[]);
  void checkCommand(char priorCommand[], char* args[], char input[]);
  vector <string> recents;  
  //char** args;
  //int i;

  int getIp_Redirection();
  void setIp_Redirection(int ip);  
  int getOp_Redirection();
  void setOp_Redirection(int op);  
  bool getAmpersand();
  void setAmpersand(bool amp); 
  int getShould_run();
  void setShould_run(int run); 
  
  Shell();
  ~Shell(); 
  
  private:
  bool ampersand;
  int should_run;   
  int i;
  int ip;
  int op;
  
};

void Shell::parse(char input[], char* args[])
{  
 //parsing        
        const char* key = " ";
        char* token = strtok(input,key);
        i = 0;
        //adding token to args and wont stop until there is not more
        do
        {
          //saves command in array
            args[i] = token;
            token = strtok(NULL, " ");
            i++;//increments   
        }while (token != NULL); 
              
 }
 

void Shell::checkCommand(char priorCommand[], char* args[], char input[])
{  
   //check if there is only 1 token
   ip = 0;
   op = 0;
   
            if (i == 1)
            {
              args[i]= NULL;
            }
            else
            {//checks for & turn on the ampersand flag to 1               
              if(strcmp(args[i-1], "&")==0)
                {                
                  setAmpersand(true);
                  args[i-1] = NULL;                           
                }
                //checks for > if is true then out = 1            
                else if (strcmp(args[i-2], ">")==0) 
                {
                  args[i-2] = NULL;
                  setOp_Redirection(1);                 
                }
                //ehck for < is true then in  = 1
                else if (strcmp(args[i-2],"<")==0) 
                {
                  args[i-2] = NULL;
                  setIp_Redirection(1);                 
                }
                //otherwise that position in null
                else 
                args[i] = NULL;        
            }
            //checking for exit token
          if (strcmp(args[0],"exit")== 0)
          {
            setShould_run(0);
            cout<< "the program should_run is: "<<getShould_run()<<endl;
            cout<<"Program terminated"<<endl;
            exit(0);
            
          }
          //command to display history token
          else if(strcmp(args[0],"history") == 0)
          {
            if (recents.empty())
            cout <<"History is empty"<<endl;
            else{
              int count = 0;
              int len = recents.size();
              for (int n=0; n < len; n++ ) 
              {
                count++;                    
                cout <<count<< " "<< recents[n] << endl;
              }
            }                
          }
          // for special characters !!
          else if (strcmp(args[0],"!!") == 0)
          {//check for empty vector
            bool check = recents.empty();
            if (check)
            //prints message
            cout <<"No commands available"<<endl;
            else
            {
              saveCommand(*args);              
             // for (int j = 0; j< 5;j++)
             // {
             //   cout<<"Prior Command is "<< priorCommand[j]<<endl;
             // }

            //prints last element in the vector 
            cout<<"Last command: "<<priorCommand <<endl;            
              parse(priorCommand, args);                   
            }          
          
          }  
          else
          {
            /*int k = 0;            
             do
              {
                //copy array
                priorCommand[k]=input[k];
                k++;//increments                
              }while (k < 6);  */
              strcpy(priorCommand, args[0]);           
                        
             saveCommand(*args);
          }
          
          
}
void Shell::saveCommand(char args[])
{//store command into a vector
   recents.push_back(args);  
}

void Shell::execCommand( char* args[])
{     
  //new pid  
  pid_t  pid;
//creates a fork
  pid = fork();
  int fd;   

//cout << "My PID is: "<< pid << endl;   
  
  if (pid < 0)
  {//error ocurred
    cout <<"Fork Failed"<<endl;
  }
  if (pid == 0)
  {//child process
    // check for redirection is ">"
    if (op == 1)
    
    {
      //creates a next file
      if((fd = open(args[i-1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR) >0))
      {   
        //cout<<"[output]FD is: "<< fd<<endl;       
        fd = open(args[i-1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
        dup2(fd, 1);
        close(fd);
      }
    }
     // check for redirection is ">"
    if (ip == 1 )
    {//check if there is a file with the token stored in args[i-1]
     //value is -1 then prints message
      if ( (fd = open(args[i-1],O_RDONLY) == -1))
        {
        printf("Cannot open %s does not exits\n", args[i-1]);            
        }
        else 
        {
        //display the contentent sorted
        fd = open(args[i-1],O_RDONLY);
        //cout<<"[input]FD is: "<< fd<<endl; 
        dup2(fd, 0);
        close(fd);
        }
    }         
      execvp(args[0], args);     
  }
  else
  {//parent process
    //check for ampersand is false     
    if (getAmpersand() == false)
    {
      //parent process wait
    wait(NULL);
    }     

  }
}
int Shell::getOp_Redirection() 
{
return op;
}
void Shell::setOp_Redirection(int flag)
{
  op = flag;
}
int Shell::getIp_Redirection() 
{
return op;
}
void Shell::setIp_Redirection(int flag)
{
  ip = flag;
}

bool Shell::getAmpersand()
{
  return ampersand;
}

void Shell::setAmpersand(bool amp)
{
  ampersand = amp;
}
int Shell::getShould_run()
{
  return should_run;
}

void Shell::setShould_run(int run)
{
  should_run = run;
}

// Default constructor for shell.  
Shell::Shell()
{  
	ampersand = false;
  ip = 0;
  op = 0;
  
  should_run = 1;
}
Shell::~Shell(){}

int main(void)
{
  
  cout << "Assigment 2" << endl;
	cout << "Author: Miguel Morales,Jeffrey Lu and Jeffrey Melton" << endl;
	cout << "Date: 10/10/2021" << endl;
	cout << "Course: CS433 " << endl;
	cout << "Description : Writing a simple shell" << endl;
	cout << "=============================================" << endl;
  
 
  //int should_run = 1; // flag to determine when to exit program 
  //char priorCommand [MAX_LINE];
  char priorCommand [MAX_LINE/2+1]; 
  char input [MAX_LINE/2+1];
  vector <string> recents; 
  char* args [MAX_LINE/2+1];
  
  Shell s;
    
  while (s.getShould_run() == 1)
  {//system prompt
        
    cout <<("osh>");
    fflush(stdout);                
    //read the line and place it in the input variable      
     
        //input[MAX_LINE/2+1] = {0};
        cin.getline(input, MAX_LINE);        
        //parsing     
        s.parse(input, args);  
        //Checking if the user input a user command
        s.checkCommand(priorCommand, args, input);
        //executes the commands      
        s.execCommand(args);
  
  }
    
  return 0;
}