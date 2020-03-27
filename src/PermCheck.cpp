// https://app.codility.com/programmers/lessons/4-counting_elements/perm_check/
//
// Task Score: 100%
// Correctness: 100%
// Performance: 100%
// Detected time complexity: O(N) or O(log*log(N))
//
#include <vector>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

int solution(std::vector<int> &A)
{
    unsigned int N = A.size();

    std::vector<int> track(N, 0);
    unsigned int n = 0;

    // go through and look at elements of A.  If A[i] > N then there
    // is a number missing.  Otherwise sum up all of the numbers,
    // make sure there are no duplicates
    for (unsigned int i = 0; i < N; i++)
    {
        if (((unsigned int)A[i]) > N)
        {
            return 0;
            // A[i] is larger than N so there is a number missing
        }
        else if (track[A[i] - 1])
        {
            // We already found this element, must be a duplicate
            // Not a permutation
            return 0;
        }
        else
        {
            // Increments number of elements we found, notes specific number
            n++;
            track[A[i] - 1] = 1;
        }
    }

    // Not a permutation if we didn't get N unique elements
    if (n != N)
    {
        return 0;
    }

    return 1;
}
