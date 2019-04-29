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

// Declare global buffer struct

//static int BSIZE = 1000;

struct globalBuffer {
    char buf[10000][50];
    int occupied;
    int nextin;
    int nextout;
    pthread_mutex_t mutex;
    pthread_cond_t more;
    pthread_cond_t less;
};