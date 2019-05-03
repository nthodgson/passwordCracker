#include "global.h"
#include "producer.h"


// Programmer: Nathan Hodgson
// Program: producer.c

/*============================================================
readFile(): This is the driver function for the producer thread. 
It takes the global struct pointer as an argument and reads
in the specified dictionary. Once the internal buffer reaches a
size of 100, writeToBuffer() is called. 
============================================================*/
void *readFile(void *buf) {
	struct globalBuffer *ptr = (struct globalBuffer*) buf;
	char* buffer[100];
	int i = 0;
	char dictName[50];
	strcpy(dictName, ptr->dictName);

	for (int i=0; i<100; i++) // Allocate memory
		buffer[i] = (char*)malloc(50 * sizeof(char));

	FILE* infile;
	infile = fopen(dictName, "r");

	if (infile == NULL) {
		printf("Invalid file name... Please try again.\n");
		exit(1);
	}
	else {
		while (fscanf(infile, "%s", buffer[i]) == 1) { // Read dictionary
			i++;
			if (i % 100 == 0) {
				writeToBuffer(buffer, 100, buf);
				i = 0;
			}
		}
		if (i > 0) // Sends last of buffer
			writeToBuffer(buffer, i, buf);
	}

	for (int i=0; i<100; i++) // Free dynamic memory
		free(buffer[i]);

	fclose(infile);
	return NULL;
}

/*============================================================
writeToBuffer(): Writes the internal buffer to the global buffer
given that the global buffer has space available.
============================================================*/
void *writeToBuffer(char** buffer, int bufSize, void *buf) {
	struct globalBuffer *ptr = (struct globalBuffer*) buf;

	pthread_mutex_lock(&lock);

	while (ptr->occupied >= 10000) // Waits until global buffer has space
		pthread_cond_wait(&less, &lock);

	if (ptr->occupied >= 10000) // Fallback check
		exit(1);

	for (int i=0; i<bufSize; i++) { // Adds items to the global buffer while it has space
		strcpy(ptr->buf[ptr->nextin],buffer[i]);
		ptr->nextin++;
		ptr->nextin %= 10000;
		ptr->occupied++;
		while (ptr->occupied >= 10000)
			pthread_cond_wait(&less, &lock);
	}

	if (bufSize < 100) // Signal end of file
		ptr->endOfFile = true;

	pthread_cond_signal(&more);
	pthread_mutex_unlock(&lock);
	
	return NULL;
}

/*============================================================
readHash(): Reads in the password hash value from an input file
and stores the value in the global buffer for later use. 
============================================================*/
void* readHash(char fileName[], void *buf) {
	struct globalBuffer *ptr = (struct globalBuffer*) buf;

	FILE* infile;
	infile = fopen(fileName, "r");

	if (infile == NULL) {
		printf("Invalid file name... Please try again.\n");
		exit(1);
	}
	else {
		fscanf(infile, "%s", ptr->passHash);
	}

	fclose(infile);
	return NULL;
}

/*============================================================
writeFile(): Opens an output file specified by outputName and
stores the correct found password in it. 
============================================================*/
void writeFile(void *buf, char outputName[]) {
	struct globalBuffer *ptr = (struct globalBuffer*) buf;
	char password[50];
	strcpy(password, ptr->password);

	FILE* outfile;
	outfile = fopen(outputName, "w");

	if (outfile == NULL) {
		printf("Error writing to file. Exiting...\n");
		exit(1);
	}
	else {
		fputs(password, outfile);
		printf("Password written to output file: %s\n", outputName);
	}

	fclose(outfile);
	return;
}