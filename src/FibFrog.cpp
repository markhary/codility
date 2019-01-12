// https://app.codility.com/programmers/lessons/13-fibonacci_numbers/fib_frog/
// 
// Task Score: 100%
// Correctness: 100%
// Performance: 100%
// Detected time complexity: O(N*log(N))
//
#include <limits>
#include <list>
#include <vector>

using namespace std;

int solution(vector<int> &A) {
    const int N = A.size();

    // Create our list to track if frogs are already at a location
    vector<bool> locations(N, false);

    // Calculate the fibonacci numbers up to 100000 (max N)
    // Do it once at the start of the function
    // F(0) = 0; F(1) = 1;
    // This is O(1)
    vector<int> F = {0, 1};
    int i = 2;
    while ( (F[i-1]+F[i-2]) <= 100000 ) {
        F.push_back(F[i-1] + F[i-2]);
        i++;
    }

    // Start at location -1.  Set jumps to 0.  Push to list
    // 1. Check list
    //    - If empty, no path possible
    // 2. Check if (jumps+1) >= minimumJumps, discard if so
    // 2. Iterate through all fibonacci positions away from this one that place me <= N
    // 3. Where path available, increment jumps
    // 4. Check if we are already on that leaf, if not, push to list
    int minimumJumps = std::numeric_limits<int>::max();

    struct PathStruct {
        int location;
        int jumps;

        PathStruct(int l, int j) : location(l), jumps(j) {}
    };

    std::list<PathStruct> paths;

    // Initialize and place first position
    paths.push_back(PathStruct(-1, 0));

    // Check list
    while ( !paths.empty() ) {
        // Grab from the list.  There is no guarantee of order
        // anywhere in the list - A frog further along could not have a leaf to 
        // jump to, or could just jump one more, while a frog further behind
        // could jump ahead.  So we aren't saving any time by guessing if front
        // of list of back of list is faster, just use a FIFO.
        const PathStruct path = paths.front();
        paths.pop_front();

        // Remove this leaf from the tracked locations
        if ( path.location >= 0 ) {
            locations[path.location] = false;
        }

        // Check if this path could be shorter than the current minimumJumps
        // If not, then discard it from the queue
        if ( (path.jumps+1) >= minimumJumps ) {
            continue;
        }

        // Go through each fibonacci number and see if
        // we can reach another leaf (location<N) or the
        // bank (location == N).  F[1] and F[2] are duplicates, and F[0] is 0
        for (unsigned int f=2; f<F.size(); f++) {
            int candidate = path.location + F[f];

            if ( (candidate < N) && A[candidate] ) {
                // Don't consider leaf if it is already under conseration
                if ( locations[candidate] ) {
                    continue;
                }
                // Reached another leaf
                paths.push_back(PathStruct(candidate, path.jumps+1));
                locations[candidate] = true;
            } else if ( candidate == N ) {
                // Reached bank
                minimumJumps = std::min(minimumJumps, path.jumps+1);

                // jump out of this loop, logic says this has to be a new
                // minimum jump for this possible path
                break;
            } else if (candidate > N) {
                // Oops - kerplop!
                // F is increasing from here on out so 
                // lets stop checking this iteration
                break;
            }
        }
    }

    // check if I found a path
    if ( minimumJumps == std::numeric_limits<int>::max() ) {
        minimumJumps = -1;
    }

    return minimumJumps;
}
