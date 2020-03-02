// https://app.codility.com/programmers/lessons/6-sorting/max_product_of_three/
// 
// Task Score: 100%
// Correctness: 100%
// Performance: 100%
// Detected time complexity: O(N*log(N))
//
//
#include <algorithm>
#include <vector>

using namespace std;

// Be careful of int overflow, do math in long long int space
// Keep in mind that two negatives will create a positive

// Greatest will always be: (X*Z > Y*Z ? X*Z : Y*Z) where
//   There are at least 5 elements
//   X = biggest two negative numbers (or first two elements of array)
//   Z = largest number (last element of array)
//   Y = second and third largest number (N-1 and N-2, respectively)
// Edge cases:
//   3 elements - just return A[P]*A[Q]*A[R]
//   4 elements - [a b c d] - return greater of abd or bcd
int solution(vector<int> &A) {
    int N = A.size();

    // Sort the array using built in sort, this is O(N*log(N))
    std::sort(A.begin(), A.end());

    if ( N == 3 ) {
        return (A[0] * A[1] * A[2]);
    }

    if ( N == 4 ) {
        if ( A[2] == 0 ) return A[0] * A[1] * A[2];
        long long int abd = A[0] * A[1] * A[3];
        long long int bcd = A[1] * A[2] * A[3];
        return ( (abd>bcd) ? abd : bcd );
    }

    long long int X = A[0] * A[1];
    long long int Y = A[N-3] * A[N-2];
    long long int Z = A[N-1];

    return ( ((X*Z)>(Y*Z)) ? (X*Z) : (Y*Z) );
}
