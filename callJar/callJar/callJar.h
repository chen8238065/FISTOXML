#include   <windows.h>     
#include   <stdio.h>    
#include<string.h>
#include<iostream>
#include "resource.h"
#include<io.h>
using namespace std;
#ifdef UNICODE
#define tstring wstring
#define _tcscpy     wcscpy  
#define _taccess _waccess
#else
#define tstring string
#define _tcscpy     strcpy  
#define _taccess _access
#endif
#define MAX_SIZE 1024*502

	char* call(TCHAR cmdline[]);
	char *w2c(char *pcstr, const wchar_t *pwstr, size_t len);
	BOOL UseCustomResource();
	wstring GetProgramDir();
	tstring myGetFileType(tstring filename);
	//void CreateTempResurse(TCHAR* fileName, int ResourseName, TCHAR* resourseType);
	void CreateTempResurse(char* fileName, int ResourseName, char* resourseType);
	void DwordToString(string &outstr, DWORD dwValue);
	
	extern "C" _declspec(dllexport) char*  test();

	extern "C" _declspec(dllexport) char*  test2();
