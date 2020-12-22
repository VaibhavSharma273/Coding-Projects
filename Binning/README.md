# Binning using Bindump - An implementation of depth first search
Bindump is a program that prints the number of bins needed to store a set of items.  

## Usage
` % ./Bindump BIN_SIZE [ITEM_SIZE]* [-opt | -ff | -bf | -ffd | -bfd]*`

Here

  BIN_SIZE is the capacity of each bin and must be a positive integer.

  [ITEM_SIZE]* is a sequence of zero or more item sizes, each of which must be
    a positive integer that is less than or equal to BIN_SIZE.

  [-opt | -ff | -bf | -ffd | -bfd]* is a sequence of zero or more flags, each
    either -opt or -ff or -bf or -ffd or -bfd.

The flags specify how to compute the assignment of items to bins:

* -opt  Use backtracking to find the minimum number of bins required.

* -ff   Uses the first-fit heuristic:  Processes the items in the left-to-right
        order that they appear on the command line, and places each item in the
        lowest-numbered bin in which it fits.

* -ffd  Applies the first-fit heuristic after sorting the list of items in
        decreasing order of size (non-increasing order in the event of ties).

* -bf   Uses the best-fit heuristic:  Processes the items in the left-to-right
        order that they appear on the command line, and places each item in the
        bin that would have the least amount of room remaining (the lowest-
        numbered such bin in the event of ties).

* -bfd  Applies the best-fit heuristic, but first sorts the list of items in
        decreasing order of size (non-increasing order in the event of ties).

Bindump prints each number of bins using a statement like

        printf ("MMMM %d\n", numberofBins);

where MMMM is the current flag (blank-padded to four characters).  When more
than one flag is specified, the corresponding numbers of bins appear on
separate lines in the same order as the left-to-right order that the flags
appear on the command line.  Flags may be specified more than once.

## Example

 ```
 % ./Bindump 100 31 41 59 26 53 58 97 93 23 84 62 64 33

  % ./Bindump 100 31 41 59 26 53 58 97 93 23 84 62 64 33 -opt -opt
  -opt 8
  -opt 8

  % ./Bindump 96 14 14 14 14 14 14 33 33 33 33 33 33 49 49 49 49 49 49 -ff -ffd
  -ff  10
  -ffd 6

  % ./Bindump 96 14 14 14 14 14 14 33 33 33 33 33 33 49 49 49 49 49 49 -bfd -bf
  -bfd 6
  -bf  10
```

