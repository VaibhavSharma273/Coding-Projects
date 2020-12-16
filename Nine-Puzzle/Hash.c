#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>
#include "Hash.h"
#include <stdio.h>

//Name : Vaibhav Sharma
//NetID : vs432

//Implementation : Each struct of type Table consists of its size, the number of elements and an array of structs of type Chains
//				   Each steuct of type Chains consists of its size (all initialised to zero at the beginning) and a pointer to an array of structs of type Triple;
//				   Each triple consists of a key (pos), value1(from), and value2 (nsteps) 

#define INITIAL_SIZE 1024
#define GROWTH_FACTOR 8
#define MAX_LOAD 8
#define MULTIPLIER 9787843


typedef struct triple {
	char* pos;				//key
	char* from;				//value1
	long int steps;			//value2
} *Triple;

typedef struct chain {
	int ChainSize;			//Chain length
	Triple* RealChain;		//Pointer to the actual chain array
} *Chain;

struct htable {	
	int size;				//size of the table
	int n;					//number of elements in the table
	Chain* table;			//Pointer to the actual table
}; 


//Function to create new hash table of required size
HTable InternalCreate (int size) {
	HTable T;
	T = malloc(sizeof(*T));
	T->size = size;
	T->n = 0;
	T->table = malloc(T->size * sizeof(Chain)); 
	
	//Initialising all elements of the table to zero
	for(int i = 0; i < T->size; i++) {
		T->table[i] = malloc(sizeof(struct chain));
		T->table[i]->RealChain = 0;
		T->table[i]->ChainSize = 0;
	}
 
	return T;

}

//Function to create a table as per initial size; fresh table
HTable CreateTable (void) {
	return InternalCreate(INITIAL_SIZE);
}


//Hash Function
static long hash (char *s, long size) {
   	unsigned long sum;
    int shift;
    const unsigned long prime = 3141592653589793239L;
      
    for (sum = 0, shift = 0; *s; s++) {         // Compress string to long
             sum ^= *s<<shift;
             shift += 4;
             if (shift >= 57)
                 shift -= 57;
        }
    sum += sum >> 33;                           // Condition the bits
    sum *= prime;
    sum += sum >> 33;
      
    return (sum % size);                        // Reduce to [0,SIZE)
}

//Function to insert a new triple into existing table -- strdup??
void InsertTable (HTable T, char* key, char* value1, int value2) {

	long h = hash (key, MULTIPLIER) % T->size;
	if (T->table[h]->ChainSize == 0) {
		T->table[h]->ChainSize = 1;
		T->n++;

		T->table[h]->RealChain = malloc (sizeof(Triple)* T->table[h]->ChainSize);
		T->table[h]->RealChain[0] = malloc (sizeof(struct triple));
		T->table[h]->RealChain[0]->pos = key;
		T->table[h]->RealChain[0]->from = value1;
		T->table[h]->RealChain[0]->steps = value2;
	}
	else {
		T->table[h]->RealChain = realloc(T->table[h]->RealChain, sizeof(Triple) * (T->table[h]->ChainSize + 1));
		T->table[h]->RealChain[T->table[h]->ChainSize] = malloc (sizeof(struct triple));

		int i = 0;
		for (i = 0; i < T->table[h]->ChainSize; i++) {
			if (strcmp(T->table[h]->RealChain[i]->pos, key) > 0)
				break;
		}


		for (int j = T->table[h]->ChainSize; j > i; j--) {
			T->table[h]->RealChain[j]->pos = T->table[h]->RealChain[j-1]->pos;
			T->table[h]->RealChain[j]->from = T->table[h]->RealChain[j-1]->from;
			T->table[h]->RealChain[j]->steps = T->table[h]->RealChain[j-1]->steps;
		}

		T->table[h]->RealChain[i]->pos = key;
		T->table[h]->RealChain[i]->from = value1;
		T->table[h]->RealChain[i]->steps = value2;

		//Chainsize variable increased here; actual size increased before during realloc and allocated to null; old chainsize used to acces last element
		T->table[h]->ChainSize++; 
		T->n++;
	}
	if (T->n > T->size * MAX_LOAD) {
		grow(T);
	}
}

//Rehashing table 
void grow(HTable T) {
	HTable T2;
	T2 = InternalCreate(T->size * GROWTH_FACTOR);
	//fprintf(stderr, "Old: %d New: %d Number of Entries: %d\n", T->size, T->size * GROWTH_FACTOR, T->n);
	//Shifting each and every element; each chain, each element
	int Size = T->size;
	for (int i = 0; i < Size; i++) {
		int check = 0;
		if (T->table[i]->ChainSize != 0)
			check = 1;
		for (int j = 0; check && j < T->table[i]->ChainSize; j++) {
			InsertTable(T2, T->table[i]->RealChain[j]->pos, T->table[i]->RealChain[j]->from, T->table[i]->RealChain[j]->steps);
			free(T->table[i]->RealChain[j]);
			T->table[i]->RealChain[j] = NULL;
		}
		free(T->table[i]->RealChain);
		T->table[i]->RealChain = NULL;
		free(T->table[i]);
		T->table[i] = NULL;
	}

	free(T->table);
	T->table = NULL;
	struct htable swap = *T;
	*T = *T2;
	*T2 = swap;
	free(T2);
	T2 = NULL;
	
}

long int SearchTable (HTable T, char* key, char** old) {
	long h = hash (key, MULTIPLIER) % T->size;
	if (T->table[h]->ChainSize != 0) { 
		for (int i = 0; i < T->table[h]->ChainSize; i++) {
			if (!strcmp(T->table[h]->RealChain[i]->pos, key)) {
				*old = T->table[h]->RealChain[i]->from;
				return T->table[h]->RealChain[i]->steps;
			}
		}
		
	} 
		return -10;

}



