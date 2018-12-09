// https://app.codility.com/programmers/lessons/8-leader/dominator/
// 
// Task Score: 100%
// Correctness: 100%
// Performance: 100% or Not assessed
// Detected time complexity: O(N)
//
#include <vector>
#include <stack>

using namespace std;

// Expected time complexity is O(N)
// Expected space complexity is O(N)
int solution(vector<int> &A) {
    const int N = A.size();
    
    // First, L_l = L_r == L
    // Algorithm:
    // - Iterate and find leader
    // - Now that we know leader, go back through and iterate again,
    //   finding equileaders.  We know N and L and our current index, and
    //   can do the math
    stack<int> candidates;
    
    // Find the leader using the algorithm suggested by codility
    // This is O(N)
    for (int i=0; i<N; i++) {
        if ( !candidates.empty() ) {
            // If the top isn't equal to this, remove them both
            int candidate = candidates.top();
            if ( candidate != A[i] ) {
                candidates.pop();
            } else {
                candidates.push(A[i]);   
            }
        } else {
            // empty, so push this on the list
            candidates.push(A[i]);
        }
    }
    
    // I have my candidate.  If list is empty, then there are no candidates
    // and we can return.  If list is not empty, candidate is in the list (they must
    // all be the same)
    if ( candidates.empty() ) {
        return -1;
    }
    int candidate = candidates.top();
    
    // Iterate through list again and determine if candidate is the leader
    // Can't exit list early, because we have to know total number of leader
    // elements in A
    // This is O(N)
    int count = 0;
    int index = -1;
    for (int i=0; i<N; i++) {
        if ( A[i] == candidate ) {
            count++;
            index = i;
        }
    }
    
    // Have to have > N/2 instances to be a leader
    double half = ((double) N)/2;
    if ( !((double (count)) > half) ) {
            return -1;
    }

    // Have the leader, return the last index found
    return index;
}
