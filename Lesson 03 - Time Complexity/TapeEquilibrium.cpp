// https://app.codility.com/programmers/lessons/3-time_complexity/tape_equilibrium/
//
// Task Score: 100%
// Correctness: 100%
// Performance: 100%
// Detected time complexity: O(N)
// 
#include <limits>
#include <cmath>

int solution(vector<int> &A) {
    vector<long long> sums;
    unsigned int N = A.size();
    
    long long sum = 0;
    // generate all of the possible sums
    for (unsigned int i=0; i<N; i++) {
      sum += A[i];
      sums.push_back(sum);
    }
    
    // figure out which difference is the smallest
    long long minDiff = std::numeric_limits<long long>::max();
    
    // Can't do the entire array, have to stop at one less than the max
    for (unsigned int i=0; i<(N-1); i++) {
        // Simplifying this:
        // sums[i] - (sums[i] - sum) = 2*sums[i]-sum;

        long long diff = abs( 2*sums[i] - sum );
        if ( diff < minDiff ) {
            minDiff = diff;
        }

    }
    
    return minDiff;
}
