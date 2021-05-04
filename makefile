a.out: bst.o client.o
	gcc bst.o client.o
bst.o: bst.c bst.h
	gcc -c bst.c

client.o: client.c bst.h
	gcc -c client.c
clean:
	-rm -rf bst.o  client.o a.out
	-rm -rf *~
