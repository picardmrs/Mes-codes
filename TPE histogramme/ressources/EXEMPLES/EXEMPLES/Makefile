CC=gcc
CFLAG=-Wall -pedantic -ansi
INCLUDIR=../MODULE_IMAGE/include/
LIBDIR=../MODULE_IMAGE/

exemple1: exemple1.o
	$(CC) exemple1.o -L$(LIBDIR) -o $@ -limage

exemple1.o:	exemple1.c
	$(CC) $(CFLAG) -I$(INCLUDIR) -c exemple1.c

exemple2: exemple2.o
	$(CC) exemple2.o -L$(LIBDIR) -o $@ -limage

exemple2.o:	exemple2.c
	$(CC) $(CFLAG) -I$(INCLUDIR) -c exemple2.c

exemple3: exemple3.o
	$(CC) exemple3.o -L$(LIBDIR) -o $@ -limage

exemple3.o:	exemple3.c
	$(CC) $(CFLAG) -I$(INCLUDIR) -c exemple3.c

clean:
	rm -f *.o 
