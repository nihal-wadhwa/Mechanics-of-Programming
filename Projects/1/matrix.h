// file: matrix.h
//
// Description: Implements the transition matrix interpreted from the input
// file 
//
// @author Nihal Wadhwa (nw7554)
// // // // // // // // // // // // // // // // // // // // // // // // 

#ifndef MATRIX_H
#define MATRIX_H

//This structure represents each node of transition matrix used to interpret the//input file
typedef struct node
{
   int state;
   char action;
} node;

/// Prints the transition matrix
/// @param filename: name of file
/// @param size:  the length of the transition matrix
/// @param matrix: the transition matrix being printed
void printMtrx(char filename[], int size, node matrix[size][11]);

/// Takes the input matrix and creates a valid transition matrix based on it
/// @param filename: name of file
/// @param size: length of the input matrix
/// @param matrix: input matrix being used to initialize the transition matrix
void  initMtrx(char filename[],  int size, node  matrix[size][11] );


/// Returns the state and action  a single token based on transition matrix
/// @param token:  token being processed
/// @param node: state and action of previous token processed
/// @param start: start state of transition matrix
/// @param size: size of transition matrix
/// @param matrix: transition matrix being used
node classify(char token, node prev, int start,  int size, node matrix[size][11]);

#endif //MATRIX__H 
