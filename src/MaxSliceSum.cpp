// https://app.codility.com/programmers/lessons/9-maximum_slice_problem/max_slice_sum/
// 
// Task Score: 100%
// Correctness: 100%
// Performance: 100%
// Detected time complexity: O(N)
//

#include <algorithm>
#include <limits>
#include <vector>

using namespace std;

int solution(vector<int> &A) {
    // The algorithm implemented in the Maximum Slice lesson assumes
    // the length can be zero with a sum of 0.  That is not an assumption here.  
    // Let us look at the case where all numbers are negative.  If so, the max
    // slice is going to be the largest negative number.  If there is a single 
    // positive number, then the slice is going to be the largest positive number.
    
    // So, first find the largest number.  If it is greater than 0, then the solution
    // in Lesson 9 applies.  If it is less than 0, then just return the max
    // number
    double max = *std::max_element(A.begin(), A.end());
    
    if ( max < 0) {
        return max;
    }
    
    long long int maxEnding = 0;
    long long int maxSlice = 0;

    // OK, it is a positive number, so use the pattern described in Lesson 9
    const int N = A.size();
    for (int i=0; i<N; i++) {
        // Slice not allowed to be empty
        maxEnding = std::max((long long int)0, maxEnding+A[i]);
        maxSlice = std::max(maxSlice, maxEnding);
    }
    
    return maxSlice;
}
