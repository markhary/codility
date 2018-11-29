// https://app.codility.com/programmers/lessons/3-time_complexity/perm_missing_elem/
//
// Task Score: 100%
// Correctness: 100%
// Performance: 100%
// Detected time complexity: O(N) or O(N * log(N))
//
int solution(vector<int> &A) {
    
    // N is size of the array
    unsigned long long int N = A.size();
    unsigned long long int sum = 0;
    
    for (unsigned int i=0; i<N; i++) {
        sum += A[i];
    }
    
    // Test the missing element could be 1 or N+1
    double answer = (N+1)*(N+2)/2 - sum;

    return answer;
}
