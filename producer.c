#include "producer.h"
#include "consumer.h"

// Programmer: Nathan Hodgson
// Program: producer.c

void readFile(char dictName[], globalBuffer *b) {
	char buffer[100][50];
	int ret = 0, i = 0;

	FILE* infile;
	infile = fopen(dictName, "r");

	if (infile == NULL) {
		printf("Invalid file name... Please try again.\n");
		exit(1);
	}
	else {
		ret = fscanf(infile, "%s", buffer[0]);
		while (ret == 1 && !feof(infile)) {
			i++;
			ret = fscanf(infile, "%s", buffer[i]);
			if (i % 100 == 0)
				writeToBuffer(buffer, &b);
		}
	}

	fclose(infile);
	return;
}

void writeToBuffer(char buffer[100][50], globalBuffer *b) {


	return;
}