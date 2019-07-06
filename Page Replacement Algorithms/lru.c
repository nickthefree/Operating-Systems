/* Nicholas Freeman
 * This is a program that implements the Least Recently Used algorithm for page table replacement.
 * March 1st, 2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 500

//Rotate array left
int rotate(int *Table, int tableSize);

//Checks to see if page table is in memory
int CheckMemory(int page, int *Table, int tableSize);

int initialize(int *Table, int tabSize){
	int i;
	for(i = 0; i < tabSize; i++)
		Table[i] = -1;
}

int main (int argc, char *argv[]){
	if(argc < 2){
		printf("Please provide size of table as argument!.\n");
		exit(1);
	}

	int a, b;
	int tableSize = atoi(argv[1]);
	int pageRequest, TableIndex, pageUsedIndex, recency = 0;
	int *Table = (int *) malloc(sizeof(int) *MAX);
	int *pageUsed = (int *) malloc(sizeof(int) *MAX);
	FILE *f1 = fopen("accesses.txt", "r");
	int in = 0;
	initialize(Table, tableSize);
	initialize(pageUsed, tableSize);
	fscanf(f1, "%d", &in);


	//while ((bytesRead = getline(&in, &inputAllocated, stdin)) != EOF)
	while ( !feof(f1)){
		pageRequest = in;
		if (!CheckMemory(pageRequest, Table, tableSize)){
			printf("Page %d caused a page fault.\n", pageRequest);
			if (TableIndex < tableSize){
				pageUsed[TableIndex] = recency++;
				Table[TableIndex++] = pageRequest;
			}
			else{
				int min = 0;
				int minAdr = 0;
				int i;
				for(i=0; i<tableSize; i++){
					if(pageUsed[i] < min){
						min = pageUsed[i];
						minAdr = i;
					}
				}
				pageUsed[minAdr] = recency++;
				Table[minAdr] = pageRequest;
			}
		}
		else{
			int i;
			int j;
			for(i = 0; i < tableSize; ++i){
				if(Table[i] == pageRequest){
					j = i;
					break;
				}
			}
			pageUsed[j] = recency++;			
		}
		fscanf(f1, "%d", &in);

	}
	free(Table);
	
	return 0;
}

int rotate(int *Table, int tableSize){
	int i;
	for(i = 0; i < tableSize - 1; i++)
		Table[i] = Table[i+1];
}

int CheckMemory(int page, int *Table, int tableSize){
	int i;
	for (i=0; i<tableSize; i++)
	{
		if (Table[i] == page)
			return 1;
	}
	return 0;
}
