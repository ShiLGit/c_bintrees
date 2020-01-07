
CC = gcc
CFLAGS = -Wall -ansi -pedantic

all: a3

a3: main.o binary.o common.o main.o name.o principals.o title.o binary.h common.h name.h principals.h title.h
	$(CC) $(CFLAGS) binary.o common.o main.o name.o principals.o title.o -o$@

binary.o: binary.c common.h
	$(CC) $(CFLAGS) -c binary.c -o $@

common.o: common.c
	$(CC) $(CFLAGS) -c common.c -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o$@

name.o: name.c binary.h common.h
	$(CC) $(CFLAGS) -c name.c -o $@

principals.o: principals.c binary.h common.h
	$(CC) $(CFLAGS) -c principals.c -o$@

title.o: title.c binary.h common.h
	$(CC) $(CFLAGS) -c title.c -o$@

clean:
	rm *.o
	
