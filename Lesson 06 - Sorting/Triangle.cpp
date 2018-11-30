// https://app.codility.com/programmers/lessons/6-sorting/triangle/
// 
// Task Score: 0%
// Correctness: 0%
// Performance: 0% or Not assessed
// Detected time complexity: Complexity
#include <algorithm>
#include <vector>

using namespace std;

// This tells us the following:   (0<=P<Q<R)
// A triplet will be sequential in a sorted list
//   - numbers will be right next to each other, there could be overlapping triplets
//   - but there must be one set with three right next to each other
// Skip triplets with duplicates
// Be careful of int overflow, do math in long long space

int solution(vector<int> &A) {
    int N = A.size();
    
    // Can return immediately if N doesn't have at least three elements to 
    // be a triangle
    if ( N < 3 ) {
        return 0;
    }
    
    // Sort the array using built in sort, this is worst O(N*log(N))
    std::sort(A.begin(), A.end());

    // Last triplet set is going to be two less than end
    // This is O(N)
    for (int i=0; i<(N-2); i++) {
        // Skip negatives
        if ( A[i] < 0 ) {
            continue;
        }
        
        // Skip duplicates
        // Added in the +0 because visually it makes it easier to read
        // XOR can be done as signed ints
        if ( !(A[i+0]^A[i+1]) || 
             !(A[i+1]^A[i+2]) || 
             !(A[i+0]^A[i+2]) ) {
            // could be faster by skipping two but doesn't increase complexity
            // if we just keep it simple
            continue;
            // and return 1 the instant we find our first triplet
        }
        
        // Check the final conditions:
        //  * A[P] + A[Q] > A[R],
        //  * A[Q] + A[R] > A[P],
        //  * A[R] + A[P] > A[Q].
        // Again, the 'i+0' makes this easier to read
        
        // promote these to avoid int overflow
        long long A_p = A[i+0];
        long long A_q = A[i+1];
        long long A_r = A[i+2];
        if ( ( (A_p+A_q) > A_r ) &&
             ( (A_q+A_r) > A_p ) && 
             ( (A_r+A_p) > A_q) ) {
                 return 1;
        }
    }
    
    // Nothing was found if we exited the loop, return 0
    return 0;
}
