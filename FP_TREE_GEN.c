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
FILE *freqp;


void FP_Tree_generate()
{
  generateFrequentItemSets();  //from the input file, generate the frequent itemsets

  sortInputTransaction();
}


void generateFrequentItemSets()
{
  //get n and k values from the input file -- preprocess?
  long long currentItem, i;

  fp = fopen( "input.txt", "r" );

  fscanf( fp, "%lld %lld", &n, &k ); // n is number of datapoints, k is the number of distinct items

  minSupportCount = (long long)(minSupportCount*n/100); //minSupport is input as a percentage

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
    //printf("%lld %lld\n",itemSet[i].id, itemSet[i].support );
  }

  for(i=0; i<k; ++i)
  {
    if(itemSet[i].support < minSupportCount)
    {
      break;
    }

    //frequentItems[i] = itemSet[i].id; // frequent itemsets generated
    frequentItems[itemSet[i].id] = itemSet[i].support;
  }

  fclose(fp);
}


void sortInputTransaction()
{
  freqp = fopen("frequent.txt", "w");
  fp = fopen( "input.txt", "r" );

  char buf[500];
  //char *buf;
  //long long *tempItem, tempIdx, currentNum, i, currentLineLen;
  long long tempItem[75], tempIdx, currentNum, i, currentLineLen;
  //long long *currentLine;
  long long currentLine[75];
  size_t len = 500;
  ssize_t read;

  //buf = malloc(500*sizeof(char));//printf("one\n");
  //tempItem = malloc(k*sizeof(long long));
  //currentLine = malloc(k*sizeof(long long)); //giving malloc allocation error

  //fscanf( fp, "%lld %lld", &n, &k );
  //read = getline(&buf, &len, fp);

  fgets(buf, 500, fp);

  //sort the frequent itemsets
  //while( (read = getline(&buf, &len, fp))!=-1 )
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
    tempItem[tempIdx] = currentNum; //current line's numbers are in tempItem array  



    //currentLine = malloc(tempIdx*sizeof(long long));

    currentLineLen = 0;
    for( i=0; i<tempIdx; ++i )
    {
      if(frequentItems[tempItem[i]]==-1)
      {
        continue;
      }

      currentLine[currentLineLen++] = tempItem[i]; //fill currentLine with only frequent itemSets
    }

    qsort(currentLine, currentLineLen, sizeof(long long), comparator2);

    for( i=0; i<currentLineLen; ++i )
    {
      fprintf(freqp, "%lld ",currentLine[i] );
    }
    fprintf(freqp, "\n");

    //free(currentLine);
  }
  printf("\n");


  //free(buf);
  //free(tempItem);
  //free(currentLine);
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