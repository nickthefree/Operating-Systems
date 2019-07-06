/*Nicholas Freeman
* This program uses the second chance algorithm for page table replacement.
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 500

int rotate(int *Table, int tabSize){
	int i;
	for(i=0; i<tabSize-1; i++)
		Table[i] = Table[i+1];
}

int checkMem(int page, int *Table, int tabSize, int *SecondChance, int *pointer){
	int i;
	for (i=0; i<tabSize; i++){
		if (Table[i] == page){
		      SecondChance[i] = 1;
		      return 1;
		}
	}
	return 0;
}

int main (int argc, char *argv[]){
	if(argc < 2){
		printf("Error!\n");
		exit(1);
	}
	int a, b, c;
	int tabSize = atoi(argv[1]);
	int Request;
	ssize_t bytesRead;
	size_t inputAllocated = 0;
	int it = 0;
	int *Table = (int *) malloc(sizeof(int) *MAX);
	int *SecondChance = (int *) malloc(sizeof(int) *MAX);
	for(a = 0; a < MAX; a++)
	    SecondChance[a] = 0;
	FILE *f1 = fopen("accesses.txt", "r");
	int in = 0;
	int *pointer = NULL;
	fscanf(f1, "%d", &in);

	
	//while ((bytesRead = getline(&in, &inputAllocated, stdin)) != EOF)
	while ( !feof(f1)){
		Request = in;
		if (!checkMem(Request, Table, tabSize, SecondChance, pointer)){
			printf("Page %d caused a page fault.\n", Request);
			// shifts all elements left in the page table
			rotate(Table, tabSize);
			// insert at the end of page table
			Table[tabSize-1] = Request;
		}
		fscanf(f1, "%d", &in);
	}
	free(Table);
	free(SecondChance);
	
	return 0;
  
}
