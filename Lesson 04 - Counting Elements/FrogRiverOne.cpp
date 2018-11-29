// https://app.codility.com/programmers/lessons/4-counting_elements/frog_river_one/
//
// Task Score: 100%
// Correctness: 100%
// Performance: 100%
// Detected time complexity: O(N)
//
#include <vector>

int solution(int X, vector<int> &A) {
    unsigned int N = A.size();
    
    // Create a vector of size N initialized to 0, we are done when
    // we have set X elements
    std::vector<char> track(N, 0);
    int numElements = 0;
    
    for (unsigned int i=0; i<N; i++) {
        if ( !track[A[i]-1] ) {
            numElements++;
            track[A[i]-1] = 1;
        } else {
        }
        if (numElements == X) {
            return i;
        }
    }
    
    // Didn't find anything
    return -1;
}

