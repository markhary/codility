// https://app.codility.com/programmers/lessons/4-counting_elements/max_counters/
//
// Task Score: 100%
// Correctness: 100%
// Performance: 100%
// Detected time complexity: O(N+M)
//
#include <vector>
#include <algorithm>

vector<int> solution(int N, vector<int> &A) {
    int M = A.size();
    
    // Initialize counters to 0
    std::vector<int> counters(N, 0);
    int maximum = 0;
    int minimum = 0;
    
    for (int k=0; k<M; k++) {
        if (A[k] <= N) {
            // if A[K] = X, such that 1 ≤ X ≤ N, then operation K is increase(X)
            // and track max counter
            int counter = std::max(counters[A[k]-1], minimum) + 1;
            counters[A[k]-1] = counter;
            if (counter > maximum) {
                maximum = counter;
            }
        } else if (A[k] == (N+1)) {
            // if A[K] = N + 1 then operation K is max counter.
            // Have to set all elements of counter to max
            // Added logic to keep this O(N)
            minimum = maximum;
        }
    }
    
    // Keeping it O(N)
    // Go through and set the minimum value of all counters in case they
    // have not been updated.
    for (int k=0; k<N; k++) {
        counters[k] = std::max(counters[k], minimum);
    }
    
    return counters;
}
