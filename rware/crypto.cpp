#include <Windows.h>
#include <fstream>
#include <iostream>



int keygen() {


	HCRYPTPROV prov = NULL;
	HCRYPTKEY clé = NULL;
	DWORD bloblen = 0;
	bool ok = 0;

	if (CryptAcquireContextW(&prov, 0, 0, PROV_RSA_AES, CRYPT_VERIFYCONTEXT)) {

		std::cout << "Context acquired" << std::endl;
	}
	else {
		DWORD d = GetLastError();
		std::cout << "Failure to acquire context" << d << std::endl;
		return -1;
	}

	if (CryptGenKey(prov, CALG_AES_192, 0x00C00000 | CRYPT_EXPORTABLE, &clé)) {
		std::cout << "Key Generated : " << clé << std::endl;

	}
	else {
		DWORD d = GetLastError();
		std::cout << "Failure to generate key, error code : " << d << std::endl;
		CryptDestroyKey(clé);
		CryptReleaseContext(prov, 0);
		return -1;

	}

	if (CryptExportKey(clé, 0, PLAINTEXTKEYBLOB, 0, NULL, &bloblen)) {

		std::cout << "Size of the blob determined : " << bloblen << std::endl;
	}
	else {
		DWORD d = GetLastError();
		std::cout << "Error calculating the length, error code : " << d << std::endl;
		return -1;
	}

	BYTE blob[36];
	ok = CryptExportKey(clé, 0, PLAINTEXTKEYBLOB, 0, blob, &bloblen);

	if (ok == FALSE) {

		DWORD d = GetLastError();
		std::cout << "Error exporting key, error code : " << d << std::endl;
		return -1;
	}
	else {
		std::cout << "Content written to the blob" << std::endl;
		std::cout << "Here's the raw blob value :" << blob << std::endl;

		std::ofstream bytefile("byte.txt", std::ios::binary);
		bytefile.write((const char*)blob, sizeof(blob));
		bytefile.close();

	}

	return 0;
}

HCRYPTKEY keyimport() {

	BYTE plaintextkey[] = {
	0x08,0x02,0x00,0x00,0x0f,0x66,0x00,0x00,
	0x18,0x00,0x00,0x00,
	0x3e,0x30,0x24,0x7c,0x48,0xa4,0x0f,0x82, 0xfd,0x7c,0xa5,0x1c,0xf6,0x6c,0x07,0xb7,0x68,0x60,0x47,0x86,0xc7,0xb9,0xba,0xab
	};

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
		return clé;
	}
	else {

		DWORD d = GetLastError();
		std::cout << "Failure to import key, error code: " << d << std::endl;
		return -1;
	}


}