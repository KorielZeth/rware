#include <Windows.h>
#include <fstream>
#include <iostream>

BYTE plaintextkey[] = {
	0x08,0x02,0x00,0x00,0x0f,0x66,0x00,0x00,
	0x18,0x00,0x00,0x00,
	0x3e,0x30,0x24,0x7c,0x48,0xa4,0x0f,0x82, 0xfd,0x7c,0xa5,0x1c,0xf6,0x6c,0x07,0xb7,0x68,0x60,0x47,0x86,0xc7,0xb9,0xba,0xab
};


int keyimport() {

	HCRYPTPROV prov = NULL;
	HCRYPTKEY clé = NULL;



	if (CryptAcquireContextW(&prov, 0, 0, PROV_RSA_AES, CRYPT_VERIFYCONTEXT)) {

		std::cout << "Context acquired" << std::endl;
	}
	else {
		DWORD d = GetLastError();
		std::cout << "Failure to acquire context, error code: " << d << std::endl;
		return -1;
	}

	if (CryptImportKey(prov, plaintextkey, sizeof(plaintextkey), 0, 0, &clé)) {

		std::cout << "Key succesfully imported" << std::endl;
	}
	else {

		DWORD d = GetLastError();
		std::cout << "Failure to import key, error code: " << d << std::endl;
		return -1;
	}

	return 0;

}