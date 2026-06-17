#include <string> 
#include <cctype> 
#include <cstring> 

typedef void* cipher_t;
class Cipher {
public:
	virtual std::string encrypt(const std::string& text) = 0;
	virtual std::string decrypt(const std::string& text) = 0;
	virtual ~Cipher() = default;
};
class CaesarCipher : public Cipher {
	int key_;
public:
	CaesarCipher(int key) ;
	std::string encrypt(const std::string& text) override;
	std::string decrypt(const std::string& text) override;
};
class VigenereCipher : public Cipher {
	std::string key_;
public:
	VigenereCipher(const std::string& key);
	std::string encrypt(const std::string& text) override;
	std::string decrypt(const std::string& text) override;
};
 //extra task
class AtbashCipher : public Cipher {
public:
	std::string encrypt(const std::string& text) override;
	std::string decrypt(const std::string& text) override;
};
CaesarCipher::CaesarCipher (int key): key_(key){}
std::string CaesarCipher::encrypt(const std::string& text) {
	std::string result = text;
	for (char& c: result) {
		if (std::isupper(c)) {
c ='A'+(c -'A'+key_ %26+ 26)%26;
}
else if(std::islower(c))
{
c ='a'+(c-'a'+key_ %26 +26)%26;
		}
	}
return result;
}
std::string CaesarCipher::decrypt(const std::string& text) {
CaesarCipher reverse(-key_);
return reverse.encrypt(text);
}
VigenereCipher :: VigenereCipher(const std::string& key){
for (char c: key) {
		key_+=(char)std::toupper(c);	}
}
std::string VigenereCipher::encrypt(const std::string& text) {
	std::string result = text;
int ki=0;
	for (char& c: result) {
		if (std::isalpha(c)) {
int shift=key_[ki%key_.size()] - 'A';
if(std::isupper(c)){
c ='A'+(c -'A'+shift)%26;}
else
{
c ='a'+(c-'a'+shift)%26;
		}
ki++;
	}
}
return result;
}
 std::string VigenereCipher::decrypt(const std::string& text) {
	std::string result = text;
int ki=0;
	for (char& c: result) {
		if (std::isalpha(c)) {
int shift=key_[ki%key_.size()] - 'A';
if(std::isupper(c)){
c ='A'+(c -'A'-shift + 26)%26;}
else
{
c ='a'+(c-'a'-shift +26)%26;
		}
ki++;
	}
}
return result;
}
 std::string AtbashCipher::encrypt(const std::string& text) {
	 std::string result = text;
	 int ki = 0;
	 for (char& c : result) {
		 if (std::isupper(c)) {
			 c = 'Z' - (c - 'A');
		 }
		 else if (std::islower(c)) {
			 c = 'z' - (c - 'a');
		 }
	 }
	 return result;
 }
 std::string AtbashCipher::decrypt(const std::string& text) {
	 return encrypt(text);//since it is symmetric
 }
#ifdef _WIN32
#define EXPORT extern "C" __declspec(dllexport)
#else
#define EXPORT extern "C" __attribute__((visibility("default")))
#endif
	 EXPORT cipher_t* cipher_create_caesar(int key) {
		 return (cipher_t*) new CaesarCipher(key);
	 }
	 EXPORT cipher_t* cipher_create_vigenere(const char* key) {
		 return(cipher_t*) new VigenereCipher(std::string(key));
	 }
	 EXPORT char* cipher_encrypt(cipher_t* cipher, const char* text) {
		 Cipher* c = (Cipher*)cipher;
		 std::string res = c->encrypt(std::string(text));
		 char* out = new char[res.size() + 1];
		 strcpy_s(out, res.size()+1, res.c_str());
		 return out;
	 }
	 EXPORT char* cipher_decrypt(cipher_t* cipher, const char* text) {
		 Cipher* c = (Cipher*)cipher;
		 std::string res = c->decrypt(std::string(text));
		 char* out = new char[res.size() + 1];
		 strcpy_s(out, res.size() + 1, res.c_str());
		 return out;
	 }

	 EXPORT void cipher_destroy(cipher_t* cipher) {
		 delete (Cipher*)cipher;
	 }
	 EXPORT void cipher_free(char* str) {
		 delete[] str;
	 }
	 EXPORT cipher_t* cipher_create_atbash() {
		 return (cipher_t*)new AtbashCipher();
	 }
 
