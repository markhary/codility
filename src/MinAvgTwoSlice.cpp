// https://app.codility.com/programmers/lessons/5-prefix_sums/min_avg_two_slice/
// 
// Task Score: 100%
// Correctness: 100%
// Performance: 100%
// Detected time complexity: O(N)
//

#include <vector>
#include <limits>

#include "MinAvgTwoSlice.h"

// Easier to understand than previous solution
int minavgtwoslice::solution(std::vector<int> &A)
{
    unsigned int N = A.size();
    long int sum;
    unsigned int minIdx;
    double avg;
    double minAvg = std::numeric_limits<double>::max();
    for(unsigned int i = 0; i < N-1; i++)
    {
        sum = A[i] + A[i+1];
        avg = (double)sum/2;
        if(avg < minAvg)
        {
            minAvg = avg;
            minIdx = i;
        }
        if(i+2 < N)
        {
            sum += A[i+2];
            avg = (double)sum/3;
            if(avg < minAvg)
            {
                minAvg = avg;
                minIdx = i;
            }
        }
    }
    return minIdx;
}


//
// Task Score: 60%
// Correctness: 100%
// Performance: 20%
// Detected time complexity: O(N^2)
//
// Brute force method.
// Calculate and list all possible slices, keep positions of smallest one,
// return only smallest
//
int minavgtwoslice::bruteForce(std::vector<int> &A) {
	int minP = std::numeric_limits<int>::max();
	int minQ = std::numeric_limits<int>::max();
	double minAverage = std::numeric_limits<double>::max();
	int N = A.size();

	for (int p=0; p<N; p++) {
		int sum = A[p];
		for (int q=(p+1); q<N; q++) {
			sum += A[q];
			double average = (double) sum/(q-p+1);
			//cout << "slice(" << p << ", " << q << ") = " << average << endl;
			if (average < minAverage) {
				minAverage = average;
				minP = p;
				minQ = q;
				//cout << "  ** new minimum average found" << endl;
			} else if (average == minAverage) {
				if (p < minP) {
					// Q isn't really q but I want to keep the pair
					minP = p;
					minQ = q;
					//cout << "  -- setting new minP" << endl;
				}
			}
		}
	}

	//cout << "min average found at slice (" << minP << ", " << minQ << ") = " << minAverage << endl;

	return minP;
}
