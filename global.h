#ifndef __GLOBAL_H_
#define __GLOBAL_H_

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

// Declare global thread variables

pthread_mutex_t lock;
pthread_cond_t more;
pthread_cond_t less;

// Declare global buffer struct

struct globalBuffer {
    char* buf[10000];
    char dictName[50];
    int occupied;
    int nextin;
    int nextout;
};

#endif