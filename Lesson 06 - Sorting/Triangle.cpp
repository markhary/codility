// https://app.codility.com/programmers/lessons/6-sorting/triangle/
// 
// Task Score: 100%
// Correctness: 100%
// Performance: 100%
// Detected time complexity: O(N*log(N))
#include <algorithm>
#include <vector>

using namespace std;

// This tells us the following:   (0<=P<Q<R)
// A triplet will be sequential in a sorted list
//   - numbers will be right next to each other, there could be overlapping triplets
//   - but there must be one set with three right next to each other
// Be careful of int overflow, do math in long long space

int solution(vector<int> &A) {
    int N = A.size();
    
    // Can return immediately if N doesn't have at least three elements to 
    // be a triangle
    if ( N < 3 ) {
        return 0;
    }
    
    // Sort the array using built in sort, this is O(N*log(N))
    std::sort(A.begin(), A.end());

    // Last triplet set is going to be two less than end
    // This is O(N)
    for (int i=0; i<(N-2); i++) {
        // Check the final conditions:
        //  * A[P] + A[Q] > A[R],
        //  * A[Q] + A[R] > A[P],
        //  * A[R] + A[P] > A[Q].
        // Again, the 'i+0' makes this easier to read
        // This is a sorted list so A[P] <= A[Q] <= A[R]
        
        // promote these to avoid int overflow
        long long A_p = A[i+0];
        long long A_q = A[i+1];
        long long A_r = A[i+2];
        if ( ((A_p+A_q) > A_r ) &&
             ((A_q+A_r) > A_p ) &&
             ((A_r+A_p) > A_q ) ) {
                 // return 1 the instant we find our first triplet
                 return 1;
        }
    }
    
    // Nothing was found if we exited the loop, return 0
    return 0;
}
