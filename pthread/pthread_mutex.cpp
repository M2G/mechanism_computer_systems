#include <iostream>
#include <future>

// fonction qui retourne directement une valeur (pas besoin de malloc/pthread_exit)
int return_value()
{
    return 100;
}

int main()
{
    // lance la fonction dans un thread et récupère un "future" sur le résultat
    std::future<int> result = std::async(std::launch::async, return_value);

    // .get() attend la fin du thread (équivalent du join)
    // et récupère la valeur retournée
    int value = result.get();

    std::cout << "Returned Value: " << value << std::endl;

    return 0;
}