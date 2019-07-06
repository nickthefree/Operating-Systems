/* Nicholas Freeman
 * This program uses the first in first out algorithm for page table replacement.

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 500
#define TWO 2

int rotate(int *Table, int tabSize){
	int i;
	for(i=0; i<tabSize-1; i++)
		Table[i] = Table[i+1];
}

int initialize(int *Table, int tabSize){
	int i;
	for(i = 0; i < tabSize; i++)
		Table[i] = -1;
  
}

int checkMem(int page, int *Table, int tabSize){
	int i;
	for (i=0; i<tabSize; i++){
		if (Table[i] == page)
			return 1;
	}
	return 0;
}

int main (int argc, char *argv[]){
	if(argc < 2){
		printf("Error!\n");
		exit(1);
	}
	int a, b;
	int tabSize = atoi(argv[1]);
	int pageRequest;
	
	ssize_t bytesRead;
	size_t inputAllocated = 0;
	int it = 0;
	int *Table = (int *) malloc(sizeof(int) *MAX);
	initialize(Table, tabSize);
	FILE *f1 = fopen("accesses.txt", "r");
	int in = 0;
	fscanf(f1, "%d", &in);

	
	//while ((bytesRead = getline(&in, &inputAllocated, stdin)) != EOF)
	while (!feof(f1)){
		pageRequest = in;
		if (!checkMem(pageRequest, Table, tabSize)){
			printf("Page %d caused a page fault.\n", pageRequest);
			// shifts all elements left in the page table
			rotate(Table, tabSize);
			// insert at the end of page table
			Table[tabSize-1] = pageRequest;
		}
		fscanf(f1, "%d", &in);
	}
	free(Table);
	
	return 0;
  
}
