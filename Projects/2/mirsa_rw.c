//
// file: mirsa_rw.c
// Program that uses user input to read or write cipherfiles and plain
// text 
//
// @author Nihal Wadhwa (nw7554)
// // // // // // // // // // // // // // // // // // // // // // // //

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <getopt.h>
#include <stdbool.h>
#include "mirsa_lib.h"
#include <time.h>
#include <unistd.h>
#include <string.h>

// default is not verbose
static size_t VERBOSE = 0;


//main
int main(int argc, char* argv[]) {
    char* user  = getlogin();
    char* pubext = ".pub";
    char* prvext = ".pvt";
    char* userpub = (char *) malloc(sizeof(user) +sizeof(pubext));
    char* userpvt = (char *) malloc(sizeof(user) +sizeof(prvext));

    strcpy(userpub, user);
    strcpy(userpvt, user);

    strcat(userpub, pubext);
    strcat(userpvt, prvext);
    
    int opt;
    FILE * fr;
    FILE * fw;
    unsigned char buf[4];
    size_t bytes = 0;
    size_t readsz = sizeof(unsigned char) * 4;
    while ( (opt = getopt( argc, argv, "hvk:r:w:") ) != -1 ) 
    {
        switch ( opt ) 
        {
        case 'h':
            fprintf( stderr, "usage:\nReader use: mirsa_rw [-hv] [-k keyname] -r cipherfile [plainfile] \n" );
            fprintf( stderr, "\tIf plainfile is not provided, then reader output is to stdout.\n"); 
            fprintf( stderr, "Writer use: mirsa_rw [-hv] [-k keyname] -w cipherfile [plainfile] \n" );
            fprintf( stderr, "\tIf plainfile is not provided, then writer output is to stdout.\n");
            fprintf( stderr, "The -v flag turns on verbose output.\n"); 
            free(userpub);
            free(userpvt);
            exit( EXIT_SUCCESS);
            break;
        case 'v':
            VERBOSE = 1;
            mr_verbose(VERBOSE);
            break;
        case 'k':
            userpvt = optarg;
            userpub = optarg;
            if(optarg == NULL)
            {
                 fprintf( stderr, "error: missing file argument\n" );
                 free(userpub);
                 free(userpvt);
                 return EXIT_FAILURE; 
            }
            break; 
        case 'r':
            if(argc > 2)
              fr = fopen(optarg, "rb");

            if (!fr) {
              fprintf (stderr, "error: miRSA could not read '%s' content.\n", optarg);
              free(userpub);
              free(userpvt);
              return EXIT_FAILURE;
            }

            if (argc > 3)
                fw = fopen(argv[argc-1], "wb");
            else
                fw = stdout;

            if(!fw)
            {
                fprintf (stderr, "error: miRSA could not open '%s' for writing.\n", argv[argc-1]);
                free(userpub);
                free(userpvt);
                return EXIT_FAILURE; 
            }
             
            key_t * ptkey = mr_read_keyfile(userpvt);
 
            while ((bytes = fread (buf, sizeof *buf, readsz, fr)) == readsz) {
                uint64_t decode =  mr_decrypt(*(int *)buf , ptkey);
                char * text_chunk = mr_decode( decode);
                fwrite(text_chunk,4,sizeof(text_chunk),fw);
            }
 
            if(fw == stdout) 
                putchar('\n');
            

            if (fw != stdout)
               fclose (fw);
            fclose(fr);
            break;
        case 'w':
            if(argc > 2)
              fw = fopen(optarg, "rb");

            if (!fw) 
            {
               fprintf (stderr, "error: miRSA could not open '%s' for writing.\n", argv[argc-1]);
               free(userpub);
               free(userpvt);
               return EXIT_FAILURE;
            }

            if (argc > 3)
                fr = fopen(argv[argc-1], "wb");
            else
                fr = stdin;

            if(!fr)
            {
                fprintf (stderr, "error: miRSA could not read '%s' content.\n", optarg);
                free(userpub);
                free(userpvt);
                return EXIT_FAILURE;
            }

            key_t * pubkey = mr_read_keyfile(userpub);

            while ((bytes = fread (buf, sizeof *buf, readsz, fr)) == readsz) 
            {
                uint64_t code =  mr_encode((char*)buf);
                uint64_t cipher = mr_encrypt(code,pubkey);
                fwrite(&cipher,4,sizeof(cipher),fw);
            }

            if (fr != stdin)
               fclose (fr);
            fclose(fw);
            break;
        case '?':
            fprintf (stderr, "error: missing file argument.\n");
            free(userpub);
            free(userpvt);
            return EXIT_FAILURE;
            break;
        default:
            fprintf (stderr, "error: unknown flag\n");
            free(userpub);
            free(userpvt);
            return EXIT_FAILURE;
            break;
       }

       free(userpub);
       free(userpvt);
   }
}
