//Name : Vaibhav Sharma
//NetID : vs273

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Trie Definitions 
#define SIZE (26)

void remove_trailing(char *str) {
  int length = strlen(str);
  if (str[length-1] == '\n')
    str[length-1]  = '\0';
}

typedef struct trie_node {
		char* key; // If word found
		int counter; // Count of number of times found
		struct trie_node *kids[SIZE];
	} *Trie;

Trie makeTrie() {
	Trie t;
	t = malloc(sizeof(*t));

	t->counter = 0;
	for (int i = 0; i < SIZE; i++) {
		t->kids[i] = NULL;
	}

	t->key = NULL;
	return t;
}

void insertTrie (Trie t, char* key) {
	Trie* pres_child = &t;
	int check = 1;

	for (int i = 0; key[i] != '\0'; i++) {
		if(!isalpha(key[i])) {
			check = 0;
		}				//Checking for all to be letters		
	}

	for (int i = 0; key[i] != '\0' && check; i++) {
		key[i] = tolower(key[i]);
		int index = tolower(key[i])-'a';
		if (index>25) printf("index: %d\n", index);
		if((*pres_child)->kids[index] == NULL) {
			(*pres_child)->kids[index] = makeTrie();
		}

		pres_child = &(*pres_child)->kids[index];
	}
	(*pres_child)->key = key;
}


void searchTrie (char* Board, int Rows, int Cols, int i, int j, Trie Dict, int blank) {
	char current = tolower(Board[i*Cols + j]);
	if (current ==  '_') {
		for (int k = 0; k < SIZE; k++) {
			if (Dict->kids[k] != NULL) {
				Board[i*Cols + j] = 97 + k;
				searchTrie (Board, Rows, Cols, i, j, Dict, 1); 
				Board[i*Cols+j] = '_';
			}
		}
		Board[i*Cols+j] = '_';
	}
	else {
		int index = current - 'a';
		if (blank == 1)
			Board[i*Cols + j] = '_';

		if (Dict->kids[index] != NULL) {
			if (Dict->kids[index]->key != NULL) 
				Dict->kids[index]->counter++;				//Checking to see if there is a word on the next node 

			if (i != 0) {
				searchTrie (Board, Rows, Cols, i-1, j, Dict->kids[index], 0);
			}
			if (i != Rows-1) {
				searchTrie (Board, Rows, Cols, i+1, j, Dict->kids[index], 0);
			}
			if (j != 0) {
				searchTrie (Board, Rows, Cols, i, j-1, Dict->kids[index], 0);
			}
			if (j != Cols-1) {
				searchTrie (Board, Rows, Cols, i, j+1, Dict->kids[index], 0);
			}
			if (i != 0 && j != 0) {
				searchTrie (Board, Rows, Cols, i-1, j-1, Dict->kids[index], 0);
			}
			if (i != Rows-1 && j != Cols-1) {
				searchTrie (Board, Rows, Cols, i+1, j+1, Dict->kids[index], 0);
			}
			if (i != 0 && j != Cols-1) {
				searchTrie (Board, Rows, Cols, i-1, j+1, Dict->kids[index], 0);
			}
			if (i != Rows-1 && j != 0) {
				searchTrie (Board, Rows, Cols, i+1, j-1, Dict->kids[index], 0);
			}
		}
	}
}

void searchTrie_t (char* Board, int Visited[], int Rows, int Cols, int i, int j, Trie Dict) {
char current = tolower(Board[i*Cols + j]);
Visited[i*Cols+j] = 1;
if (current ==  '_') {
		for (int k = 0; k < SIZE; k++) {
			if (Dict->kids[k] != NULL) {
				Board[i*Cols + j] = 97 + k;
				searchTrie_t (Board, Visited, Rows, Cols, i, j, Dict); 
			}
			Board[i*Cols+j] = '_';
		}
		Board[i*Cols+j] = '_';
		Visited[i*Cols+j] = 0;
	}
else {
		int index = current - 'a';
		if (Dict->kids[index] != NULL) {
			if (Dict->kids[index]->key != NULL) {
				Dict->kids[index]->counter++;
			}

			if (i != 0 && !Visited[(i-1)*Cols+j]) {
				searchTrie_t (Board, Visited, Rows, Cols, i-1, j, Dict->kids[index]);
			}
			if (i != Rows-1 && !Visited[((i+1)*Cols)+j]) {
				searchTrie_t (Board, Visited, Rows, Cols, i+1, j, Dict->kids[index]);
			}
			if (j != 0 && !Visited[i*Cols+j-1]) {
				searchTrie_t (Board, Visited, Rows, Cols, i, j-1, Dict->kids[index]);
			}
			if (j != Cols-1 && !Visited[i*Cols+j+1]) {
				searchTrie_t (Board, Visited, Rows, Cols, i, j+1, Dict->kids[index]);
			}
			if (i != 0 && j != 0 && !Visited[(i-1)*Cols+j-1]) {
				searchTrie_t (Board, Visited, Rows, Cols, i-1, j-1, Dict->kids[index]);
			}
			if (i != Rows-1 && j != Cols-1 && !Visited[(i+1)*Cols+j+1]) {
				searchTrie_t (Board, Visited, Rows, Cols, i+1, j+1, Dict->kids[index]);
			}
			if (i != 0 && j != Cols-1 && !Visited[(i-1)*Cols+j+1]) {
				searchTrie_t (Board, Visited, Rows, Cols, i-1, j+1, Dict->kids[index]);
			}
			if (i != Rows-1 && j != 0 && !Visited[(i+1)*Cols+j-1]) {
				searchTrie_t (Board, Visited, Rows, Cols, i+1, j-1, Dict->kids[index]);
			}
			Visited[i*Cols+j] = 0;
		}
		else{
			Visited[i*Cols+j] = 0;
		}
			
	}
}

void printTrie (Trie Dict, int c_flag) {
	if (c_flag == 0) {
		//printf("Reached\n");
		if (Dict->key != NULL && Dict->counter > 0) {
			printf("%s: %d\n", Dict->key, Dict->counter);
		}
		for (int i = 0; i < SIZE; i++) {
			if (Dict->kids[i] != NULL) {
				printTrie (Dict->kids[i], c_flag);
			}
		}
	}
	else  {
		//printf("Reached");
		if (Dict->key != NULL && Dict->counter == 0)
				printf("%s\n", Dict->key);
		for (int i = 0; i < SIZE; i++) {
			if (Dict->kids[i] != NULL) {
				printTrie (Dict->kids[i], c_flag);
			}
		}
	}
}
int main(int argc, char* argv[]) {
	
	int t_flag = 0;
	int c_flag = 0;
	int start_rows = 1;
//Checking for the right number of arguments and type of flags
	if (argc == 6) {
		if (strlen(argv[1]) != 2 || strlen(argv[2]) != 2)
			exit(fprintf(stderr, "Wrong type of argument -a\n"));

		if (strcmp(argv[1], "-c") != 0 || strcmp(argv[2], "-t") != 0)
			exit(fprintf(stderr, "Wrong type of argument -b\n"));

		t_flag = 1;
		c_flag = 1;

		start_rows = 3;
	}

	else if (argc == 5) {
		if (strlen(argv[1]) != 2)
			exit(fprintf(stderr, "Wrong type of argument -c\n"));

		if (strcmp(argv[1], "-c") == 0)
			c_flag = 1;
		else if (strcmp(argv[1], "-t") == 0)
			t_flag = 1;
		else
			exit(fprintf(stderr, "Wrong type of argument -d\n"));

		start_rows = 2;
	}

	else if (argc != 4) 
		exit(fprintf(stderr, "Wrong type of argument -e\n"));

//Checking for the right type of rows, cols, and board --Checl for decimals, invalid ?
	int nRows = 0;
	int nCols = 0;
	char *Board = NULL;

	int RowLen = strlen (argv[start_rows]);
	int ColLen = strlen (argv[start_rows + 1]);
	char *RowString = argv[start_rows];
	char *ColString = argv[start_rows + 1];

	for (int i = 0; i < RowLen; i++) {
		if (!isdigit (RowString[i]))
			exit(fprintf(stderr, "Wrong type of argument -f\n"));
	}

	for (int i = 0; i < ColLen; i++) {
		if (!isdigit (ColString[i]))
			exit(fprintf(stderr, "Wrong type of argument -g\n"));
	}

	nRows = atoi(argv[start_rows]);
	nCols = atoi(argv[start_rows + 1]);

	if (nRows <= 0 || nCols <= 0) {
		exit(fprintf(stderr, "Wrong type of argument -h\n"));
	}
	if (strlen(argv[start_rows + 2]) != nRows * nCols) {
		exit(fprintf(stderr, "Wrong type of argument -j\n"));
	}
	Board = argv[start_rows + 2];

	for (int i = 0; i < nRows*nCols; i++) {
		if (!isalnum(Board[i]) && Board[i] != '_') {
			exit(fprintf(stderr, "Wrong type of argument -k\n"));
		}
	}

	Trie dict = makeTrie();
//Making the dictionary
	size_t linefetch = 0;
	char* line = NULL;
	while (getline(&line, &linefetch, stdin) >= 0) {
		char* key = strdup(line);
		remove_trailing(key);
		insertTrie(dict, key);
		free(line);
		line = NULL;
	}


//Evaliating Boggle Words
	for (int i = 0; i < nRows; i++) {
		for (int j = 0; j < nCols; j++) {
			int Visited[nRows*nCols];
			for (int k = 0; k < nRows*nCols && t_flag; k++) {
					Visited[k] = 0;
				}
			if (t_flag) 
				searchTrie_t (Board, Visited, nRows, nCols, i, j, dict);
			else
				searchTrie (Board, nRows, nCols, i, j, dict, 0);
		}
	}

	printTrie(dict, c_flag);
	exit(0);

}