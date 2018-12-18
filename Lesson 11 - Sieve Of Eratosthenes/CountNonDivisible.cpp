// https://app.codility.com/programmers/lessons/11-sieve_of_eratosthenes/count_non_divisible/
// 
// Task Score: 100%
// Correctness: 100%
// Performance: 100%
// Detected time complexity: O(N*log(N))
//
#include <iostream>
#include <map>
#include <vector>

using namespace std;

vector<int> solution(vector<int> &A) {
    const int N = A.size();

    map<int, int> divisors;

    // Get list of possible divisors, map will sort it
	// This is worst case O( N*log(N) )
	for (const auto &a: A) {
		divisors[a]++;
	}

    // Go through and calculate the number of divisors that are missing
    // We know that there are at least N nondivisors present if none
	// of the divisors are present.  Making this +1 so I don't have to use
	// zero based indices
    vector<int> track((2*N)+1, N);

    // Generate divisors list
	// This is the Sieve of Eratosthenes method
	for (const auto &d: divisors) {
		for (int i=1; i*d.first <= 2*N; i++) {
			track[i*d.first] -= d.second;
		}
	}

	// Look up nondivisors
    vector<int> nondivisors(N, 0);
	for (int i=0; i<N; i++) {
        nondivisors[i] = track[A[i]];
	}

    return nondivisors;
}
