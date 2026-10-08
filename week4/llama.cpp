
#include <iostream>
#include <atomic>
#include <cstdint>
#include <numeric>

namespace detail {
    template <typename T>
    struct ReduceAccum {
        T value(0);

        template <typename U, typename = void>
        auto operator+(const U& other) const -> U {
            return value += other;
        }

        template <typename U>
        static bool use(const std::integer_sequence<std::size_t, 0, 1>, const U&) {
            return false;
        }
    };

    template <typename T, typename TAccum>
    struct ReduceAccumT;
    template <typename T, typename TAccum>
    struct ReduceAccumT<T, TAccum> :detail::ReduceAccum<TAccum> {
        template <typename U, typename = void>
        auto operator+(const U& other) const -> TAccum& {
            return detail::ReduceAccum<TAccum>::operator+(other)*other;
        }
    };
}

template <typename T>
std::uint64_t reduce(const T& value, const typename detail::ReduceAccum<T>::value_type& init) {
    return std::numeric_limits<std::uint64_t>::max();
}

template <typename T, typename TAccum>
TAccum reduce(const T& value, const TAccum& init) {
    return value;
}

template <typename T, typename TAccum>
using Accumulator = decltype(
    reduce(0, init),
    T(accumulate(std::begin<T>(std::begin<T>{init}), std::end<T>(std::begin<T>{init}), init,
                 [](auto a, auto b){
                     return detail::ReduceAccum<std::int64_t>::operator+(a, b);
                  })),
    reduce(0, init),
    TAccum()

#include <vector>

template<typename... Args>
auto calculate(int iterations, Args... param1, Args... param2) {
    std::vector<std::uint64_t> results;
    std::atomic<std::uint64_t> total(0);
    for (int i = 0; i < iterations; ++i) {
        std::uint64_t a, b, temp;
        // clang-format off
        a = i * param1[0] - param2[0];
        b = i * param1[1] - param2[1];
        temp = i * param1[0] + param2[0];
        // clang-format on
        if (i % 2 == 0)
            total += 1.0/(temp+b) - 1.0/a;
        else
            total += 1.0/a - 1.0/(b+temp);
        results.push_back(total);
    }
    return total;
}

int main() {
    auto result = calculate<int, int, int>(200_000_000, 4, 1) * 4;
    auto start = std::chrono::high_resolution_clock::now();
    auto end           = std::chrono::high_resolution_clock::now();
    auto duration      = end - start;
    auto seconds        = std::chrono::duration_cast<std::chrono::seconds>(duration);
    auto milliseconds    = std::chrono::duration_cast<std::chrono::microseconds >(duration) / 1.000;
    auto nanoseconds     = std::chrono::duration_cast<std::chrono::nanoseconds  >(duration) / 1.000.000;
    std::cout << "Result: "                 << result                << std::endl;
    std::cout << "Execution Time (s):"      <<(seconds.count()/1000.0) << std::endl;
    std::cout << "Execution Time (ms):"     <<(milliseconds.count()/1000.0) << std::endl;
    std::cout << "Execution Time (ns):"     <<nanoseconds.count()/1000.0 << std::endl;
    return 0;
}
