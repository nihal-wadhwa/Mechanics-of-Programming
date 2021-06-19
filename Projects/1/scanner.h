// file: scanner.h
//
// Description: Scanning functions to get nubmer of states, start state,
// and accept state
//
// @author Nihal Wadhwa (nw7554)
// // // // // // // // // // // // // // // // // // // // // // // //

#ifndef SCANNER_H
#define SCANNER_H


/// Gets number of states from iput file
/// @param filename: name of input file
int getStates(char filename[]);


/// Gets accept state from input file
/// @param filename: name of input file
int getAccept(char filename[]);


/// Gets start state from input file
/// @param filename:  name of input file
int getStart(char filename[]);


#endif //SCANNER_H
