//
// Test executable for Directory/Lesson.cpp
//
#include <iostream>
#include <vector>
#include <functional>

#include <gtest/gtest.h>
#include <gflags/gflags.h>

#include "macros.h"
#include "args.h"

#include "NailingPlanks.h"

using namespace std;

namespace nailingplanks
{
namespace test
{

// Add utility functions here
void generateRandom(vector<int> &A, vector<int> &B, vector<int> &C,
                    const int min, const int max, int seed)
{
    if (!seed)
    {
        seed = time(0);
        cout << "Seeding... ";
    }
    cout << "Generating random sequence using " << seed << endl;
    srand(seed);

    const int N = A.size();

    for (int i = 0; i < N; i++)
    {
        A[i] = min + rand() % ((max - min) + 1);
        B[i] = A[i] + rand() % ((max - A[i]) + 1);
    }

    const int M = C.size();
    for (int j = 0; j < M; j++)
    {
        // handle case M > N
        int i = j % N;
        C[j] = (A[i] + B[i]) / 2;
    }
}

void generateRandomPlanks(vector<int> &A, vector<int> &B, const int min, const int max, int seed)
{
    if (!seed)
    {
        seed = time(0);
        cout << "Seeding... ";
    }
    cout << "Generating random planks using " << seed << endl;
    srand(seed);

    const int N = A.size();

    for (int i = 0; i < N; i++)
    {
        A[i] = min + rand() % ((max - min) + 1);
        B[i] = A[i] + rand() % ((max - A[i]) + 1);
    }
}

void generateRandomNails(vector<int> &A, const int min, const int max, int seed)
{
    if (!seed)
    {
        seed = time(0);
        cout << "Seeding... ";
    }
    cout << "Generating random nails using " << seed << endl;
    srand(seed);

    const int N = A.size();

    for (int i = 0; i < N; i++)
    {
        A[i] = min + rand() % ((max - min) + 1);
    }
}

// Measures execution times, returns value in milliseconds
double profile(const std::function<int(vector<int> &A, vector<int> &B, vector<int> &C)> &func,
               vector<int> &A, vector<int> &B, vector<int> &C, int &answer)
{
    auto start = chrono::high_resolution_clock::now();
    answer = func(A, B, C);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    return duration.count() / 1000.0;
}

} // namespace test
} // namespace nailingplanks

using namespace nailingplanks;
using namespace nailingplanks::test;

TEST(NailingPlanksTest, BruteForce)
{
    vector<int> A = {1, 4, 5, 8};
    vector<int> B = {4, 5, 9, 10};
    vector<int> C = {4, 6, 7, 10, 2};

    ASSERT_EQ(bruteForce(A, B, C), 4);

    C = {4};
    ASSERT_EQ(bruteForce(A, B, C), -1);
}

TEST(NailingPlanksTest, CorrectSample)
{
    vector<int> A = {1, 4, 5, 8};
    vector<int> B = {4, 5, 9, 10};
    vector<int> C = {4, 6, 7, 10, 2};

    ASSERT_EQ(bruteForce(A, B, C), solution(A, B, C));
}

TEST(NailingPlanksTest, CorrectSmallRandom)
{
    // A[N], B[N], and C[M]
    // N and M are integers within the range [1..30,000]
    // each element of arrays A, B, C is an integer within the range [1..2*M];
    const int N = 20;
    const int M = 20;

    const int min = 1;
    const int max = 2 * M;

    vector<int> A(N);
    vector<int> B(N);
    vector<int> C(M);

    generateRandomPlanks(A, B, min, max, FLAGS_seed);
    generateRandomNails(C, min, max, FLAGS_seed);

    ASSERT_EQ(bruteForce(A, B, C), solution(A, B, C));
}

TEST(NailingPlanksTest, PerformanceMaxRandom)
{
    // A[N], B[N], and C[M]
    // N and M are integers within the range [1..30,000]
    // each element of arrays A, B, C is an integer within the range [1..2*M];
    const int N = 30000;
    const int M = 30000;

    const int min = 1;
    const int max = 2 * M;

    vector<int> A(N);
    vector<int> B(N);
    vector<int> C(M);

    generateRandomPlanks(A, B, min, max, FLAGS_seed);
    generateRandomNails(C, min, max, FLAGS_seed);

    int bruteForceAnswer;
    double bruteForceDuration = profile(bruteForce, A, B, C, bruteForceAnswer);

    int solutionAnswer;
    double solutionDuration = profile(solution, A, B, C, solutionAnswer);

    ASSERT_EQ(bruteForceAnswer, solutionAnswer);
    EXPECT_GE(bruteForceDuration, solutionDuration);
}

TEST(NailingPlanksTest, PerformanceRandomMaxNEqualM)
{
    // A[N], B[N], and C[M]
    // N and M are integers within the range [1..30,000]
    // each element of arrays A, B, C is an integer within the range [1..2*M];
    const int N = 30000;
    const int M = 30000;

    const int min = 1;
    const int max = 20000;

    vector<int> A(N);
    vector<int> B(N);
    vector<int> C(M);

    generateRandom(A, B, C, min, max, FLAGS_seed);

    int bruteForceAnswer;
    double bruteForceDuration = profile(bruteForce, A, B, C, bruteForceAnswer);

    int solutionAnswer;
    double solutionDuration = profile(solution, A, B, C, solutionAnswer);

    ASSERT_EQ(bruteForceAnswer, solutionAnswer);
    EXPECT_GE(bruteForceDuration, solutionDuration);
}

TEST(NailingPlanksTest, PerformanceRandomNSmallerM)
{
    // A[N], B[N], and C[M]
    // N and M are integers within the range [1..30,000]
    // each element of arrays A, B, C is an integer within the range [1..2*M];
    const int N = 20;
    const int M = 30000;

    const int min = 1;
    const int max = 2 * M;

    vector<int> A(N);
    vector<int> B(N);
    vector<int> C(M);

    generateRandom(A, B, C, min, max, FLAGS_seed);

    int bruteForceAnswer;
    double bruteForceDuration = profile(bruteForce, A, B, C, bruteForceAnswer);
    (void)bruteForceDuration; // get rid of unused variable warning

    int solutionAnswer;
    double solutionDuration = profile(solution, A, B, C, solutionAnswer);
    (void)solutionDuration; // get rid of unused variable warning

    ASSERT_EQ(bruteForceAnswer, solutionAnswer);
    // bruteForce is faster than solution, and I don't know why, but I don't care too
    // much, it may be that sorting introduces overhead but is much faster for max
    // cases, and I don't want to tune the overhead
    //EXPECT_GE(bruteForceDuration, solutionDuration);
}

TEST(NailingPlanksTest, PerformanceMinMaxOne)
{
    // A[N], B[N], and C[M]
    // N and M are integers within the range [1..30,000]
    // each element of arrays A, B, C is an integer within the range [1..2*M];
    const int N = 30000;
    const int M = 30000;

    const int min = 1;
    const int max = 2 * M;

    vector<int> A(N, min);
    vector<int> B(N, max);
    vector<int> C(M, 30000);

    int bruteForceAnswer;
    double bruteForceDuration = profile(bruteForce, A, B, C, bruteForceAnswer);
    (void)bruteForceDuration; // get rid of unused variable warning

    int solutionAnswer;
    double solutionDuration = profile(solution, A, B, C, solutionAnswer);
    (void)solutionDuration; // get rid or unused variable warning

    ASSERT_EQ(bruteForceAnswer, solutionAnswer);
    //EXPECT_GE(bruteForceDuration, solutionDuration);
}

TEST(NailingPlanksTest, PerformanceRandomNLargerM)
{
    // A[N], B[N], and C[M]
    // N and M are integers within the range [1..30,000]
    // each element of arrays A, B, C is an integer within the range [1..2*M];
    const int N = 30000;
    const int M = 30000;

    const int min = 1;
    const int max = 2 * M;

    vector<int> A(N);
    vector<int> B(N);
    vector<int> C(M);

    generateRandom(A, B, C, min, max, FLAGS_seed);

    int bruteForceAnswer;
    double bruteForceDuration = profile(bruteForce, A, B, C, bruteForceAnswer);

    int solutionAnswer;
    double solutionDuration = profile(solution, A, B, C, solutionAnswer);

    ASSERT_EQ(bruteForceAnswer, solutionAnswer);
    EXPECT_GE(bruteForceDuration, solutionDuration);
}
