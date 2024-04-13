#include <iostream>
#include <vector>
#include <cstdint>
#include <random>
#include <bitset>
#include <thread>
#include <algorithm>


constexpr uint64_t n = 10000;
uint64_t array[n];

void Generate()
{
	std::mt19937_64 gen(1);
	std::uniform_int_distribution<uint64_t> distr(0u, std::numeric_limits<uint64_t>::max());
	for (size_t i = 0; i < n; ++i)
	{
		array[i] = distr(gen);
	}
}

/*void InvertOneBit(uint64_t* number, uint64_t position)
{
	uint64_t mask = (1 << position);
	*number ^= mask;
}

void InvertRangeOfBits(uint64_t* number, uint64_t range)
{
	uint64_t mask = ((1 << range) - 1);
	*number ^= mask;
}*/

void InvertRangeOfBitsInPosition(uint64_t* number, const uint64_t position, const uint64_t range)
{
	const uint64_t mask = (((1 << range) - 1) << position);
	*number ^= mask;
}

void InvertBits(uint64_t* begin, uint64_t* end, const uint64_t position, const uint64_t range)
{
	for (; begin != end; ++begin)
	{
		InvertRangeOfBitsInPosition(begin, position, range);
	}
}

void ParallelInvertBits(uint64_t* begin, const uint64_t length, const uint64_t position, const uint64_t range)
{
	if (length <= 0)
	{
		return;
	}

	const size_t min_job_size = 1000;
	const size_t hardware_threads = std::thread::hardware_concurrency();
	const size_t max_threads = (hardware_threads == 0 ? 2 : hardware_threads);
	const size_t num_threads = std::min(max_threads, (length + min_job_size - 1) / min_job_size);

	std::vector<std::thread> threads;
	threads.reserve(num_threads - 1);

	auto first = begin;
	const auto block_size = length / num_threads;
	for (size_t i = 0; i < num_threads - 1; ++i)
	{
		const auto last = first + block_size;
		threads.emplace_back(InvertBits, first, last, position, range);
		first = last;
	}
	InvertBits(first, (begin + length), position, range);
	for (auto& t : threads)
	{
		t.join();
	}
}

int main()
{
	Generate();
	uint64_t array_before[n];
	std::copy(array, array + n, array_before);

	auto start = std::chrono::high_resolution_clock::now();
	ParallelInvertBits(array, n, 0, 4);
	auto end = std::chrono::high_resolution_clock::now();
	std::cout << "ParallelInvertBits: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
		<< "ms \n";

	/*std::cout << "Before\t\t\tAfter\n\n";
	for (size_t i = 0; i < n; ++i)
	{
		std::cout << std::bitset<8>(array_before[i]) << "\t->\t" << std::bitset<8>(array[i]) << '\n';
	}*/
}