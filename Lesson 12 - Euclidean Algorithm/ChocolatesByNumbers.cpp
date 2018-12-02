// https://app.codility.com/programmers/lessons/12-euclidean_algorithm/chocolates_by_numbers/
// 
// Task Score: 100%
// Correctness: 100%
// Performance: 100%
// Detected time complexity: Complexity
//

// Defined in Codility Chapter 12 - Euclidean Algorithm (12.2)
long long int greatestCommonDivisor(long long int a, long long int b) {
    if ((a % b) == 0) {
        return b;
    }
    return greatestCommonDivisor(b, a%b);
}

// Defined in Codility Chapter 12 - Euclidean Algorithm (12.4)
long long int leastCommonMultiple(long long int a, long long int b) {

   return (a*b)/greatestCommonDivisor(a,b); 
}

int solution(int N, int M) {
    // Algorithm
    // Find Least Common Multiple of {N, M}
    // Answer is LCM/M
    
    long long int lcm = leastCommonMultiple(N, M);
    
    return lcm/M;
}
