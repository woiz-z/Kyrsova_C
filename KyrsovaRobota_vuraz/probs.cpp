#include <iostream>
#include <chrono>  // Для вимірювання часу
#include "Kyrsova.cpp"

int main() {
    try {
        // Початок вимірювання часу
        auto start = std::chrono::high_resolution_clock::now();

        // Виклик вашого запиту
        auto result = solve_24(1, 6, 6, 6);

        // Кінець вимірювання часу
        auto end = std::chrono::high_resolution_clock::now();

        // Обчислення тривалості
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        // Вивід результату та часу виконання
        std::cout << "Result: " << result << "\n";
        std::cout << "Execution Time: " << duration.count() << " microseconds" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}
