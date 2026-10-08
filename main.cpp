
#include <iostream>
#include <iomanip>
#include <chrono>

/**
 * The Python logic implements: 
 * result = 1.0
 * for i in 1 to 200,000,000:
 *     result -= 1/(4*i - 1)
 *     result += 1/(4*i + 1)
 * result *= 4
 * 
 * This is the Leibniz formula for Pi (1 - 1/3 + 1/5 - 1/7 + ... = PI/4)
 */

int main() {
    const long long iterations = 200000000;
    const double param1 = 4.0;
    const double param2 = 1.0;

    auto start = std::chrono::high_resolution_clock::now();

    double result = 1.0;
    
    // Using OpenMP or loop unrolling is possible, 
    // but the serial dependency on the result makes simple summation best.
    // Modern compilers will vectorize this effectively with -Ofast and -mcpu=native.
    for (long long i = 1; i <= iterations; ++i) {
        double i_f = static_cast<double>(i);
        result -= 1.0 / (i_f * param1 - param2);
        result += 1.0 / (i_f * param1 + param2);
    }

    result *= 4.0;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;

    std::cout << "Result: " << std::fixed << std::setprecision(12) << result << std::endl;
    std::cout << "Execution Time: " << std::fixed << std::setprecision(6) << diff.count() << " seconds" << std::endl;

    return 0;
}
