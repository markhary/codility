// https://app.codility.com/programmers/lessons/15-caterpillar_method/abs_distinct/
// 
// Task Score: 100%
// Correctness: 100%
// Performance: 100%
// Detected time complexity: O(N) or O(N*log(N))
//
#include <cmath>
#include <map>
#include <vector>

using namespace std;

// Going to use a hash.  
// Expect time complexity O(N)
// Expect space complexity O(N)

int solution(vector<int> &A) {
    const int N = A.size();
    
    std::map<int, int> absolutes;
    
    // Put it into the map and increase the number (although we don't need it)
    for (int i=0; i<N; i++) {
        unsigned int absolute = std::abs(A[i]);
        absolutes[absolute]++;
    }
    
    return absolutes.size();
}

