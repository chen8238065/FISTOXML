//this file is part of notepad++
//Copyright (C)2003 Don HO <donho@altern.org>
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either
//version 2 of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#include "PluginDefinition.h"
#include "menuCmdID.h"

#define MAX_SIZE 1024*1024*4


//#include "afx.h"
//
// The plugin data that Notepad++ needs
//
FuncItem funcItem[nbFunc];

//
// The data of Notepad++ that you can use in your plugin commands
//
NppData nppData;

//
// Initialize your plugin data here
// It will be called while plugin loading   
void pluginInit(HANDLE hModule)
{
	//创建临时fasttoxml.jar
	//CreateTempResurse(TEXT("fasttoxml.jar"), IDR_JAR2, TEXT("JAR"));

	//创建临时FastInfoset-1.2.9.jar
	//CreateTempResurse(TEXT("FastInfoset-1.2.9.jar"), IDR_JAR1, TEXT("JAR"));
}

//
// Here you can do the clean up, save the parameters (if any) for the next session
//
void pluginCleanUp()
{
}

//
// Initialization of your plugin commands
// You should fill your plugins commands here
void commandMenuInit()
{

	//--------------------------------------------//
	//-- STEP 3. CUSTOMIZE YOUR PLUGIN COMMANDS --//
	//--------------------------------------------//
	// with function :
	// setCommand(int index,                      // zero based number to indicate the order of command
	//            TCHAR *commandName,             // the command name that you want to see in plugin menu
	//            PFUNCPLUGINCMD functionPointer, // the symbol of function (function pointer) associated with this command. The body should be defined below. See Step 4.
	//            ShortcutKey *shortcut,          // optional. Define a shortcut to trigger this command
	//            bool check0nInit                // optional. Make this menu item be checked visually
	//            );
	setCommand(0, TEXT("convertToXML"), convertToXML, NULL, false);
	setCommand(1, TEXT("Open Fastinfoset document"), OpenFIS, NULL, false);
}

//
// Here you can do the clean up (especially for the shortcut)
//
void commandMenuCleanUp()
{
	// Don't forget to deallocate your shortcut here
}


//
// This function help you to initialize your plugin commands
//
bool setCommand(size_t index, TCHAR *cmdName, PFUNCPLUGINCMD pFunc, ShortcutKey *sk, bool check0nInit)
{
	if (index >= nbFunc)
		return false;

	if (!pFunc)
		return false;

	lstrcpy(funcItem[index]._itemName, cmdName);
	funcItem[index]._pFunc = pFunc;
	funcItem[index]._init2Check = check0nInit;
	funcItem[index]._pShKey = sk;

	return true;
}

//----------------------------------------------//
//-- STEP 4. DEFINE YOUR ASSOCIATED FUNCTIONS --//
//----------------------------------------------//
void convertToXML()
{
	TCHAR path[MAX_PATH];
	// Get the current scintilla
	int which = -1;
	::SendMessage(nppData._nppHandle, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&which);
	if (which == -1)
		return;
	HWND curScintilla = (which == 0) ? nppData._scintillaMainHandle : nppData._scintillaSecondHandle;
	::SendMessage(nppData._nppHandle, NPPM_GETFULLCURRENTPATH, MAX_PATH, (LPARAM)path);
	int encoding = (int)::SendMessage(curScintilla, SCI_GETCODEPAGE, 0, 0);
	char pathA[MAX_PATH];
	WideCharToMultiByte(encoding, 0, path, -1, pathA, MAX_PATH, NULL, NULL);
	tstring  sss = path;
	tstring cmd = TEXT("java -jar plugins//lib//fasttoxml.jar  ") + sss;

	TCHAR tcmd[MAX_PATH + 20];
	_tcscpy(tcmd, cmd.c_str());
	char ctcmd[MAX_PATH + 20];
	WideCharToMultiByte(encoding, 0, tcmd, -1, ctcmd, MAX_PATH + 20, NULL, NULL);
	char *str = call(tcmd);
	::SendMessage(curScintilla, SCI_SETTEXT, 0, (LPARAM)str);
}

void OpenFIS()
{
	::SendMessage(nppData._nppHandle, NPPM_MENUCOMMAND, 0, IDM_FILE_OPEN);
	TCHAR path[MAX_PATH];
	// Get the current scintilla
	int which = -1;
	::SendMessage(nppData._nppHandle, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&which);
	if (which == -1)
		return;
	HWND curScintilla = (which == 0) ? nppData._scintillaMainHandle : nppData._scintillaSecondHandle;
	::SendMessage(nppData._nppHandle, NPPM_GETFULLCURRENTPATH, MAX_PATH, (LPARAM)path);
	//judge file type ,if the type is fi convert to XML 
	int encoding = (int)::SendMessage(curScintilla, SCI_GETCODEPAGE, 0, 0);
	char pathA[MAX_PATH];
	WideCharToMultiByte(encoding, 0, path, -1, pathA, MAX_PATH, NULL, NULL);
	tstring  sss = path;
	tstring fi = TEXT("fi");
	tstring type = myGetFileType(sss);
	if (type == fi)
	{
		tstring cmd = TEXT("java -jar fasttoxml.jar  ") + sss;

		TCHAR tcmd[MAX_PATH + 20];
		_tcscpy(tcmd, cmd.c_str());
		char ctcmd[MAX_PATH + 20];
		WideCharToMultiByte(encoding, 0, tcmd, -1, ctcmd, MAX_PATH + 20, NULL, NULL);
		char *str = call(tcmd);
		::SendMessage(curScintilla, SCI_SETTEXT, 0, (LPARAM)str);
	}
	else
	{
		::MessageBox(nppData._nppHandle, TEXT("The file type is wrong"), TEXT("Alert"), MB_OK | MB_ICONWARNING);
		::SendMessage(nppData._nppHandle, NPPM_MENUCOMMAND, 0, IDM_FILE_CLOSE);
	}

}


char* call(TCHAR cmdline[])
{
	SECURITY_ATTRIBUTES   sa;
	HANDLE   hRead, hWrite;
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;
	if (!CreatePipe(&hRead, &hWrite, &sa, 0))
	{
		return   0;
	}
	STARTUPINFO   si;
	PROCESS_INFORMATION   pi;

	// Set up members of the PROCESS_INFORMATION structure. 
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

	// Set up members of the STARTUPINFO structure. 
	ZeroMemory(&si, sizeof(STARTUPINFO));

	si.cb = sizeof(STARTUPINFO);
	GetStartupInfo(&si);
	si.hStdError = hWrite;
	si.hStdOutput = hWrite;
	si.hStdInput = hRead;
	si.wShowWindow = SW_HIDE;
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	//TCHAR cmdline[] = TEXT("ipconfig ");
	//关键步骤，CreateProcess函数参数意义请查阅MSDN     
	//cmdline  必须是传形参
	if (!CreateProcess(NULL, cmdline, NULL, NULL, true, NULL, NULL, NULL, &si, &pi))
	{
		return   0;
	}
	CloseHandle(hWrite);
	//TCHAR  * buffer = (TCHAR*)malloc(MAX_SIZE*sizeof(TCHAR));
	char *buffer = (char*)malloc(MAX_SIZE*sizeof(char));
	DWORD   bytesRead, dwWritten;
	WaitForSingleObject(pi.hProcess, INFINITE);
	while (true)
	{
		if (!ReadFile(hRead, buffer, MAX_SIZE, &bytesRead, NULL) ||
			bytesRead == 0)
		{
			break;
		}
		else
		{
			buffer[bytesRead] = '\0';
		}
		//if (!WriteFile(hStdout, buffer, bytesRead, &dwWritten, NULL))
		//	break;
	}
	return buffer;
}


tstring GetProgramDir()
{
	TCHAR exeFullPath[MAX_PATH]; // Full path
	GetModuleFileName(NULL, exeFullPath, MAX_PATH);
	tstring strPath = __TEXT("");
	strPath = (tstring)exeFullPath;    // Get full path of the file
	int pos = strPath.find_last_of(L'\\', strPath.length());
	return strPath.substr(0, pos);  // Return the directory without the file name
}

tstring myGetFileType(tstring filename)
{
	int len = filename.length();
	int pos = filename.find_last_of(L'.', len);
	return filename.substr(pos + 1, len);
}

void CreateTempResurse(TCHAR* fileName, int ResourseName, TCHAR* resourseType)
{
	tstring name = fileName;
	/*if (_taccess(name.c_str(), 0) != 0)
	{*/
		
		tstring path = GetProgramDir()+TEXT("//plugins//NppPluginTemplate_Debug.dll");
		TCHAR tpath[MAX_PATH + 20];
		_tcscpy(tpath, path.c_str());
		if (_taccess(tpath, 0) != 0)
		{
			::MessageBox(nppData._nppHandle, TEXT("do not had path"), TEXT("Alert"), MB_OK | MB_ICONWARNING);
		}
		else
		{
			::MessageBox(nppData._nppHandle, TEXT("had path"), TEXT("Alert"), MB_OK | MB_ICONWARNING);
		}
		HMODULE hmd = LoadLibrary(tpath);
		HMODULE hThis = GetModuleHandle(tpath);
		HRSRC   hRes = FindResource(hThis, MAKEINTRESOURCE(ResourseName), resourseType);
		HGLOBAL hGres = LoadResource(hThis, hRes);
		// 创建一个临时的jar文件。文件路径自定义。
		HANDLE  hFile = CreateFile(fileName, GENERIC_WRITE, NULL, NULL, CREATE_NEW, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_ARCHIVE, NULL);

		// 将dll资源文件写入临时创建的jar文件中。
		PVOID   pRes = LockResource(hGres);
		DWORD  dwSize = SizeofResource(NULL, hRes);
		DWORD dwSizeWritten = 0;
		WriteFile(hFile, pRes, dwSize, &dwSizeWritten, NULL);
		string dsd = "qw";
		DwordToString(dsd, dwSize);
		CloseHandle(hFile);
		::MessageBox(nppData._nppHandle, tpath, TEXT("Alert"), MB_OK | MB_ICONWARNING);
		FreeLibrary(hmd);
	//}
}

//转为十六进制字符串
void DwordToString(string &outstr, DWORD dwValue)
{

	char szHex[10];
	char chrTmp[] = "0123456789ABCDEF";
	/*if(sizeof(szHex) < 10)
	return;*/
	szHex[0] = '0';
	szHex[1] = 'x';

	for (int i = 0; i < 8; i++)
		szHex[2 + i] = *(chrTmp + (((dwValue) >> (28 - i * 4)) & 0xF));

	outstr = szHex;
}