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