#include <bits/stdc++.h>
#include <pthread.h>

#define NUM_READERS 5
#define NUM_WRITERS 5
int add=0;



int main(){
	int readerData[NUM_READERS];
	int writerData[NUM_WRITERS];

	// creating the threads
	pthread_t readerThreads[NUM_READERS];
	pthread_t writerThreads[NUM_WRITERS];

	// starting reader threads
	for (int i = 0; i < NUM_READERS; i++) {
		readerThreads[i] = i; // data to feed to readers
		pthread_create(&readerThreads[i],NULL, readerFunc, &readerThreads[i] );
	}

	pthread_t readerThreadIDs[NUM_READERS];
	return 0;
}