#include "global.h"
#include "producer.h" 
#include "consumer.h"


// Programmer: Nathan Hodgson
// Program: main.c

int main (int args, char** arg) {

	char dictName[50], inputName[50], outputName[50];
	strcpy(dictName, arg[1]);
	strcpy(inputName, arg[2]);
	strcpy(outputName, arg[3]);
	int consumerThreads = atoi(arg[4]);

	readFile(dictName);

	return 0;
}