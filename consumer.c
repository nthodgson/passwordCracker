#include "producer.h"
#include "consumer.h"
#include "global.h"

// Programmer: Nathan Hodgson
// Program: consumer.c

void getWord(char word[]) {

	for (int i=0; word[i] != '\0'; i++) {
		printf("%c\n", word[i]);
	}

	return;
}