// https://app.codility.com/programmers/lessons/6-sorting/number_of_disc_intersections/
//
// Task Score: 100%
// Correctness: 100%
// Performance: 100%
// Detected time complexity: O(N*log(N)) or O(N)
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include "macros.h"

#include "NumberOfDiscIntersections.h"

int number_of_disc_intersections::brute_force(std::vector<int> &A)
{

    int n_intersections = 0;
    int length = A.size();

    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++)
        {
            if ((j - i) <= ((long)A[i] + (long)A[j]))
            {
                n_intersections++;
            }
        }
    }

    n_intersections = n_intersections - (length * (length + 1) / 2);
    if (n_intersections > 1e7)
        return -1;

    return n_intersections;
}

int number_of_disc_intersections::optimized(std::vector<int> &A)
{
    long l = A.size();

    std::vector<long> A1(l);
    std::vector<long> A2(l);

    long i = 0;

    std::generate(
        A1.begin(),
        A1.end(),
        [&]() {
            auto val = (long)A[i] + i;
            i++;
            return val;
        });

    long j = 0;

    std::generate(
        A2.begin(),
        A2.end(),
        [&]() {
            auto val = (long)-(A[j] - (j));
            j++;
            return val;
        });

    std::sort(A1.begin(), A1.end());
    std::sort(A2.begin(), A2.end());

    long n_intersections = 0;

    std::for_each(A1.begin(), A1.end(), [&](long v) {
        auto it = std::upper_bound(A2.begin(), A2.end(), v);
        n_intersections += it - A2.begin();
    });

    n_intersections = n_intersections - (l * (l + 1) / 2);

    if (n_intersections > 1e7)
        return -1;

    return (int)n_intersections;
}

int number_of_disc_intersections::solution(std::vector<int> &A)
{
    return number_of_disc_intersections::optimized(A);
}