// https://app.codility.com/programmers/lessons/1-iterations/binary_gap/
// 
// Task Score: 100%
// Correctness: 100%
// Performance: Not assessed
//
#include <cmath>

int solution(int N) {

    int numBits = floor(std::log2(N))+1;

    bool foundOne = false;
    int maximumGap = 0;
    int possibleGap = 0;
    
    for (int i=0; i<numBits; i++) {
        // find a 0
        if ( foundOne && !(N & (1<<i))) {
            possibleGap++;
        } else if ((N & (1<<i))) {
            // If we found a one, set the gap length and reset the
            // current counter
            if (foundOne) {
                if (possibleGap > maximumGap) {
                    maximumGap = possibleGap;
                }
                possibleGap = 0;
            }
            foundOne = true;
        }
    }
    
    return maximumGap;
}
