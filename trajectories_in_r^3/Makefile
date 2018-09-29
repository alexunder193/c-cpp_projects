OBJS   = main.o domes.o
SOURCE = main.c domes.c
HEADER = domes.h
OUT    = cluster
CC     = gcc
FLAGS  = -c

all:  $(OBJS)
	$(CC) -o $(OUT)  $(OBJS) -lm

main.o: main.c
	$(CC) $(FLAGS) main.c

domes.o: domes.c
	$(CC) $(FLAGS) domes.c