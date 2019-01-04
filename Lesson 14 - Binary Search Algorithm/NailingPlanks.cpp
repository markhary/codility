// https://app.codility.com/programmers/lessons/14-binary_search_algorithm/nailing_planks/
// 
// Task Score: 87%
// Correctness: 100%
// Performance: 75%
// Detected time complexity: O((N + M) * log(M))
//

#include <iostream>
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
    int solution(vector<int> &A, vector<int> &B, vector<int> &C)
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
}
