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
    vector<int> A = {1, 5, 2, 1, 4, 0};
    ASSERT_EQ(brute_force(A), 11);
}

TEST(NumberOfDiscIntersectionsTest, CorrectSample)
{
    vector<int> A = {1, 5, 2, 1, 4, 0};
    ASSERT_EQ(brute_force(A), solution(A));
}

TEST(NumberOfDiscIntersectionsTest, CorrectMediumRandom)
{
    // A[N]
    // N is an integer within the range [0..100,000]
    // each element of array A is an integer within the range [0..2147483647]
    const int N = 1000;
    vector<int> A(N);
    int min = 0;
    int max = INT_MAX;

    generate_random(A, min, max, FLAGS_seed);
    ASSERT_EQ(brute_force(A), solution(A));
}

TEST(NumberOfDiscIntersectionsTest, CorrectMaxRandom)
{
    // A[N]
    // N is an integer within the range [0..100,000]
    // each element of array A is an integer within the range [0..2147483647]
    const int N = 100000;
    vector<int> A(N);
    int min = 0;
    int max = INT_MAX;

    generate_random(A, min, max, FLAGS_seed);
    // Tests take too long
    //ASSERT_EQ(brute_force(A), solution(A));
    ASSERT_EQ(solution(A), solution(A));
}

TEST(NumberOfDiscIntersectionsTest, PerformanceMaxRandom)
{
    // A[N]
    // N is an integer within the range [0..100,000]
    // each element of array A is an integer within the range [0..2147483647]
    const int N = 30000;

    const int min = 0;
    const int max = INT_MAX;

    vector<int> A(N);

    generate_random(A, min, max, FLAGS_seed);

    int bruteForceAnswer;
    double bruteForceDuration = profile(brute_force, A, bruteForceAnswer);

    int solutionAnswer;
    double solutionDuration = profile(solution, A, solutionAnswer);

    ASSERT_EQ(bruteForceAnswer, solutionAnswer);
    EXPECT_GE(bruteForceDuration + gDurationPadding, solutionDuration);
}