#include <iostream>
#include <string>
using namespace std;
#include "Crypto.h"

int main() {
	Crypto object;
	object.setInputDataBuffer();
	object.setCryptoKey();
	object.Encrypt();
	object.DisplayCryptoMatrix();
	object.Decrypt();
	
	return 0;
}
// Encrypting
void Crypto::Encrypt() {
	char LocalInputDataBuffer[SIZE];
	short LocalInputDataCount;
	char LocalCryptoKey[9];
	char LocalCryptoMatrix[SIZE];

	for (int x = 0; x < 8; x++) {
		LocalCryptoKey[x] = CryptoKey[x];
	}
	// Need to create a local copy of InputDataBuffer
	for (int x = 0; x <= InputDataCount; x++) 
		LocalInputDataBuffer[x] = InputDataBuffer[x];
	LocalInputDataCount = InputDataCount;
	
	cout << "After Encryption: " << endl;
	LocalCryptoKey[8] = '\0';
	
	_asm {
		mov cx, LocalInputDataCount
		mov eax, 0
		mov esi, 0
		mov edi, 0
	L1:
		cmp edi, 8 // Equals 8 reset
		je L2
		mov al, LocalInputDataBuffer[esi]
		xor al, LocalCryptoKey[edi]
		mov	LocalCryptoMatrix[esi], al
		inc esi
		inc edi
		
		Loop L1
	L2 :
		mov edi, 0 
		jz L1
	}

	// After encrypting data copy all local data to the ones in the class
	// use another for loop
	for (int x = 0; x <= InputDataCount; x++) 
		CryptoMatrix[x] = LocalCryptoMatrix[x];
}
void Crypto::Decrypt() {
	char LocalInputDataBuffer[SIZE];
	short LocalInputDataCount;
	char LocalCryptoKey[9];
	char LocalCryptoMatrix[SIZE];


	// Need to create a local copy of InputDataBuffer
	cout << endl << "After Decryption: " << endl;

	LocalInputDataCount = InputDataCount;

	for (int x = 0; x < 9; x++)
		LocalCryptoKey[x] = CryptoKey[x];

	for (int x = 0; x < InputDataCount; x++)
		LocalCryptoMatrix[x] = CryptoMatrix[x];

	// After encrypting data copy all local data to the ones in the class
	

	__asm {
		mov eax, 0
		mov esi, 0
		mov edi, 0
		mov cx, LocalInputDataCount

		L1 :
		cmp edi, 8
			je  L2
			mov al, LocalCryptoMatrix[esi]
			xor al, LocalCryptoKey[edi]
			mov LocalCryptoMatrix[esi], al
			inc esi
			inc edi
			loop L1

			L2 :
	   mov edi, 0
			jz L1
	}

	for (int i = 0; i < LocalInputDataCount; i++) {
		CryptoMatrix[i] = LocalCryptoMatrix[i];
		cout << CryptoMatrix[i] << " ";
	}
		cout << endl;
		cout << "Here is the matrix after clearing" << endl;

	for (int i = 0; i < InputDataCount; i++) {
		ClearMatrix[i] = NULL;
		cout << ClearMatrix[i] << endl;
	}
	
}
void Crypto::setInputDataBuffer() {
	string LocalInputDataBuffer = "";  
	cout << "Enter a string to be encrypted" << endl;// I got InputDataBuffer Corruption Error
	getline (cin ,LocalInputDataBuffer); 
	InputDataCount = LocalInputDataBuffer.size();
	for (int i = 0; i < SIZE; i++) {
		InputDataBuffer[i] = ' ';
	}
	for (int i = 0; i < InputDataCount; i++)
		InputDataBuffer[i] = LocalInputDataBuffer[i];

}
void Crypto::setCryptoKey() {
	string localCryptoKey = "";  //Initializing as a char gives errors 
	cout << "Please enter encrypt key:" << endl;// works as a local string 
	getline(cin, localCryptoKey);
	for (int i = 0; i < 8; i++) {
		CryptoKey[i] = ' ';
	}
	for (int i = 0; i < localCryptoKey.size(); i++) {
		CryptoKey[i] = localCryptoKey[i];
	}
}
void Crypto::DisplayCryptoMatrix() {
	for(int x = 0; x < InputDataCount; x++)
	cout << CryptoMatrix[x] << " ";
	cout << endl;
}