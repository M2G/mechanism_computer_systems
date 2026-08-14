#include <iostream>
#include <thread>

void print_message()
{
    std::cout << "Hello from threads\n";
}

int main()
{
    std::thread t1(print_message);
    t1.detach(); // le thread continue en arrière-plan, indépendamment de main

    return 0; // main se termine, le thread peut ne pas avoir fini : rien ne s'affiche parfois
}