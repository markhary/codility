// https://app.codility.com/programmers/lessons/14-binary_search_algorithm/min_max_division/
// 
// Task Score: 83%
// Correctness: 100%
// Performance: 66%
// Detected time complexity: O(N*log(N+M));
//
#include <iostream>
#include <algorithm>
#include <cmath>
#include <limits>
#include <numeric>
#include <vector>

#include "macros.h"

#define PRINT_BLOCK(X) { \
	cout << #X << ": [ "; \
	for (const auto &x: X) { cout << "{" << x.first << ", " << x.last << "} "; } \
	cout << "]" << endl; \
}

using namespace std;

struct Block {
	int first;
	int last;
};

// Used to debug brute force algorithm
vector<Block> gMinimalBlocks;
vector<int> gMinimalSums;

vector<int> calculateDifferences (const vector<int> A)
{
    vector<int> diffs(A.size()-1, 0);
    for (int i=1; i<(int)A.size(); i++) {
        diffs[i-1] = A[i]-A[i-1];
    }
    return diffs;
}

//
// Brute force solution looks like
//   for (I = [0 .. N-1])   // left index anchored at 0
//     for (J = [I+1 .. N-1])
//       for (K = [J+1 .. N-1])  // right most element anchored at N-1
// Where there are K for loops (hence O(N^K) complexity)
//
// So turning nested for loop into a recursive function call
// P is my partial sums and goes from 0 .. N
//
int calculateLargeSums(const vector<int> &P, vector<Block> &blocks, 
		const int b, const int &minimalLargeSum) 
{
	const int K = blocks.size();
	const int N = P.size() - 1;  // Because P.size() is actually one larger than N

	// This is the innermost for loop
	if ( b == K ) {
		int innerLargeSum = 0;

		// calculate sum for each block
		vector<int> sums(K, 0);
		for (int k=0; k<K; k++) {
			sums[k] = P[blocks[k].last] - P[blocks[k].first];
		}

		// large sum is going to be max of sums
		auto maxSum = max_element(std::begin(sums), std::end(sums));
		innerLargeSum = *maxSum;

        if ( innerLargeSum < minimalLargeSum ) {
            gMinimalBlocks = blocks;
            gMinimalSums = sums;
        }

		return min(innerLargeSum, minimalLargeSum);
	}

	//	Mimic all of the actual "for (..; ..; ..) {} loops

	// Modify the first and last index based on where we are in the recursion
	// First block is anchored to 0
	if ( b == 0 ) {
		blocks[b].first = 0;
	} else if (blocks[b-1].last <= N) {
		blocks[b].first = blocks[b-1].last;
	} else {
		// keep first at N
	}

	// Last block is anchored to N
	if ( b == (K-1) ) {
		blocks[b].last = N;
	} else if (blocks[b].last <= N) {
		// Otherwise block starts off null
		blocks[b].last = blocks[b].first;
	} else {
		// keep last at N
	}

	// A couple more things happen when this is the Kth call, which is the
	// innermost for loop
	// 1. Print the blocks structure so we can see where we are
	// 2. Do the calculation of the large blocks and return the latest
	//    minimumLargeSum
	int newMinimalLargeSum = minimalLargeSum;

	int largeSum = 0;
	for (int i = blocks[b].last; i <= N; i++) {
		blocks[b].last = i;
		largeSum = calculateLargeSums(P, blocks, b+1, newMinimalLargeSum);

		newMinimalLargeSum = min(largeSum, newMinimalLargeSum);
	}

	return newMinimalLargeSum;
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
	vector<Block> blocks(K);

	minimalLargeSum = calculateLargeSums(P, blocks, 0, minimalLargeSum);

    PRINT_BLOCK(gMinimalBlocks);
    PRINT_VECTOR(gMinimalSums);
    vector<int> diffs = calculateDifferences(gMinimalSums);
    PRINT_VECTOR(diffs);

	return minimalLargeSum;
}

int solution(int K, int M, vector<int> &A)
{
	const int N = A.size();
    M += 0;

	// Binary search uses information that data is sorted, so this
	// means we are going to use partial sums which will be sorted
    // But reduce the number of elements so that Rank(P) = Rank(A)+1;
	std::vector<int> P(1, 0);
    for (int i=0; i<N; i++) {
        if (A[i]) {
            P.push_back( P.back()+A[i] );
        }
    }

    int rankA = P.size()-1;

    // Quick check - if Rank(A) <= K then answer is max(A);
    if ( rankA <= K ) {
		auto maxElement = max_element(std::begin(A), std::end(A));
		return *maxElement;
    }

    // OK - we need K blocks
	vector<Block> blocks(K);

    // Going to put the average sum (or close to it)
    double searchValue = 0.0;
    double averageSum = ((double)(P.back()) / K );
    PRINT_VAR(averageSum);
    for (int k=0; k<K; k++) {
        // The average sum of the blocks we are looking for is
        // (total sum)/(num blocks)
        searchValue += averageSum;
        PRINT_VAR(searchValue);

        // First block first is 0
        // Last block last is rankA
        if ( k == 0 ) {
            blocks[k].first = 0;
        } else {
            blocks[k].first = blocks[k-1].last;
            // it is equal to the end of the last block
        }

        if ( k == (K-1) ) {
            blocks[k].last = rankA;
        } else {
            // Has to be at least one element, because rank > K
            // Go and find the element that is closest to the average as searched for
            // above
            int searchResult = upper_bound(P.begin(), P.end(), searchValue)-P.begin();
            int candidate = ((abs(searchValue-P[searchResult-1])) <= (abs(searchValue-P[searchResult]))) ?
                            searchResult-1 : searchResult;
            blocks[k].last = max((int) blocks[k].first+1, candidate);
        }
    }
	PRINT_VECTOR(P);
	PRINT_BLOCK(blocks);

    vector<int> sums(K, 0);

    // calculate sum for each block
    for (int k=0; k<K; k++) {
        sums[k] = P[blocks[k].last] - P[blocks[k].first];
    }
    PRINT_VECTOR(sums);
    int minimalLargeSum = *max_element(std::begin(sums), std::end(sums));
    PRINT_VAR(minimalLargeSum);

    cout << "optimizing ..." << endl;

    // Now go through and see if we can reduce the maximal further
    // Mainly go through and see if we can reduce any of the maxes, at least
    // until both are not smaller than they were.  Basically, if we made an
    // adjustment last time, assume we can make an adjustment this time
    // Do at each block until it can be done no further, then repeat loop
    // until no adjustments made
    bool furtherReductionPossible = false;
    do {
        cout << "--" << endl;
        furtherReductionPossible = false;

        // If we make an adjustment, then further reduction is possible
        for (int k=1; k<K; k++) {
            // If blocks equal continue
            if (sums[k] == sums[k-1]) {
                continue;
            }

            // If negative, take number from block [k-1] to block [k].
            // If positive, take number from block [k] to block [k-1].
            int direction = sums[k]-sums[k-1];

            Block bk = blocks[k];
            Block bk_1 = blocks[k-1];

            if ( direction < 0 ) {
                bk_1.last--;
                bk.first--;
            } else {
                bk_1.last++;
                bk.first++;
            }

            // Now check both sums are smaller than the previous max
            // Has to be smaller, cannot be the same
            int s = P[bk.last]-P[bk.first];
            int s_1 = P[bk_1.last]-P[bk_1.first];
            if ( (s<minimalLargeSum) && (s_1<minimalLargeSum) && s && s_1) {
                blocks[k] = bk;
                blocks[k-1] = bk_1;
            }
        }
        // calculate sum for each block
        for (int k=0; k<K; k++) {
            sums[k] = P[blocks[k].last] - P[blocks[k].first];
        }
	    PRINT_BLOCK(blocks);
	    PRINT_VECTOR(sums);
    
	    int innerMinimalLargeSum = *max_element(std::begin(sums), std::end(sums));
        PRINT_VAR(innerMinimalLargeSum);
    
        vector<int> diffs = calculateDifferences(sums);
        PRINT_VECTOR(diffs);
    
        int diff = std::accumulate(diffs.begin(), diffs.end(), 0);
        PRINT_VAR(diff);

        if ( innerMinimalLargeSum < minimalLargeSum ) {
            minimalLargeSum = innerMinimalLargeSum;
            furtherReductionPossible = true;
        }
    } while (furtherReductionPossible);

    cout << " ... optimized" << endl;
    
	PRINT_VAR(minimalLargeSum);

	return minimalLargeSum;
}
