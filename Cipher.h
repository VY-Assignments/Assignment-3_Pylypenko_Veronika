#pragma once
#include <string>
#include <windows.h>
#include "cipher_api.h"

enum class CipherType {
	Caesar, 
	Vigenere,
	Atbash 
};
class Cipher {
public:
	Cipher(CipherType type, const std::string& key);
	~Cipher();
	Cipher(const Cipher&) = delete;
	Cipher& operator=(const Cipher&) = delete;
	std::string encrypt(const std::string& text) const;
	std::string decrypt(const std::string& text) const;


private:
	typedef cipher_t* (*fn_create_caesar)(int);
	typedef cipher_t* (*fn_create_vigenere)(const char*);
	typedef cipher_t* (*fn_create_atbash)();
	typedef char* (*fn_encrypt)(cipher_t*, const char*);
	typedef char* (*fn_decrypt)(cipher_t*, const char*);
	typedef void (*fn_destroy)(cipher_t*);
	typedef void (*fn_free)(char*);

	HMODULE lib_ = nullptr;
	cipher_t* handle_ = nullptr;
	fn_create_caesar createCaesar_ = nullptr;
	fn_create_vigenere createVigenere_ = nullptr;
	fn_create_atbash createAtbash_ = nullptr;
	fn_encrypt encryptFn_ = nullptr;
	fn_decrypt decryptFn_ = nullptr;
	fn_destroy destroyFn_ = nullptr;
	fn_free freeFn_ = nullptr;
	void loadLibraryAndSymbols();
	void createCipherInstance(CipherType type, const std::string& key);
	void unload();
};
