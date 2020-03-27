// https://app.codility.com/programmers/lessons/14-binary_search_algorithm/min_max_division/
// 
// Task Score: 100%
// Correctness: 100%
// Performance: 100%
// Detected time complexity: O(N*log(N+M));
//
#include <numeric>
#include <vector>
#include <algorithm>

#include "MinMaxDivision.h"

using namespace std;

namespace minmaxdivision
{

    // Used to debug brute force algorithm
    vector<int> gMinimalBlocks;
    vector<int> gMinimalSums;

    //////////////////////////////////////////////////////////
    // Brute Force
    //////////////////////////////////////////////////////////

    // This is 100% correct, but fails performance tests

    //
    // Brute force solution looks like
    //   for (I = [0 .. N-K])   // left index anchored at 0
    //     for (J = [I+1 .. N-K+1])
    //       for (K = [J+1 .. N-1])  // right most element anchored at N-1
    // Where there are K for loops (hence O(N^K) complexity)
    //
    // So turning nested for loop into a recursive function call
    // P is my partial sums and goes from 0 .. N
    //
    void calculateLargeSums(const vector<int> &P, vector<int> &blocks, 
            vector<int> &sums, const int b, int &minimalLargeSum, int &maxIndex) 
    {
        const int K = blocks.size();
        const int N = P.size() - 1;  // Because P.size() is actually one larger than N

        //	Mimic all of the actual "for (..; ..; ..) {} loops
        // This is the innermost for loop
        if ( b == (K-1) ) {
            // calculate sum for each block
            for (int k=1; k<K; k++) {
                sums[k-1] = P[blocks[k]] - P[blocks[k-1]];
            }

            // large sum is going to be max of sums
            auto maxSum = max_element(std::begin(sums), std::end(sums));
            int largeSum = *maxSum;
            maxIndex = maxSum- sums.begin() + 1;

            if ( largeSum < minimalLargeSum ) {
                gMinimalBlocks = blocks;
                gMinimalSums = sums;
                minimalLargeSum = largeSum;
            }
        } else {
            // A couple more things happen when this is the Kth call, which is the
            // innermost for loop
            // 1. Print the blocks structure so we can see where we are
            // 2. Do the calculation of the large blocks and return the latest
            //    minimumLargeSum
            int iMax = N-(K-1)+b;
            for (int i = (blocks[b-1]+1); i <= iMax; i++) {
                blocks[b] = i;
                calculateLargeSums(P, blocks, sums, b+1, minimalLargeSum, maxIndex);

                if ( maxIndex < b ) {
                    break;
                }
            }
        }
    }

    //
    // Brute force looks like:
    //   for (I = [0 .. N-1])   // left index anchored at 0
    //     for (J = [I+1 .. N-1])
    //       for (K = [J+1 .. N-1])  // right most element anchored at N-1
    //			checkSums;
    //
    // Going to add in one optimization:  reduce complexity to Rank(A)
    // rather than N
    //
    // 100% correct, but this is O(N^K) complexity, don't try to
    // test too big
    //
    int bruteForce(int K, int M, vector<int> &A)
    {
        // reduce A from N to Rank(A) (e.g. remove 0s)
        std::vector<int> B;
        for (int i=0; i<(int)A.size(); i++) {
            if (A[i]) {
                B.push_back(A[i]);
            }
        }

        const int N = B.size();

        // Get rid of unused error;
        M += 0;

        // means all zeros and answer is 0
        if ( !N ) {
            return 0;
        }

        // Binary search uses information that data is sorted, so this
        // means we are going to use partial sums which will be sorted
        std::vector<int> P(N, 0);
        std::partial_sum(B.begin(), B.end(), P.begin());

        // Adding 0 to front of array lets me do some very simple math 
        // later on
        P.emplace(P.begin(), 0);

        int minimalLargeSum = std::numeric_limits<int>::max();

        // Instantiate our K blocks
        // Cap K at N since it makes no sense to have more blocks than numbers
        K = min(K, N);
        vector<int> blocks(K+1, 0);
        blocks[0] = 0;
        blocks[K] = N;

        vector<int> sums(K, 0);

        // This starts on the first index, since index[0] doesn't move
        int maxIndex;
        calculateLargeSums(P, blocks, sums, 1, minimalLargeSum, maxIndex);

        return minimalLargeSum;
    }

    //
    // Implementing a binary search algorithm
    // The check function starts creating blocks and increments the blocks each 
    // time we exceed the maximum sum. Return false if we run out of blocks.
    //
    bool validateSolution (const int K, const vector<int> &A, const int &maxSum)
    {
        int numBlocks = 1;
        int sum = 0;
        for (const auto &a: A) {
            sum += a;
            if ( sum > maxSum ) {
                numBlocks++;
                sum = a;
            }
            if (numBlocks > K) {
                return false;
            }
        }

        return true;
    }

    // We know the solution will either be:
    // * 0 if we have no non-zero elements
    // * max(A) if K >= rank(A)
    // * Found via binary search, and the answer is going to be between
    //    max(A) and sum(A)
    int solution(int K, int M, vector<int> &A)
    {
        const int N = A.size();
        // Cannot figure out a use for M
        M += 0;

        // Going to use B to reduce the rank of A, since 0s do not count toward
        // anything.  Might as well reduce overhead.
        vector<int> B;

        // Binary search uses information that data is sorted, so this
        // means we are going to use partial sums which will be sorted
        // But reduce the number of elements so that Rank(P) = Rank(A)+1;
        int sum = 0;
        int max = 0;
        for (int i=0; i<N; i++) {
            if (A[i]) {
                B.push_back(A[i]);
                sum+= A[i];
                max = std::max(max, A[i]);
            }
        }

        // Quick check - if B is empty then return 0
        if ( !B.size() ) {
            return 0;
        }

        // Quick check - if Rank(B) <= K then answer is max(B);
        if ( (int) B.size() <= K ) {
            auto maxElement = max_element(std::begin(B), std::end(B));
            return *maxElement;
        }

        // The answer is somewhere between max(A) and sum(A)
        int lowerBound = max;
        int upperBound = sum;

        // Implement the classic binary search algorithm
        while ( lowerBound <= upperBound ) {
            int candidate = (lowerBound+upperBound)/2;
            if ( validateSolution(K, B, candidate) ) {
                upperBound = candidate - 1;
            } else {
                lowerBound = candidate + 1;
            }
        }

        return lowerBound;
    }

}
