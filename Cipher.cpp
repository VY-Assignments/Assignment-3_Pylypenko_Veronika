#include "Cipher.h"
#include <stdexcept>

Cipher::Cipher(CipherType type, const std::string& key) {
    loadLibraryAndSymbols();
    createCipherInstance(type, key);
}

Cipher::~Cipher() {
    unload();
}

void Cipher::loadLibraryAndSymbols() {
    lib_ = LoadLibraryA("cipher.dll");
    if (!lib_) {
        throw std::runtime_error("Cannot load cipher.dll. Make sure it is next to the .exe");
    }

    createCaesar_ = (fn_create_caesar)GetProcAddress(lib_, "cipher_create_caesar");
    createVigenere_ = (fn_create_vigenere)GetProcAddress(lib_, "cipher_create_vigenere");
    createAtbash_ = (fn_create_atbash)GetProcAddress(lib_, "cipher_create_atbash");
    encryptFn_ = (fn_encrypt)GetProcAddress(lib_, "cipher_encrypt");
    decryptFn_ = (fn_decrypt)GetProcAddress(lib_, "cipher_decrypt");
    destroyFn_ = (fn_destroy)GetProcAddress(lib_, "cipher_destroy");
    freeFn_ = (fn_free)GetProcAddress(lib_, "cipher_free");

    if (!createCaesar_ || !createVigenere_ || !createAtbash_ ||
        !encryptFn_ || !decryptFn_ || !destroyFn_ || !freeFn_) {
        FreeLibrary(lib_);
        lib_ = nullptr;
        throw std::runtime_error("cipher.dll is missing one or more expected exported functions!!!");
    }
}

void Cipher::createCipherInstance(CipherType type, const std::string& key) {
    switch (type) {
    case CipherType::Caesar: {
        int shift = 0;
        try {
            shift = std::stoi(key);
        }
        catch (...) {
            throw std::invalid_argument("Caesar cipher key must be an integer");
        }
        handle_ = createCaesar_(shift);
        break;
    }
    case CipherType::Vigenere:
        if (key.empty()) {
            throw std::invalid_argument("Vigenere cipher key must not be empty");
        }
        handle_ = createVigenere_(key.c_str());
        break;
    case CipherType::Atbash:
        handle_ = createAtbash_();
        break;
    }

    if (!handle_) {
        throw std::runtime_error("Failed to create cipher instance inside cipher.dll");
    }
}
std::string Cipher::encrypt(const std::string& text) const {
    char* raw = encryptFn_(handle_, text.c_str());
    std::string result(raw);
    freeFn_(raw);
    return result;
}

std::string Cipher::decrypt(const std::string& text) const {
    char* raw = decryptFn_(handle_, text.c_str());
    std::string result(raw);
    freeFn_(raw);
    return result;
}

void Cipher::unload() {
    if (handle_ && destroyFn_) {
        destroyFn_(handle_);
        handle_ = nullptr;
    }
    if (lib_)
    {
        FreeLibrary(lib_);
        lib_ = nullptr;
    }
}
