#THIS IS THE MAKEFILE

EXECS = assemble

#### use next two lines for Mac
CC = g++
CCFLAGS	 = -std=c++17 

#### use next two lines for mathcs* machines:
#CC = g++
#CCFLAGS = -std=c++17

all: $(EXECS)

assemble: $(OBJS) project1.o
	$(CC) $(CCFLAGS) $^ -o $@

project1.o: project1.cpp project1.h
	$(CC) $(CCFLAGS) -c project1.cpp 

clean:
	/bin/rm -f a.out $(OBJS) project1.o $(EXECS)
