//
// file: string.c
// Program for creating and manipulating strings
//
//
// @author Nihal Wadhwa (nw7554)
// // // // // // // // // // // // // // // // // // // // // // // //

#include <stdio.h>
#include <stdlib.h>
#include "String.h"
#include <assert.h>

//Struct for storing Strings
typedef struct string_s
{
    size_t length;
    size_t capacity;
    char* data; 

} string_s;

//Creates a string based on the size, length, and data specified
String str_create( size_t size, size_t length, const unsigned char *data )
{
    String new;

    new = (String) malloc ( sizeof(struct string_s) );
    if(size == 0)
    {
        new->capacity = 0;
        new->length = 0;
    }
    else
    {
        if(length == 0 || data == NULL)
        {
            new->length = 0;
        }
        else
        {
            new->length = length;
            if(size>length)
                new->capacity = size;
            else
            {
                new->capacity = length;
                new->data = (char *)malloc(sizeof(char)*new->capacity);
                for(unsigned int i = 0; i < length; i++)
                {
                    new->data[i] = data[i];
                }
            }
        }
    }
    
    return new;
}

//Restores the memory allocated by String
void str_destroy( String str )
{
    assert( str != NULL );
    free(str->data);
    free(str);
}


//Converts String to a C String
char *str_to_c( const String str )
{
    assert( str != NULL ); 
    char * c_string;
    c_string = (char *) calloc(sizeof(char*), str->capacity);
    for(unsigned int i = 0; i < str->length; i++)
    {
        c_string[i] = str->data[i];

    }
    
    return c_string;

}


//Returns the length of string
size_t str_length( const String str )
{
    assert( str != NULL ); 
    return str->length;

}


//Creates and returns a string that is the reverse of the source string
String str_reverse( const String src )
{  
    assert( src != NULL ); 
    if(src->length == 0 || src->data == NULL)
    {
        return NULL;
    }
    else
    {
        String dst =  str_create( src->capacity, src->length, NULL);
        dst->length = src->length;
        dst->capacity = dst->length;
        dst->data = (char *)malloc(sizeof(char)*src->capacity);
        int x = 0;
        for(size_t i = src->length-1; i>0; i--)
        { 
            dst->data[x] = src->data[i];
            x++;
        }
        dst->data[src->length-1] = src->data[0];
        return dst; 

    }
    return NULL;
}


//Copies one string and overwrites the other string with the source string
size_t str_copy( String dst, const String src )
{
    assert( src != NULL );
    assert( dst != NULL );
    if(dst->capacity <  src->capacity)
    {
        dst = (String) realloc (dst, sizeof(src) );
        dst->capacity = src->capacity;
    }
    dst->length = src->length;    
    for(size_t i = 0; i < src->length; i++)
    {
        dst->data[i] = src->data[i];
    }
    
    return src->length;
}


//Concatenates two Strings together and returns the resulting String
size_t str_concat( String dst, String src)
{
    assert( dst != NULL );
    assert( src != NULL );
    size_t i = dst->length;
    dst = (String) realloc (dst, sizeof(src)+sizeof(dst));
    dst->capacity += src->capacity;
    dst->length += src->length;
    int x = 0;
    for(; i < dst->length; i++)
    {
        dst->data[i] = src->data[x];
        x++;
    }
    return dst->length;    
}


//Compares two strings and returns the comparison as an int
int str_compare( String s1, String s2)
{
    assert( s1 != NULL );
    assert( s2 != NULL );
    if(s1->capacity < s2->capacity)
        return 1;
    else if(s1->capacity == s2->capacity)
        return 0;
    else
        return -1;
}


//Returns the character at a specific index specified
int str_char_at( String str, int index )
{    
    assert( str != NULL );
    if((size_t)index > str->length)
       return STR_ERROR;
    else if(&str->data[index] == NULL)
       return 0;
    else
       return (char) str->data[index];
}



//Returns a String of the substring with the start and end specified
String str_substring( const String str, int start, int end)
{
    assert( str != NULL ); 
    int negstart, negend;
    String dst =  str_create( str->capacity, str->length, NULL);
    dst->length = str->length;
    if(start<0 && end<0)
    {
       negstart = str->length + start;
       negend = str->length + end;
       if(negend > negstart)
       {
            dst->data = (char *) malloc(sizeof(char)* (negend-negstart));
            int x = 0;
            for(int i = negstart; i<= negend; i++)
            {
                dst->data[x] = str->data[i];
                x++;
            }
        }
        else
        {
            dst->data = (char *) malloc(sizeof(char)* (negstart-negend));
            int x = 0;
            for(int i = negend; i<= negstart; i++)
            {
                dst->data[x] = str->data[i];
                x++;
            }
        }

    }
    else if(start<0)
    {
       negstart = str->length - start;
       if(end > negstart)
       {
            dst->data = (char *) malloc(sizeof(char)* (end-negstart));
            int x = 0;
            for(int i = negstart; i<= end; i++)
            {
                dst->data[x] = str->data[i];
                x++;
            }
        }
        else
        {
            dst->data = (char *) malloc(sizeof(char)* (negstart-end));
            int x = 0;
            for(int i = end; i<= negstart; i++)
            {
                dst->data[x] = str->data[i];
                x++;
            }
        }

    }
    else if(end<0)
    {
       negend = str->length - end;
       if(negend > start)
       {
            dst->data = (char *) malloc(sizeof(char)* (negend-start));
            int x = 0;
            for(int i = start; i<= negend; i++)
            {
                dst->data[x] = str->data[i];
                x++;
            }
        }
        else
        {
            dst->data = (char *) malloc(sizeof(char)*( start-negend));
            int x = 0;
            for(int i = negend; i<= start; i++)
            {
                dst->data[x] = str->data[i];
                x++;
            }
        }

    }
    else
    {
       if(end > start)
       {
            dst->data = (char *) malloc(sizeof(char)* (end-start));
            int x = 0;
            for(int i = start; i<= end; i++)
            {
                dst->data[x] = str->data[i];
                x++;
            }
        }
        else
        {
            dst->data = (char *) malloc(sizeof(char)* (start-end));
            int x = 0;
            for(int i = end; i<= start; i++)
            {
                dst->data[x] = str->data[i];
                x++;
            }
        }
     }
  
    return dst;
}


