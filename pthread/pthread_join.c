#include <iostream>
#include <thread>

void print_message()
{
    std::cout << "Hello from threads\n";
}

int main()
{
    std::thread t1(print_message);

    t1.join();

    return 0;
}