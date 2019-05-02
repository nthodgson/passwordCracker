# This target compiles the program.
CFLAGS=-c -Wall -g

all: pc

pc: main.o producer.o consumer.o
	gcc main.o producer.o consumer.o sha-256.c -lpthread -o pc

main.o: main.c
	gcc $(CFLAGS) main.c

producer.o: producer.c
	gcc $(CFLAGS) producer.c

consumer.o: consumer.c
	gcc $(CFLAGS) consumer.c

clean: 
	rm -f *o pc

# Default execution command for testing:

runSmall:
	./pc smallDict.txt input.txt output.txt 5

