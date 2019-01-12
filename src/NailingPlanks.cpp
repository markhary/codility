// https://app.codility.com/programmers/lessons/14-binary_search_algorithm/nailing_planks/
// 
// Task Score: 100%
// Correctness: 100%
// Performance: 100%
// Detected time complexity: O((N+M)*log(M))
//

#include <iostream>
#include <numeric>
#include <vector>

#include "NailingPlanks.h"
#include "macros.h"

using namespace std;

namespace nailingplanks
{
    struct PlankStruct {
        int start;
        int stop;
    };

    #define PRINT_PLANKS(X) { \
		cout << #X << " =  [ "; \
		for (const auto &x: X) { cout << "{" << x.start << ", " << x.stop << "} "; } \
		cout << "];" << endl; \
	}

    //
    // Task Score: 87%
    // Correctness: 100%
    // Performance: 75%
    // Detected time complexity: O((N + M) * log(M))
    //
    // Put planks into a list, then iterate through the list for each
    // C and pop it off if the list is empty.  Return -1 if the list isn't empty.
    //
    // Assumptions:
    //  - N and M are integers within the range [1..30,000];
    //  - each element of arrays A, B, C is an integer within the range [1..2*M];
    //  - A[K] ≤ B[K].
    //
    // Edge conditions:
    //  - N never empty
    //
    int bruteForce(vector<int> &A, vector<int> &B, vector<int> &C)
    {
        const int N = A.size();
        const int M = C.size();
        vector<PlankStruct> remaining(N);
        vector<bool> nails(2*M+1, false);

        // create plank struct
        for (int i=0; i<N; i++) {
            remaining[i].start = A[i];
            remaining[i].stop = B[i];
        }

        int minimum = -1;

        // go through each nail, done once list is empty
        vector<PlankStruct> planks;

        for (int j=0; j<M; j++ ) {
            if ( nails[C[j]] ) {
                continue;
            }

            nails[C[j]] = true;
            planks = remaining;
            remaining.clear();

            for (int i=0; i<(int)planks.size(); i++) {
                if ( (C[j] < planks[i].start) || (C[j] > planks[i].stop) ) {
                    // Nail doesn't touch this plank 
                    remaining.push_back(planks[i]);
                } else {
                    // Nail is in plank, remove it from consideration
                    // by not adding it to remaining
                }
            }

            // Nothing remains!  This was the final nail.
            if ( remaining.size() == 0 ) {
                minimum = j+1;
                break;
            }
        }

        return minimum;
    }

    //
    // Assumptions:
    //  - N and M are integers within the range [1..30,000];
    //  - each element of arrays A, B, C is an integer within the range [1..2*M];
    //  - A[K] ≤ B[K].
    //
    // Going to use a prefix sum as the basis of the binary search.  Increment the
    // count each time a nail is encountered
    bool isNailed(int nail, const vector<int> &A, const vector<int> &B, const vector<int> &C)
    {
        const int N = A.size();
        const int M = C.size();

        // This also accounts for duplicate nails, essentially ignores them
        vector<int> nails(2*M+1, 0);
        for (int i = 0; i < nail; i++)
        {
            nails[C[i]] = 1;
        }

        // Create the partial sums based on the nails present
        std::partial_sum(nails.begin(), nails.end(), nails.begin());

        // A given plank is nailed when the number of nails changes
        // within its range.  Have to check the nail right before 
        // start though (since the nail could be put in at the first
        // element.  Stop as soon as we find a plank that is not nailed
        bool nailed = true;
        for (int i = 0; (i < N) && nailed; i++)
        {
            nailed = (nails[B[i]] - nails[A[i]-1]) > 0;
        }

        return nailed;
    }

    // The standard binary search mechanism
    int solution(vector<int> &A, vector<int> &B, vector<int> &C)
    {
        int minNails = 1;
        int maxNails = C.size();

        int result = -1;
        while (minNails <= maxNails)
        {
            int mid = (minNails + maxNails) / 2;
            if (isNailed(mid, A, B, C))
            {
                maxNails = mid - 1;
                result = mid;
            } else {
                minNails = mid + 1;
            }
        }

        return result;
    }
}
