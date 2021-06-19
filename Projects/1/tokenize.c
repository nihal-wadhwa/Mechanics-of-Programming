// file: tokenize.c
//
// Description: Used to take input file and convert to transition matrix
// and interpret input strings
// 
// @author Nihal Wadhwa (nw7554)
// // // // // // // // // // // // // // // // // // // // // // // // 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"
#include "scanner.h"


///main function
int main(int argc,  char* argv[] )
{

   if(argc < 2)
   {
     printf("Input Error");
   }

   node matrix[75][11];
   initMtrx(argv[1],75, matrix);
   printf("Scanning using the following matrix:\n");
   printMtrx(argv[1], 75, matrix);
  
   node currNode = {-1, ' '};
   char token;
   char buffer[79];
   int bufidx;
   int accept = getAccept(argv[1]);
   int start = getStart(argv[1]);

 
   while(!feof(stdin))
   {
      token = getchar();
      if(currNode.state == -1 )
      {
        printf("%d ", start);
      }
      
      currNode = classify(token,currNode, start , 75, matrix);
      printf("%d ",currNode.state);
      if(currNode.state == 99)
      {
        printf("rejected\n"); 
        while((token = getchar()) != 32 )
        {
        }
        currNode.state = -1;
        memset(buffer,0,79);
        bufidx = 0;
      }
      if(currNode.state == accept)
      {
        if(strlen(buffer) == 0)
        {
          printf("EOF");
        }
        else
        {
        printf("recognized \'%s\'\n", buffer);
        currNode.state = -1;
        memset(buffer,0,79);
        bufidx = 0;
        }
      }
      if(currNode.action == 's')
      {
        buffer[bufidx] = token;
        bufidx++;
      }
   }
   return 0;

}
