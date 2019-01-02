//
// Test executable for Lesson 14 - Binary Search Algorithm/MinMaxDivision.cpp
//
#include <iostream>
#include <vector>

#include "macros.h"
#include "gtest/gtest.h"

#include "MinMaxDivision.h"

//
// Configure command line arguments
//
#include "gflags/gflags.h"
DEFINE_int32(seed, 0, "Use given seed to repeat previous result, 0 means use current time as seed");

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
        cout << "solution: " << minmaxdivision::solution(K, M, A) << endl;
    }
}

TEST(MinMaxDivisionTest, PerformanceBinary)
{
    int N = 100000;
    int M = 10000;
    int K = 100000;
    vector<int> A = minmaxdivision::test::generateRandomSequence(N, 1, FLAGS_seed);
    cout << "solution: " << minmaxdivision::solution(K, M, A) << endl;
}

TEST(MinMaxDivisionTest, PerformanceRandom)
{
    int N = 100000;
    int M = 10000;
    int K = 100000;
    vector<int> A = minmaxdivision::test::generateRandomSequence(N, M, FLAGS_seed);
    cout << "solution: " << minmaxdivision::solution(K, M, A) << endl;
}

int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv);
    gflags::SetUsageMessage("Runs the tests for MinMaxDivision");
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    if ( argc > 1 ) {
        cerr << "Command line arguments not recognized, please execute:" << endl;
        cerr << "  " << argv[0] << " --help or" << endl;
        cerr << "  " << argv[0] << " --gtest_help" << endl;
        exit(1);
    }

    return RUN_ALL_TESTS();
}
