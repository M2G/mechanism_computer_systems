#include <iostream>
#include <thread>
#include <vector>

void fn(int nom)
{
    for (int i = 0; i < 50; i++) {
        std::cout << "Thread N" << nom << " " << i << "\n";
    }
}

int main()
{
    std::thread thread1(fn, 1);
    std::thread thread2(fn, 2);

    for (int i = 0; i < 50; i++) {
        std::cout << "Main thread " << i << "\n";
    }

    thread1.join();
    thread2.join();

    return 0;
}