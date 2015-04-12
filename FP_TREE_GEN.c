/*
  Copyright (c) data-fetish

  Team: Knowledge-mining

  Authors:  Akash Raj K N
            Gopichand Paturi
            Anjali Thakur
*/

/*
    FP-Growth Algorithm
    FP_TREE_GEN.c
*/

#include "FP_TREE_GEN.h"


//global variables
long long minSupportCount = 0;



void FP_Tree_Generation( long long minSupport )
{
  minSupportCount = minSupport;

  generateFrequentItemSets();  //from the input file, generate the frequent itemsets
}





