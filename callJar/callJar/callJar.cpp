// callJar.cpp : 定义控制台应用程序的入口点。
//

// CppCallJava.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include"callJar.h"

int _tmain(int argc, _TCHAR* argv[])
{
	//临时fasttoxml.jar
	CreateTempResurse("fasttoxml.jar", IDR_JAR21, "JAR");

	////临时lib/FastInfoset-1.2.9.jar
	CreateTempResurse("FastInfoset-1.2.9.jar", IDR_JAR11, "JAR");
	//HMODULE hThis1 = GetModuleHandle(NULL);
	//HRSRC   hRes1 = FindResource(hThis1, MAKEINTRESOURCE(IDR_JAR1), _T("JAR"));
	//HGLOBAL hGres1 = LoadResource(hThis1, hRes1);
	//// 创建一个临时的dll文件。文件路径自定义。
	//HANDLE  hFile1 = CreateFile(_T("test.jar"), GENERIC_WRITE, NULL, NULL, CREATE_NEW, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_ARCHIVE, NULL);
	//// 将dll资源文件写入临时创建的dll文件中。
	//PVOID   pRes1 = LockResource(hGres1);
	//DWORD  dwSize1 = SizeofResource(NULL, hRes1);
	//DWORD dwSizeWritten1 = 0;
	//WriteFile(hFile1, pRes1, dwSize1, &dwSizeWritten1, NULL);
	//CloseHandle(hFile1);

	////临时lib/sax2.jar
	//CreateTempResurse(_T("lib\sax2.jar"), _T("JAR"));
	//HMODULE hThis = GetModuleHandle(NULL);
	//HRSRC   hRes = FindResource(hThis, MAKEINTRESOURCE(IDR_JAR1), _T("JAR"));
	//HGLOBAL hGres = LoadResource(hThis, hRes);
	//// 创建一个临时的dll文件。文件路径自定义。
	//HANDLE  hFile = CreateFile(_T("test.jar"), GENERIC_WRITE, NULL, NULL, CREATE_NEW, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_ARCHIVE, NULL);
	//// 将dll资源文件写入临时创建的dll文件中。
	//PVOID   pRes = LockResource(hGres);
	//DWORD  dwSize = SizeofResource(NULL, hRes);
	//DWORD dwSizeWritten = 0;
	//WriteFile(hFile, pRes, dwSize, &dwSizeWritten, NULL);
	//CloseHandle(hFile);

	TCHAR cmdline1[] = TEXT("java -jar fasttoxml.jar E:\\Study\\Ctrip\\FISerialization\\FISerialization\\bin\\Debug\\Noemax.FastInfoset.Net41.fi");
	string buffer = call(cmdline1);
	int lll = buffer.size();
	int len = strlen(buffer.c_str());
	char *dd = (char*)malloc((len + 1)*sizeof(char));
	strcpy_s(dd, len + 1, buffer.c_str());
#ifdef UNICODE
	/*char *pcstr = (char *)malloc(sizeof(char)*(2 * wcslen(buffer) + 1));
	memset(pcstr, 0, 2 * wcslen(buffer) + 1);
	w2c(pcstr, buffer, 2 * wcslen(buffer) + 1);
	std::string ss = pcstr;
	printf("%s", ss);*/
#else
	printf(buffer);
#endif
	printf("%s", dd);
	//STARTUPINFO si;
	//PROCESS_INFORMATION pi;
	//char ReadBuf[100];
	//DWORD ReadNum;
	//HANDLE hRead; // 管道读句柄
	//HANDLE hWrite; // 管道写句柄
	//BOOL bRet = CreatePipe(&hRead, &hWrite, NULL, 0); // 创建匿名管道
	//if (bRet == TRUE)
	//	printf("成功创建匿名管道!\n");
	//else
	//	printf("创建匿名管道失败,错误代码:%d\n", GetLastError());
	//// 得到本进程的当前标准输出
	//HANDLE hTemp = GetStdHandle(STD_OUTPUT_HANDLE);
	//// 设置标准输出到匿名管道
	//SetStdHandle(STD_OUTPUT_HANDLE, hWrite);
	//GetStartupInfo(&si); // 获取本进程的STARTUPINFO结构信息
	//TCHAR cmdline[] = TEXT("ipconfig ");
	//bRet = CreateProcess(NULL, cmdline, NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi); // 创建子进程
	//SetStdHandle(STD_OUTPUT_HANDLE, hTemp); // 恢复本进程的标准输出
	//if (bRet == TRUE) // 输入信息
	//	printf("成功创建子进程!\n");
	//else
	//	printf("创建子进程失败,错误代码:%d\n", GetLastError());
	//CloseHandle(hWrite); // 关闭写句柄
	//// 读管道直至管道关闭
	//while (ReadFile(hRead, ReadBuf, 1000, &ReadNum, NULL))
	//{
	//	ReadBuf[ReadNum] = '\0';
	//	printf("从管道[%s]读取%d字节数据\n", ReadBuf, ReadNum);
	//}
	//if (GetLastError() == ERROR_BROKEN_PIPE) // 输出信息
	//	printf("管道被子进程关闭\n");
	//else
	//	printf("读数据错误,错误代码:%d\n", GetLastError());

	system("pause");

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
	char buffer[MAX_SIZE];
	DWORD   bytesRead, dwWritten;
	std::string s3s = "";
	WaitForSingleObject(pi.hProcess, INFINITE);
	//Sleep(1000);
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
		/*if (!WriteFile(hStdout, buffer, bytesRead, &dwWritten, NULL))
		break;*/
		s3s = buffer;

	}
	int len = s3s.size();
	return buffer;
}

//将wchar_t* 转成char*的实现函数如下：
char *w2c(char *pcstr, const wchar_t *pwstr, size_t len)
{

	int nlength = wcslen(pwstr);

	//获取转换后的长度

	int nbytes = WideCharToMultiByte(0, // specify the code page used to perform the conversion

		0,         // no special flags to handle unmapped characters

		pwstr,     // wide character string to convert

		nlength,   // the number of wide characters in that string

		NULL,      // no output buffer given, we just want to know how long it needs to be

		0,

		NULL,      // no replacement character given

		NULL);    // we don't want to know if a character didn't make it through the translation

	// make sure the buffer is big enough for this, making it larger if necessary

	if (nbytes>len)   nbytes = len;

	// 通过以上得到的结果，转换unicode 字符为ascii 字符

	WideCharToMultiByte(0, // specify the code page used to perform the conversion

		0,         // no special flags to handle unmapped characters

		pwstr,   // wide character string to convert

		nlength,   // the number of wide characters in that string

		pcstr, // put the output ascii characters at the end of the buffer

		nbytes,  // there is at least this much space there

		NULL,      // no replacement character given

		NULL);

	return pcstr;

}

//BOOL UseCustomResource()
//{
//	////定位我们的自定义资源，这里因为我们是从本模块定位资源，所以将句柄简单地置为NULL即可
//	//HRSRC hRsrc = Findresource(null, MAKEINTRESOURCE(ITEMID), TEXT("MyType"));
//	//if (NULL == hRsrc)
//	//	return FALSE;
//	////获取资源的大小
//	//DWORD dwSize = SizeofResource(NULL, hRsrc);
//	//if (0 == dwSize)
//	//	return FALSE;
//	////加载资源
//	//HGLOBAL hGlobal = LoadResource(NULL, hRsrc);
//	//if (NULL == hGlobal)
//	//	return FALSE;
//	////锁定资源
//	//LPVOID pBuffer = LockResource(hGlobal);
//	//if (NULL == pBuffer)
//	//	return FALSE;
//
//	//我们用刚才得到的pBuffer和dwSize来做一些需要的事情。可以直接在内存中使
//	//用，也可以写入到硬盘文件。这里我们简单的写入到硬盘文件，如果我们的自定
//	//义资源是作为嵌入DLL来应用，情况可能要复杂一些。
//	//BOOL bRt = FALSE;
//	//FILE* fp = _tfopen(_T("demo.exe"), _T("wb"));
//	//if (fp != NULL)
//	//{
//	//	if (dwSize == fwrite(pBuffer, sizeof(char), dwSize, fp))
//	//		bRt = TRUE;
//	//	fclose(fp);
//	//}
//
//	////FreeResource(hGlobal);
//	//return bRt;
//}

wstring GetProgramDir()
{
	TCHAR exeFullPath[MAX_PATH]; // Full path
	GetModuleFileName(NULL, exeFullPath, MAX_PATH);
	wstring strPath = __TEXT("");
	strPath = (wstring)exeFullPath;    // Get full path of the file
	int pos = strPath.find_last_of(L'\\', strPath.length());
	return strPath.substr(0, pos);  // Return the directory without the file name
}


tstring myGetFileType(tstring filename)
{
	int len = filename.length();
	int pos = filename.find_last_of(L'.', len);
	return filename.substr(pos + 1, len);
}



//void CreateTempResurse(TCHAR* fileName, int ResourseName, TCHAR* resourseType)
//{
//	tstring name = fileName;
//	//if (_taccess(name.c_str(), 0) != 0)
//	//{
//		HMODULE hmd=LoadLibrary(TEXT("C:\\Users\\CHEN\\Documents\\Visual Studio 2013\\Projects\\callJar\\Debug\\callJar.exe"));
//		if (_taccess(TEXT("C:\\Users\\CHEN\\Documents\\Visual Studio 2013\\Projects\\callJar\\Debug\\callJar.exe"), 0) != 0)
//		{
//			int ddadf = 0;
//		}
//		//HMODULE hmd = LoadLibrary(TEXT("C:\\Users\\CHEN\\Documents\\Visual Studio 2013\\Projects\\callJar\\Debug\\callJar.exe"));
//		int ee = GetLastError();
//		HMODULE hThis = GetModuleHandle(TEXT("C:\\Users\\CHEN\\Documents\\Visual Studio 2013\\Projects\\callJar\\Debug\\callJar.exe"));
//		int ss = GetLastError();
//		HRSRC   hRes = FindResource(hThis, MAKEINTRESOURCE(ResourseName), resourseType);
//		HGLOBAL hGres = LoadResource(hThis, hRes);
//		// 创建一个临时的jar文件。文件路径自定义。
//		HANDLE  hFile = CreateFile(fileName, GENERIC_WRITE, NULL, NULL, CREATE_NEW, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_ARCHIVE, NULL);
//
//		// 将dll资源文件写入临时创建的jar文件中。
//		PVOID   pRes = LockResource(hGres);
//		DWORD  dwSize = SizeofResource(NULL, hRes);
//		DWORD dwSizeWritten = 0;
//		WriteFile(hFile, pRes, dwSize, &dwSizeWritten, NULL);
//		string dsd="";
//		DwordToString(dsd, dwSize);
//		CloseHandle(hFile);
//		FreeLibrary(hmd);
//	//}
//}

void CreateTempResurse(char* fileName, int ResourseName, char* resourseType)
{
	string name = fileName;
	//if (_taccess(name.c_str(), 0) != 0)
	//{
	HMODULE hmd = LoadLibraryA("C:\\Users\\CHEN\\Documents\\Visual Studio 2013\\Projects\\callJar\\Debug\\callJar.exe");
	if (_access("C:\\Users\\CHEN\\Documents\\Visual Studio 2013\\Projects\\callJar\\Debug\\callJar.exe", 0) != 0)
	{
		int ddadf = 0;
	}
	//HMODULE hmd = LoadLibrary(TEXT("C:\\Users\\CHEN\\Documents\\Visual Studio 2013\\Projects\\callJar\\Debug\\callJar.exe"));
	int ee = GetLastError();
	HMODULE hThis = GetModuleHandleA("C:\\Users\\CHEN\\Documents\\Visual Studio 2013\\Projects\\callJar\\Debug\\callJar.exe");
	int ss = GetLastError();
	HRSRC   hRes = FindResourceA(hThis, MAKEINTRESOURCEA(ResourseName), resourseType);
	HGLOBAL hGres = LoadResource(hThis, hRes);
	// 创建一个临时的jar文件。文件路径自定义。
	HANDLE  hFile = CreateFileA(fileName, GENERIC_WRITE, NULL, NULL, CREATE_NEW, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_ARCHIVE, NULL);

	// 将dll资源文件写入临时创建的jar文件中。
	PVOID   pRes = LockResource(hGres);
	DWORD  dwSize = SizeofResource(NULL, hRes);
	DWORD dwSizeWritten = 0;
	WriteFile(hFile, pRes, dwSize, &dwSizeWritten, NULL);
	string dsd = "";
	DwordToString(dsd, dwSize);
	CloseHandle(hFile);
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
//转为无符号长整数
DWORD HexStringToDword(string strIn)
{
	char szHex[10];
	for (int i = 0; i<strIn.length(); i++)
		szHex[i] = strIn[i];
	szHex[strIn.length()] = '\0';

	DWORD dwValue = 0;
	if (strstr(szHex, "0x"))
	{
		strcpy(szHex, szHex + 2);
		szHex[8] = '\0';
	}
	char *szUP = _strupr(szHex);
	char chrTmp[] = "0123456789ABCDEF";
	char *pFind = NULL;
	for (int i = 0; i < 8; i++)
	{
		pFind = strchr(chrTmp, szHex[i]);
		dwValue = dwValue | (((DWORD)(pFind - chrTmp) << (7 - i) * 4) & 0xFFFFFFFF);
	}
	return dwValue;
}


char* test()
{
	//临时fasttoxml.jar
	CreateTempResurse("fasttoxml.jar", IDR_JAR21, "JAR");
	////临时lib/FastInfoset-1.2.9.jar
	CreateTempResurse("FastInfoset-1.2.9.jar", IDR_JAR11, "JAR");
	TCHAR cmdline1[] = TEXT("java -jar fasttoxml.jar E:\\Study\\Ctrip\\FISerialization\\FISerialization\\bin\\Debug\\Noemax.FastInfoset.Net41.fi");
	string buffer = call(cmdline1);
	int lll = buffer.size();
	int len = strlen(buffer.c_str());
	char *dd = (char*)malloc((len + 1)*sizeof(char));
	strcpy_s(dd, len + 1, buffer.c_str());
	return dd;
	//printf("%s", dd);

	//system("pause");

}

char*  test2()
{
	char ch[5]= "dddd";
	
	return ch;
}