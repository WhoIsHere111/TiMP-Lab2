#include "modAlphaCipher.h"
#include <cwctype>

// ---------- Валидация ключа ----------
std::wstring modAlphaCipher::getValidKey(const std::wstring& s) {
    if (s.empty())
        throw cipher_error("Empty key");

    for (wchar_t c : s)
        if (!iswdigit(c))
            throw cipher_error("Key must contain only digits");

    int k = std::stoi(s);
    if (k < 2)
        throw cipher_error("Key must be >= 2");
    if (k > 100)
        throw cipher_error("Key too large");

    return s;
}

// ---------- Валидация открытого текста ----------
std::wstring modAlphaCipher::getValidOpenText(const std::wstring& s) {
    std::wstring tmp;
    for (wchar_t c : s)
        if (iswalpha(c))
            tmp.push_back(towupper(c));
    if (tmp.empty())
        throw cipher_error("Empty open text");
    return tmp;
}

// ---------- Валидация шифротекста ----------
std::wstring modAlphaCipher::getValidCipherText(const std::wstring& s) {
    if (s.empty())
        throw cipher_error("Empty cipher text");
    for (wchar_t c : s)
        if (!iswupper(c) && c != L'*')
            throw cipher_error("Cipher text must contain only uppercase letters or *");
    return s;
}

// ---------- Конструктор ----------
modAlphaCipher::modAlphaCipher(const std::wstring& skey) {
    key = std::stoi(getValidKey(skey));
}

// ---------- Зашифрование ----------
std::wstring modAlphaCipher::encrypt(const std::wstring& open_text) {
    std::wstring text = getValidOpenText(open_text);
    int n = key;
    int len = text.length();
    int rows = (len + n - 1) / n;

    while ((int)text.length() < rows * n)
        text.push_back(L'*');

    std::vector<std::vector<wchar_t>> table(rows, std::vector<wchar_t>(n));

    int k = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < n; j++)
            table[i][j] = text[k++];

    std::wstring result;
    for (int j = n - 1; j >= 0; j--)
        for (int i = 0; i < rows; i++)
            result.push_back(table[i][j]);

    return result;
}

// ---------- Расшифрование ----------
std::wstring modAlphaCipher::decrypt(const std::wstring& cipher_text) {
    std::wstring text = getValidCipherText(cipher_text);
    int n = key;
    int len = text.length();
    int rows = (len + n - 1) / n;

    std::vector<std::vector<wchar_t>> table(rows, std::vector<wchar_t>(n));

    int k = 0;
    for (int j = n - 1; j >= 0; j--)
        for (int i = 0; i < rows; i++)
            table[i][j] = text[k++];

    std::wstring result;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < n; j++)
            result.push_back(table[i][j]);

    return result;
}