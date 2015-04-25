/*----------------------------------------------------------------------------*/
/*                                                                            */
/*   Copyright (c) 2015 data-fetish                                           */
/*   All rights reserved.                                                     */
/*                                                                            */
/*   Team: Knowledge-mining                                                   */
/*                                                                            */
/*   Authors:  Akash Raj K N                                                  */
/*             Gopichand Paturi                                               */
/*             Anjali Thakur                                                  */
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

//#include "FP_TREE_GEN.c"
#include "FP_GROWTH.cpp"

int main()
{
  /*
     - get the min support count or percentage from user
       
     - FP-Tree-Generation
       - generate frequent itemset 
       - sort the input transactions in descending order based on frequent itemset support count
       - create the FP-tree

     - FP-Growth

  */

//  long long minSupportCount = 0;

  printf( "Enter the minimum support count: " );
  scanf( "%lld", &minSupportCount );

  //FP_Tree_Generation();
  FP_Tree_generate();
  //FP_Growth();

  //checkPrinter();

  tree_growth();

  return 0;
}



