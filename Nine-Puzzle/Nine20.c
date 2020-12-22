#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Deque.h"
#include "Hash.h"
#include <limits.h>
#include <ctype.h>


void sort(char *word)
{
    for (int i = 0; i < strlen(word) - 1; i++) {
    	for (int j = i + 1; j < strlen(word); j++) {
        	if (word[i] > word[j]) {
            	char temp = word[i];
            	word[i] = word[j];
            	word[j] = temp;
            }
        }
    }      
}

int main (int argc, char* argv[]) {
	int height, width;
	int index;
	char* max;

//Check for correct number of command line arguments and type of height, width
	if (argc == 6) {
		if (strlen(argv[1]) != 1 || strlen(argv[2]) != 1)
			exit(fprintf(stderr, "Wrong type of argument -a\n"));	
		if (!isdigit(argv[1][0]) || !isdigit(argv[2][0])) {
			exit(fprintf(stderr, "Wrong type of argument -a\n"));
		}

		height = atoi(argv[1]);
		width = atoi(argv[2]);
		index = 4;
		max = argv[3];
		if (height > 5 || width > 5 || height < 2 || width < 2)
			exit(fprintf(stderr, "Wrong type of argument -b\n"));	
	}
	else if (argc == 4) {
		height = 3;
		width = 3;
		index = 2;
		max = argv[1];
	}
	else
		exit(fprintf(stderr, "Wrong type of argument -c\n"));

	 char *initial;
	 char *goal;	

//Check for correct number of characters entered
	if (strlen(argv[index]) == strlen(argv[index+1])) {
		if (strlen(argv[index]) == height * width) {
			initial = argv[index];
			goal = argv[index+1];
		}
		else
			exit(fprintf(stderr, "Wrong type of argument -d\n"));
	}
	else 
		exit(fprintf(stderr, "Wrong type of argument -e\n"));

//Check for correct characters: same characters and number of -; sort both char array and use strcmp
	char* copyInitial = strdup(initial);
	char* copyGoal = strdup(goal);
	sort(copyInitial);
	sort(copyGoal);
	if (!strcmp(copyInitial, copyGoal)) {
		int check = 0;
		for (int i = 0; i < height*width; i++) {
			if (copyInitial[i] == '-')
				check++;
			if (!isprint(copyInitial[i]))
				exit(fprintf(stderr, "Wrong type of argument -f\n"));
		}
		if (check != 1)
			exit(fprintf(stderr, "Wrong type of argument -f\n"));
	}
	else 
		exit(fprintf(stderr, "Wrong type of argument -g\n"));

//Check for correct type of max
	for (int i = 0; i < strlen(max); i++) {
		if (!isdigit(max[i]))
			exit(fprintf(stderr, "Wrong type of argument -h\n"));
	}

	free(copyInitial);
	free(copyGoal);

	if (!strcmp(initial, goal)) {
		printf("%s\n", goal);
		exit(0);
	}

	int MaxSteps = atoi(max);

	HTable T = CreateTable();
	Deque Q;

	createD(&Q);
	addD(&Q, initial);
	InsertTable(T, initial, NULL, 0);


	while (!isEmptyD(&Q)) {
		char* key;
		remD(&Q, &key);
		char* from = NULL;
		long int N = SearchTable(T, key, &from);

		if (N < MaxSteps) {
			int found = 0;
			int i, j;
			for (i = 0; i < height && !found; i++) {
				for (j = 0; j < width && !found; j++) {
					if (key[(i*width)+j] == '-')
						found++;
				}
			}
			i--;
			j--;
			
			if (i != 0) {
				char* tester;
				char* transform = strdup(key);
				char s = transform[i*width+j];
				transform[i*width+j] = transform[(i-1)*width+j];
				transform[(i-1)*width+j] = s;
				if (!strcmp(transform, goal)) {
					int count = N+1;
					Deque Result;
					createD(&Result);
					pushD(&Result, transform);
					while (count != 0) {
						char* key2 = key;
						pushD(&Result, key2);
						count = SearchTable(T, key, &key);
					}
					while(!isEmptyD(&Result)) {
						char* key;
						remD(&Result, &key);
						printf("%s\n", key);
						N--;
					}
					destroyD(&Q);
					destroyD(&Result);
					exit(0);
				}
				else if (SearchTable(T, transform, &tester) == -10) {
					addD(&Q, transform);
					InsertTable(T, transform, key, N+1);
				}
				else
					free (transform);
				
			}
			if (j != 0) {
				char* tester;
				char* transform = strdup(key);
				char s = transform[i*width+j];
				transform[i*width+j] = transform[i*width+(j-1)];
				transform[i*width+(j-1)] = s;
				if (!strcmp(transform, goal)) {
					int count = N+1;
					Deque Result;
					createD(&Result);
					pushD(&Result, transform);
					while (count != 0) {
						char* key2 = key;
						pushD(&Result, key2);
						count = SearchTable(T, key, &key);
					}
					while(!isEmptyD(&Result)) {
						char* key;
						remD(&Result, &key);
						printf("%s\n", key);
						N--;
					}
					destroyD(&Q);
					destroyD(&Result);
					exit(0);
				}
				else if (SearchTable(T, transform, &tester) == -10){
					addD(&Q, transform);
					InsertTable(T, transform, key, N+1);
				}
				else
					free (transform);
			}
			if (i != height-1) {
				char* tester;
				char* transform = strdup(key);
				char s = transform[i*width+j];
				transform[i*width+j] = transform[(i+1)*width+j];
				transform[(i+1)*width+j] = s;
				if (!strcmp(transform, goal)) {
					int count = N+1;
					Deque Result;
					createD(&Result);
					pushD(&Result, transform);
					while (count != 0) {
						char* key2 = key;
						pushD(&Result, key2);
						count = SearchTable(T, key, &key);
					}
					while(!isEmptyD(&Result)) {
						char* key;
						remD(&Result, &key);
						printf("%s\n", key);
						N--;
					}
					destroyD(&Q);
					destroyD(&Result);
					exit(0);
				}
				else if (SearchTable(T, transform, &tester) == -10) {
					addD(&Q, transform);
					InsertTable(T, transform, key, N+1);
				}
				else
					free (transform);
			}
			if (j != width-1) {
				char* tester;
				char* transform = strdup(key);
				char s = transform[i*width+j];
				transform[i*width+j] = transform[i*width+(j+1)];
				transform[i*width+(j+1)] = s;
				if (!strcmp(transform, goal)) {
					int count = N+1;
					Deque Result;
					createD(&Result);
					pushD(&Result, transform);
					while (count != 0) {
						char* key2 = key;
						pushD(&Result, key2);
						count = SearchTable(T, key, &key);
					}
					while(!isEmptyD(&Result)) {
						char* key;
						remD(&Result, &key);
						printf("%s\n", key);
						N--;
					}
					destroyD(&Q);
					destroyD(&Result);
					exit(0);
				}
				else if (SearchTable(T, transform, &tester) == -10) {
					addD(&Q, transform);
					InsertTable(T, transform, key, N+1);
				}
				else
					free (transform);
			}
		}
	else {
		exit(0);
	}
		
	}
exit(0);
}

