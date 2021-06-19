// file: mirsa_lib.c
// description: This program is the implementation of the Mirsa RSA
// Encryption Library of functions needed to implement RSA algorithm
//
//
// author: Nihal Wadhwa (nw7554)
// // // // // // // // // // // // // // // // // // // // // // // //
#include "mirsa_lib.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

//Global variable that keeps track of verbose
bool VERBOSE = false;

//Manipulates the verbose value and prints out diagnostic information
bool mr_verbose( bool value )
{
    if(value > 0)
    {
        VERBOSE = true;
        return value;
    }
    else
        return value;
}


//Gets prime value from the filename specified
//
//@param filename the string file name storing the prime numbers
//@return a prime value in the form of a uint64_t 
static uint64_t getPrimeValue(char * filename)
{
    FILE *fp;

    fp = fopen( filename,  "r" );

    // check to be sure the open succeeded
    if( fp == NULL )
    {
        // something went wrong - report it, and exit
        perror("Primes.txt");
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

    int val = rand() % arrSize;
    free(primeArr);
    return val;
}



//Returns the multiplicative inverse based on the extended Euclidean algorithm
//
//@param a represents the e integer in the RSA algorithm
//@param b represents the phi integer in the RSA algorithm
//
//@return multiplicative inverse of the two input integers.
static uint64_t inverse(uint64_t a, uint64_t b)
{

   uint64_t  old_r = a;
   uint64_t r = b;
   uint64_t old_s = 1;
   uint64_t s = 0;
   uint64_t old_t = 0;
   uint64_t t = 1;

   while(r != 0)
   {
      uint64_t quotient = old_r / r;
      uint64_t tempr = old_r;
      old_r = r;
      r = tempr-quotient*r;
      uint64_t temps = old_s;
      old_s = s;
      s = temps-quotient*s;
      uint64_t tempt = old_t;
      old_t = t;
      t = tempt - quotient*t;
      if(old_r == 1)
          return old_s + b;
   }
   return 0;
}


//Generates public and private keypairs based on RSA alg stores it in a binary file
bool mr_make_keys( uint64_t p, uint64_t q, const char * user )
{
    uint64_t n = p * q;
    uint64_t phi = (p-1)*(q-1);
    uint64_t e = 3;
    uint64_t d = 0;
    key_t private;
    key_t public;
    
    for(int c = 0; c < 4; c++)
    {
        if(n == 3)
        {
            fprintf(stderr, "error: mr_make_keys: overflow. no keyset for <%lu, %lu>.\n",p, q);
            return false;
        }
        if(__builtin_umull_overflow( p, q, &n))
        {
            char* file = "Primes.txt";
            p = getPrimeValue(file);
            q = getPrimeValue(file);
        }
    }
        

    while (e < 9) 
    { 
        // e must be co-prime to phi and 
        // smaller than phi. 
        if (inverse(e, phi)>0)
        { 
            d = inverse(e, phi);
            break; 
        }
        else
            e++; 
     }

    if(d == 0)
    {
        return false;
    }
    else
    {
        public.key = e;
        public.nonce = n;
        private.key = d;
        private.nonce = n; 
    }
    
    char* pubext = ".pub";
    char* prvext = ".pvt";
    char* userpub = (char *) malloc(sizeof(user) +sizeof(pubext));
    char* userpvt = (char *) malloc(sizeof(user) +sizeof(prvext));

    strcpy(userpub, user);
    strcpy(userpvt, user);

    strcat(userpub, pubext);
    strcat(userpvt, prvext); 

    FILE *f = fopen (userpub, "wb");
    if (f != NULL) {
        fwrite (&public, sizeof (key_t), 1, f);
        fclose (f);
    }
    else
    {
        fprintf( stderr, "error: miRSA could not open '%s' for writing.\n", userpub);
        return false;
    }

    f = fopen (userpvt, "wb");
    if (f != NULL) {
        fwrite (&private, sizeof (key_t), 1, f);
        fclose (f);
    }
    else
    {
        fprintf( stderr, "error: miRSA could not open '%s' for writing.\n", userpvt);
        return false;
    }
     
    free(userpub);
    free(userpvt);

    if(VERBOSE == true)
    {
        printf("Your e value is %lu.\nYour d value is %lu.\n",e,d);
        printf("The private key pair is %lu,%lu.\n",public.key, public.nonce);
        printf("The public key pair is %lu,%lu.\n", private.key, private.nonce);
    }

    return true;
}


//Reads a binary file file_name and returns the key pair stored within
key_t * mr_read_keyfile( const char * file_name )
{
    key_t *  keypair = (key_t *) malloc(sizeof(keypair)*2);
    FILE * fp;
    fp = fopen(file_name, "rb");
    if(fp == NULL)
    {
        fprintf( stderr, "error: miRSA could not open '%s' for writing.\n", file_name);
        exit(EXIT_FAILURE); 
    }
    else
    {
        while (1) 
        {
            fread(keypair, sizeof(key_t), 1, fp);
            if(feof(fp)) 
                break;
        }
        fclose(fp);
    }
    if(VERBOSE == true)
    {
       printf("Keypair interpreted from %s is %lu,%lu.", file_name, keypair->key, keypair->nonce);
    }  
    return keypair;
}


//Encrypts plaintext p using the public key pubkey
uint64_t mr_encrypt( uint64_t p, const key_t * pubkey)
{
    uint64_t x = p;
    uint64_t e = pubkey->key;
    uint64_t n = pubkey->nonce;
    uint64_t y = 1;
    uint64_t z = x;
    while (e != 0) 
    {
        if ((e % 2) != 0) 
            y = y * z % n ;
    
         z = z * z % n;
         e = e/2;
    }
   
    return y;
}

//Encrypts decrypts c using the private key pvtkey
uint64_t mr_decrypt( uint64_t c, const key_t * pvtkey)
{
    uint64_t x = c;
    uint64_t e = pvtkey->key;
    uint64_t n = pvtkey->nonce;
    uint64_t y = 1;
    uint64_t z = x;
    while (e != 0)
    {
        if ((e % 2) != 0) 
            y = y * z % n ;
    
        z = z * z % n;
        e = e/2;
    }
    return y;
}


//Encodes a string
uint64_t mr_encode( const char * st)
{

    char output[(strlen(st)*2)+1];
    int x = 0;
    int i = 0;

    while(st[x] != '\0')
    {
        sprintf((char*)(output+i),"%02X", st[x]);
        x+=1;
        i+=2;
    }

    output[i++] = '\0';

    uint64_t encode = (uint64_t) strtoul(output, NULL, 16);


    return encode;
}


//Returns of substring of string from position of length length
//To be used in mr_decode
//
//@param str represents string to be used make substring
//@param pos represents start of substring
//@param len represents length of substring
//
//@return substring of str
static char *substring(char *str, int pos, int len)
{
   char *sub;
   int x;

   sub = malloc(len+1);

   for (x = 0; x < len; x++)
   {
      *(sub+x) = *(str+pos-1);
      str++;
   }

   *(sub+x) = '\0';

   return sub;
}


//Decodes an integer to a string
char * mr_decode( uint64_t code)
{
    int nDigits = floor(log10(abs(code))) + 1;
    if(code == 0)
      nDigits = 1;
    char hex[(nDigits*2) +1];
    sprintf(hex, "%lx", code);
    char ascii[nDigits/2];
 
    for (size_t i = 0; i < strlen(hex); i += 2)
    {
        char * part = substring(hex, i-1, 2);
        char ch = strtoul(part, NULL, 16);
        strncat(ascii, &ch, sizeof(ch));
    }
    
    char *ret = malloc(strlen(ascii));
    strncpy(ret, ascii, strlen(ascii) );
    return ret;   
}

	
