#ifndef __GLOBAL_H_
#define __GLOBAL_H_

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

// Consumer thread struct declaration

struct consumerThread {

};

void checkWord(char word[], char hash[]);

#endif