//Structure for hash table data structure
typedef struct htable *HTable;

//Function to create new hash table; returns the creates table; assigned to a variable of type table
HTable CreateTable (void);

//Function to insert keys into the table
void InsertTable (HTable T, char* key, char* value1, int value2);

//Function to grow the table; doesn't need to be in hash.h though
void grow(HTable T);

//Function to search table and return true and false depending on whether key was found or not
long int SearchTable (HTable T, char* key, char** old) ;
