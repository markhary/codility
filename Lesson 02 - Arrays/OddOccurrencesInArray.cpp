// https://app.codility.com/programmers/lessons/2-arrays/odd_occurrences_in_array/
//
// Task Score: 100%
// Correctness: 100%
// Performance: 100%
// Detected time complexity: O(N) or O(N*log(N))
//
int solution(vector<int> &A) {
    unsigned int size = A.size();
    unsigned long long int sum = 0;
    
    for (unsigned int i=0; i<size; i++) {
        // A xor B xor A = B
        sum ^= A[i];
    }
    
    return sum;
}
