// file: matrix.c
//
// Description: Used to create and print transition matrix
// 
// @@author Nihal Wadhwa (nw7554)
// // // // // // // // // // // // // // // // // // // // // // // //

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"
#include "scanner.h"


//Prints matrix
void printMtrx(char filename[], int size, node  matrix[size][size])
{

    int states = getStates(filename);
    printf("  ");
    for(int row = 0; row < states+1; row++)
    {
        printf("  %2d ", row);
    }
    
    printf("\n");

    for(int row = 0; row < states; row++)
    { 
        printf(" %d", row);
        for(int col = 0; col < 11; col++)
        {
          printf("  %2d%c",matrix[row][col].state, matrix[row][col].action);   
        }
        printf("\n");
    }
    
}



//Uses file to initialize and fill transition matrix 
void initMtrx(char filename[], int size, node matrix[size][size])
{
    FILE *fp;

    // open the TM file
    fp = fopen( filename,  "r" );

    // check to be sure the open succeeded
    if( fp == NULL )
    {
        // something went wrong - report it, and exit
        perror( filename );
        exit( EXIT_FAILURE );
    }

    int BUFLENGTH = 127;

    char *ptr, *str;
    char buf[BUFLENGTH];
    int states = getStates(filename);
    node tem;
    char strl[5];
 
    int colState,nextState, rowState = 0;
    char act;
    
    node error = {99, 'd'};
    for(int row = 0; row < states; row++)
    {
        for(int col = 0; col < 11; col++)
        {
             matrix[row][col] = error;
        }
    } 
    
   for(int line = 0; line < 3; line++)
   {
      ptr = fgets(buf, BUFLENGTH, fp);
   }
  
    while( (ptr = fgets(buf, BUFLENGTH, fp)) != NULL )
    {
        str = strtok(ptr, " ");
        sscanf(str, "%d", &rowState);
        while( (str=strtok(NULL, " "))  != NULL )
        {
            sscanf(str, "%d/%s" , &colState , strl);
            sscanf(strl, "%d%c", &nextState, &act);
            tem.state = nextState;
            tem.action = act;
            matrix[rowState][colState] = tem;
        }
      
    }

   
   // when done, close the input stream
   fclose( fp );
}


//Classifies a single token and returns the state and action
node classify(char token, node prev, int start,  int size, node matrix[size][size])
{

    if( (token == 32) || (token == 9) || (token == 10) )
    {
        if(prev.state == -1)
        {
            return  matrix[start][0];
        }
        else
            return matrix[prev.state][0];
    }
    else if( ((token >= 65) && (token <= 90)) || ((token >= 97) && (token <= 122)) || ((token == 95 )) )
    {
        if(prev.state == -1)
        {
            return  matrix[start][1];
        } 
        else
            return matrix[prev.state][1];
    }
   else if(token == 48)
   {
        if(prev.state == -1)
        {
            return  matrix[start][2];
        }
        else
            return matrix[prev.state][2];

   }    
   else if( (token >= 48) && (token <= 55) )
   {
       if(prev.state == -1)
        {
            return  matrix[start][3];
        }
        else
            return matrix[prev.state][3];

   }
   else if( (token == 56) || (token == 57) )
   {
       if(prev.state == -1)
        {
            return  matrix[start][4];
        }
        else
            return matrix[prev.state][4]; 

   } 
   else if(token == 47)
   {
        if(prev.state == -1)
        {
            return  matrix[start][5];
        }
        else
            return matrix[prev.state][5];

   }
   else if(token == 42)
   {
        if(prev.state == -1)
        {
            return  matrix[start][6];
        }
        else
            return matrix[prev.state][6];

   }
   else if((token == 43) || (token == 45) || (token == 37) )
   {
        if(prev.state == -1)
        {
            return  matrix[start][7];
        }
        else
            return matrix[prev.state][7];

   }
   else if( (token >= 0) && (token < 127) )
   {
       if(prev.state == -1)
        {
            return  matrix[start][8];
        }
        else
            return matrix[prev.state][8];
   }
   else if(token == EOF)
   {
       if(prev.state == -1)
        {
            return  matrix[start][9];
        }
        else
            return matrix[prev.state][9];

   }
   else
   {
      if(prev.state == -1)
        {
            return  matrix[start][10];
        }
        else
            return matrix[prev.state][10];
   }
   
}
