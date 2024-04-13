#include <iostream>
#include <chrono>
#include <random>
#include <bit>
#include <thread>

// Дан массив чисел. Необходимо посчитать количество выставленных бит/флагов в этом массиве

uint64_t array[1000000];

void Generate() {
    std::mt19937_64 generator(11);
    std::uniform_int_distribution<uint64_t> distr(0u, std::numeric_limits<uint64_t>::max());
    for (int i = 0; i < 1000000; ++i) {
        array[i] = distr(generator);
    }
}

void CountBits(uint64_t* begin, uint64_t* end, uint64_t(*func)(uint64_t), uint64_t& result) {
    for (; begin != end; ++begin) {
        result += func(*begin);
    }
}

uint64_t CountBitsSlow(uint64_t x) {  // O(n)
    uint64_t count = 0;
    while (x) {
        count += x & 1u;
        x >>= 1;
    }
    return count;
}

uint64_t CountBitsFast(uint64_t x) {  // O(n_1)
    uint64_t count = 0;
    while (x) {
        ++count;
        x &= (x - 1);
    }
    return count;
}

uint64_t CountBitsFaster(uint64_t x) {
    x = (x & 0x5555555555555555) + ((x >> 1) & 0x5555555555555555);
    x = (x & 0x3333333333333333) + ((x >> 2) & 0x3333333333333333);
    x = (x & 0x0f0f0f0f0f0f0f0f) + ((x >> 4) & 0x0f0f0f0f0f0f0f0f);
    x = (x & 0x00ff00ff00ff00ff) + ((x >> 8) & 0x00ff00ff00ff00ff);
    x = (x & 0x0000ffff0000ffff) + ((x >> 16) & 0x0000ffff0000ffff);
    x = (x & 0x00000000ffffffff) + ((x >> 32) & 0x00000000ffffffff);
    return x;
}

// (x + y - 1) / y  // деление с округлением вверх (x / y)

template <class Function>
uint64_t ParallelCountBits(uint64_t* begin, uint64_t* end, Function func) {
    if (begin == end) {
        return 0;
    }
    const size_t size = end - begin;
    const size_t min_job_size = 1000;
    const size_t hardware_threads = std::thread::hardware_concurrency();
    const size_t max_threads = 2;//(hardware_threads == 0 ? 2 : hardware_threads);
    const size_t num_threads = std::min(max_threads, (size + min_job_size - 1) / min_job_size);

    std::vector<uint64_t> results(num_threads, 0u);
    std::vector<std::thread> threads;
    threads.reserve(num_threads - 1);
    auto first = begin;
    const auto block_size = size / num_threads;
    for (size_t i = 0; i < num_threads - 1; ++i) {
        const auto last = first + block_size;
        threads.emplace_back(CountBits, first, last, func, std::ref(results[i]));
        first = last;
    }
    CountBits(first, end, func, results.back());
    for (auto& t : threads) {
        t.join();
    }
    return std::accumulate(results.begin(), results.end(), uint64_t{ 0 });
}


int main() {
    Generate();
    uint64_t result = 0;
    std::cout << std::thread::hardware_concurrency() << '\n';
    auto start = std::chrono::high_resolution_clock::now();
    CountBits(array, array + 1000000, CountBitsSlow, result);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << result << '\n';
    std::cout << "CountBitsSlow: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
        << "ms \n";

    result = 0;
    start = std::chrono::high_resolution_clock::now();
    CountBits(array, array + 1000000, CountBitsFaster, result);
    end = std::chrono::high_resolution_clock::now();
    std::cout << result << '\n';
    std::cout << "CountBitsFaster: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
        << "mcs \n";

    start = std::chrono::high_resolution_clock::now();
    result = ParallelCountBits(array, array + 1000000, CountBitsSlow);
    end = std::chrono::high_resolution_clock::now();
    std::cout << result << '\n';
    std::cout << "ParallelSlow: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
        << "mcs \n";

    start = std::chrono::high_resolution_clock::now();
    result = ParallelCountBits(array, array + 1000000, CountBitsFaster);
    end = std::chrono::high_resolution_clock::now();
    std::cout << result << '\n';
    std::cout << "ParallelFaster: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
        << "mcs \n";
}