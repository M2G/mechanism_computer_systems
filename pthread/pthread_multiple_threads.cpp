#include <iostream>
#include <thread>
#include <vector>

#define NUM_THREADS 8

void print_message()
{
    std::cout << "Hello from threads\n";
}

int main()
{
    std::vector<std::thread> threads;

    // création des threads
    for (int i = 0; i < NUM_THREADS; i++)
    {
        threads.push_back(std::thread(print_message));
    }

    // attente (join) des threads
    for (int i = 0; i < NUM_THREADS; i++)
    {
        threads[i].join();
        std::cout << "Thread ID " << i << " has finished\n";
    }

    return 0;
}