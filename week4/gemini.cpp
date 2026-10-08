
#include <iostream>
#include <iomanip>
#include <chrono>

/**
 * The Python logic implements a Leibniz-like series for Pi:
 * result = sum_{i=1 to N} (-1/(4i - 1) + 1/(4i + 1))
 * Total = 4 * sum = 4 * (1/1 - 1/3 + 1/5 - 1/7 ...) = PI
 */
int main() {
    const long long iterations = 200000000;
    const double param1 = 4.0;
    const double param2 = 1.0;

    auto start = std::chrono::high_resolution_clock::now();

    double result = 0.0;
    
    // Loop unrolling and compiler optimization will handle the floating point operations.
    // Using double precision for the calculation.
    #pragma omp simd reduction(+:result)
    for (long long i = 1; i <= iterations; ++i) {
        double j1 = i * param1 - param2;
        double j2 = i * param1 + param2;
        result += (1.0 / j2) - (1.0 / j1);
    }

    result *= 4.0;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Result: " << std::fixed << std::setprecision(12) << result << std::endl;
    std::cout << "Execution Time: " << std::fixed << std::setprecision(6) << elapsed.count() << " seconds" << std::endl;

    return 0;
}
