// https://app.codility.com/programmers/lessons/4-counting_elements/missing_integer/
//
// Task Score: 100%
// Correctness: 100%
// Performance: 100%
// Detected time complexity: O(N) or O(N * log(N))
//
#include <vector>

using namespace std;

int solution(vector<int> &A) {
	const int N = 1000001;
	vector<bool> integers(N, false);

	int n = A.size();
	for (int i=0; i<n; i++) {
		if (A[i] > 0) {
			integers[A[i]] = true;
		}
	}

	for (int i=1; i<N; i++) {
		if (!integers[i]) {
			return i;
		}
	}

	return 0;
}
