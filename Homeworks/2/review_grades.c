// 
// file: review_grades.c
// implements stats functions and creates output
// 
// 
// @author Nihal Wadhwa
// // // // // // // // // // // // // // // // // // // // // // // // 

#include <stdio.h>
#include <stdlib.h>
#include "stats.h" 
#include <ctype.h>
#include <math.h>

//Converts string to int by manipulating ASCII val in ch array
//@param str input string in form of char array
//@return integer of equivalent value
int str_to_int(char str[])
{

  int value = 0;
  for(int i = 0; str[i] != '\0'; i++)
  {
   if( isdigit(str[i]))
   {        
      value = (value * 10) + (str[i]- '0'); 
   }
   else
   {
     break;
   }
  }

  return value;
}


/// Takes input from user and return output statistics for grades
/// @param argc number of command line tokens
/// @param argv array of C string values, the command line arguments
///
/// @return 0 to tell the OS that the process ran successfully, OR
///         return 1 to tell the OS that the result was out of range.
int main(int argc, char *argv[])
{

  printf("input population: %d\n", argc-1);

  int negs = 0;
  for(int i = 1; i < argc; i++)
  {
    if (argv[i][0] == '-')
    {
	negs++;
    }
  }
  
  int adjLength = argc-negs-1;
  int scores[adjLength];
  int x = 0;
  for(int i = 1; i < argc; i++)
  {
     if (argv[i][0] != '-')
     {
       scores[x]= str_to_int(argv[i]);
       printf("%d ",scores[x]);
       x++;
      }
  }
  printf("\nadjusted population: %d\n",adjLength);
  printf("mean: %f\n", average(adjLength, scores));
  printf("std deviation: %f\n", std_dev(adjLength, scores,average(adjLength, scores) ));
  histogram(adjLength, scores);

  return 0;
}
