a.out: bst.o
	gcc bst.o
bst.o: bst.c bst.h
	gcc -c bst.c

clean:
	-rm -rf bst.o a.out
