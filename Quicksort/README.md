# Linesort - An implementation of quick sort

Linesort is a sort program that reads lines from the files specified, removes their trailing newlines if any, sorts them in ascending order using quick sort, and writes the sorted lines to the standard output, each followed by a newline. When more than one file is specified, all of the lines in all of the files are sorted into one output stream.  When no files are specified, nothing is written.

## Usage

```
$ make
$ ./Linesort [-POS[,LEN]] [FILE]*
```
 
The sorted order is based on a "key" associated with each line.  Normally, this key is the entire line, but if the -POS[,LEN] option is specified, it consists of the substring of length LEN beginning with line[POS].  If line[POS] lies beyond the end of line, the key is the empty string.  If there are fewer than LEN characters starting with line[POS], the key consists of only those characters.

For example,

        LINE            POS,[LEN]       KEY
        ~~~~            ~~~~~~~~~       ~~~
        abcdefgh        2,4             cdef
        abcdefgh        4               efgh
        abcdefgh        6,3             gh
        abcdefgh        8,2
        
Linesort is STABLE. That is, if two lines have equal keys, they appear in the same relative order in the output as they did in the input. To make the assignment more challenging, Linesort does not use any arrays other than argv[] and the strings returned by getline(). Instead, it is limited to ONE queue and TWO stacks of string pointers; that is, no more than one queue and two stacks may exist at any point during its execution.

Rather than implement two separate data structures, one for queues and one for stacks, Linesort uses three deques (\*), one used only as a queue (i.e., items can only be added to the tail and removed from the head), the other two used only as stacks (i.e., items can only be added to the head and removed from the head). If the same deque is used as both a queue and a stack (i.e., items are added to both the tail and the head), then it counts as one of each.

  *(\*) A deque (or double-ended queue, pronounced "deck") is a data structure that combines the attributes of a queue and a stack:  Items can be added to the tail (as in a queue) or the head (as in a stack), but can only be removed from the head.*

These deques are implemented in a separate source file as the abstract data type (ADT) Deque defined in the header file Deque.h, an alternate version of the header file for the Deque ADT provided by Prof. Stanley Eisenstat. 

The implementation of Linesort runs in O(n\*log2(n)) time under the usual randomness assumptions. Additionally, to make the implementation efficient, Linesort uses at most 2*#compares + N calls to addD() or pushD() (i.e. the commands used to add elements to the deques).     

