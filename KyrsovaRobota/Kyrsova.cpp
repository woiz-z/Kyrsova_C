#ifndef KyrsovaRobota
#define KyrsovaRobota

#include <string>
#include <stack>
#include <stdexcept>
#include <cstdlib>
#include <cstring>
#include <cmath>

extern "C" {
    double evaluate_expression(const char* expression);
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

double apply_operation(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            // Якщо відбувається ділення на нуль, повернути 0
            if (b == 0) return 0;
            return a / b;
        default: throw std::runtime_error("Невірний оператор");
    }
}

double evaluate_expression(const char* expression) {
    std::stack<double> values;
    std::stack<char> operators;
    size_t i = 0;

    while (i < std::strlen(expression)) {
        // Пропустити пробіли
        if (expression[i] == ' ') {
            i++;
            continue;
        }

        // Якщо поточний символ є числом
        if (std::isdigit(expression[i])) {
            double value = 0;
            while (i < std::strlen(expression) && (std::isdigit(expression[i]) || expression[i] == '.')) {
                if (expression[i] == '.') {
                    double fraction = 0;
                    int divisor = 10;
                    i++;
                    while (i < std::strlen(expression) && std::isdigit(expression[i])) {
                        fraction += (expression[i] - '0') / divisor;
                        divisor *= 10;
                        i++;
                    }
                    value += fraction;
                    break;
                }
                value = (value * 10) + (expression[i] - '0');
                i++;
            }
            values.push(value);
        }
        // Якщо поточний символ є відкриваючою дужкою
        else if (expression[i] == '(') {
            operators.push(expression[i]);
            i++;
        }
        // Якщо поточний символ є закриваючою дужкою
        else if (expression[i] == ')') {
            while (!operators.empty() && operators.top() != '(') {
                double b = values.top(); values.pop();
                double a = values.top(); values.pop();
                char op = operators.top(); operators.pop();
                values.push(apply_operation(a, b, op));
            }
            if (!operators.empty() && operators.top() == '(') {
                operators.pop();
            }
            i++;
        }
        // Якщо поточний символ є оператором
        else {
            while (!operators.empty() && precedence(operators.top()) >= precedence(expression[i])) {
                double b = values.top(); values.pop();
                double a = values.top(); values.pop();
                char op = operators.top(); operators.pop();
                values.push(apply_operation(a, b, op));
            }
            operators.push(expression[i]);
            i++;
        }
    }

    // Застосування залишкових операцій
    while (!operators.empty()) {
        double b = values.top(); values.pop();
        double a = values.top(); values.pop();
        char op = operators.top(); operators.pop();
        values.push(apply_operation(a, b, op));
    }

    return values.top();
}

#endif // KyrsovaRobota