#include "producer.h"
#include "consumer.h"

// Programmer: Nathan Hodgson
// Program: consumer.c

void getWord(char word[], char hash[]) {
	char variants[8][50];
	char checkWord[50], checkHash[65];
	bool foundPass = false;

	// [0]oil [1]0il [2]o!l [3]oi1 [4]0i1 [5]o!1 [6]0!l [7]0!1 

	for (int i=0; i<8; i++) 
		strcpy(variants[i], word);

	for (int i=0; word[i] != '\0'; i++) {
		if (word[i] == 'i') {
			variants[2][i] = '!';
			variants[5][i] = '!';
			variants[6][i] = '!';
			variants[7][i] = '!';
		}
		if (word[i] == 'l') {
			variants[3][i] = '1';
			variants[4][i] = '1';
			variants[5][i] = '1';
			variants[7][i] = '1';
		}
		if (word[i] == 'o') {
			variants[1][i] = '0';
			variants[4][i] = '0';
			variants[6][i] = '0';
			variants[7][i] = '0';
		}
	}

	for (int i=0; i<8 && !foundPass; i++) {
		sha_256_string(checkHash, variants[i], strlen(variants[i]));
		if (strcmp(checkHash, hash) == 0) 
			foundPass = true;
		for (int j=0; j<10 && !foundPass; j++) {
			sprintf(checkWord, "%s%d", variants[i], j);
			sha_256_string(checkHash, checkWord, strlen(checkWord));
			if (strcmp(checkHash, hash) == 0) 
				foundPass = true;
		}
	}

	if (foundPass)
		printf("Found the password! It is: %s\n", checkWord);

	return;
}