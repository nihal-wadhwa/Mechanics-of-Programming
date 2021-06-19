// file: scanner.c
//
// Description: Scanner functions to get number of states, start state
// and accept state
//
// @@author Nihal Wadhwa (nw7554)
// // // // // // // // // // // // // // // // // // // // // // // //

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"


//Retrieves number of states from file
int getStates(char filename[])
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

    char *ptr;
    char buf[BUFLENGTH];
    int states = 0;
    char temp[8];
    ptr = fgets(buf, BUFLENGTH, fp);
    sscanf(ptr, "%s %d", temp, &states);

    // when done, close the input stream
    fclose( fp );

    return states;
}


//Retrieves start state from file
int getStart(char filename[])
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

    char *ptr;
    char buf[BUFLENGTH];
    int start = 0;
    char temp[8];

    for(int i = 1; i <= 2; i++)
    {
        ptr = fgets(buf, BUFLENGTH, fp);
        if(i == 2)
        {
           sscanf(ptr, "%s %d", temp, &start);
        }
    }

    // when done, close the input stream
    fclose( fp );

    return start;
}



//Retrieves accept state from file
int getAccept(char filename[])
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

    char *ptr;
    char buf[BUFLENGTH];
    int accept = 0;
    char temp[8];

        for(int i = 1; i <= 3; i++)
    {
        ptr = fgets(buf, BUFLENGTH, fp);
        if(i == 3)
        {
            sscanf(ptr, "%s %d", temp, &accept);
        }
    }
    // when done, close the input stream
    fclose( fp );

    return accept;
}


