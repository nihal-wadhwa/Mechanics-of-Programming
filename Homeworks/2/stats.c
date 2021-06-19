
/// file: stats.c
/// description: implementation for stats functions
/// @author RIT CS Dept.
/// @author Nihal Wadhwa (nw7554)
/////////////////////////////////////////////////// 

#include "stats.h"
#include <math.h>
#include <stdio.h>

/// compute and return the average of the data set
double average( int count, const int scores[] ) {
    double avg  = 0;
    for(int i = 0; i < count; i++)
    {
	avg += scores[i];
    }
    
    avg = avg/count;
    return avg;
}


/// compute and return the standard deviation of the data set
double std_dev(int count, const int scores[], double mean)
{
    double sum= 0;
    for(int i = 0; i < count; i++)
    {
        sum += pow((scores[i]- mean), 2);
    }
    sum = sum /(count-1);
    return sqrt(sum);
    
    
}
 

/// returns histogram categorizing array values into corresponding grade
/// ranges, and frequency of each grade
void histogram( int count, const int scores[] )
{
  int freq[10] = {0,0,0,0,0,0,0,0,0,0};
  for(int i = 0; i < count; i++)
  {
      if(scores[i]>=92)
      {
 	freq[0] += 1;
      }
      else if(scores[i]>=89 && scores[i]<92)
      {
        freq[1] += 1;
      }
      else if(scores[i]>=85 && scores[i]<89)
      {
        freq[2] += 1;
      }
      else if(scores[i]>=82 && scores[i]<85)
      {
        freq[3] += 1;
      }
      else if(scores[i]>=79 && scores[i]<82)
      {
        freq[4] += 1;
      }
      else if(scores[i]>=75 && scores[i]<79)
      {
	freq[5] += 1;	
      }
      else if(scores[i]>=72 && scores[i]<75)
      {
        freq[6] += 1;
      }
      else if(scores[i]>=69 && scores[i]<72)
      {
	freq[7] += 1;
      }
      else if(scores[i]>=60 && scores[i]<69)
      {
	freq[8] += 1;
      }
      else if(scores[i]<60)
      {
	freq[9] += 1;
      }
   }

    printf("A:\t%d\n", freq[0]);
    printf("A-:\t%d\n", freq[1]);
    printf("B+:\t%d\n", freq[2]);
    printf("B:\t%d\n", freq[3]);
    printf("B-:\t%d\n", freq[4]);
    printf("C+:\t%d\n", freq[5]);
    printf("C:\t%d\n", freq[6]);
    printf("C-:\t%d\n", freq[7]);
    printf("D:\t%d\n", freq[8]);
    printf("F: \t%d\n", freq[9]);
 }


