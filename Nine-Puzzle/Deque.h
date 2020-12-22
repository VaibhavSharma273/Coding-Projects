#include <stdbool.h>

typedef struct deque *Deque;

// Sets *d to a new object of type Deque.
bool createD (Deque *d);

// Returns true if the deque is empty, false otherwise.
bool isEmptyD (Deque *d);

// Adds a string pointer to the tail of the deque; the string itself is not duplicated.
bool addD (Deque *d, char *s);

// Removes the string pointer at the head of the deque and stores that value in the string pointer.
bool remD (Deque *d, char **s);

// Stores the value of the string pointer at the head of the deque.
bool headD (Deque *d, char **s);

// Add the string pointer to the head of the deque; the string itself is not duplicated.
bool pushD (Deque *d, char *s);

// An alternate name for remD() when the Deque is used as a stack.
#define popD(d,s)  remD(d,s)

// An alternate name for headD() when the Deque is used as a stack.
#define topD(d,s)  headD(d,s)

// Destroys the Deque *D by freeing any storage that it uses (but not the blocks
// of storage to which the string pointers point) and sets the value of *D to
// NULL.
bool destroyD (Deque *d);
