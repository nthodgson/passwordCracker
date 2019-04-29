#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <pthread.h>
#include "sha-256.h"

// Programmer: Nathan Hodgson
// Program: producer.h

// Producer thread struct declaration

struct producerThread {

};

void readFile(char dictName[], globalBuffer *b);
void writeToBuffer(char buffer[100][50], globalBuffer *b);