#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <pthread.h> 

// Programmer: Nathan Hodgson
// Program: main.c

int main (int args, char** arg) {

	char dictName[50], inputName[50], outputName[50];
	strcpy(dictName, arg[1]);
	strcpy(inputName, arg[2]);
	strcpy(outputName, arg[3]);
	int consumerThreads = atoi(arg[4]);

	

	return 0;
}