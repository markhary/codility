// https://app.codility.com/programmers/lessons/7-stacks_and_queues/fish/
// 
// Task Score: 100%
// Correctness: 100%
// Performance: 100%
// Detected time complexity: O(N)
//
#include <vector>
#include <stack>

using namespace std;

int solution(vector<int> &A, vector<int> &B) {
    // In the algorithm, we are looking for fish to eat each other
    // until B looks something like [ {0s} {1s} ]
    // This is basically a sorting algorithm, so I expect it to be O(N*log(N))
    // but I am only going through it once so this should be O(N)

    // Probably could do this with two stacks but let's use a struct
    // to ensure we keep data together
    struct FishStruct {
      int size;
      int direction;
    };

    std::stack<FishStruct> fishes;

    int N = A.size();
    
    for (int i=0; i<N; i++) {
        // no fish, push and move on
        if ( fishes.empty() ) {
            FishStruct fish{A[i], B[i]};
            fishes.push(fish);
            continue;
        }
        
        bool eaten = false;
        do {
            // Get the last fish in the stack, and check the direction
            // If same, push this on stack and move on
            FishStruct lastFish = fishes.top();
            if ( lastFish.direction == B[i] ) {
                break;
            }
            
            // If fish on stack is 0 and we are a 1, we won't meet, so
            // push fish on stack and move
            // (Note, not strictly necessary to check B[i] because we know they are not equal)
            if ( !lastFish.direction && B[i] ) {
                break;
            }
            
            // Last Fish is moving downstream (1), this fish is moving upstream (0), somebody
            // is going to be eaten.  If this fish is bigger, then the other one is eaten
            // Need to do in loop until we are either eaten or going in same direction
            eaten = false;
            if ( A[i] > lastFish.size ) {
                // current fish going to eat fish on stack, eat fish on stack and repeat loop
                fishes.pop();
            } else {
                // F[i] is eaten, exit loop
                eaten = true;
            }
        } while (!fishes.empty() && !eaten);
            
        if ( !eaten) {
            // Fish not eaten, add it to the stack
            FishStruct fish{A[i], B[i]};
            fishes.push(fish);
        }
        
    }

    return fishes.size();
}
