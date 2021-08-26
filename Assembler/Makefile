CC = gcc
CFLAGS = -g -Wall -ansi -pedantic 

assembler: main.c assembler.o symbol_table.o first_pass.o second_pass.o list.o memory_map.o errors.o instruction.o utils.o guide.o externals.o
	$(CC) -g main.c $(CFLAGS) *.o -o assembler
assembler.o: assembler.c assembler.h
	$(CC) -c $(CFLAGS) assembler.c -o assembler.o
first_pass.o: first_pass.c first_pass.h 
	$(CC) -c $(CFLAGS) first_pass.c -o first_pass.o
second_pass.o: second_pass.c second_pass.h 
	$(CC) -c $(CFLAGS) second_pass.c -o second_pass.o	
memory_map.o: memory_map.c memory_map.h
	$(CC) -c $(CFLAGS) memory_map.c -o memory_map.o
symbol_table.o: symbol_table.c symbol_table.h
	$(CC) -c $(CFLAGS) symbol_table.c -o symbol_table.o
list.o: list.c list.h
	$(CC) -c $(CFLAGS) list.c -o list.o
errors.o: errors.c errors.h
	$(CC) -c $(CFLAGS) errors.c -o errors.o
instruction.o: instruction.c instruction.h
	$(CC) -c $(CFLAGS) instruction.c -o instruction.o
utils.o: utils.c utils.h
	$(CC) -c $(CFLAGS) utils.c -o utils.o
guide.o: guide.c guide.h
	$(CC) -c $(CFLAGS) guide.c -o guide.o
externals.o: externals.c externals.h
	$(CC) -c $(CFLAGS) externals.c -o externals.o
.PHONY: clean

clean:
	rm -f *.o  *.ext *.ent *.ob assembler