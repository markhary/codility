// https://app.codility.com/programmers/lessons/5-prefix_sums/min_avg_two_slice/
// 
// Task Score: 100%
// Correctness: 100%
// Performance: 100%
// Detected time complexity: O(N)
//

#include <vector>
#include <limits>

int solution(std::vector<int> &A)
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
