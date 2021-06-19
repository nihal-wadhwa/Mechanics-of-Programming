//
// File: stats.h 
// stats.h is the interface for functions in a simple statistics module.
//
// @author csci243: Mechanics Course Account
// @author Nihal Wadhwa (nw7554)
// @date 08/06/2020
// 
// // // // // // // // // // // // // // // // // // // // // // //
#ifndef STATS_H
#define STATS_H




/// average takes the data array scores[] and the size of data array
/// count and computes the average of all the data in the array
/// @param count size of data array 
/// @param scores the data array inputed
/// @return numrical average of data in data array 
double average( int count, const int scores[] );

/// std_dev takes the size of the data array count, the data array
/// scores[] and the mean and computes the standard deviation of the
/// data
/// @param count size of data array
/// @param scores the data array inputed
/// @param mean the average of the data array
/// @return standard deviation of the data array
double std_dev( int count, const int scores[], double mean );

/// std_dev takes the size of the data array count and the data array
/// scores[] and catagorizes each numerical score in the data array 
/// into the corresponding letter grade, counts frequency of each grade,
/// and prints results
/// @param count size of data array
/// @param scores the data array inputed
/// @return none 
void histogram( int count, const int scores[] );

#endif
