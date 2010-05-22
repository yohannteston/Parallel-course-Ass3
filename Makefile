CC	= gcc   
CC2	= /opt/SUNWspro-12u1/bin/cc
CFLAGS    =  -O3 -fopenmp  
CFLAGS2 = -O3 -xopenmp  
LIBS 	= -lm

all: gram_schmidt gram_schmidt_task

gram_schmidt: gram_schmidt.c
	$(CC) $(CFLAGS) -o gram_schmidt gram_schmidt.c $(LIBS)

gram_schmidt_task: gram_schmidt_task.c
	$(CC) $(CFLAGS) -o gram_schmidt_task gram_schmidt_task.c $(LIBS)

clean: 
	rm -f *.o *~ gram_schmidt gram_schmidt_task
