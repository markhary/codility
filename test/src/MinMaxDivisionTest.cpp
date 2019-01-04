//
// Test executable for Lesson 14 - Binary Search Algorithm/MinMaxDivision.cpp
//
#include <iostream>
#include <vector>

#include <gtest/gtest.h>
#include <gflags/gflags.h>

#include "macros.h"
#include "args.h"

#include "MinMaxDivision.h"

using namespace std;

namespace minmaxdivision
{ 
    namespace test 
    {

        vector<int> generateRandomSequence(const int &N, const int &M, int seed)
        {
            vector<int> A(N);
            if ( !seed ) {
                seed = time(0);
            }
            cout << "Generating random sequence using " << seed << endl;
            srand(seed);

            for (int i=0; i<N; i++) {
                A[i] = rand() % (M+1);
            }
            return A;
        }

        vector<int> generateOneOrMSequence(const int &N, const int & M, const double &prob, int seed)
        {
            vector<int> A(N);
            if ( !seed ) {
                seed = time(0);
            }
            cout << "Generating random [1, M] sequence using " << seed << endl;
            srand(seed);

            for (int i=0; i<N; i++) {
                A[i] = rand() % (M+1);
                ( A[i] < (prob*M) ) ? (A[i] = 1 ) : (A[i]=M);
            }
            return A;
        }
    }
}

TEST(MinMaxDivisionTest, EdgeShortZeroes) 
{
    int K = 1;
    int M = 5;
    vector<int> A = {0, 0};
    ASSERT_EQ(minmaxdivision::bruteForce(K, M, A), minmaxdivision::solution(K, M, A));
}

TEST(MinMaxDivisionTest, Decrementing)
{
    int K = 4;
    int M = 10;
    vector<int>A = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    ASSERT_EQ(minmaxdivision::bruteForce(K, M, A), minmaxdivision::solution(K, M, A));
}

TEST(MinMaxDivisionTest, LessonSample)
{
    int M = 5;
    vector<int>A = {2, 1, 5, 1, 2, 2, 2};

    for (int K=1; K<=5; K++) {
        ASSERT_EQ(minmaxdivision::bruteForce(K, M, A), minmaxdivision::solution(K, M, A));
    }

    int K = 10000;
    ASSERT_EQ(minmaxdivision::bruteForce(K, M, A), minmaxdivision::solution(K, M, A));
}

TEST(MinMaxDivisionTest, EdgeOhFiveOh)
{
    int K = 20;
    int M = 5;
    vector<int> A = {0, 5, 0};
    ASSERT_EQ(minmaxdivision::bruteForce(K, M, A), minmaxdivision::solution(K, M, A));

    K = 4000;
    ASSERT_EQ(minmaxdivision::bruteForce(K, M, A), minmaxdivision::solution(K, M, A));
}

TEST(MinMaxDivisionTest, RandomSequenceOne)
{
    int N = 20;
    int M = 5;
    int K = 5;
    vector<int> A = minmaxdivision::test::generateRandomSequence(N, M, FLAGS_seed);
    ASSERT_EQ(minmaxdivision::bruteForce(K, M, A), minmaxdivision::solution(K, M, A));
}

TEST(MinMaxDivisionTest, RandomSequenceTwo)
{
    int N = 10;
    int M = 10000;
    int K = 5;
    vector<int> A = minmaxdivision::test::generateRandomSequence(N, M, FLAGS_seed);
    ASSERT_EQ(minmaxdivision::bruteForce(K, M, A), minmaxdivision::solution(K, M, A));
}

TEST(MinMaxDivisionTest, OneOrMSequence)
{
    int N = 40;
    int M = 100000;
    int K = 5;
    vector<int> A = minmaxdivision::test::generateOneOrMSequence(N, M, 0.90, FLAGS_seed);
    ASSERT_EQ(minmaxdivision::bruteForce(K, M, A), minmaxdivision::solution(K, M, A));
}

TEST(MinMaxDivisionTest, PerformanceMaxK)
{
    int N = 100000;
    int M = 10000;
    int K = 100000;
    vector<int> A(N);
    // Test max values with max K
    {
        for (int i=0; i<N; i++) {
            A[i] = M;
        }
        EXPECT_GE(minmaxdivision::solution(K, M, A), 0);
    }
}

TEST(MinMaxDivisionTest, PerformanceBinary)
{
    int N = 100000;
    int M = 10000;
    int K = 100000;
    vector<int> A = minmaxdivision::test::generateRandomSequence(N, 1, FLAGS_seed);
    EXPECT_GE(minmaxdivision::solution(K, M, A), 0);
}

TEST(MinMaxDivisionTest, PerformanceRandom)
{
    int N = 100000;
    int M = 10000;
    int K = 100000;
    vector<int> A = minmaxdivision::test::generateRandomSequence(N, M, FLAGS_seed);
    EXPECT_GE(minmaxdivision::solution(K, M, A), 0);
}
