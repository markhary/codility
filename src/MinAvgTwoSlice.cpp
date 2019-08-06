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

// Thank you @arthurafarias for the optimized solution
// The new algorithm reduces complexity from O(N^2) to O(N) by convolving 
// an average filter of length 3 and length 2. These filters are sufficient 
// in order to determine the minimum average of any slice from the vector.
int minavgtwoslice::solution(std::vector<int> &A)
{
	double minimum = std::numeric_limits<double>::max();
	int minimum_idx = 0;

	auto avg_filter = [](std::vector<int>::iterator begin, std::vector<int>::iterator end) -> double {
		double avg = 0;
		double size = end - begin;

		for (auto it = begin; it < end; it++)
			avg += (double)*it;

		avg = avg / size;

		return avg;
	};

	auto minimum_update = [&](double value, int idx) -> void { if (value < minimum) { minimum = value; minimum_idx = idx; } };

	for (unsigned idx = 0; idx < A.size(); idx++)
	{

		double avg2, avg3;

		if ((idx + 1) < A.size())
		{
			avg2 = avg_filter(A.begin() + idx, A.begin() + idx + 2);
			minimum_update(avg2, (int)idx);
		}

		if ((idx + 2) < A.size())
		{
			avg3 = avg_filter(A.begin() + idx, A.begin() + idx + 3);
			minimum_update(avg3, (int)idx);
		}
	}

	return minimum_idx;
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
