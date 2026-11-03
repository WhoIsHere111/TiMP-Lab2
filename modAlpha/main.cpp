#include <iostream>
#include <locale>
#include "modAlphaCipher.h"
using namespace std;

int main() {
    if (!setlocale(LC_ALL, "ru_RU.UTF-8"))
        if (!setlocale(LC_ALL, "en_US.UTF-8"))
            if (!setlocale(LC_ALL, "C.UTF-8"))
                setlocale(LC_ALL, "");

    wstring key, text;
    unsigned op;

    wcout << L"=== Шифр Гронсфельда ===\n";
    wcout << L"Введите ключ (слово из русских букв): ";
    wcin >> key;

    try {
        modAlphaCipher cipher(key);
        wcout << L"Ключ установлен.\n";

        do {
            wcout << L"\nОперация (0-выход, 1-зашифровать, 2-расшифровать): ";
            wcin >> op;

            if (op > 2) {
                wcout << L"Неверная операция!\n";
            } else if (op > 0) {
                wcout << L"Введите текст: ";
                wcin >> text;
                try {
                    if (op == 1)
                        wcout << L"Зашифровано:  " << cipher.encrypt(text) << endl;
                    else
                        wcout << L"Расшифровано: " << cipher.decrypt(text) << endl;
                } catch (const cipher_error& e) {
                    cout << "Ошибка: " << e.what() << "\n";
                }
            }
        } while (op != 0);

    } catch (const cipher_error& e) {
        cerr << "Ошибка ключа: " << e.what() << "\n";
        return 1;
    }
    return 0;
}