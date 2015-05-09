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
    FP-Tree Construction
    FP_TREE_GEN.h
*/


#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


struct itemNode
{
  long long id;
  long long support;
};

struct treeNode
{
  struct treeNode *parent;
  long long id;
  long long count;
  struct treeNode *horizontal;
  struct treeNode **children;
};

struct fList
{
  long long id;
  long long support;
  struct treeNode *ptr;
};


void FP_Tree_generate();

void generateFrequentItemSets();

void sortInputTransaction();

void createFPTree();

int comparator(const void *, const void *);

int comparator2(const void *, const void *);


extern long long minSupportCount;

extern struct treeNode *head;

extern long long numFreqItems;

extern struct fList freqList[100];

extern long double minConfidence;