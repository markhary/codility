// https://app.codility.com/programmers/lessons/6-sorting/distinct/
// 
// Task Score: 100%
// Correctness: 100%
// Performance: 100% or Not assessed
// Detected time complexity: O(N) or O(N*log*N))
//
#include <map>
#include <vector>

using namespace std;

int solution(vector<int> &A) {
    std::map<int, int> hash;
    
    // Very simple, put this into a hash array, not counting
    // or sorting, and return size of array.
    unsigned int N = A.size();
    for (unsigned int i=0; i<N; i++) {
        hash[A[i]] = 1;    
    }
    return hash.size();
}
