#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

#define NUM_THREADS 10

std::mutex mtx; // remplace pthread_mutex_t

void try_lock(int threadID)
{
    // le thread dort un temps aléatoire entre 0 et 2 secondes
    int sleeptime = rand() % 3;
    std::this_thread::sleep_for(std::chrono::seconds(sleeptime));

    // si le thread obtient le verrou
    if (mtx.try_lock())
    {
        std::cout << "Thread " << threadID << " got the lock!\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        mtx.unlock();
    }
    // si le thread n'obtient pas le verrou
    else
    {
        std::cout << "Thread " << threadID << " did not get the lock!\n";
    }
}

int main()
{
    // std::thread(try_lock, i);

    return 0;
}