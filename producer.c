#include "producer.h"
#include "consumer.h"
#include "global.h"

// Programmer: Nathan Hodgson
// Program: producer.c

void readFile(char dictName[]) {
	char buffer[100][50];
	int ret = 0, i = 1;

	FILE* infile;
	infile = fopen(dictName, "r");

	if (infile == NULL) {
		printf("Invalid file name... Please try again.\n");
		exit(1);
	}
	else {
		ret = fscanf(infile, "%s", buffer[0]);
		while (ret == 1 && !feof(infile) && i < 100) {
			ret = fscanf(infile, "%s", buffer[i]);
			i++;
		}
	}

	fclose(infile);
	return;
}

void writeToBuffer() {

	return;
}