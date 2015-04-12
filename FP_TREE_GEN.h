/*
  Copyright (c) data-fetish

  Team: Knowledge-mining

  Authors:  Akash Raj K N
            Gopichand Paturi
            Anjali Thakur
*/

/*
    FP-Growth Algorithm
    FP_TREE_GEN.h
*/


#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


void FP_Tree_Generation(long long);

void generateFrequentItemSets();

void sortInputTransaction();

void createFPTree();