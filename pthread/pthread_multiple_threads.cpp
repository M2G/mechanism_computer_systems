#include <iostream>
#include <thread>
#include <vector>

constexpr int NUM_THREADS = 8;

void print_message()
{
    std::cout << "Hello from threads\n";
}

int main()
{
    std::vector<std::thread> threads;
    threads.reserve(NUM_THREADS);

    for (int i = 0; i < NUM_THREADS; ++i)
    {
        threads.emplace_back(print_message);
    }

    for (int i = 0; i < NUM_THREADS; ++i)
    {
        threads[i].join();
        std::cout << "Thread ID " << i << " has finished\n";
    }

    return 0;
}