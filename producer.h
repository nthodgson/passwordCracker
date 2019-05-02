#ifndef __PRODUCER_H_
#define __PRODUCER_H_

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

void *readFile(void *buf);
void *writeToBuffer(char** buffer, int bufSize, void *buf);
void *readHash(char fileName[], void *buf);

#endif