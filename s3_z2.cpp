#include <iostream>
#include <thread>
#include <chrono>

int main() {
    int N;

    std::cout << "Enter number of seconds: ";
    std::cin >> N;

    std::cout << "\n Timer started!\n\n";

    // Таймер обратного отсчета
    for (int i = N; i > 0; --i) {
        std::cout << "Seconds left: " << i << " ";



        std::cout << std::endl;

        // Задержка в 1 секунду
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout << "\n Times is up!" << std::endl;

    return 0;
}
