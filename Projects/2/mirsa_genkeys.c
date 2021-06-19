//
// file: mirsa_genkeys.c
// Program that uses user input to create and store RSA keypairs in binary files
//
//
// @author Nihal Wadhwa (nw7554)
// // // // // // // // // // // // // // // // // // // // // // // //

#include <stdio.h>
#include <stdlib.h>
#include "mirsa_lib.h"
#include <getopt.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>

// default is not verbose
static size_t VERBOSE = 0;


// main
int main( int argc, char * argv[] ) {
    int opt;
    int numarg  = 0;
    int seed = -1;
    char* username = getlogin();
    while ( (opt = getopt( argc, argv, "hvk:s:") ) != -1 ) {
        switch ( opt ) {
        case 'h':
            fprintf( stderr, "usage: mirsa_genkeys [-hv] [-k keyname] [-s seed]\n" );
            exit( EXIT_SUCCESS);
            break;
        case 'v':
            VERBOSE = 1;
            mr_verbose(VERBOSE);
            break;
        case 'k':
            username  = optarg; 
            break;     
        case 's':
            numarg = (int)strtol( optarg, NULL, 10 );
            printf("%d",numarg);
            if(numarg < 0)
            {
                fprintf( stderr, "error: Invalid seed value \'%s\'\n",optarg );
                fprintf( stderr, "usage: mirsa_genkeys [-hv] [-k keyname] [-s seed]\n" );
                exit( EXIT_FAILURE );
            }
            else
                seed = numarg;
            break;
        default:
            // some unknown, possibly unacceptable option flag
            fprintf( stderr, "usage: mirsa_genkeys [-hv] [-k keyname] [-s seed]\n" );
            exit( EXIT_FAILURE );
            break;
        }
    }


    
    if(argv[optind] != NULL)
    {
    fprintf( stderr, "error: extra argument: \'%s\'\n",argv[optind]);
    fprintf( stderr, "usage: mirsa_genkeys [-hv] [-k keyname] [-s seed]" );
    exit( EXIT_FAILURE );
    }
    
    FILE *fp;

    fp = fopen( "Primes.txt",  "r" );

    // check to be sure the open succeeded
    if( fp == NULL )
    {
        // something went wrong - report it, and exit
        fprintf( stderr, "error: missing primes file.\n");
        exit( EXIT_FAILURE );
    }

    int arrSize = 0;
    fscanf(fp, "%d", &arrSize);
    
    uint64_t * primeArr = (uint64_t *)malloc(arrSize*sizeof(uint64_t));
    int i=0;
    for(; i<arrSize; i++)
    {
        fscanf(fp,"%lu",&(primeArr[i]));

    }                              
    fclose(fp);

    if(seed != -1)
    {
        srand(seed);

    }
    else
        srand(time(0));

    int val = rand() % arrSize;
    uint64_t p = primeArr[val];
    uint64_t q = primeArr[val];
   
    bool keygen =  mr_make_keys(p, q, username); 
    if(keygen == false)
    {
        exit(EXIT_FAILURE);
    }

    free(primeArr);
    return 0;
}

