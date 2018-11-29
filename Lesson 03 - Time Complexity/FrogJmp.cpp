// https://app.codility.com/programmers/lessons/3-time_complexity/frog_jmp/
//
// Task Score: 100%
// Correctness: 100%
// Performance: 100%
// Detected time complexity: O(1)
//
#include <math.h>

int solution(int X, int Y, int D) {
    // Very simple solution, just make sure to not get caught by
    // quantization
    double numJumps = (( (double)Y)-( (double) X) )/ ((double)D);
    return ( ceil(numJumps) );
}
