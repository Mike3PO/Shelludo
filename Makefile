CC = gcc
CFLAGS = -lreadline

all: shelludo

shelludo: shelludo.o
	$(CC) -o shelludo shelludo.o $(CFLAGS)

shelludo.o: shelludo.c shelludo-helper.h man-helper.h
	$(CC) -c shelludo.c

clean:
	rm shelludo shelludo.o