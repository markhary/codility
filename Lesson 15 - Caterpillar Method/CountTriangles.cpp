// https://app.codility.com/programmers/lessons/15-caterpillar_method/count_triangles/
// 
// Task Score: 100%
// Correctness: 100%
// Performance: 100%
// Detected time complexity: O(N^2)
//

#include <algorithm>
#include <vector>
#include <map>

using namespace std;

// This is the simple brute force method, but it O(N^3)
// Solution passes 100%, performance tests fail
int bruteForce(vector<int> &A) {
    const int N = A.size();
    
    if ( N<3 ) {
        return 0;
    }

    long long int triangles = 0;
    for (int i=0; i<(N-2); i++) {
        for (int j=(i+1); j<(N-1); j++) {
            for (int k=(j+1); k<N; k++) {
                if ( ( (A[i] + A[j]) > A[k]) &&
                     ( (A[j] + A[k]) > A[i]) &&
                     ( (A[k] + A[i]) > A[j]) ) {
                    triangles++;
                }
            }
        }
    }
    
    return triangles;
}

//
// This is the optimized solution
//
int solution(vector<int> &A) {
    const int N = A.size();

    // If we sort the array, we only need to find A[P] + A[Q] > A[R]
    // Given 
    //   0 <= P < Q < R < N
    //   0 < A[P] <= A[Q] <= A[R]
    // Then
    //   A[Q] + A[R] > A[P]  because A[n] > 0 and A[Q] and A[R] both >= A[P]
    //   A[P] + A[R] > A[Q]  Because A[n] > 0 and A[R] >= A[Q]
    //
    int triangles = 0;

    // Sort the algorithm, this is O(N*log(N)) complexity
    std::sort(A.begin(), A.end());
    
    // Iterate through all numbers and find where A[P] + A[Q] > A[R]
    // or more specifically, where A[P] > A[R] - A[Q]
    for (int p=0; p<(N-2); p++) {
        // {P}, {Q = P+1}, {R = Q+1 = P+2}
        int r = p+2;
        // To make this O(N^2) we need to only loop through Q and R once,
        // knowing that when R > Q+1, then all of the A[Q] .. A[R-1] are
        // also solutions and we can just add them to the next iteration
        for (int q=(p+1); q<(N-1); q++) {
            // Stop if R reaches the end or if A[P] <= A[R]-A[Q]
            while ( (r<N) && (A[p] > (A[r]-A[q])) ) {
                // Increment the triangles and keep pushing R out to the right
                r++;
            }
            triangles += (r-q-1);
        }
    }
    
    return triangles;
}
