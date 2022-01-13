###################################
# OS COURSE - CS 433 example
# 
###################################
CC = g++			# use g++ for compiling c++ code or gcc for c code
CFLAGS = -g -Wall 		# -std=c++11 compilation flags: -g for debugging. Change to -O or -O2 for optimized code.
LIB = -lm			# linked libraries	
LDFLAGS = -L.			# link flags
PROG = sjf fcfs rr priority 		# target executables (output)
SRCS = fcfs.cpp roundrobin.cpp sjf.cpp priority.cpp  \
     process.cpp # .c or .cpp source files.
OBJ = $(SRCS:.cpp=.o) 	# object files for the target. Add more to this and next lines if there are more than one source files.

all : $(PROG) depend

fcfs: fcfs.o process.o
	$(CC) -o fcfs fcfs.o process.o $(LDFLAGS) $(LIB)

rr: roundrobin.o process.o
	$(CC) -o rr roundrobin.o process.o $(LDFLAGS) $(LIB)

sjf: sjf.o process.o
	$(CC) -o sjf sjf.o process.o $(LDFLAGS) $(LIB)

priority: priority.o process.o
	$(CC) -o priority priority.o process.o $(LDFLAGS) $(LIB)

.cpp.o:
	$(CC) -c $(CFLAGS) $< -o $@
	
depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CC) $(CFLAGS) -MM $^ > ./.depend;

include .depend

# cleanup
clean:
	/bin/rm -f *.o $(PROG) .depend

# DO NOT DELETE
