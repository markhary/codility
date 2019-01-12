// https://app.codility.com/programmers/lessons/16-greedy_algorithms/tie_ropes/
// 
// Task Score: 100%
// Correctness: 100%
// Performance: 100%
// Detected time complexity: O(N)

#include <vector>

using namespace std;

int solution(int K, vector<int> &A) {
    const int N = A.size();
    
    int ropes = 0; 
    int length = 0;
    
    for (int i=0; i<N; i++) {
		// Add rope to the "stack".  Tie it as soon as
		// it exceeds or equals K.  Assume this is
		// optimal.  This is O(N)
        length += A[i];
        
        if ( length >= K ) {
            ropes++;
			// Ropes have to be adjacent, so "cut" the rope
			// as soon as we tie one off
            length = 0;
        }
    }

    return ropes;
}
