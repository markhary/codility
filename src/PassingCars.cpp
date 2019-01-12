// https://app.codility.com/programmers/lessons/5-prefix_sums/passing_cars/
//
// Task Score: 100%
// Correctness: 100%
// Performance: 100%
// Detected time complexity: O(N)
// 
#include <numeric>
#include <vector>

int solution(std::vector<int> &A) {

    int n = A.size();
    unsigned int numPassing = 0;

    // Generate prefix sums
    std::vector<int> P(n, 0);
    std::partial_sum(A.begin(), A.end(), P.begin());

    // Go through array and count cars passed for ones starting with 0
    for (int i=0; i<n; i++) {
        if (!A[i]) {  
            int num = P[n-1] - P[i];
            numPassing += num;
            if (numPassing > 1000000000) {
                return -1;
            }
        }
    }

    return numPassing;
}

// End of submitted code
//
// This code here shows the evolution of my program, from brute force
// to final draft
//

#ifdef NOT_SUBMITTED

#include <numeric>

// Implementing these methods from https://codility.com/media/train/3-PrefixSums.pdf
// TODO: Look at using std::partial_sum once this works
vector<int> prefixSums(vector<int> A) {
    int n = A.size();
    vector<int> B(n+1, 0);
    for (int k=1; k<(n+1); k++) {
        B[k] = B[k-1] + A[k-1];
    }

    for (int i=0; i<n+1; i++) {
        cout << "B[" << i << "] = " << B[i] << endl;
    }
    return B;
}

int countTotal(const vector<int>P, int x, int y) {
    return P[y] - P[x];
}

int solution(vector<int> &A) {

    int n = A.size();
    unsigned int numPassing = 0;

#ifdef BRUTE_FORCE

    for (int i=0; i<n; i++) {
        // get car direction - we are A[i]

        // Go through every car and see if it is the opposite of me.  If it is,
        // then this is a car I will pass.  Don't consider pairs I have already
        // considered (meaning don't go backwards)
        // Also, passing is P going east, and Q going west, not other way around
        // so !0 AND 1
        for (int j=i; j<n; j++) {
            if ( !A[i] && A[j] ) {
                numPassing++; 
                if (numPassing > 1000000000) {
                    return -1;
                }
            }
        }
    }
#elif 0 // Faster method using methods in PrefixSums.pdf (see above)

    // Using passing sums method
    // I can iterate through array and add up sums
    // Then iterate again, skip ones starting with 1 and only look at A[i]
    // starting with 0.  Then look at p(y+1)- p(x)
    // In example we have I am looking for 3 + 2 = 5;
    // Test with other examples
    // This is going to be O(N) if I do it right.

    cout << "generating prefix sums" << endl;

    // Generate prefix sums
    vector<int> P = prefixSums(A);
    //int m = P.size();

    cout << "done" << endl;

    // Go through array and count cars passed for ones starting with 0
    for (int i=0; i<n; i++) {
        if (!A[i]) {  
            int num = countTotal(P, i, n);
            cout << "Car " << i << " passed " << num << " cars" << endl;
            numPassing += num;
            if (numPassing > 1000000000) {
                return -1;
            }
        }
    }

#else   // using std::partial_sum instead of writing my own
    // Generate prefix sums
    vector<int> P(n, 0);
    std::partial_sum(A.begin(), A.end(), P.begin());

    cout << "done" << endl;

    // Go through array and count cars passed for ones starting with 0
    for (int i=0; i<n; i++) {
        if (!A[i]) {  
            int num = P[n-1] - P[i];
            cout << "Car " << i << " passed " << num << " cars" << endl;
            numPassing += num;
            if (numPassing > 1000000000) {
                return -1;
            }
        }
    }

#endif

    return numPassing;
}

#endif
