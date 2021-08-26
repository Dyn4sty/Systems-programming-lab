# Usage:
# make        # compile all binary
# make clean  # remove ALL binaries and objects

CC = gcc # compiler to use
CFLAGS = -Wall -g -ansi -pedantic -o # -Wall enables all compiler's warning messages.
									# -g Turn on debug info.
									# -ansi tells the compiler to implement the ANSI language option. *equivalent to -std=c89 \
									   This turns off certain "features" of GCC which are incompatible with the ANSI standard.
									# -pedantic: used in conjunction with -ansi, this tells the compiler to be adhere strictly to the ANSI standard, \
									   rejecting any code which is not compliant.
									 
SRCS = letters.c
BINS = letters

BUILD = ${CC} ${SRCS} ${CFLAGS} ${BINS}

letters: ${SRCS} 
	${BUILD}

# prevent name collsion \
  if "clean" file exists in the filesystem.
.PHONY: clean

clean: 
	rm -rf ${BINS}
