/*----------------------------------------------------------------------------*/
/*                                                                            */
/*                   Copyright (c) 2015 data-fetish                           */
/*                   All rights reserved.                                     */
/*                                                                            */
/*                   Team: Knowledge-mining                                   */
/*                                                                            */
/*                   Authors:  Akash Raj K N                                  */
/*                             Gopichand Paturi                               */
/*                             Anjali Thakur                                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*
    FP-Growth Algorithm
    main.c
*/

//#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "FP_GROWTH.cpp"
#include "RULE_MINING.cpp"


int main()
{


  printf( "Enter the minimum support count [0-100]: " );
  scanf( "%lld", &minSupportCount );

  printf( "Enter the minimum confidence [0-1]: \n" );
  scanf("%Lf", &minConfidence);

  FP_Tree_generate();  //create the FP_Tree

  tree_growth();       //find the frequent itemsets using growth algorithm

  frequentItemSetRuleMining(minConfidence);  //form rules from the frequent itemsets

  return 0;
}



