#include "global.h"
#include "producer.h" 
#include "consumer.h"

// Programmer: Nathan Hodgson
// Program: main.c

int main (int args, char** arg) {
	char hash[100], buffer[50], word[50];
	strcpy(word, "oil");
	strcpy(buffer, "oi18");
	char inputName[50], outputName[50];
	struct globalBuffer buffer_t;

	if (args != 5) {
		printf("Incorrect number of command line arguments. Terminating...\n");
		exit(1);
	}
	if (pthread_mutex_init(&lock, NULL) != 0) {
		printf("Mutex init has failed...\n");
		exit(1);
	}
	for (int i=0; i<10000; i++) {
		buffer_t.buf[i] = (char*)malloc(strlen(word) * sizeof(char));
	}

	strcpy(buffer_t.dictName, arg[1]);
	strcpy(inputName, arg[2]);
	strcpy(outputName, arg[3]);
	int numThreads = atoi(arg[4]);

	// Producer thread creation

	pthread_t tid[numThreads+1];
	pthread_create(&tid[0], NULL, readFile, (void*)&buffer_t);

	sha_256_string(hash, buffer, strlen(buffer));
	checkWord(word, hash);

	return 0;
}