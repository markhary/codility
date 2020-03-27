//
// Test executable for Directory/Lesson.cpp
//
#include <iostream>
#include <vector>
#include <random>
#include <functional>

#include <gtest/gtest.h>
#include <gflags/gflags.h>

#include "macros.h"
#include "args.h"

#include "MinAvgTwoSlice.h"

using namespace std;

namespace minavgtwoslice
{
namespace test
{

// Amount of time to allow execution to vary just because
int gDurationPadding = 10;

// Add utility functions here
void generateRandom(vector<int> &A, const int min, const int max, int seed)
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
} // namespace minavgtwoslice

using namespace minavgtwoslice;
using namespace minavgtwoslice::test;

TEST(MinAvgTwoSliceTest, BruteForce)
{
    vector<int> A = {4, 2, 2, 5, 1, 5, 8};

    ASSERT_EQ(bruteForce(A), 1);
}

TEST(MinAvgTwoSliceTest, CorrectSample)
{
    vector<int> A = {4, 2, 2, 5, 1, 5, 8};

    ASSERT_EQ(bruteForce(A), solution(A));
}

TEST(MinAvgTwoSliceTest, CorrectMediumRandom)
{
    const int N = 700;
    const int min = -10000;
    const int max = 10000;

    vector<int> A(N);
    generateRandom(A, min, max, FLAGS_seed);

    ASSERT_EQ(bruteForce(A), solution(A));
}

TEST(MinAvgTwoSliceTest, PerformanceMaxRandom)
{
    const int N = 100000;
    const int min = -10000;
    const int max = 10000;

    vector<int> A(N);
    generateRandom(A, min, max, FLAGS_seed);

    int bruteForceAnswer;
    double bruteForceDuration = profile(bruteForce, A, bruteForceAnswer);

    int solutionAnswer;
    double solutionDuration = profile(solution, A, solutionAnswer);

    ASSERT_EQ(bruteForceAnswer, solutionAnswer);
    EXPECT_GE(bruteForceDuration + gDurationPadding, solutionDuration);
}
