main: main.o FP_TREE_GEN.o
	gcc main.o FP_TREE_GEN.o -o main

main.o: main.c FP_TREE_GEN.h
	gcc -c main.c

FP_TREE_GEN.o: FP_TREE_GEN.c FP_TREE_GEN.h
	gcc -c FP_TREE_GEN.c

clean:
	rm *.o main