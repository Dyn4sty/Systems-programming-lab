# C Project: 12-bit Assembler

# About
 The purpose of this project is to build an assembler for 32-bit instruction asssembly language, for an imaginary **32-bit** CPU and **2<sup>25</sup>** bits of memory size (about **4MB**).
 using 2's complement
 Supports ASCII
 
  For any issues, questions and ideas turn to the Issues tab.

# Source structure (Modules)

1. `assembler` - main function definition, argv & argc processing, single file processing.
2. `first_pass` - contains functions for processing a single line in the first pass and a code line in the first pass.
3. `second_pass` - contains function for processing a single line in second pass and replacing symbol by it's address.
4. `list` - contains definition of linked list data structure.
5. `instruction` - contains types and function for processing instruction  line .
6. `guide` - contains types and functions for processing guide line.
7. `symbol_table` - contains defintion of types and functions to handle symbols.
8. `utils` - contains useful function for processing code.
9. `constants` - contains type and constant definitions.
10. `errors` - contains fucntion for printing errors, and defintion of common error codes.

# Usage

`./assembler file1 file2 file3 ...` Will start the processing of each file .

# Build

Using `make` command (Makefile)