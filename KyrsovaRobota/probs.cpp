#include <iostream>
#include <chrono>  // Для вимірювання часу
#include "Kyrsova.cpp"

int main() {
    const char* test_expression = "5+3+2-6";
    try {
        // Початок вимірювання часу
        auto start = std::chrono::high_resolution_clock::now();

        // Виклик функції evaluate_expression
        double result = evaluate_expression(test_expression);

        // Кінець вимірювання часу
        auto end = std::chrono::high_resolution_clock::now();

        // Обчислення тривалості
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        // Виведення результату та часу виконання
        std::cout << "Expression: " << test_expression << "\n";
        std::cout << "Result: " << result << "\n";
        std::cout << "Execution Time: " << duration.count() << " microseconds\n";

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}
