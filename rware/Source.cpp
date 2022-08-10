#include <iostream>
#include <fstream>
#include <ostream>
#include <windows.h>




int main() {

	
	HCRYPTPROV prov = NULL;
	HCRYPTKEY clé = NULL;
	DWORD bloblen = 0;
	bool ok;

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

		std::ofstream bytefile("byte.txt",std::ios::binary);
		bytefile.write((const char*)blob,sizeof(blob));
		bytefile.close();

	}

	// import key
	
	/*if (CryptAcquireContextW(&prov, 0, 0, PROV_RSA_AES, CRYPT_VERIFYCONTEXT)) {

		std::cout << "Context acquired" << std::endl;
	}
	else {
		DWORD d = GetLastError();
		std::cout << "Failure to acquire context, error code: " << d << std::endl;
		return -1;
	}

	if (CryptImportKey(prov,blob, sizeof(clé), 0, 0, &clé)) {

		std::cout << "Key succesfully imported" << std::endl;
	}
	else {

		DWORD d = GetLastError();
		std::cout << "Failure to import key, error code: " << d << std::endl;
		return -1;
	}*/

	//File handling 
	/*
	const wchar_t* sourcefile = L"C:\\Users\\garma\\source\\repos\\rware\\x64\\Debug\\testfile.txt";
	const wchar_t* destfile = L"C:\\Users\\garma\\source\\repos\\rware\\x64\\Debug\\testfile2.txt";
	HANDLE sourcehandle = NULL;
	HANDLE desthandle = NULL;


	sourcehandle = CreateFileW(sourcefile, FILE_READ_DATA, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	desthandle = CreateFileW(destfile, FILE_WRITE_DATA | DELETE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (sourcehandle == INVALID_HANDLE_VALUE) {
		DWORD d = GetLastError();
		std::cout << "Error code : " << d << std::endl;
	}

	LPVOID buffer = NULL;
	DWORD count = 0;
	DWORD blocklen = 1280;
	DWORD bufferlen = 1280;
	int ending = 0;

	while (ending == 0) {
		if (ReadFile(sourcehandle, buffer, blocklen, &count, NULL) == 0) {

			std::cout << "Error reading from file" << std::endl;
			break;

		}
		std::cout << "Byte count : " << count;
		if (count < blocklen) {

			ending = 1;
		}
		if (CryptEncrypt(clé, 0, ending, 0, (BYTE*)buffer, &count, bufferlen) == 0) {

			DWORD d = GetLastError();
			std::cout << "Failed to encrypt, error code 0x" << count << " , last error : " << d << std::endl;
			break;
		}
		if (WriteFile(desthandle, buffer, count, &count, NULL) == 0) {

			std::cout << "Error writing to file" << std::endl;
			break;
		}
		CloseHandle(sourcehandle);
		CloseHandle(desthandle);

	}*/

	return 0;
}