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
  FP_GROWTH.h
*/

#ifndef HEADER_FILE
#define HEADER_FILE

#ifdef __cplusplus

extern "C"
{

#endif

//declare functions here
  void checkPrinter();

  void initializeStack();

  long long findIndex(long long);

  int isCandidateFrequent();

  void generateSubProblems();

  void tree_growth();

  void fileInitializer();

#ifdef __cplusplus

}

#endif

#endif

