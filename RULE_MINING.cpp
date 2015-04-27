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
    rule mining from frequent item sets
    RULE_MINING.cpp
*/

//#pragma once
#include <bits/stdc++.h>
#include "RULE_MINING.h"

using namespace std;

FILE *freq, *tfreq;
FILE *rgen;                        //the rules are written to this file
vector <long long> currentSet;     //the current set that was read
char buf[500], tbuf[500];
long long idx ,currentNum;         //the current number parsed from the frequentItemSet file
long long currentSupport;          //records the support of the current frequent itemset
vector <long long> tempCurrentSet;
vector <long long> leftHandSide;
long double minConfRule;


extern "C" void checker()
{
  cout<<"whaaat?"<<endl;
}


extern "C" long long sup()
{
  long long ans;
  bool isSame;

  tfreq = fopen("frequentItemSet.txt", "r");

  //find the support of leftHandSide
  sort(leftHandSide.begin(), leftHandSide.end());

  long long tidx, tnum;
  vector <long long> tcurr;

  while( fgets(tbuf, 500, tfreq) != NULL )
  {
    isSame = true;
    tidx = 0;
    tnum = 0;
    tcurr.clear();

    for(int i=0; i<strlen(tbuf); ++i)
    {
      if(tbuf[i]!=' ')
      {
        tnum *= 10;
        tnum += (tbuf[i]-'0');
      }
      else
      {
        tcurr.push_back(tnum);
        tidx++;
        tnum = 0;
      } 
    }

    //current line is in tcurr
    sort(tcurr.begin(), tcurr.begin()+tidx);

    for( int i=0; i<tcurr.size()-1; ++i)
    {
      if(tcurr[i] != leftHandSide[i])
      {
        isSame = false;
        break;
      }
    }

    if(isSame)
    {
      ans = tcurr[tidx-1];
      break;
    }

  }


  fclose(tfreq);

  return ans;
}


extern "C" void makePartitions()
{
  /*
      suppose currentSet = {A,B,C,D}..... partitions make= A->BCD, AB->CD, ABC->D
  */
  long double currentConfidence;

  for(int i=1; i<tempCurrentSet.size(); ++i)
  {
    //current rule = vj(j=0 to i) -> vl(l=i+1 to tempCurrentSet.size())
    for(int j= 0 ; j<i; ++j)
    {
      leftHandSide.push_back(tempCurrentSet[j]);
    }

    currentConfidence = ((long double) currentSet[idx-1]) / ((long double)sup()); //current rule's confidence

    if(currentConfidence > minConfRule)
    {

      //this rule is allowed
      fprintf(rgen, "( " );
      for(int j = 0; j<i; ++j)
      {
        fprintf(rgen, "%lld ", tempCurrentSet[j]);
      }
      fprintf(rgen, ")" );

      fprintf(rgen, " --> " );

      fprintf(rgen, "( " );
      for(int j = i; j<tempCurrentSet.size(); ++j)
      {
        fprintf(rgen, "%lld ", tempCurrentSet[j]);
      }
      fprintf(rgen, ")" );

      fprintf(rgen, "    confidence = %Lf ", currentConfidence);

      fprintf(rgen, "\n");
    }

    leftHandSide.clear();
    break;
  }
}



extern "C" void generatePermutations(long long a, long long n)
{
  if(a==n)
  {
    //this a permutation
    //find all the parititions of this rule and check if confidence of the rules are > minConfRule
    makePartitions();
  }
  else
  {
    for(int j=a; j<=n; ++j)
    {
      iter_swap(tempCurrentSet.begin()+a, tempCurrentSet.begin()+j);
      generatePermutations(a+1, n);
      iter_swap(tempCurrentSet.begin()+a, tempCurrentSet.begin()+j);
    }
  }
  
}



extern "C" void frequentItemSetRuleMining(long double minc)
{
  /*
    read from freq itemset file
    for each frequent set
      generate the permutations of the set
      for each permutation
        generate rules by partitioning
          for each partition, 
            if the rule confidence > minconf
              print the rule

  */

  minConfRule = minc;

  freq = fopen("frequentItemSet.txt", "r");
  rgen = fopen("generatedRules.txt", "w");  //write the generated rules in this doc

  while( fgets(buf, 500, freq) != NULL )
  {
    idx = 0;
    currentNum = 0;
    currentSet.clear();                     //clear the previous vector before adding items of new set
    tempCurrentSet.clear();

    for(int i=0; i<strlen(buf); ++i)
    {
      if(buf[i]!=' ')
      {
        currentNum *= 10;
        currentNum += (buf[i]-'0');
      }
      else
      {
        currentSet.push_back(currentNum);
        idx++;
        currentNum = 0;
      } 
    }

    for(int i=0; i<idx-1; ++i)
    {
      tempCurrentSet.push_back(currentSet[i]);
    }

    //now currentSet has the numbers, the last item in the vector is the support of this set
    currentSupport = currentSet[idx-1];
    
    if(idx==2) //frequent 1 itemSets, cant form rules
    {
      continue;
    }

    generatePermutations(0, idx-2); //0 to size-1



  } //while loop ends here --- while loop is freq itemset loop



  fclose(freq);
  fclose(rgen);

}


