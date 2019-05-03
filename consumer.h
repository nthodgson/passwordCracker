#ifndef __CONSUMER_H_
#define __CONSUMER_H_

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
// Program: consumer.h

// Consumer thread function declaration

bool checkWord(char word[], char hash[], void *buf);
void* runConsumer(void *buf);
void getWord(void *buf, char word[]);

#endif