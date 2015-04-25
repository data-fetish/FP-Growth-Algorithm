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
  FP-Growth - Generation of frequent itemsets
  FP_GROWTH.cpp
*/

#include <bits/stdc++.h>
#include <vector>
#include "FP_TREE_GEN.c"

using namespace std;

FILE *fitem;
stack< vector<long long> > s;
vector<long long> candidateItemSet;


void checkPrinter()
{

  cout<<"im high as the moon== "<<minSupportCount<<endl;

}


void initializeStack()
{
  //initialize the stack with single items frequent sets
  for(int i=0; i<numFreqItems; ++i)
  {
    vector<long long> temp;
    temp.push_back(freqList[i].id);
    s.push(temp);
  }

}


void generateSubProblems()
{
  int len = candidateItemSet.size();
  long long lastOne = candidateItemSet[len-1];

  vector<long long> candidateExtend, tempvec;

  candidateExtend = candidateItemSet;
  candidateExtend.push_back(-1);


  for(int i=0; i<numFreqItems; ++i)
  {
    if(lastOne==freqList[i].id)
    {
      break;
    }
    
    candidateExtend[len] = freqList[i].id;

    s.push(candidateExtend);
    /*tempvec = s.top();

    for(int j=0; j<tempvec.size();++j)
    {
      cout<<tempvec[j]<<" ";
    }
    cout<<endl;*/
  }
}


long long findIndex(long long p)
{
  //linear search the freqList for the current item id
  long long idx = -1;

  for(int i=0; i<numFreqItems; ++i)
  {
    if(freqList[i].id == p)
    {
      idx = i;
      break;
    }
  }

  return idx;
}



int isCandidateFrequent()
{
  if(candidateItemSet.size()==1)
  {
    return 1;
  }

  long long currentSupport = 0, totalSupport = 0;
  long long freqIdx, tempIdx;
  int setFound;

  struct treeNode *currentPtr, *horizontalPtr;

  //find the index of the frequent item in the freqList table, uses linear search
  //can be optimized with binary search
  for(int i=0; i<numFreqItems; ++i)
  {
    if(freqList[i].id==candidateItemSet[0])
    {
      freqIdx = i;
      break;
    }
  }

  horizontalPtr = freqList[freqIdx].ptr;

  //go to all paths which end with freqList[i].id
  while(horizontalPtr!=NULL)
  {
    currentPtr = horizontalPtr;
    tempIdx = 0; //to iterate the candidateItemSet
    setFound = 1; //default, the candidateItemSet is present in the current path
    currentSupport = currentPtr->count;

    //search if the entire itemSet is in the path
    while(currentPtr!=head)
    {
      if(currentPtr->id != candidateItemSet[tempIdx]) //current id in the path is not equal to the candidate[idx]
      {
        if(findIndex(currentPtr->id) > findIndex(candidateItemSet[tempIdx]))
        {
          setFound = 0;
          break;
        }
      }
      else
      {
        if(tempIdx == candidateItemSet.size()-1) //if the entire itemSet is found, then exit
        {
          break;
        }
      }

      currentPtr = currentPtr->parent;
    }

    if(setFound)
    {
      totalSupport += currentSupport;
    }

    horizontalPtr = horizontalPtr->horizontal; //go to the next horizontal pointer
  }
/*
  for(int i=0; i<candidateItemSet.size(); ++i)
  {
    printf("%lld  ", candidateItemSet[i]);
  }
  printf("\n");

  cout<<"support="<<totalSupport<<endl;
*/
  return totalSupport>minSupportCount?1:0;

}


void tree_growth()
{

  fitem = fopen("frequentItemSet.txt","w");

  initializeStack();

  while(!s.empty())
  {
    candidateItemSet = s.top(); //take top of stack
    s.pop();

    if(isCandidateFrequent())
    {
      //write to file the current frequent ItemSet
      for(int i=0; i<candidateItemSet.size(); ++i)
      {
        fprintf(fitem, "%lld ", candidateItemSet[i]);
      }
      fprintf(fitem, "\n");

      generateSubProblems();
    }

  }



  fclose(fitem);
}






