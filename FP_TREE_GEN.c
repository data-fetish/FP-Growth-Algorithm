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
    FP_TREE_GEN.c
*/

#include "FP_TREE_GEN.h"


//global variables
long long minSupportCount = 0;
long long n ,k;
struct itemNode *itemSet;
long long *frequentItems;

FILE *fp;


extern void FP_Tree_Generation( long long minSupport )
{
  minSupportCount = (long long)(minSupport*n/100); //minSupport is input as a percentage

  generateFrequentItemSets();  //from the input file, generate the frequent itemsets
}


void generateFrequentItemSets()
{
  //get n and k values from the input file -- preprocess?
  long long currentItem, i;

  fp = fopen( "input.txt", "r" );

  fscanf( fp, "%lld %lld", &n, &k ); // n is number of datapoints, k is the number of distinct items

  itemSet = malloc( k * sizeof(struct itemNode) ); //create an itemset to find the support count of each item

  //initialize the itemSet with the itemnumbers
  for( i=0; i<k; ++i )
  {
    itemSet[i].id = i+1;
  }

  while( (fscanf(fp, "%lld", &currentItem))!=EOF )
  {
    (itemSet[currentItem-1].support)++; //increment current item's support count
  }

  //sort in decreasing order of support
  qsort( itemSet, k, sizeof(struct itemNode), comparator );

  //generate the frequent itemsets
  frequentItems = malloc( k*sizeof(long long));

  for(i=0; i<k; ++i)
  {
    frequentItems[i] = -1; //initialize with -1
  }

  for(i=0; i<k; ++i)
  {
    if(itemSet[i].support < minSupportCount)
    {
      break;
    }

    frequentItems[i] = itemSet[i].id; // frequent itemsets generated
  }

  sortInputTransaction();
}


void sortInputTransaction()
{
  
}


int comparator( const void *p, const void *q )
{
  long long l = ((struct itemNode *)p)->support;
  long long r = ((struct itemNode *)q)->support;

  return (r-l);
}