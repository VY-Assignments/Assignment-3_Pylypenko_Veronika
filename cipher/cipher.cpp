#include <string> 
#include <cctype> 
#include <cstring> 
#include "cipher_api.h"

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
c ='A'+(c -'A'+shift %26+ 26)%26;}
else
{
c ='a'+(c-'a'+shift %26 +26)%26;
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
c ='A'+(c -'A'+shift %26+ 26)%26;}
else
{
c ='a'+(c-'a'+shift +26)%26;
		}
ki++;
	}
}
return result;
}
