#include "modAlphaCipher.h"
#include <cwctype>

// ---------- Валидация ключа ----------
std::wstring modAlphaCipher::getValidKey(const std::wstring& s) {
    if (s.empty())
        throw cipher_error("Empty key");

    std::wstring tmp;
    for (wchar_t c : s) {
        if (!iswalpha(c))
            throw cipher_error("Invalid key: only letters allowed");
        tmp.push_back(towupper(c));
    }

    // Проверка на вырожденный ключ
    bool allSame = true;
    for (size_t i = 1; i < tmp.size(); i++)
        if (tmp[i] != tmp[0]) {
            allSame = false;
            break;
        }
    if (allSame)
        throw cipher_error("Weak key: all letters are same");

    return tmp;
}

// ---------- Валидация открытого текста ----------
std::wstring modAlphaCipher::getValidOpenText(const std::wstring& s) {
    std::wstring tmp;
    for (wchar_t c : s) {
        if (iswalpha(c))
            tmp.push_back(towupper(c));
    }
    if (tmp.empty())
        throw cipher_error("Empty open text");
    return tmp;
}

// ---------- Валидация шифротекста ----------
std::wstring modAlphaCipher::getValidCipherText(const std::wstring& s) {
    if (s.empty())
        throw cipher_error("Empty cipher text");
    for (wchar_t c : s) {
        if (!iswalpha(c))
            throw cipher_error("Invalid cipher text: only letters allowed");
        if (!iswupper(c))
            throw cipher_error("Invalid cipher text: only uppercase letters");
    }
    return s;
}

// ---------- Конструктор ----------
modAlphaCipher::modAlphaCipher(const std::wstring& skey) {
    numAlpha = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
    for (unsigned i = 0; i < numAlpha.size(); i++)
        alphaNum[numAlpha[i]] = i;

    key = convert(getValidKey(skey));
}

// ---------- Зашифрование ----------
std::wstring modAlphaCipher::encrypt(const std::wstring& open_text) {
    std::vector<int> work = convert(getValidOpenText(open_text));
    for (unsigned i = 0; i < work.size(); i++)
        work[i] = (work[i] + key[i % key.size()]) % alphaNum.size();
    return convert(work);
}

// ---------- Расшифрование ----------
std::wstring modAlphaCipher::decrypt(const std::wstring& cipher_text) {
    std::vector<int> work = convert(getValidCipherText(cipher_text));
    for (unsigned i = 0; i < work.size(); i++)
        work[i] = (work[i] + alphaNum.size() - key[i % key.size()]) % alphaNum.size();
    return convert(work);
}

// ---------- Строка → вектор ----------
inline std::vector<int> modAlphaCipher::convert(const std::wstring& s) {
    std::vector<int> result;
    for (wchar_t c : s) {
        auto it = alphaNum.find(c);
        if (it == alphaNum.end())
            throw cipher_error("Invalid character");
        result.push_back(it->second);
    }
    return result;
}

// ---------- Вектор → строка ----------
inline std::wstring modAlphaCipher::convert(const std::vector<int>& v) {
    std::wstring result;
    for (int i : v)
        result.push_back(numAlpha[i]);
    return result;
}