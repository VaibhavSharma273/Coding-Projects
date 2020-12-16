//Name : Vaibhav Sharma
//NetID : vs273
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "/c/cs223/Hwk4/Deque.h"
#include <limits.h>
#include <ctype.h>

void QuickSort (Deque*, Deque*, Deque*, int, int, int);

int main (int argc, char* argv[]) {
	int pos = 0;
	int len = INT_MAX;
	int divider = 0;
	int start = 1;
	size_t linefetch = 0;

	if (start == argc) {
		exit(0);
	}

	char* check = argv[1];
	if (check[0] == '-') {
		start = 2;
		for (int i = 1; check[i] != '\0'; i++) {
			if (check[i] == ','&& divider == 0 && i!=1) {
				divider = i;
				len = 0;
				continue;
			}
			if (!isdigit(check[i])) {
				exit(fprintf(stderr, "Wrong type of length/position\n"));
			}
			if (divider == 0) {
				pos = pos*10 + (check[i] - '0');
			}
			else {
				len = len*10 + (check[i] - '0');
			}
		}
	}

	Deque Q;
	if (!createD(&Q)){
					exit(fprintf(stderr, "Memory allocation failed\n"));
	}

	if (start == argc) {
		exit(0);
	}
	

// Filling elements into Queue from different files
	int q = 0;

	while (start<argc) {

		FILE *fp;
		if ((fp = fopen(argv[start], "r")) == NULL) {
			exit(fprintf(stderr, "File not found\n"));
		}

		char* line = NULL;
		while (getline(&line, &linefetch, fp) >= 0) {
			if (!addD(&Q, line)) {
				exit(fprintf(stderr, "Memory allocation failed\n"));
			}
			line = NULL;
			q++;
		}
		free(line);
		fclose(fp);
		start++;
	}

//Creating stacks
	Deque LS, HS;
	if (!createD(&LS)){
		fprintf(stderr, "Memory allocation failed\n");
					exit(0);
	}

	if (!createD(&HS)){
		fprintf(stderr, "Memory allocation failed\n");
					exit(0);
	}

	QuickSort (&LS, &Q, &HS, pos, len, q);

	char* line1 = NULL;
	
	while (remD(&HS, &line1)) {
			printf("%s", line1);
		free (line1);
		line1 = NULL;
	}	
	
	destroyD(&LS);
	destroyD(&HS);
	destroyD(&Q);

}

void QuickSort (Deque* LS, Deque* Q, Deque* HS, int pos, int len, int q) {

	int new_lc = 0;
	int new_q = 0;
	char* pivot;
	remD(Q, &pivot);
	q--;
	char* key;

	for (int i = q; i > 0; i--) {
		if (!remD(Q, &key))
			exit(fprintf(stderr, "Memory allocation failed\n"));

		int x = strlen(key);
		if (pos > x)
			pos = x;

		if (strncmp(pivot+pos, key+pos, len) > 0) {
			if (!pushD(LS, key))
				exit(fprintf(stderr, "Memory allocation failed\n"));
			new_lc++;
		}
		else {
			if (!addD(Q, key))
				exit(fprintf(stderr, "Memory allocation failed\n"));
			new_q++;
		}			
		key = NULL;
	}

	if (new_q  > 1) {
		QuickSort (LS, Q, HS, pos, len, new_q);
	} 
	else if (new_q == 1) {
		if (remD (Q, &key)) {
			if (!pushD(HS, key))
				exit(fprintf(stderr, "Memory allocation failed\n"));
		}
		else 
			exit(fprintf(stderr, "Memory allocation failed\n"));
	}


	if (!pushD(HS, pivot))
		exit(fprintf(stderr, "Memory allocation failed\n"));

	if (new_lc > 1) {
		for (int i = new_lc ; i>0 && !isEmptyD(LS); i--) {
			if (!remD(LS, &key))
				exit(fprintf(stderr, "Memory allocation failed\n"));
			if (!pushD(HS, key))
				exit(fprintf(stderr, "Memory allocation failed\n"));
			key = NULL;
		}
		for (int i = new_lc ; i>0 && !isEmptyD(HS); i--) {
			if (!remD(HS, &key))
				exit(fprintf(stderr, "Memory allocation failed\n"));
			if (!addD(Q, key))
				exit(fprintf(stderr, "Memory allocation failed\n"));
			key = NULL;
		}
		QuickSort (LS, Q, HS, pos, len, new_lc);
	}
	else if (new_lc == 1) {
		if (remD (LS, &key)) {
			if (!pushD(HS, key))
				exit(fprintf(stderr, "Memory allocation failed\n"));
		}
		else 
			exit(fprintf(stderr, "Memory allocation failed\n"));
	}

}
