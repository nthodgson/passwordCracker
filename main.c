#include "global.h"
#include "producer.h" 
#include "consumer.h"

// Programmer: Nathan Hodgson
// Program: main.c

int main (int args, char** arg) {
	char buffer[50], word[50];
	strcpy(word, "oil");
	strcpy(buffer, "oi18");
	char outputName[50], inputName[50];
	struct globalBuffer buffer_t;
	buffer_t.occupied = 1;
	buffer_t.nextin = 0;
	buffer_t.nextout = 0;
	buffer_t.foundPass = false;

	if (args != 5) {
		printf("Incorrect number of command line arguments. Terminating...\n");
		exit(1);
	}
	if ((pthread_mutex_init(&lock, NULL) != 0) || (pthread_cond_init(&less, NULL) != 0) || (pthread_cond_init(&more, NULL) != 0)) {
		printf("Pthread initialization has failed...\n");
		exit(1);
	}
	for (int i=0; i<10000; i++) {
		buffer_t.buf[i] = (char*)malloc(strlen(word) * sizeof(char));
	}

	strcpy(buffer_t.dictName, arg[1]);
	strcpy(inputName, arg[2]);
	strcpy(outputName, arg[3]);
	int numThreads = atoi(arg[4]);

	readHash(inputName, &buffer_t);

	// Producer and consumer thread creation

	pthread_t tid[numThreads+1];
	pthread_create(&tid[0], NULL, readFile, (void*)&buffer_t); // Producer

	for (int i=1; i<numThreads+1; i++)
		pthread_create(&tid[i], NULL, getWord, (void*)&buffer_t); // Consumers

	for (int i=0; i<numThreads+1; i++) {
		if (pthread_join(tid[i], NULL))
			printf("ERROR ON TID: %ld\n", tid[i]);
	}

	pthread_mutex_destroy(&lock); // Destroy thread mutex
	pthread_exit(NULL);

	return 0;
}