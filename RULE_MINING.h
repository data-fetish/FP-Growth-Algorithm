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
    RULE_MINING.h
*/

#ifndef HEADER_FILE
#define HEADER_FILE

#ifdef __cplusplus

extern "C"
{

#endif

//declare functions here
  void checker();

  long long sup();

  void makePartitions();

  void generatePermutations(long long, long long);

  void frequentItemSetRuleMining(long double);
  


#ifdef __cplusplus

}

#endif

#endif


