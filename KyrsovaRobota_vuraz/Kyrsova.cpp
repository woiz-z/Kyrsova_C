#ifndef KyrsovaRobota_vuraz
#define KyrsovaRobota_vuraz

#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

extern "C" {
    const char* solve_24(int a, int b, int c, int d) {
        // Перевірка вхідних даних
        if (a < 1 || a >= 10 || b < 1 || b >= 10 ||
            c < 1 || c >= 10 || d < 1 || d >= 10) {
            return "-1";
        }

        // Всі можливі операції
        const char ops[] = {'+', '-', '*', '/'};

        // Вектор для зберігання чисел
        std::vector<int> nums = {a, b, c, d};

        // Перебираємо всі перестановки чисел
        do {
            // Перебираємо всі комбінації операцій
            for (int op1 = 0; op1 < 4; op1++) {
                for (int op2 = 0; op2 < 4; op2++) {
                    for (int op3 = 0; op3 < 4; op3++) {
                        // Перебираємо різні варіанти дужок

                        // Варіант 1: ((a op1 b) op2 c) op3 d
                        double res1 = 0;
                        if (op1 == 0) res1 = nums[0] + nums[1];
                        else if (op1 == 1) res1 = nums[0] - nums[1];
                        else if (op1 == 2) res1 = nums[0] * nums[1];
                        else if (op1 == 3 && nums[1] != 0) res1 = (double)nums[0] / nums[1];

                        if (op1 == 3 && nums[1] == 0) continue;

                        double res2 = 0;
                        if (op2 == 0) res2 = res1 + nums[2];
                        else if (op2 == 1) res2 = res1 - nums[2];
                        else if (op2 == 2) res2 = res1 * nums[2];
                        else if (op2 == 3 && nums[2] != 0) res2 = res1 / nums[2];

                        if (op2 == 3 && nums[2] == 0) continue;

                        double res3 = 0;
                        if (op3 == 0) res3 = res2 + nums[3];
                        else if (op3 == 1) res3 = res2 - nums[3];
                        else if (op3 == 2) res3 = res2 * nums[3];
                        else if (op3 == 3 && nums[3] != 0) res3 = res2 / nums[3];

                        if (op3 == 3 && nums[3] == 0) continue;

                        if (std::abs(res3 - 24.0) < 1e-9) {
                            std::string* expr = new std::string;
                            *expr = "(((" + std::to_string(nums[0]) + " " + ops[op1] + " " +
                                    std::to_string(nums[1]) + ") " + ops[op2] + " " +
                                    std::to_string(nums[2]) + ") " + ops[op3] + " " +
                                    std::to_string(nums[3]) + ")";
                            return expr->c_str();
                        }

                        // Варіант 2: (a op1 b) op2 (c op3 d)
                        double left = 0, right = 0;
                        if (op1 == 0) left = nums[0] + nums[1];
                        else if (op1 == 1) left = nums[0] - nums[1];
                        else if (op1 == 2) left = nums[0] * nums[1];
                        else if (op1 == 3 && nums[1] != 0) left = (double)nums[0] / nums[1];

                        if (op1 == 3 && nums[1] == 0) continue;

                        if (op3 == 0) right = nums[2] + nums[3];
                        else if (op3 == 1) right = nums[2] - nums[3];
                        else if (op3 == 2) right = nums[2] * nums[3];
                        else if (op3 == 3 && nums[3] != 0) right = (double)nums[2] / nums[3];

                        if (op3 == 3 && nums[3] == 0) continue;

                        double final_res = 0;
                        if (op2 == 0) final_res = left + right;
                        else if (op2 == 1) final_res = left - right;
                        else if (op2 == 2) final_res = left * right;
                        else if (op2 == 3 && right != 0) final_res = left / right;

                        if (op2 == 3 && right == 0) continue;

                        if (std::abs(final_res - 24.0) < 1e-9) {
                            std::string* expr = new std::string;
                            *expr = "((" + std::to_string(nums[0]) + " " + ops[op1] + " " +
                                    std::to_string(nums[1]) + ") " + ops[op2] + " (" +
                                    std::to_string(nums[2]) + " " + ops[op3] + " " +
                                    std::to_string(nums[3]) + "))";
                            return expr->c_str();
                        }
                    }
                }
            }
        } while (std::next_permutation(nums.begin(), nums.end()));

        // Якщо жодного варіанту не знайдено
        return "-1";
    }
}

#endif // KyrsovaRobota_vuraz
