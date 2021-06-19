// file: main.c
// description: simple main program uses the circle module.
// @author RIT CS Dept.
// @author Nihal Wadhwa (nw7554)
#include <stdio.h>        // printf
#include "circle.h"    // getArea, getCircumference

/// Display the result of computing the area and circumference of a circle.
///
/// @param radius integer value of the circle radius

static void compute(int radius) {
    printf("Area of circle with radius %d: %f\n", 
           radius, getArea(radius));
    printf("Circumference of circle with radius %d: %f\n", 
           radius, getCircumference(radius));
}

/// main program uses the circle module.
/// @return 0 indicating successful execution

int main(void) {
    compute(1);
    compute(5);
    compute(10);

    return 0;
}

