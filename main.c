#include "global.h"
#include "producer.h" 
#include "consumer.h"

// Programmer: Nathan Hodgson
// Program: main.c

int main (int args, char** arg) {
	char hash[100], buffer[50], word[50];
	strcpy(word, "oil");
	strcpy(buffer, "oi18");
	char dictName[50], inputName[50], outputName[50];
	struct globalBuffer buffer_t;

	if (args != 5) {
		printf("Incorrect number of command line arguments. Terminating...\n");
		exit(1);
	}

	strcpy(dictName, arg[1]);
	strcpy(inputName, arg[2]);
	strcpy(outputName, arg[3]);
	int consumerThreads = atoi(arg[4]);

	// Thread creation

	readFile(dictName, &buffer_t);
	sha_256_string(hash, buffer, strlen(buffer));
	getWord(word, hash);

	return 0;
}