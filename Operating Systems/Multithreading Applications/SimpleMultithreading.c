/* Nicholas Freeman 

   Description: This program is creates multiple threads to print different messages.
*/

#include <pthread.h>

#include <stdio.h>      /* printf, stderr */

#include <sys/types.h>  /* pid_t */

#include <unistd.h>     /* fork */

#include <stdlib.h>     /* atoi */

#include <errno.h>      /* errno */ 

#include <string.h>

void *print_messageA(void *pointer);
void *print_messageB(void *pointer);


int main(int argc, char *argv[]) {
    //declare two threads
    pthread_t thread1, thread2;
    //allocate memory for user delay input
    int* arg1 = malloc(sizeof(int));
    int* arg2 = malloc(sizeof(int));
    arg1[0] = atoi(argv[1]);
    arg2[0] = atoi(argv[1]);
    
    int t1, t2;
    //change pointer to void to pass into function
    t1 = pthread_create(&thread1, NULL, print_messageA, (void*) arg1);
    //standard error message
    if (t1){
	fprintf(stderr,"Error - pthread_create() return code: %d\n",t1);
	exit(EXIT_FAILURE);
    }
    
    t2 = pthread_create(&thread2, NULL, print_messageB, (void*) arg2);
    //standard error message
    if (t2){
	fprintf(stderr,"Error - pthread_create() return code: %d\n", t2);
	exit(EXIT_FAILURE);
    }
    
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL); 
    
    return 0;

}
//print function for first thread
void *print_messageA(void *pointer){
      int* arg;
      arg = (int*) pointer;
      int j;
      for(j = 0; j < 100; j++){
	  printf("Thread 1 %d\n", j);
	  usleep(arg[0]);
      }
}
//print function for second thread
void *print_messageB(void *pointer){
      int* arg;
      arg = (int*) pointer;
      int j;
      for(j = 0; j < 100; j++){
	  printf("\t\t\tThread 2 %d\n", j);
	  usleep(arg[0]);
      }
}
