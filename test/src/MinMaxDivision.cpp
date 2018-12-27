#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>

#include "macros.h"

using namespace std;

int solution(int, int, vector<int> &);
int bruteForce(int, int, vector<int> &);

void test(int testNum, int runTestNum, int K, int M, vector<int> A, bool assert = false, bool printA = false, bool runBruteForce = true) 
{
    if ( runTestNum && testNum != runTestNum ) {
        return;
    }
    cout << "---- Test " << testNum << " ----" << endl;
    if (printA) {
        PRINT_VECTOR(A);
    }

    PRINT_VAR(K);
    PRINT_VAR(M);

    auto start = chrono::high_resolution_clock::now();

	cout << "calculating solution..." << endl;
    auto answer = solution(K, M, A);

    auto stop = chrono::high_resolution_clock::now();

	PRINT_VAR(answer);

    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start); 
    cout << duration.count() << " us" << endl; 

	if ( !runBruteForce ) {
		cout << "skipping brute force answer..." << endl;
		return;
	}

	cout << "  == == == == == == == == == ==  " << endl;
	cout << "calculating brute force answer..." << endl;
   	auto correct = bruteForce(K, M, A);
	PRINT_VAR(correct);
    cout << answer << " =? " << correct << endl;

	if (assert) {
		assert( answer == correct );
	}

    // Nice debug statement if we are not asserting
    cout << ((answer == correct) ? " pass " : " *** FAIL *** ") << endl;
}

vector<int> generateRandomSequence(int N, int M)
{
    vector<int> A(N);
    srand(time(0));

    for (int i=0; i<N; i++) {
        A[i] = rand() % (M+1);
    }
    return A;
}

vector<int> generateOneOrMSequence(int N, int M, double prob)
{
    vector<int> A(N);
    srand(time(0));

    for (int i=0; i<N; i++) {
        A[i] = rand() % (M+1);
        ( A[i] < (prob*M) ) ? (A[i] = 1 ) : (A[i]=M);
    }
    return A;
}

int main(int argc, char **argv) 
{
	bool assert = false;
    int runTestNum = 0;
    bool printA = true;
    bool runBruteForce = true;

    cout << "========================================" << endl;
    cout << "==              START TEST            ==" << endl;
    cout << "========================================" << endl;

	if (argc == 2) {
		if ( !strcmp(argv[1], "true") ) {
			assert = true;
		}
	}

	if (argc == 3) {
	   runTestNum = atoi(argv[2]);
	}

	if (argc == 4) {
        assert = false;
        printA = false;
        runBruteForce = false;

		int N = atoi(argv[3]);
		int M = atoi(argv[2]);
		int K = atoi(argv[1]);
		vector<int> A = generateRandomSequence(N, M);
		test(1, 0, K, M, A, assert, printA, runBruteForce);
		exit(0);
	}	

	int testNum = 1;
   	test(testNum++, runTestNum, 1, 5, {0, 0}, assert, printA, runBruteForce); 
   	test(testNum++, runTestNum, 4, 10, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, assert, printA, runBruteForce); 
   	test(testNum++, runTestNum, 4, 10, {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, assert, printA, runBruteForce); 
   	test(testNum++, runTestNum, 1, 5, {2, 1, 5, 1, 2, 2, 2}, assert, printA, runBruteForce); 
   	test(testNum++, runTestNum, 2, 5, {2, 1, 5, 1, 2, 2, 2}, assert, printA, runBruteForce); 
   	test(testNum++, runTestNum, 3, 5, {2, 1, 5, 1, 2, 2, 2}, assert, printA, runBruteForce); 
   	test(testNum++, runTestNum, 4, 5, {2, 1, 5, 1, 2, 2, 2}, assert, printA, runBruteForce); 
   	test(testNum++, runTestNum, 5, 5, {2, 1, 5, 1, 2, 2, 2}, assert, printA, runBruteForce); 
   	test(testNum++, runTestNum, 20, 5, {0, 5, 0}, assert, printA, runBruteForce); 
   	test(testNum++, runTestNum, 4000, 5, {0, 5, 0}, assert, printA, runBruteForce); 
   	test(testNum++, runTestNum, 10000, 5, {2, 1, 5, 1, 2, 2, 2}, assert, printA, runBruteForce); 
   	test(testNum++, runTestNum, 10000, 10000, {0, 10000, 0}, assert, printA, runBruteForce); 

    // Calculated array tests
    //
    // Do some mini random sequence tests
	int N = 20;
	int M = 5;
	int K = 5;
    {
		vector<int> A = generateRandomSequence(N, M);
	    test(testNum++, runTestNum, K, M, A, assert, printA, runBruteForce);
    }

    {
        N = 10;
        M = 10000;
		vector<int> A = generateRandomSequence(N, M);
        test(testNum++, runTestNum, K, M, A, assert, printA, runBruteForce);
    }

    {
        N = 20;
        M = 10000;
		vector<int> A = generateOneOrMSequence(N, M, 0.90);
        test(testNum++, runTestNum, K, M, A, assert, printA, runBruteForce);
    }

	// Don't run brute force test below here because brute force
    // is O(N^K)
    assert = false;
    printA = false;
    runBruteForce = false;

	N = 100000;
	M = 10000;
	K = 100000;
	vector<int> T(N);

    // Test max values with max K
    {
        for (int i=0; i<N; i++) {
            T[i] = M;
        }
        test(testNum++, runTestNum, K, M, T, assert, printA, runBruteForce);
    }

    // Make it so that K blocks need to be calculated
	M = 10000;
	K = 10000;

    // Test max values
    {
        for (int i=0; i<N; i++) {
            T[i] = M;
        }
        test(testNum++, runTestNum, K, M, T, assert, printA, runBruteForce);
    }

    // Test binary values
    {
		vector<int> A = generateRandomSequence(N, 2);
        test(testNum++, runTestNum, K, M, T, assert, printA, runBruteForce);
    }
    
    // Test random values from [0 .. M] but with K=10000
    {
        vector<int> A = generateRandomSequence(N, M);
        test(testNum++, runTestNum, K, M, A, assert, printA, runBruteForce);
    }
}
