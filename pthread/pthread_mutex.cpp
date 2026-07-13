#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

constexpr int ITERATIONS = 1000000;
constexpr int NUM_THREADS = 2;

int sum = 0;
std::mutex mtx;

void increase_sum()
{
    for (int i = 0; i < ITERATIONS; i++)
    {
        std::lock_guard<std::mutex> lock(mtx);
        sum++;
    }
}

int main()
{
    std::vector<std::thread> threads;

    for (int i = 0; i < NUM_THREADS; i++)
    {
        threads.emplace_back(increase_sum);
    }

    for (auto& t : threads)
    {
        t.join();
    }

    std::cout << "Total attendu : " << ITERATIONS * NUM_THREADS << "\n";
    std::cout << "Total obtenu  : " << sum << "\n";

    return EXIT_SUCCESS;
}