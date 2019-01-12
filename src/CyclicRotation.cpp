// https://app.codility.com/programmers/lessons/2-arrays/cyclic_rotation/
//
// Task Score: 100%
// Correctness: 100%
// Performance: Not assessed
// 
#include <vector>

vector<int> solution(vector<int> &A, int K) {
    int n = A.size();
    vector<int> B(n, 0);

    // Handle case of empty input array
    if (!n) {
        return B;
    }
    
    int index = 0;
    if (K%n) {
        index = (n-K%n);
    }
    
    // Copy elements from A to B, starting at the
    // calculated index
    for (int i=0; i<n; i++) {
        B[i] = A[index];
        index = ((index+1)%n);
    }
    
    return B;
}
