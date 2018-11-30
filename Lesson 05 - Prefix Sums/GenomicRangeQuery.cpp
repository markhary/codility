// https://app.codility.com/programmers/lessons/5-prefix_sums/genomic_range_query/
// 
// Task Score: 100%
// Correctness: 100%
// Performance: 100%
// Detected time complexity: O(N+M)
//
#include <vector>
#include <string>
using namespace std;

#include <vector>
#include <string>
using namespace std;

vector<int> solution(string &S, vector<int> &P, vector<int> &Q) {
	const int A_VAL = 1;
	const int C_VAL = 2;
	const int G_VAL = 3;
	const int T_VAL = 4;

	// Have to track these values separately, this costs us space complexity
	// but saves us time complexity.  Can't do this simply with prefix_sums with
	// single  vector of fundamental type (or at least I am not clever enough to see it)
	int N = S.size();
	vector<int> A(N, -1);
	vector<int> C(N, -1);
	vector<int> G(N, -1);
	vector<int> T(N, -1);

	int aLastIndex = -1;
	int cLastIndex = -1;
	int gLastIndex = -1;
	int tLastIndex = -1;

	// Complexity of this operation is O(N)
	for (int n=0; n<N; n++) {
		switch (S[n]) {
			case 'A': 
				aLastIndex = n;
				break;
			case 'C': 
				cLastIndex = n;
				break;
			case 'G': 
				gLastIndex = n;
				break;
			case 'T': 
				tLastIndex = n;
				break;
			default: 
				break;
		}
		A[n] = aLastIndex;
		C[n] = cLastIndex;
		G[n] = gLastIndex;
		T[n] = tLastIndex;
	}

	int M = P.size();
	vector<int> result(M, 0);

	// Complexity of this operation is O(M+1) ==> O(M)
	for (int m=0; m<M; m++) {
		int l = P[m];
		int r = Q[m];

		// Check if the last seen index is greater or less than the left value
		// If it is then that is the nucleotide for this space.  Done in order
		// of lowest to highest impact factor.
		// LOGIC:  
		//   1. A[r] cannot be greater than the n at that location.
		//      See assignment above, so no need to check it separately
		//   2. A[r] will be equal to l if A was last seen at index l
		//   3. A[r] will be less than l if A was last seen before index l
		//   4. A[r] will be greater than l if A was seen after l up to and including r
		if ( A[r] >= l ) { 
			result[m] = A_VAL;
		} else if ( C[r] >= l ) {
			result[m] = C_VAL;
		} else if ( G[r] >= l ) {
			result[m] = G_VAL;
		} else if ( T[r] >= l ) {
			result[m] = T_VAL;
		}
	}

	return result;
}

// End of submitted code
//
// This code here shows the evolution of my program, from brute force
// to final draft
//

#ifdef BRUTE_FORCE

// Original Solution
//
// Task Score: 62%
// Correctness: 100%
// Performance: 0%
// Detected time complexity: Not detected, performance timed out.
vector<int> solution(string &S, vector<int> &P, vector<int> &Q) {
	const int A_VAL = 1;
	const int C_VAL = 2;
	const int G_VAL = 3;
	const int T_VAL = 4;

	// iterate through array and create my value array
	int N = S.size();
	vector<int> V(N, 0);
	for (int n=0; n<N; n++) {
		switch (S[n]) {
			case 'A': V[n] = A_VAL; break;
			case 'C': V[n] = C_VAL; break;
			case 'G': V[n] = G_VAL; break;
			case 'T': V[n] = T_VAL; break;
			default: break;
		}
	}

	int M = P.size();
	vector<int> result(M, 0);

	for (int m=0; m<M; m++) {
		int l = P[m];
		int r = Q[m];

		int minimum = 4;

		for (int i=l; i<=r; i++) {
			if (V[i] < minimum) {
				minimum = V[i];
			}
			// If this is an A then we know minimum is 1, can go to next iteration
			if (minimum == 1) {
				result[m] = minimum;
				break;
			}
		}
		result[m] = minimum;
	}

	return result;

}

#endif
