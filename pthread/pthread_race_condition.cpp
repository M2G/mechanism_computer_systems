#include <iostream>
#include <thread>

int sum = 0;

// augmente la valeur de la variable sum
void increase_sum()
{
    for (int i = 0; i < 1000000; i++)
    {
        sum++;
    }
}

int main()
{
    // création des threads
    std::thread t1(increase_sum);
    std::thread t2(increase_sum);

    // attente de la fin des deux threads
    t1.join();
    t2.join();

    // NOTE: affichage de sum après que les deux threads ont terminé
    std::cout << "The total should be 2000000\n";
    std::cout << "The total sum is " << sum << "\n";

    return 0;
}