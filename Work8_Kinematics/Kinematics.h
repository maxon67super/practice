#pragma once
#include <stdexcept>
#include <string>

// Структура для кинематических расчётов (вариант 6).
// Используется равноускоренное прямолинейное движение:
//   v = v0 + a * t
//   s = v0 * t + a * t^2 / 2
struct Kinematics {
    // Расчёт конечной скорости: v = v0 + a * t
    static double velocity(double v0, double a, double t) {
        if (t < 0) {
            throw std::invalid_argument(
                "Время не может быть отрицательным");
        }
        return v0 + a * t;
    }

    // Расчёт пройденного расстояния: s = v0 * t + a * t^2 / 2
    static double distance(double v0, double a, double t) {
        if (t < 0) {
            throw std::invalid_argument(
                "Время не может быть отрицательным");
        }
        return v0 * t + a * t * t / 2.0;
    }

    // Расчёт времени достижения скорости: t = (v - v0) / a
    static double time(double v, double v0, double a) {
        if (a == 0) {
            throw std::invalid_argument(
                "Ускорение не может быть равно нулю");
        }
        double t = (v - v0) / a;
        if (t < 0) {
            throw std::invalid_argument(
                "Получено отрицательное время");
        }
        return t;
    }

    // Расчёт ускорения: a = (v - v0) / t
    static double acceleration(double v, double v0, double t) {
        if (t == 0) {
            throw std::invalid_argument(
                "Время не может быть равно нулю");
        }
        return (v - v0) / t;
    }
};
