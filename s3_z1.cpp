#include <iostream>
#include <chrono>

// Функция для вычисления суммы чисел от 1 до N
long long calculateSum(int N) {//для очень больших чисел
    long long sum = 0;
    for (int i = 1; i <= N; ++i) {
        sum += i;
    }
    return sum;
}
//мета не нужно так как цель посчитаь время выполнения
int main() {
    int N;
    std::cout << "Enter N: ";
    std::cin >> N;

    // Засекаем время перед выполнением функции
    auto start = std::chrono::high_resolution_clock::now();

    // Выполняем вычисление
    long long result = calculateSum(N);

    // Засекаем время после выполнения
    auto end = std::chrono::high_resolution_clock::now();

    // Вычисляем разницу и конвертируем в миллисекунды
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // Выводим результаты
    std::cout << "Sum from 1 to " << N << " = " << result << std::endl;
    std::cout << "Duration: " << duration.count() << " миллисекунд" << std::endl;

    return 0;
}
