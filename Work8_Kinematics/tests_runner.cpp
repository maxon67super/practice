// Переносимый запуск тех же тестов (AAA), что и в проекте модульного
// тестирования Visual Studio. Выводит результат по каждому тесту.
#include <iostream>
#include <cmath>
#include <functional>
#include <stdexcept>
#include "Kinematics.h"

static int passed = 0, failed = 0;

void check(const std::string& name, bool ok) {
    std::cout << (ok ? "[  PASSED  ] " : "[  FAILED  ] ") << name << "\n";
    ok ? ++passed : ++failed;
}

bool areEqual(double expected, double actual, double tol = 0.0001) {
    return std::fabs(expected - actual) < tol;
}

bool throwsInvalidArgument(std::function<void()> fn) {
    try { fn(); } catch (const std::invalid_argument&) { return true; }
    catch (...) { return false; }
    return false;
}

int main() {
    setlocale(LC_ALL, "Russian");
    std::cout << "=== Запуск модульных тестов структуры Kinematics ===\n\n";

    // --- Позитивный тест 1: корректный расчёт скорости ---
    {
        double v = Kinematics::velocity(10.0, 2.0, 5.0); // Act
        check("TestVelocity_ValidData_ReturnsCorrect (ожид. 20)", areEqual(20.0, v));
    }

    // --- Позитивный тест 2: корректный расчёт расстояния ---
    {
        double s = Kinematics::distance(10.0, 2.0, 5.0); // s = 50 + 25 = 75
        check("TestDistance_ValidData_ReturnsCorrect (ожид. 75)", areEqual(75.0, s));
    }

    // --- Негативный тест 1: нулевое ускорение в time() -> исключение ---
    {
        bool ok = throwsInvalidArgument([] { Kinematics::time(20.0, 10.0, 0.0); });
        check("TestTime_ZeroAcceleration_ThrowsException", ok);
    }

    // --- Негативный тест 2: нулевое время в acceleration() -> исключение ---
    {
        bool ok = throwsInvalidArgument([] { Kinematics::acceleration(20.0, 10.0, 0.0); });
        check("TestAcceleration_ZeroTime_ThrowsException", ok);
    }

    // --- Тест для функции напарника (distance с отрицательным временем) ---
    {
        bool ok = throwsInvalidArgument([] { Kinematics::distance(10.0, 2.0, -3.0); });
        check("TestPartner_Distance_NegativeTime_ThrowsException", ok);
    }

    std::cout << "\nИтого: пройдено " << passed << ", провалено " << failed << "\n";
    return failed == 0 ? 0 : 1;
}
