// https://app.codility.com/programmers/lessons/15-caterpillar_method/count_distinct_slices/
// 
// Task Score: 100%
// Correctness: 100%
// Performance: 100%
// Detected time complexity: O(N)
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

int solution(int M, vector<int> &A) {
    const int N = A.size();

    // M is [0..100000], so need to account for 0
    // This will give me time complexity O(N) and space complexity O(M)
    // I could use a hash but that would give me time complexity O(N) but
    // worst case space complexity is still O(M), just going to go for O(N) and O(M)
    vector<int>Z(M+1, 0);

    // Remember that slices of length 1 count, which means we will
    // always have at least N distinct slices.  I do not have to count them
    // specifically, as the method below will count them
    long long int distinctSlices = 0;

    // track where start of current sequence is
    int j = 0;

    // track how long current sequence is.  
    long long int sequenceLength = 0;

    // Go through all items
    for ( int i=0; i<N; i++) {
        // Everytime we loop we need to add the current sequenceLength
        // to the count.  This is done by observation.  At first I waited
        // until I found a duplicate, and then I added x*(x+1)/2 but this
        // double counted elements.  Then I observed everytime I incremented
        // a number, I needed to add that many combinations, and I do
        // not double count what I have already seen.
        Z[A[i]]++;
        if ( Z[A[i]] < 2 ) {
            sequenceLength++;
            distinctSlices += sequenceLength;
            continue;
        }

        // then start incrementing j and removing items from
        // the duplicate list.  There is going to be one item in the
        // list with a duplicate (value == 2), and keep 
        // incrementing j/removing sequenceLength until we
        // remove it or get to i
        bool removedDuplicate = false;

        while ( (j < i) && !removedDuplicate ) {
            // remove A[j] from list
            Z[A[j]]--;
            
            // This will either be 0 (because it was not a duplicate) or else 1
            // (because it was the duplicate).  Continue until we remove the
            // duplicate
            if ( Z[A[j]] ) {
                // New distinct element, so add sequence length as before
                distinctSlices += sequenceLength;
                removedDuplicate = true;
            } else {
                // haven't removed duplicate yet, continue along
                sequenceLength--;
            }
            j++;
        }
    }

    // If the number of distinct slices is greater than 1000000000,
    // then function should return 1000000000;
    return std::min(distinctSlices, (long long int)1000000000);
}
