
#ifndef CRYPTO_H
#define CRYPTO_H
const short SIZE = 133;
class Crypto {
private:
	char InputDataBuffer[SIZE];
	char CryptoKey[9];
	char CryptoMatrix[SIZE];
	char ClearMatrix[SIZE];
	short InputDataCount;
	
public:
	// this sets the Input Data buffer with what is entered by the user
	void setInputDataBuffer();
	void setCryptoKey();
	void Encrypt();
	void Decrypt();
	void DisplayCryptoMatrix();
	
};
#endif