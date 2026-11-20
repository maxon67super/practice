#include <iostream>
#include "Kinematics.h"

int main() {
    setlocale(LC_ALL, "Russian");
    std::cout << "=== Демонстрация структуры Kinematics ===\n\n";

    double v0 = 10.0, a = 2.0, t = 5.0;
    std::cout << "Исходные данные: v0 = " << v0
              << " м/с, a = " << a << " м/с^2, t = " << t << " с\n\n";

    std::cout << "Конечная скорость v = v0 + a*t     = "
              << Kinematics::velocity(v0, a, t) << " м/с\n";
    std::cout << "Пройденный путь   s = v0*t+a*t^2/2 = "
              << Kinematics::distance(v0, a, t) << " м\n";
    std::cout << "Ускорение         a = (v-v0)/t     = "
              << Kinematics::acceleration(20.0, v0, t) << " м/с^2\n";
    std::cout << "Время             t = (v-v0)/a     = "
              << Kinematics::time(20.0, v0, a) << " с\n";

    return 0;
}
