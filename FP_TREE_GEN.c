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
    FP_TREE_GEN.c
*/

#include "FP_TREE_GEN.h"


//global variables
long long minSupportCount = 0;
long long n ,k;
long long numFreqItems = 0;
struct itemNode *itemSet;
long long *frequentItems;
struct treeNode *head = NULL;
long double minConfidence = 0;

struct fList freqList[100]; /* have to make it dynamic allocation */

FILE *fp;
FILE *freqp;


void FP_Tree_generate()
{
  generateFrequentItemSets();  //from the input file, generate the frequent itemsets

  sortInputTransaction();      //sort input tid based on support and discard infrequent items

  createFPTree();
}


void generateFrequentItemSets()
{
  //get n and k values from the input file -- preprocess?
  long long currentItem, i;

  fp = fopen( "input.txt", "r" );

  fscanf( fp, "%lld %lld", &n, &k ); // n is number of datapoints, k is the number of distinct items

  minSupportCount = (long long)(minSupportCount*n/100); //minSupport is input as a percentage

  itemSet = (struct itemNode *)malloc( k * sizeof(struct itemNode) ); //create an itemset to find the support count of each item

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
  frequentItems = (long long *)malloc( (k+1)*sizeof(long long));//the numbers are 1-based eg 1-75

  for(i=0; i<=k; ++i)
  {
    frequentItems[i] = -1; //initialize with -1
  }

  for(i=0; i<=k; ++i)
  {
    if(itemSet[i].support < minSupportCount)
    {
      break;
    }

    frequentItems[itemSet[i].id] = itemSet[i].support;
  }


  /* create the table for the FP-Tree */
  numFreqItems = i; //number of frequent items (with support > than minSupportCount)

  for( i=0; i<numFreqItems; ++i )
  {
    freqList[i].id = itemSet[i].id;
    freqList[i].support = itemSet[i].support;
    freqList[i].ptr = NULL;
  }

  fclose(fp);
}


void sortInputTransaction()
{
  freqp = fopen("frequent.txt", "w");
  fp = fopen( "input.txt", "r" );

  char buf[500];

  long long tempItem[k], tempIdx, currentNum, i, currentLineLen;
  
  long long currentLine[k]; //current line that is read, sorted

  fgets(buf, 500, fp);int counter = 0;

  while( (fgets(buf, 500,fp))!=NULL )
  {
    tempIdx = 0;
    currentNum = 0;
    //printf("%s\n\n",buf );
    for( i = 0; i<strlen(buf); ++i )
    {
      if(buf[i]!=' ')
      {
        currentNum *= 10;
        currentNum += (buf[i]-'0');
      }
      else
      {
        tempItem[tempIdx++] = currentNum;
        currentNum = 0;
      } 
    }

    currentLineLen = 0;
    for( i=0; i<tempIdx; ++i )
    {
      if(frequentItems[tempItem[i]]==-1)
      {
        continue;
      }

      currentLine[currentLineLen++] = tempItem[i]; //fill currentLine with only frequent itemSets
    }

    qsort(currentLine, currentLineLen, sizeof(long long), comparator2); //sort the current line of transactions

    for( i=0; i<currentLineLen; ++i )
    {
      fprintf(freqp, "%lld ",currentLine[i] );
    }
    fprintf(freqp, "\n");
  }

  printf("\n");

  fclose(fp);

  fclose(freqp);

}


int comparator( const void *p, const void *q )
{
  long long l = ((struct itemNode *)p)->support;
  long long r = ((struct itemNode *)q)->support;

  return (r-l);
}

int comparator2( const void *p, const void *q )
{
  long long l = frequentItems[*(long long *)p];
  long long r = frequentItems[*(long long *)q];

  return (r-l);
}


void createFPTree()
{
  freqp = fopen("frequent.txt", "r");

  char buf[500];
  long long currentNum, i, j, l;
  struct treeNode *currentPtr; //points to the current transaction path in the tree
  struct treeNode *horizontalPtr, *prevHorizontal, **tempPtr1;

  // initialize the null node 
  head = (struct treeNode *)malloc(sizeof(struct treeNode));
  head->children = (struct treeNode **)malloc(numFreqItems * sizeof(struct treeNode *));
  for(j=0; j<numFreqItems; ++j)
  {
    head->children[j] = NULL;
  }
  head->parent = NULL;
  head->id = 0;
  head->count = -1;
  head->horizontal = NULL;


  while( fgets(buf, 500, freqp)!=NULL ) //start reading the transactions line by line
  {
    currentNum = 0;
    currentPtr = head;

    for( i = 0; i<strlen(buf); ++i )
    {
      if(buf[i]!=' ')
      {
        currentNum *= 10;
        currentNum += (buf[i]-'0');
      }
      else
      {
        /* add the current num into the tree */

        //find the currentNum index in freqList array --- can be improved with binary search
        //linear search
        for(j=0; j<numFreqItems; ++j)
        {
          if(freqList[j].id == currentNum)
          {
            break;
          }
        }

        if(currentPtr->children[j] == NULL)
        {
          currentPtr->children[j] = (struct treeNode *)malloc(sizeof(struct treeNode));
          currentPtr->children[j]->id = currentNum;
          currentPtr->children[j]->parent = currentPtr;
          currentPtr->children[j]->count = 1;
          currentPtr->children[j]->horizontal = NULL; //if you remove this stmt, all hell will break loose

          struct treeNode **temp2ptr;

          if(freqList[j].ptr == NULL)
          {
            freqList[j].ptr = currentPtr->children[j]; 
          }
          else //if(currentPtr->children[j]->horizontal == NULL)
          {
            horizontalPtr = freqList[j].ptr;
            prevHorizontal = NULL;  

            while(horizontalPtr != NULL)
            {
              prevHorizontal = horizontalPtr;
              temp2ptr = &(horizontalPtr->horizontal);
              horizontalPtr = *temp2ptr;
            }

            if(prevHorizontal != currentPtr->children[j])
            {
              *temp2ptr = currentPtr->children[j];  
            }
            
            //print the path here
          }
    
          currentPtr->children[j]->children = (struct treeNode **)malloc(numFreqItems * sizeof(struct treeNode));
          for(l=0; l<numFreqItems; ++l)
          {
            currentPtr->children[j]->children[l] = NULL;
          }

        }
        else
        {
          currentPtr->children[j]->count++;
        }
        
        currentPtr = currentPtr->children[j]; // point to next child in the path

        currentNum = 0;
      }
    }

  }

  fclose(freqp);
}



