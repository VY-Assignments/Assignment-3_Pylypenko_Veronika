#include <iostream>
#include <string>
#include <windows.h>
typedef void* cipher_t;
typedef cipher_t*(*fn_create_caesar)(int);
typedef cipher_t* (*fn_create_vigenere)(const char*);
typedef char* (*fn_encrypt)(cipher_t*, const char*);
typedef char* (*fn_decrypt)(cipher_t*, const char*);
typedef void (*fn_destroy)(cipher_t*);
typedef void (*fn_free)(char*);
typedef cipher_t* (*fn_create_atbash)();

int main()
{
    HMODULE lib = LoadLibraryA("cipher.dll");
    if (!lib) {
        std::cerr << "Error! cipher.dll cannot be load!\n";
        return 1;
    }
    auto create_caesar = (fn_create_caesar)GetProcAddress(lib, "cipher_create_caesar");
    auto create_vigenere = (fn_create_vigenere)GetProcAddress(lib, "cipher_create_vigenere");
    auto enc = (fn_decrypt)GetProcAddress(lib, "cipher_encrypt");
    auto decrypt = (fn_encrypt)GetProcAddress(lib, "cipher_decrypt");
    auto destroy = (fn_destroy)GetProcAddress(lib, "cipher_destroy");
    auto cfree = (fn_free)GetProcAddress(lib, "cipher_free");
    auto create_atbash = (fn_create_atbash)GetProcAddress(lib, "cipher_create_atbash");



    while (true) {
        std::cout << "1.Caesar cipher\n";
        std::cout << "2.Vigenere cipher\n";
        std::cout << "3.Atbash cipher\n";
        std::cout << "0.Exit\n";
        std::cout << "Choose: \n";
        int choice;
        std::cin >> choice;
        if (choice == 0)break;
        cipher_t* cipher = nullptr;
        if (choice == 1) {
            int key;
            std::cout << "Enter Caesar key:";
            std::cin >> key;
            cipher = create_caesar(key);
        }
        else if (choice == 3) {
            cipher = create_atbash();
        }
        else {
            std::string key;
            std::cout << "Enter Vigenere key:";
            std::cin >> key;
            cipher = create_vigenere(key.c_str());
        }
        std::cout << "1. Encrypt; 2.Decrypt\n Choose: ";
        int op;
        std::cin >> op;
        std::cin.ignore();
        std::string text;
        std::cout << "Enter text:";
        std::getline(std::cin, text);
        char* result = nullptr;
        if (op == 1) result = enc(cipher, text.c_str());
        else 
        { result = decrypt(cipher, text.c_str()); }
        std::cout << "Result: " << result << "\n";
        cfree(result);
        destroy(cipher);
    }
    FreeLibrary(lib);
   
    return 0;

}

