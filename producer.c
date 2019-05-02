#include "global.h"
#include "producer.h"


// Programmer: Nathan Hodgson
// Program: producer.c

void *readFile(void *buf) {
	struct globalBuffer *ptr = (struct globalBuffer*) buf;
	char* buffer[100];
	int ret = 0, i = 0;
	char dictName[50];
	strcpy(dictName, ptr->dictName);

	for (int i=0; i<100; i++) 
		buffer[i] = (char*)malloc(50 * sizeof(char));

	FILE* infile;
	infile = fopen(dictName, "r");

	if (infile == NULL) {
		printf("Invalid file name... Please try again.\n");
		exit(1);
	}
	else {
		while (fscanf(infile, "%s", buffer[i]) == 1) {
			i++;
			if (i % 100 == 0) {
				writeToBuffer(buffer, &buf);
				i = 0;
			}
		}
	}

	fclose(infile);
}

void *writeToBuffer(char** buffer, void *buf) {
	struct globalBuffer *ptr = (struct globalBuffer*) buf;

	pthread_mutex_lock(&lock);
	
}