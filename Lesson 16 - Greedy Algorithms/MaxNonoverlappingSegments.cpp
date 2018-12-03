// https://app.codility.com/programmers/lessons/16-greedy_algorithms/max_nonoverlapping_segments/
// 
// Task Score: 100%
// Correctness: 100%
// Performance: 100%
// Detected time complexity: O(N)
//
#include <vector>

using namespace std;

int solution(vector<int> &A, vector<int> &B) {
    const int N = A.size();
    
    // This handles case where N=0 and N=1
    // If N = 0, then we have no segments, and if N=1, we have one segment
    if (N < 2) {
        return N;
    }
    
    // This is going to be some sort of greedy search algorithm
    // We know we have to have a least one in a set
    int nonoverlappingSegments = 1;

    // our first end is the first end in the list
    // we know the segments are sorted by end (B)
    // We start with the first segment (which has the first ending),
    // and increment until we find a segment that does not start
    // within our segment.  That segment becomes
    // our next segment end, and we repeat the algorithm.  Seems to
    // work.  Not sure I find all sets, but I definitely am finding the
    // most nonoverlapping sets.
    int b = B[0];

    // start searching using the second element
    int i = 1;

    while ( i < N ) {
        // Skip all items overlapping with this one
        while ((i < N) && (A[i] <= b)) {
            i++;
        }
        if ( i==N ) {
            // No more segments to process
            break;
        }
        // move to next segment
        nonoverlappingSegments++;
        b=B[i];
    }
   
    return nonoverlappingSegments;
}
