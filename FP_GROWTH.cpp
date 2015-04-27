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
#include "FP_TREE_GEN.c"

using namespace std;

FILE *fitem;
FILE *fitem1, *fitem2, *fitem3, *fitem4, *fitem5, *fitem6,
     *fitem7, *fitem8, *fitem9, *fitem10;
stack< vector<long long> > s;
vector<long long> candidateItemSet;
long long totalSupport = 0;


extern "C" void checkPrinter()
{

  cout<<"im high as the moon== "<<minSupportCount<<endl;

}


extern "C" void initializeStack()
{
  //initialize the stack with single items frequent sets
  for(int i=0; i<numFreqItems; ++i)
  {
    vector<long long> temp;
    temp.push_back(freqList[i].id);
    s.push(temp);
  }

}


extern "C" void generateSubProblems()
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


extern "C" long long findIndex(long long p)
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



extern "C" int isCandidateFrequent()
{
  if(candidateItemSet.size()==1)
  {
    totalSupport = freqList[findIndex(candidateItemSet[0])].support;

    return 1;
  }

  long long currentSupport = 0;
  long long freqIdx, tempIdx;
  int setFound;

  totalSupport = 0;

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
        if(findIndex(currentPtr->id) < findIndex(candidateItemSet[tempIdx]))
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

        tempIdx++;
      }

      currentPtr = currentPtr->parent;
    } //end of while

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


extern "C" void fileInitializer()
{
  fitem1 = fopen("frequent1ItemSet.txt", "w");
  fitem2 = fopen("frequent2ItemSet.txt", "w");
  fitem3 = fopen("frequent3ItemSet.txt", "w");
  fitem4 = fopen("frequent4ItemSet.txt", "w");
  fitem5 = fopen("frequent5ItemSet.txt", "w");
  fitem6 = fopen("frequent6ItemSet.txt", "w");
  fitem7 = fopen("frequent7ItemSet.txt", "w");
  fitem8 = fopen("frequent8ItemSet.txt", "w");
  fitem9 = fopen("frequent9ItemSet.txt", "w");
  fitem10 = fopen("frequent10ItemSet.txt", "w");
}


extern "C" void tree_growth()
{

  fitem = fopen("frequentItemSet.txt","w");

  fileInitializer();

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

      // write to files
      switch(candidateItemSet.size())
      {
        case 1: for(int i=0; i<candidateItemSet.size(); ++i)
                {
                  fprintf(fitem1, "%lld ", candidateItemSet[i]);
                }
                fprintf(fitem1, "%lld ", totalSupport);
                fprintf(fitem1, "\n");
                break;

        case 2: for(int i=0; i<candidateItemSet.size(); ++i)
                {
                  fprintf(fitem2, "%lld ", candidateItemSet[i]);
                }
                fprintf(fitem2, "%lld ", totalSupport);
                fprintf(fitem2, "\n");
                break;

        case 3: for(int i=0; i<candidateItemSet.size(); ++i)
                {
                  fprintf(fitem3, "%lld ", candidateItemSet[i]);
                }
                fprintf(fitem3, "%lld ", totalSupport);
                fprintf(fitem3, "\n");
                break;

        case 4: for(int i=0; i<candidateItemSet.size(); ++i)
                {
                  fprintf(fitem4, "%lld ", candidateItemSet[i]);
                }
                fprintf(fitem4, "%lld ", totalSupport);
                fprintf(fitem4, "\n");
                break;

        case 5: for(int i=0; i<candidateItemSet.size(); ++i)
                {
                  fprintf(fitem5, "%lld ", candidateItemSet[i]);
                }
                fprintf(fitem5, "%lld ", totalSupport);
                fprintf(fitem5, "\n");
                break;

        case 6: for(int i=0; i<candidateItemSet.size(); ++i)
                {
                  fprintf(fitem6, "%lld ", candidateItemSet[i]);
                }
                fprintf(fitem6, "%lld ", totalSupport);
                fprintf(fitem6, "\n");
                break;

        case 7: for(int i=0; i<candidateItemSet.size(); ++i)
                {
                  fprintf(fitem7, "%lld ", candidateItemSet[i]);
                }
                fprintf(fitem7, "%lld ", totalSupport);
                fprintf(fitem7, "\n");
                break;

        case 8: for(int i=0; i<candidateItemSet.size(); ++i)
                {
                  fprintf(fitem8, "%lld ", candidateItemSet[i]);
                }
                fprintf(fitem8, "%lld ", totalSupport);
                fprintf(fitem8, "\n");
                break;

        case 9: for(int i=0; i<candidateItemSet.size(); ++i)
                {
                  fprintf(fitem9, "%lld ", candidateItemSet[i]);
                }
                fprintf(fitem9, "%lld ", totalSupport);
                fprintf(fitem9, "\n");
                break;

        case 10:for(int i=0; i<candidateItemSet.size(); ++i)
                {
                  fprintf(fitem10, "%lld ", candidateItemSet[i]);
                }
                fprintf(fitem10, "%lld ", totalSupport);
                fprintf(fitem10, "\n");
                break;

        default: cout<<"frequent "<<candidateItemSet.size()<<" itemsets are not considered"<<endl;
      }

      fprintf(fitem, "%lld ", totalSupport);
      fprintf(fitem, "\n");

      generateSubProblems();
    }

  }



  fclose(fitem);
  fcloseall();
}






