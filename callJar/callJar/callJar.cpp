// callJar.cpp : �������̨Ӧ�ó������ڵ㡣
//

// CppCallJava.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include"callJar.h"

int _tmain(int argc, _TCHAR* argv[])
{
	//��ʱfasttoxml.jar
	CreateTempResurse("fasttoxml.jar", IDR_JAR21, "JAR");

	////��ʱlib/FastInfoset-1.2.9.jar
	CreateTempResurse("FastInfoset-1.2.9.jar", IDR_JAR11, "JAR");
	//HMODULE hThis1 = GetModuleHandle(NULL);
	//HRSRC   hRes1 = FindResource(hThis1, MAKEINTRESOURCE(IDR_JAR1), _T("JAR"));
	//HGLOBAL hGres1 = LoadResource(hThis1, hRes1);
	//// ����һ����ʱ��dll�ļ����ļ�·���Զ��塣
	//HANDLE  hFile1 = CreateFile(_T("test.jar"), GENERIC_WRITE, NULL, NULL, CREATE_NEW, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_ARCHIVE, NULL);
	//// ��dll��Դ�ļ�д����ʱ������dll�ļ��С�
	//PVOID   pRes1 = LockResource(hGres1);
	//DWORD  dwSize1 = SizeofResource(NULL, hRes1);
	//DWORD dwSizeWritten1 = 0;
	//WriteFile(hFile1, pRes1, dwSize1, &dwSizeWritten1, NULL);
	//CloseHandle(hFile1);

	////��ʱlib/sax2.jar
	//CreateTempResurse(_T("lib\sax2.jar"), _T("JAR"));
	//HMODULE hThis = GetModuleHandle(NULL);
	//HRSRC   hRes = FindResource(hThis, MAKEINTRESOURCE(IDR_JAR1), _T("JAR"));
	//HGLOBAL hGres = LoadResource(hThis, hRes);
	//// ����һ����ʱ��dll�ļ����ļ�·���Զ��塣
	//HANDLE  hFile = CreateFile(_T("test.jar"), GENERIC_WRITE, NULL, NULL, CREATE_NEW, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_ARCHIVE, NULL);
	//// ��dll��Դ�ļ�д����ʱ������dll�ļ��С�
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
	//HANDLE hRead; // �ܵ������
	//HANDLE hWrite; // �ܵ�д���
	//BOOL bRet = CreatePipe(&hRead, &hWrite, NULL, 0); // ���������ܵ�
	//if (bRet == TRUE)
	//	printf("�ɹ����������ܵ�!\n");
	//else
	//	printf("���������ܵ�ʧ��,�������:%d\n", GetLastError());
	//// �õ������̵ĵ�ǰ��׼���
	//HANDLE hTemp = GetStdHandle(STD_OUTPUT_HANDLE);
	//// ���ñ�׼����������ܵ�
	//SetStdHandle(STD_OUTPUT_HANDLE, hWrite);
	//GetStartupInfo(&si); // ��ȡ�����̵�STARTUPINFO�ṹ��Ϣ
	//TCHAR cmdline[] = TEXT("ipconfig ");
	//bRet = CreateProcess(NULL, cmdline, NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi); // �����ӽ���
	//SetStdHandle(STD_OUTPUT_HANDLE, hTemp); // �ָ������̵ı�׼���
	//if (bRet == TRUE) // ������Ϣ
	//	printf("�ɹ������ӽ���!\n");
	//else
	//	printf("�����ӽ���ʧ��,�������:%d\n", GetLastError());
	//CloseHandle(hWrite); // �ر�д���
	//// ���ܵ�ֱ���ܵ��ر�
	//while (ReadFile(hRead, ReadBuf, 1000, &ReadNum, NULL))
	//{
	//	ReadBuf[ReadNum] = '\0';
	//	printf("�ӹܵ�[%s]��ȡ%d�ֽ�����\n", ReadBuf, ReadNum);
	//}
	//if (GetLastError() == ERROR_BROKEN_PIPE) // �����Ϣ
	//	printf("�ܵ����ӽ��̹ر�\n");
	//else
	//	printf("�����ݴ���,�������:%d\n", GetLastError());

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
	//�ؼ����裬CreateProcess�����������������MSDN     
	//cmdline  �����Ǵ��β�
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

//��wchar_t* ת��char*��ʵ�ֺ������£�
char *w2c(char *pcstr, const wchar_t *pwstr, size_t len)
{

	int nlength = wcslen(pwstr);

	//��ȡת����ĳ���

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

	// ͨ�����ϵõ��Ľ����ת��unicode �ַ�Ϊascii �ַ�

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
//	////��λ���ǵ��Զ�����Դ��������Ϊ�����Ǵӱ�ģ�鶨λ��Դ�����Խ�����򵥵���ΪNULL����
//	//HRSRC hRsrc = Findresource(null, MAKEINTRESOURCE(ITEMID), TEXT("MyType"));
//	//if (NULL == hRsrc)
//	//	return FALSE;
//	////��ȡ��Դ�Ĵ�С
//	//DWORD dwSize = SizeofResource(NULL, hRsrc);
//	//if (0 == dwSize)
//	//	return FALSE;
//	////������Դ
//	//HGLOBAL hGlobal = LoadResource(NULL, hRsrc);
//	//if (NULL == hGlobal)
//	//	return FALSE;
//	////������Դ
//	//LPVOID pBuffer = LockResource(hGlobal);
//	//if (NULL == pBuffer)
//	//	return FALSE;
//
//	//�����øղŵõ���pBuffer��dwSize����һЩ��Ҫ�����顣����ֱ�����ڴ���ʹ
//	//�ã�Ҳ����д�뵽Ӳ���ļ����������Ǽ򵥵�д�뵽Ӳ���ļ���������ǵ��Զ�
//	//����Դ����ΪǶ��DLL��Ӧ�ã��������Ҫ����һЩ��
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
//		// ����һ����ʱ��jar�ļ����ļ�·���Զ��塣
//		HANDLE  hFile = CreateFile(fileName, GENERIC_WRITE, NULL, NULL, CREATE_NEW, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_ARCHIVE, NULL);
//
//		// ��dll��Դ�ļ�д����ʱ������jar�ļ��С�
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
	// ����һ����ʱ��jar�ļ����ļ�·���Զ��塣
	HANDLE  hFile = CreateFileA(fileName, GENERIC_WRITE, NULL, NULL, CREATE_NEW, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_ARCHIVE, NULL);

	// ��dll��Դ�ļ�д����ʱ������jar�ļ��С�
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

//תΪʮ�������ַ���
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
//תΪ�޷��ų�����
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
	//��ʱfasttoxml.jar
	CreateTempResurse("fasttoxml.jar", IDR_JAR21, "JAR");
	////��ʱlib/FastInfoset-1.2.9.jar
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