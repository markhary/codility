// https://app.codility.com/programmers/lessons/7-stacks_and_queues/stone_wall/
// 
// Task Score: 100%
// Correctness: 100%
// Performance: 100%
// Detected time complexity: O(N)
//
#include <vector>
#include <stack>
using namespace std;

int solution(vector<int> &H) {
    int N = H.size();

    // Algorithm seems to be:
    // 1. Every time building grows, push a height
    // 2. If height stays same, do nothing
    // 3. When height drops, pop while queue not empty and last height greater than current height
    // 4. If height is now equal to last height, then continue along, otherwise push new height
    // 5. At end need to close out all current blocks in queue
    // Should be 0(N) time complexity
    std::stack<int> heights;
    int blocks = 0;
    
    for (int i=0; i<N; i++) {
        if ( !heights.size() ) {
            // stack is empty, either because we just started
            // or we ended a current building line.  So just push it
            heights.push(H[i]);
        } else if ( H[i] == heights.top() ) {
        } else if ( H[i] > heights.top() ) {
            // height grew, push to stack
            heights.push(H[i]);
        } else {
            // height must have dropped.  Pop height and increment bricks 
            // while the last height is taller than this height (and stack not empty)
            while ( heights.size() && (heights.top() > H[i]) ) {
                blocks++;
                heights.pop();
            }

            // If stack is empty, or H[i] not equal heights.top(), need to push this height onto the stack
            // If the heights are equal, then continue along (since it wasn't popped)
            if ( !heights.size() || (heights.top() != H[i]) ) {
                heights.push(H[i]);
            }
        }
    }
    
    // At the very end, need to close out all blocks in queue
    while ( heights.size() ) {
        blocks++;
        heights.pop();
    }
    
    return blocks;
}
