#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

// Вариант 6:
// 1) Сохранить и вывести любимое слово.
// 2) Сохранить цвет консоли по выбору пользователя (red, blue, green)
//    и восстанавливать его при запуске.
// Для каждого пункта варианта написана отдельная функция,
// все проверки ввода выполняются внутри функций.

const string FILE_NAME = "settings.txt";

// Применение цвета консоли. В Windows используется system("color XY"),
// где X - цвет фона, Y - цвет текста. На других ОС используется ANSI.
void applyConsoleColor(const string& color) {
#ifdef _WIN32
    if (color == "red")        system("color 0C"); // красный текст
    else if (color == "blue")  system("color 09"); // синий текст
    else if (color == "green") system("color 0A"); // зелёный текст
    else                       system("color 07"); // по умолчанию
#else
    if (color == "red")        cout << "\033[31m";
    else if (color == "blue")  cout << "\033[34m";
    else if (color == "green") cout << "\033[32m";
    else                       cout << "\033[0m";
#endif
}

// Функция 1: ввод и проверка любимого слова (не должно быть пустым).
string inputFavoriteWord() {
    string word;
    while (true) {
        cout << "Введите любимое слово: ";
        cin >> word;
        if (!word.empty()) return word;
        cout << "Ошибка: слово не может быть пустым!\n";
    }
}

// Функция 2: ввод и проверка цвета консоли (только red, blue, green).
string inputConsoleColor() {
    string color;
    while (true) {
        cout << "Введите цвет консоли (red, blue, green): ";
        cin >> color;
        if (color == "red" || color == "blue" || color == "green")
            return color;
        cout << "Ошибка: допустимы только red, blue или green!\n";
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    string word, color;
    ifstream fin(FILE_NAME);

    if (fin.is_open()) {
        // Файл есть — читаем и восстанавливаем настройки
        fin >> word >> color;
        fin.close();
        applyConsoleColor(color);
        cout << "Загружены сохранённые настройки:\n";
        cout << "Любимое слово: " << word << "\n";
        cout << "Цвет консоли:  " << color << "\n";

        char choice;
        cout << "\nИзменить настройки? (y/n): ";
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            word = inputFavoriteWord();
            color = inputConsoleColor();
            applyConsoleColor(color);
            ofstream fout(FILE_NAME);
            fout << word << " " << color;
            fout.close();
            cout << "Настройки обновлены!\n";
            cout << "Любимое слово: " << word << "\n";
        }
    } else {
        // Файла нет — первый запуск, вводим настройки
        cout << "Файл настроек не найден. Первый запуск.\n";
        word = inputFavoriteWord();
        color = inputConsoleColor();
        applyConsoleColor(color);
        ofstream fout(FILE_NAME);
        fout << word << " " << color;
        fout.close();
        cout << "Настройки сохранены!\n";
        cout << "Любимое слово: " << word << "\n";
    }

#ifndef _WIN32
    cout << "\033[0m"; // сброс цвета (ANSI)
#endif
    return 0;
}
