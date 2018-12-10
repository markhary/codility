// https://app.codility.com/programmers/lessons/10-prime_and_composite_numbers/min_perimeter_rectangle/
// 
// Task Score: 100%
// Correctness: 100%
// Performance: 100%
// Detected time complexity: O(sqrt(N))
//
#include <cmath>
#include <limits>
using namespace std;

int solution(int N) {
    // We need to go up to square root of N, because rootN * rootN = N
    // We will find the other pair if
    //   N % D = 0
    
    // we know that factors are always going to be 1 and N so go ahead and
    // count those.  Need to check from 2 to sqrt(N)
    int rootN = sqrt(N);
    int minPerimeter = std::numeric_limits<int>::max();
    
    for (int i=1; i<=rootN; i++) {
        // Find factors and calculate minimum area
        if ( !(N % i) ) {
            int a = i;
            int b = N/i;
            int perimeter = 2*(a+b);
            if (perimeter < minPerimeter) {
                minPerimeter = perimeter;
            }
        }
    }
    
    return minPerimeter;
}
