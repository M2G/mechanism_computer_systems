#include <iostream>
#include <future>

int return_value()
{
    return 100;
}

int main()
{
    std::future<int> result = std::async(std::launch::async, return_value);

    int value = result.get();

    std::cout << "Returned Value: " << value << std::endl;

    return 0;
}