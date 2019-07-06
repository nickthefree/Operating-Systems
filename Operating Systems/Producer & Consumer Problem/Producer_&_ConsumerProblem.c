/*Nicholas Freeman
# 02/5/2019
# This program solves the consumer/producer problem utilizing semaphores. 
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>

#define nprod 2
#define ncons 10
#define SIZE 5

int arr[SIZE];

pthread_t consumer[ncons];
pthread_t producer[nprod];
int consumerIndex = 0;
int producerIndex = 0;

sem_t mutex, full, empty;

void Producer(void* arg);
void Consumer(void* arg);

int main() {
    //initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, SIZE);
    //create threads
    static int i;
    for(i = 0; i < nprod; i++){
	pthread_create(&producer[i], NULL, Producer, (void*)i);
    }
    for(i = 0; i < ncons; i++){
	pthread_create(&consumer[i], NULL, Consumer, (void*)i);
    }
    //This infinite loop stops main from terminating
    sleep(1);
    
    //printf("Main thread done.\n");
    //sem_unlink("Semaphore");
    return 0;
}
//producer function
void Producer(void* arg){
    int item = 0;
    int index = 0;
    while(1){ 
	//...
	//Produce next item
	item = rnd();
	//...
	//
	sem_wait(&empty);
	sem_wait(&mutex);
	//...
	//add the item to buffer
	arr[producerIndex % SIZE] = item;
	index = producerIndex % SIZE;
	producerIndex++;
	printf("Producer %d | Produced item %d, stored in buff at index %d.\n", (int)arg, item, index);
	
	fflush(stdout);
	
	//...
	sem_post(&mutex);
	sem_post(&full);
	//sleep(1);

    }
}
//consumer function
void Consumer(void* arg){
    int item = 0;
    int index = 0;
    while(1){
	sem_wait(&full);
	sem_wait(&mutex);
	//...
	
	//read next item from buffer
	item = arr[consumerIndex % SIZE];
	index = consumerIndex % SIZE;
	consumerIndex++;
	//...
	printf("Consumer %d | Got item %d from buff index %d. \n", (int)arg, item, index);
	fflush(stdout);
	sem_post(&mutex);
	sem_post(&empty);
	//...
	//print the item

	//...
	//sleep(1);
    }
}
int rnd(){
    return (rand() % 100) + 1;
}


