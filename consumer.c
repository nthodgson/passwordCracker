#include "global.h"
#include "consumer.h"

// Programmer: Nathan Hodgson
// Program: consumer.c

/*============================================================
runConsumer(): This is the driver function for the consumer
threads. It grabs words from the global buffer by calling
getWord() and checks them with checkWord(). 
============================================================*/
void* runConsumer(void *buf) {
	struct globalBuffer *ptr = (struct globalBuffer*) buf;
	char word[50];

	while (!ptr->foundPass) { // Will run until password found or end of file reached
		getWord(buf, word);
		if (ptr->endOfFile && ptr->occupied <= 0) {
			return NULL;
		}
		else if (checkWord(word, ptr->passHash, buf)) {
			pthread_cond_broadcast(&more);
			pthread_cond_broadcast(&less);
			return NULL;
		} 
	}	

	return NULL;
}

/*============================================================
getWord(): Waits until the global buffer has words in it and 
then stores it in the variable word which is passed by reference.
============================================================*/
void getWord(void *buf, char word[]) {
	struct globalBuffer *ptr = (struct globalBuffer*) buf;

	pthread_mutex_lock(&lock);

	while (ptr->occupied <= 0 && !ptr->foundPass) // Waits until global buffer is not empty
		if (ptr->endOfFile) {
			pthread_mutex_unlock(&lock);
			return;
		} 
		else
			pthread_cond_wait(&more, &lock);

	if (ptr->foundPass) {
		pthread_mutex_unlock(&lock);
		pthread_exit(NULL);
	}

	if (ptr->endOfFile && ptr->occupied <= 0) { // Ensure all words have been checked
		pthread_mutex_unlock(&lock);
		return;
	}

	if (ptr->occupied <= 0) // Failsafe
		exit(1);

	// printf("---------------------------\n");
	// printf("Occupied: %d\n", ptr->occupied);
	// printf("Nextin: %d\n", ptr->nextin);
	// printf("Nextout: %d\n", ptr->nextout);
	// printf("---------------------------\n");

	strcpy(word, ptr->buf[ptr->nextout]);
	ptr->nextout++;
	ptr->nextout %= 10000;
	ptr->occupied--;

	pthread_cond_signal(&less); 
	pthread_mutex_unlock(&lock);
	
	return; 
}

/*============================================================
checkWord(): Given a word and the correct password hash, this
function will check 88 different variations of the word's hash
to see if it matches the correct password hash. If the password
is found, this function will return true, else false. 
============================================================*/
bool checkWord(char word[], char hash[], void *buf) {
	struct globalBuffer *ptr = (struct globalBuffer*) buf;
	char** variants;
	char checkWord[50], checkHash[65];
	bool foundPass = false;

	variants = (char**)malloc(8 * sizeof(char*));
	for (int i=0; i<8; i++) { // Fills variants[] with word[]
		variants[i] = (char*)malloc(50 * sizeof(char));
		strcpy(variants[i], word);
	}

	// The following for loop will modify each variants[] index
	// location as shown below (example word "oil" is used):
	// [0]oil [1]0il [2]o!l [3]oi1 [4]0i1 [5]o!1 [6]0!l [7]0!1 

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

	for (int i=0; i<8; i++) { // Compare the 88 variants with the password hash
		sha_256_string(checkHash, variants[i], strlen(variants[i]));
		if (strcmp(checkHash, hash) == 0) {
			ptr->foundPass = true;
			strcpy(ptr->password, variants[i]);
			foundPass = true;
			break;
		}
		for (int j=0; j<10; j++) {
			sprintf(checkWord, "%s%d", variants[i], j);
			sha_256_string(checkHash, checkWord, strlen(checkWord));
			if (strcmp(checkHash, hash) == 0) {
				ptr->foundPass = true;
				strcpy(ptr->password, checkWord);
				foundPass = true;
				break;
			}
		}
	}

	for (int i=0; i<8; i++) // Free dynamic memory
		free(variants[i]);
	free(variants);

	return foundPass;
}