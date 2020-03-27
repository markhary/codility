#include <iostream>
#include <vector>
#include <random>
#include <functional>

#include <gtest/gtest.h>
#include <gflags/gflags.h>

#include "macros.h"
#include "args.h"

#include "NumberOfDiscIntersections.h"

using namespace std;

namespace number_of_disc_intersections
{
namespace test
{

// Amount of time to allow execution to vary just because
int gDurationPadding = 10;

// Add utility functions here
void generate_random(vector<int> &A, const int min, const int max, int seed)
{
    
    if (!seed)
    {
        seed = time(0);
        cout << "Seeding... ";
    }

    cout << "Generating random sequence using " << seed << endl;
    default_random_engine generator(seed);
    uniform_int_distribution<int> distribution(min, max);

    const int N = A.size();

    for (int i = 0; i < N; i++)
    {
        A[i] = distribution(generator);
    }
}

// Measures execution times, returns value in milliseconds
double profile(const std::function<int(vector<int> &A)> &func,
               vector<int> &A, int &answer)
{
    auto start = chrono::high_resolution_clock::now();
    answer = func(A);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    return duration.count() / 1000.0;
}

} // namespace test
} // namespace number_of_disc_intersections

using namespace number_of_disc_intersections;
using namespace number_of_disc_intersections::test;

TEST(NumberOfDiscIntersectionsTest, BruteForce)
{
    ASSERT_TRUE(true);
}

TEST(NumberOfDiscIntersectionsTest, CorrectSample)
{
    ASSERT_TRUE(true);
}

TEST(NumberOfDiscIntersectionsTest, CorrectMediumRandom)
{
    ASSERT_TRUE(true);
}

TEST(NumberOfDiscIntersectionsTest, CorrectMaxRandom)
{
    ASSERT_TRUE(true);
}

TEST(NumberOfDiscIntersectionsTest, PerformanceMaxRandom)
{
    ASSERT_TRUE(true);
}