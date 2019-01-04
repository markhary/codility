//
// Test executable for Directory/Lesson.cpp
//
#include <iostream>
#include <vector>

#include <gtest/gtest.h>
#include <gflags/gflags.h>

#include "macros.h"
#include "args.h"

#include "Lesson.h"

using namespace std;

namespace lesson
{ 
    namespace test 
    {
        // Add utility functions here
        /*
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
        */
    }
}

/*
TEST(LessonTest, BruteForce) 
{
    ASSERT_EQ(lesson::bruteForce(A), 0);
}

TEST(LessonTest, Edge) 
{
    ASSERT_EQ(lesson::bruteForce(A), lesson::solution(A));
}

TEST(LessonTest, Sample) 
{
    ASSERT_EQ(lesson::bruteForce(A), lesson::solution(A));
}

TEST(LessonTest, Empty) 
{
    ASSERT_EQ(lesson::bruteForce(A), lesson::solution(A));
}

TEST(LessonTest, Zeroes) 
{
    ASSERT_EQ(lesson::bruteForce(A), lesson::solution(A));
}

TEST(LessonTest, Maximum) 
{
    ASSERT_EQ(lesson::bruteForce(A), lesson::solution(A));
}

TEST(LessonTest, Minimum) 
{
    ASSERT_EQ(lesson::bruteForce(A), lesson::solution(A));
}

TEST(LessonTest, MaxRandom) 
{
    ASSERT_EQ(lesson::bruteForce(A), lesson::solution(A));
}
*/
