// https://app.codility.com/programmers/lessons/9-maximum_slice_problem/max_profit/
// 
// Task Score: 100%
// Correctness: 100%
// Performance: 100%
// Detected time complexity: O(N)
//
#include <algorithm>
#include <vector>

using namespace std;

int solution(vector<int> &A) {
    // Guessing that solution is max slice of all of the deltas
    const int N=A.size();

    // Don't do anything if we have less than two elements
    if ( N < 2 ) {
        return 0;
    }

    vector<int> delta(N-1, 0);
    
    // Calculate deltas
    for (int i=1; i<N; i++) {
        delta[i-1] = A[i]-A[i-1];
    }

    int maxEnding = 0;
    int maxProfit = 0;
    
    // Iterate through all deltas and find max sum, this will be
    // max profit.  Use method defined in Lesson 9.
    const int M = delta.size();
    for (int i=0; i<M; i++) {
        // Slice not allowed to be empty
        maxEnding = std::max(0, maxEnding+delta[i]);
        maxProfit = std::max(maxProfit, maxEnding);
    }
    
    return maxProfit;
}
