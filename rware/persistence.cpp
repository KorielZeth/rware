#include <windows.h>
#include "strsafe.h"
#include <ShlObj.h>
#include <iostream>

//finish this one day lmao

/*int checkForRegkey() {

	HKEY cl�Registre;
	if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_READ, &cl�Registre) == ERROR_SUCCESS) {

		if (RegGetValueW(cl�Registre, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", L"rware", 2, NULL, NULL, NULL) == ERROR_SUCCESS) {

			std::cout << "The key does indeed exist";
			return 0;
		}
		else
		{
			DWORD d;
			d = GetLastError();
			std::cout << "Failure to check the key, error code 0x" << d << std::endl;
			RegCloseKey(cl�Registre);
			return -1;
		}


	}
	else {
		DWORD d;
		d = GetLastError();
		std::cout << "Failure to open handle to the regkey, error code 0x" << d << std::endl;
		RegCloseKey(cl�Registre);
		return -1;
	};
}*/


/*int setRegkey() {

	HKEY cl�Registre;
	if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\Microsoft\Windows\CurrentVersion\Run", 0, KEY_READ, &cl�Registre) == ERROR_SUCCESS) {
		LPWSTR path;
		GetModuleFileNameW(nullptr, path, MAX_PATH);
		DWORD pathlen = sizeof(path);

		//RegSetValueExW(cl�Registre,L"rware",NULL,REG_SZ,path,pathlen);


	}
	else {
		DWORD d;
		d = GetLastError();
		std::cout << "Failure to open handle to the regkey, error code 0x" << d << std::endl;
		RegCloseKey(cl�Registre);
		return -1;

	}




	return 0;
}*/