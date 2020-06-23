CFLAGS += -Wall -O0 -g3 -std=c99 
 
.PHONY: bst clean 
 
all: bst 
 
bst:
	gcc $(CFLAGS) -o bst.out bst.c main.c 
 
clean:
	rm -f *.out 