main: main.o FP_GROWTH.o
	g++ main.o FP_GROWTH.o -o main

main.o: main.c FP_GROWTH.cpp
	g++ -c main.c

FP_GROWTH.o: FP_GROWTH.cpp FP_GROWTH.h FP_TREE_GEN.c
	g++ -c FP_GROWTH.cpp

FP_TREE_GEN.o: FP_TREE_GEN.c FP_TREE_GEN.h
	g++ -c FP_TREE_GEN.c

clean:
	rm *.o main