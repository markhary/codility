// https://app.codility.com/programmers/lessons/5-prefix_sums/count_div/
// 
// Task Score: 100%
// Correctness: 100%
// Performance: 100%
// Detected time complexity: O(1)
//

#include <iostream>
#include <vector>

#include "macros.h"

using namespace std;

namespace countdiv
{
    int bruteForce(int A, int B, int K) 
    {
        int count = 0;
        for (int i = A; i <= B; i++) {
            count += !(i%K);
        }

        return count;
    }

    int solution(int A, int B, int K) 
    {
        // Have to separate these because of integer rounding
        // in this case int(B/K) - int (A/K) != int (B-A)/K
        // The rest is just simple math and % cleverness
        // Not sure why this is a prefix sum solution
        return ( B/K - A/K + !(A%K) );
    }
        
}
