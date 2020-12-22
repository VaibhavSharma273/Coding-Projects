# IDFilter - A filter for identifiers in a C program

"IDFilter" is a filter that reads a C program from the standard input and
writes to the standard output a line of the form:

`<C-identifier>:<line-number>`

for each instance of each C identifier that appears.  The order of the lines is the same as the order in which the identifiers appear in the input.

In particular, IDFilter:
* handles line splices correctly
* treats keywords as identifiers
* handles both /*...*/ and //... comments correctly
* handles integer constants correctly
* handles char constants and strings correctly
* handles escaped characters within char constants and strings correctly
* assumes that there are no preprocessing directives;
* assumes that there are no multicharacter char constants
* not make ANY assumptions as to the maximum length of a line;

## Usage
On command-line, run:
```
$ make
$ ./IDFilter <input>
```

## Example
For the input:
```
main()
  {
      int a, b = 1, c = 0xface;
      one ( "( /* %s )",  ( "*/" ) );
      two ( /* " is a quote character */ " */ )");
      three ("\",", ",0);  ",0);
      four ('"', ('"'));
      a = b //* Hello! */ c ;
      -c;
  }
```
the output should be:
```
 main:1
  int:3
  a:3
  b:3
  c:3
  one:4
  two:5
  three:6
  four:7
```
This program can be tested with the winning programs of  International Obfuscated C Code Contest (IOCCC), a computer programming contest for the most creatively obfuscated C code. To download some of the winning programs run the getProgs.txt file written by Lucas Jehu Silva Shepard:
```
$ ./getProgs
```

This will create a separate directory called testCases to store some of the winning programs. To run IDFilter on all of them, run:
```
$  ./sampleAttempts.txt testCases ./IDFilter` 
```
