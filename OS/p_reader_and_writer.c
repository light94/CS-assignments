#include <stdio.h>
#include <pthread.h>

#define NUM_READERS 5
#define NUM_WRITERS 5
int add=0;

int gReaders = 0;
pthread_mutex_t *mutex;


void *readerFunc (void *args);
void *writerFunc (void *args);

int main(){
	int i;
	int readerData[NUM_READERS];
	int writerData[NUM_WRITERS];

	//initialising the mutex
	//pthread_mutex_init()
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

	++gReaders;
	int *data = args;
	printf("(R) Data in thread: %d \n", *data);
	printf("Number of readers present: %d \n", gReaders);
}

void *writerFunc (void *args){
	int *data = args;
	printf("(W) Data in thread: %d \n", *data);
	printf("Number of readers present: %d \n", gReaders);
}

