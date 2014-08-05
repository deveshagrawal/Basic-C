CC          =	gcc
# Flags that are sent to the compiler
# Do not change these
CFLAGS      =	-Wall -ansi -pedantic -g

#Directories where the compiler can find things
INCLUDES    = -Iinclude

all : program test

program: 
	gcc $(CFLAGS) src/binarytree.c src/main.c -o main -Iinclude

test: 
	gcc $(CFLAGS) src/binarytree.c src/test.c -o test -Iinclude

clean:
	@ rm *.o



