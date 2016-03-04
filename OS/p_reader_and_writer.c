#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_READERS 5
#define NUM_WRITERS 5
#define NUM_READS 2
#define NUM_WRITES 2
int add=0;

int gReaders = 0;
int gWaitingReaders = 0; // to give privilege to readers
pthread_mutex_t mutex= PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t rCond = PTHREAD_COND_INITIALIZER;
pthread_cond_t wCond = PTHREAD_COND_INITIALIZER;


void *readerFunc (void *args);
void *writerFunc (void *args);

int main(int argc,char *argv){
	int i;
	int readerData[NUM_READERS];
	int writerData[NUM_WRITERS];

	//initialising the mutex
	//pthread_mutex_init(&mutex, NULL);
	//pthread_cond_init(&rCond, NULL);
	//pthread_cond_init(&wCond, NULL);
	// creating the threads
	pthread_t readerThreads[NUM_READERS];
	pthread_t writerThreads[NUM_WRITERS];

	// starting reader threads
	for (i = 0; i < NUM_READERS; i++) {
		readerData[i] = i; // data to feed to readers
		pthread_create(&readerThreads[i],NULL, readerFunc, &readerData[i]);
	}
	// starting writer threads
	for (i = 0; i < NUM_WRITERS; i++) {
		writerData[i] = i;
		pthread_create(&writerThreads[i], NULL, writerFunc, &writerData[i]);
	}

	// join readers
	for(i = 0; i < NUM_READERS; i++) {
		pthread_join(readerThreads[i], NULL);
	}
	// join writers
	for(i = 0; i < NUM_WRITERS; i++) {
		pthread_join(writerThreads[i], NULL);
	}

	
	return 0;
}

void *readerFunc (void *args){
	int i = 0;
	int *data = args;
	for (i = 0; i < NUM_READS; i++) {
	
		pthread_mutex_lock(&mutex);
		++gWaitingReaders;
		while (gReaders == -1) {
			pthread_cond_wait (&rCond,&mutex);
		}
		++gReaders;
		--gWaitingReaders;
		pthread_mutex_unlock(&mutex);
		
		printf("(R) Data in thread: %d \n", *data);
		printf("Number of readers present: %d \n", gReaders);

		pthread_mutex_lock(&mutex);
		--gReaders;
		// priority implementation
		if (gWaitingReaders == 0) {
			pthread_cond_signal(&wCond);	
		}
		pthread_mutex_unlock(&mutex);	
	}

	pthread_exit(0);
}

void *writerFunc (void *args) {
	int i = 0;
	int *data = args;
	for (i = 0; i < NUM_WRITES; i++) {

		pthread_mutex_lock(&mutex);
		while (gReaders != 0) {
			pthread_cond_wait (&wCond,&mutex);
		}
		gReaders = -1;
		pthread_mutex_unlock(&mutex);

		printf("(W) Data in thread: %d \n", *data);
		printf("Number of readers present: %d \n", gReaders);

		pthread_mutex_lock(&mutex);
		gReaders = 0;
		// priority implementation
		if (gWaitingReaders)
			pthread_cond_broadcast(&rCond);
		else
			pthread_cond_signal(&wCond);	
		pthread_mutex_unlock(&mutex);
	}

	pthread_exit(0);
}

