/* Nicholas Freeman 

   1/15/2019  

   Programming in C and use of Systems Calls
   
   This program creates seven processes and gives the ID of each individual process as well as its
   parent ID.
*/
#include <pthread.h>

#include <stdio.h>      /* printf, stderr */

#include <sys/types.h>  /* pid_t */

#include <unistd.h>     /* fork */

#include <stdlib.h>     /* atoi */

#include <errno.h>      /* errno */ 

int main(int argc, char *argv[]) {

    pid_t  pid1, pid2, pid3, pid4, pid5, pid6;

    int i = 0, n = atoi(argv[1]); // n microseconds to input from keyboard for delay

    printf("\n Before forking.\n");

    pid1 = fork();//main creates one child process
                
    if (pid1 == -1) {//Check to see if fork worked

        fprintf(stderr, "can't fork, error %d\n", errno);

    }
    
    if (pid1){//If in main create another child process

        // Parent process
	    //printf("First child created!\n");
            //printf("\t \t \t  Process a %d \n", i);//Tracks number of process
	    
	    pid2 = fork();//main creates second child process
	    
	    if (pid2 == -1) {//Check to see if fork worked
		
		fprintf(stderr, "can't fork, error %d\n", errno);
	    
	    }
	    
	    if(pid2){//if in main do nothing
		
	    }
	    
	    else{//if in pid2 create two more child processes
		
		printf("Pid2 created! ID: %d, Parent ID: %d\n", getpid(), getppid());
		
		pid3 = fork();//pid2 Creates child process pid3
		
		if (pid3 == -1) {//Check to see if fork worked
		
		    fprintf(stderr, "can't fork, error %d\n", errno);
		
		}
		
		
		
		if(pid3){//if in child 2, create second grandchild process
		  
		    //printf("First grandchild created!\n");
		    
		    pid4 = fork();
		    
		    if (pid4 == -1) {//Check to see if fork worked
		
			fprintf(stderr, "can't fork, error %d\n", errno);
	    
		    }
		    
		    if(!pid4){//if in child 4, print ID
		      
			printf("Pid4 Created! ID: %d, Parent ID: %d\n", getpid(), getppid());
		      
			//printf("Second grandchild created!\n");

		    }
		}
		else//in pid3
		    printf("Pid3 Created! ID: %d, Parent ID: %d\n", getpid(), getppid());
	    }
	    exit(1);//Exit to make sure forked processes don't get out of control
    }
    
    
    else{
      
	printf("Pid1 created! ID: %d; Parent ID: %d\n", getpid(), getppid());
        // Child process pid1
	pid5 = fork();
            //printf(" Process c %d\n",i);
	if (pid5 == -1){//Check to see if fork worked
	
	    fprintf(stderr, "can't fork, error %d\n", errno);
	    
        }
        
	if (pid5){//if in child 1, create second grandchild
	    
	    //printf("Third grandchild created!\n");
	    
	    pid6 = fork();
	    
	    if (pid6 == -1) {//Check to see if fork worked
		
		fprintf(stderr, "can't fork, error %d\n", errno);
		
	    }
	    
	    if(!pid6){//if in child 6
		
		printf("Pid6 Created! ID: %d; Parent ID: %d\n", getpid(), getppid());
		
		//printf("Fourth grandchild created!\n");
	      
	    }
	}
	else//in child 5
	    printf("Pid5 Created! ID: %d; Parent ID: %d\n", getpid(), getppid());
    }

    return 0;

}
