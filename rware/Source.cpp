#include <iostream>
#include <fstream>
#include <ostream>
#include <windows.h>




int wmain() {


	HCRYPTPROV prov = NULL;
	HCRYPTKEY clé = NULL;
	//DWORD bloblen = 0;
	//bool ok = 0;

	BYTE plaintextkey[] = {
	0x08,0x02,0x00,0x00,0x0f,0x66,0x00,0x00,
	0x18,0x00,0x00,0x00,
	0x3e,0x30,0x24,0x7c,0x48,0xa4,0x0f,0x82, 0xfd,0x7c,0xa5,0x1c,0xf6,0x6c,0x07,0xb7,0x68,0x60,0x47,0x86,0xc7,0xb9,0xba,0xab
	};

	/*if (CryptAcquireContextW(&prov, 0, 0, PROV_RSA_AES, CRYPT_VERIFYCONTEXT)) {

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

		std::ofstream bytefile("byte.txt",std::ios::binary);
		bytefile.write((const char*)blob,sizeof(blob));
		bytefile.close();

	}*/

	// import key

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

	//File handling 

	LPCWSTR pzSourceFile = L"C:\\Users\\Nono\\source\\repos\\rware\\x64\\Debug\\testfile.txt";
	LPCWSTR pzDestFile = L"C:\\Users\\Nono\\source\\repos\\rware\\x64\\Debug\\testfile2";

	HANDLE hSourceFile = INVALID_HANDLE_VALUE;
	HANDLE hDestFile = INVALID_HANDLE_VALUE;


	DWORD eof = 0;
	PBYTE pbBuffer[960];
	DWORD dwBlockLen = 960;
	DWORD dwBufferLen = 960;
	DWORD dwCount = 0;


	hSourceFile = CreateFileW(pzSourceFile, FILE_READ_DATA, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hSourceFile != INVALID_HANDLE_VALUE) {

		std::cout << "The sourcefile is open" << std::endl;
	}
	else {
		DWORD d = GetLastError();
		std::cout << "Error opening handle to the sourcefile, error code: " << d << std::endl;
		return -1;

	}

	hDestFile = CreateFileW(pzDestFile, FILE_WRITE_DATA | DELETE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE != hDestFile) {

		std::cout << "The destfile is open" << std::endl;
	}
	else {
		DWORD d = GetLastError();
		std::cout << "Error opening handle to the destfile, error code 0x8" << d << std::endl;
		return -1;

	}

	while (eof == 0) {

		if (ReadFile(hSourceFile, pbBuffer, dwBlockLen, &dwCount, NULL) == 0) {

			DWORD d = GetLastError();
			std::cout << "Error reading from the sourcefile, error code 0x8:" << d << std::endl;
			break;

		}

		std::cout << dwCount << std::endl;

		if (CryptEncrypt(clé, 0, eof, 0, (BYTE*)pbBuffer, &dwCount, dwBufferLen) == 0) {

			DWORD d = GetLastError();
			std::cout << "Error encrypting the buffer, error code 0x8" << d << std::endl;
			break;

		}

		if (WriteFile(hDestFile, pbBuffer, dwCount, &dwCount, NULL) == 0) {

			DWORD d = GetLastError();
			std::cout << "Error writing to the destfile, error code 0x8:" << d << std::endl;
			break;


		}

	}


	return 0;
}