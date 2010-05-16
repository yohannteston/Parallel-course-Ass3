CC	= gcc   
CFLAGS    =  -O3 -fopenmp -g 
LIBS 	= -lm

all: gram_schmidt

gram_schmidt:	gram_schmidt.c
	$(CC) $(CFLAGS) -o gram_schmidt gram_schmidt.c $(LIBS)

clean: 
	rm -f *.o *~ gram_schmidt