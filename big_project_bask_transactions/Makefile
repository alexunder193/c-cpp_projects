OBJS   = main.o graph.o lookfor.o others.o header.o
SOURCE = main.c graph.c lookfor.c others.c header.c
HEADER = graph.h lookfor.h others.h header.h
OUT    = elegxos
CC     = gcc
FLAGS  = -c

all:  $(OBJS)
	$(CC) -o $(OUT)  $(OBJS)

main.o: main.c
	$(CC) $(FLAGS) main.c

graph.o: graph.c
	$(CC) $(FLAGS) graph.c

lookfor.o: lookfor.c
	$(CC) $(FLAGS) lookfor.c

others.o: others.c
	$(CC) $(FLAGS) others.c

header.o: header.c
	$(CC) $(FLAGS) header.c
