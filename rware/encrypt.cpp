#include <Windows.h>
#include <iostream>
#include <fstream>


int encrypt() {

	HCRYPTPROV prov = NULL;
	HCRYPTKEY clé = NULL;

	LPCWSTR pzSourceFile = L"srcfile";
	LPCWSTR pzDestFile = L"destfile";

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
		if (dwCount < dwBlockLen) {

			eof = 1;
		}

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