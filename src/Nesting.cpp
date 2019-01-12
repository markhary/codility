// https://app.codility.com/programmers/lessons/7-stacks_and_queues/nesting/
// 
// Task Score: 100%
// Correctness: 100%
// Performance: 100%
// Detected time complexity: O(N)
//
#include <string>
#include <stack>
using namespace std;

int solution(string &S) {
    int N = S.length();

    // Quick check for empty string
    if ( N == 0) {
        return 1;
    }
    
    // Any nested string is a pair, so odd length strings are improperly nested
    if ( N%2 ) {
        return 0;
    }
    
    // Go through the string:
    // * Push if '('
    // * Pop if ')' and check if '(' returned - return 0 if not
    // * When done with loop, stack should be empty, return 0 if not
    // This is O(N)
    stack<char> nest;
    char c;
    for (int i=0; i<N; i++) {
        switch (S[i]) {
            case '(':
                nest.push(S[i]);
                break;
            case ')':
                c = nest.top();
                nest.pop();
                if ( c != '(') {
                    return 0;
                }
                break;
            default: break;
        }
    }

    // Some elements were left hanging!
    if (nest.size() > 0 ) {
        return 0;
    }
    
    // No errors, so good!
    return 1;
}
