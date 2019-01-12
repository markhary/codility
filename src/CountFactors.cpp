// https://app.codility.com/programmers/lessons/10-prime_and_composite_numbers/count_factors/
// 
// Task Score: 100%
// Correctness: 100%
// Performance: 100%
// Detected time complexity: O(sqrt(N))
//
#include <cmath>
using namespace std;

int solution(int N) {
    // We need to go up to square root of N, because rootN * rootN = N
    // We will find the other pair if
    //   N % D = 0
    
    // Edge cases are 1 and 2
    if ( N == 1) {
        return 1;
    } else if ( N == 2 ) {
        return 2;
    }
    
    // we know that factors are always going to be 1 and N so go ahead and
    // count those.  Need to check from 2 to sqrt(N)
    int factors = 2;
    int rootN = sqrt(N);
    
    bool exactRootN = false;
    if ( sqrt((double)N) == ((double)rootN) ) {
        exactRootN = true;
    }
    
    for (int i=2; i<=rootN; i++) {
        // There are always two factors unless rootN is exact
        if ( !(N % i) ) {
            if ( (i == rootN) && exactRootN ) {
                factors += 1;
            } else {
                factors += 2;
            }
        }
    }
    
    return factors;
}
