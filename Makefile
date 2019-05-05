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
	rm -f *o pc output.txt

# Execution commands for testing:

runSmall:
	./pc smallDict.txt input.txt output.txt 5

runTiny:
	./pc tinyDict.txt input.txt output.txt 5

runMed:
	./pc medDict.txt input.txt output.txt 5

runFull:
	./pc fullDict.txt input.txt output.txt 5

valSmall:
	valgrind ./pc smallDict.txt input.txt output.txt 5

valFull:
	valgrind ./pc fullDict.txt input.txt output.txt 5

gdbSmall:
	gdb ./pc smallDict.txt input.txt output.txt 5

gdbFull:
	gdb ./pc fullDict.txt input.txt output.txt 5
