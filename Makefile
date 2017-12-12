CC = gcc
CFLAGS = -g -Wall
LDFLAGS = -lm -lSDL -lSDL_image

all: GNUdelbrot

GNUdelbrot: display.o complex.o menu.o main.o
	$(CC) $(CFLAGS) display.o complex.o menu.o main.o -o GNUdelbrot $(LDFLAGS)
	
main.o: main.c const.h
	$(CC) $(CFLAGS) -c main.c
	
display.o: display.c display.h
	$(CC) $(CFLAGS) -c display.c
	
complex.o: complex.c complex.h
	$(CC) $(CFLAGS) -c complex.c
	
menu.o: menu.c menu.h
	$(CC) $(CFLAGS) -c menu.c
	
clean:
	rm -f *.o *~ GNUdelbrot
