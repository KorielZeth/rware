#include <iostream>
#include <fstream>
#include <windows.h>

const char* targetExts[] = { ".pl", ".7z", ".rar", ".m4a", ".wma", ".avi", ".wmv", ".d3dbsp", ".sc2save", ".sie",
".sum", ".bkp", ".flv", ".js", ".raw", ".jpeg", ".tar", ".zip", ".tar.gz", ".cmd",
".key", ".DOT", ".docm", ".txt", ".doc", ".docx", ".xls", ".xlsx", ".ppt", ".pptx",
".odt", ".jpg", ".png", ".csv", ".sql", ".mdb", ".sln", ".php", ".asp", ".aspx",
".html", ".xml", ".psd", ".bmp", ".pdf", ".py", ".rtf" };


int wmain() {

	WIN32_FIND_DATA* file_data = NULL;
	HANDLE hFind = NULL;
	LPCWSTR pzDestDirectory = L"destdir";

	hFind = FindFirstFileW(pzDestDirectory,file_data);
	if (hFind == INVALID_HANDLE_VALUE) {
		std::cout << "FindFirstFile failed, with errorcode : " <<  GetLastError() << std::endl;
		return -1;
	}


	
	return 0;
}