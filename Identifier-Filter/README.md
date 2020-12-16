# Cxref - A filter for identifiers in a C program

"Cxref" is a filter that reads a C program from the standard input and
writes to the standard output a line of the form:

`<C-identifier>:<line-number>`

for each instance of each C identifier that appears.  The order of the lines
should is the same as the order in which the identifiers appear in the input.

In particular, Cxref:
* handles line splices correctly
* treats keywords as identifiers
* handles both /*...*/ and //... comments correctly
* handles integer constants correctly
* handles char constants and strings correctly
* handles escaped characters within char constants and strings correctly
* assumes that there are no preprocessing directives;
* assumes that there are no multicharacter char constants
* not make ANY assumptions as to the maximum length of a line;

