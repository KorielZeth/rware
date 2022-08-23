#include <windows.h>
#include "strsafe.h"
#include <ShlObj.h>

int checkforenkrypt() {

	LPWSTR canaryfile ;
	SHGetKnownFolderPath(FOLDERID_Profile, 0, NULL, &canaryfile);
	StringCchCatW(canaryfile, MAX_PATH,L"\\Favorites\canary.txt");










	return 0;
}