
// collectorDlg.h: soubor hlaviček
//
#ifndef DLG_H
#define DLG_H
 // !DLG_H

#pragma once
#pragma warning(disable: 6262)
#include <stdio.h>
#include <stdint.h>
#include <winevt.h>
#include <zipper.h>
#include <fstream>

#define MAX_UNICODE_PATH 32767
// Dialog colectDlg
using namespace std;
using namespace zipper;

class colectDlg : public CDialogEx
{
// Konstrukce
public:
	colectDlg(CWnd* pParent = nullptr);	// standardní konstruktor
	bool winpe = false;
// Data dialogu
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COLLECTOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// Podpora DDX/DDV
private:
	void GetDrives();
	
	//bool ExtractResource(uint16_t ResourceID, wchar_t* OutputFileName, wchar_t* path, const wchar_t* ResType);
	template <size_t size>
	static inline DWORD GetFiles(wchar_t* path, const wchar_t filepattern[], wchar_t* files, int sizeofarray, ULONG (&filessize)[size], ULONG (&fileslen)[size], wchar_t* pointer[], UINT* countfiles);
	template <size_t size>
	 static inline DWORD GetFiles(char* path,const char filepattern[], char* files, int sizeofarray, ULONG (&filessize)[size], ULONG (&fileslen)[size], char* pointer[], UINT *countfiles);
	 static inline DWORD CopyDelete(wchar_t* path,wchar_t* files, wchar_t* pointer[], UINT countfiles, UINT action=1U,wchar_t* destination = nullptr);
	 static inline DWORD CopyDelete(char* path, char* files,char *pointer[], UINT countfiles, UINT action = 1U, char* destination = nullptr);
// Implementace
protected:
	HICON m_hIcon;

	// Vygenerované funkce mapy zpráv
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedGen();
private:
	CComboBox* seldisk = nullptr;
	CProgressCtrl* prog = nullptr;
	char *files = nullptr;
	char* filespointer[100] = { nullptr };
	wchar_t* filest = nullptr;
	wchar_t* filespointert[100] = { nullptr };
	ULONG fileslen[100] = { 0 };
	ULONG fileslent[100] = { 0 };
	ULONG filesize[100] = {0};
	ULONG filesizet[100] = { 0 };
	UINT countFiles;
	UINT countFilest;
	
};
template <size_t size>
inline DWORD colectDlg::GetFiles(wchar_t* path, const wchar_t filepattern[], wchar_t* files, int sizeofarray, ULONG (&filessize)[size], ULONG (&fileslen)[size], wchar_t* pointer[], UINT* countfiles)
{
	UINT count=0;
	BOOL retval = 0;
	DWORD errorcode = 0;
	WIN32_FIND_DATA data;
	UINT size1 = *(&filessize + 1) - filessize;
	ZeroMemory(files, sizeofarray-1);
	ZeroMemory(countfiles, size1-1);
	ZeroMemory(fileslen, size1-1);
	for (UINT i = 0; i < size1-1; i++)
	{
		filessize[i] = 0;
		fileslen[i] = 0;
	}
	wchar_t* buffer = (wchar_t*)malloc(MAX_PATH);
	if (buffer == nullptr)
	{
		return -1;
	}
	ZeroMemory(buffer, MAX_PATH);
	swprintf_s(buffer, (MAX_PATH / 2)-2, L"%s\\%s", path, filepattern);
	HANDLE filex = FindFirstFile(buffer, &data);

	if (filex == INVALID_HANDLE_VALUE)
	{
		errorcode = GetLastError();
		if (errorcode == ERROR_FILE_NOT_FOUND)
		{
			goto endfile2;
		}
		else if (errorcode == ERROR_INVALID_NAME)
		{
			free(buffer);
			return errorcode;
		}
		else
		{
			free(buffer);
			return errorcode;
		}
	}

	if (!wcscmp(data.cFileName, L"."))
	{
		retval = FindNextFile(filex, &data);
		if (retval != 0)
		{
			if (!wcscmp(data.cFileName, L".."))
			{
				retval = FindNextFile(filex, &data);
				if (retval != 0)
				{
					goto nxt;
				}
				else
				{
					errorcode = GetLastError();
					if (errorcode == ERROR_NO_MORE_FILES)
					{
						goto endfile2;
					}
				}
			}
		}
		else
		{
			errorcode = GetLastError();
			if (errorcode == ERROR_NO_MORE_FILES)
			{
				goto endfile2;
			}
		}
	}
nxt:
	wcscat_s(files, sizeofarray / 2, data.cFileName);
	count++;
	fileslen[count - 1] = wcslen(data.cFileName);
	for (unsigned int i = 0; i < 59; i++)
	{
		retval = FindNextFile(filex, &data);
		if (retval != 0)
		{
			wcscat_s(files, sizeofarray / 2, L"\n");
			wcscat_s(files, sizeofarray / 2, data.cFileName);
			count++;
			fileslen[count - 1] = wcslen(data.cFileName);
		}
		else
		{
			errorcode = GetLastError();
			if (errorcode == ERROR_NO_MORE_FILES)
			{
				goto endfile2;
			}
		}
	}
endfile2:
	FindClose(filex);
	ULONG len = fileslen[0];
	for (ULONG p = 0; p < count; p++)
	{
		if (files[len] == *L"\n")
		{

			files[len] = *L"\0";
			len = len + fileslen[p] + 1;
		}
	}
	len = 0;
	wchar_t* filedd = (wchar_t*)malloc(MAX_PATH);
	if (filedd == nullptr)
	{
		free(buffer);
		return -1;
	}
	ZeroMemory(filedd, MAX_PATH);
	for (ULONG i = 0; i < count; i++)
	{
		int ret;
		LARGE_INTEGER x;
		pointer[i] = &files[len];
		swprintf_s(filedd, (MAX_PATH / 2)-2, L"%s\\%s", path, pointer[i]);
		HANDLE h = CreateFile(filedd, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (h == INVALID_HANDLE_VALUE)
		{
			goto skiphandle;
		}
		ret = GetFileSizeEx(h, &x);
		if (ret == 0)
		{
			filessize[i] = 0;
		}
		else
		{
			filessize[i] = (ULONG)x.QuadPart;
		}
		CloseHandle(h);
	skiphandle:
		len = len + fileslen[i] + 1;
	}
	free(filedd);
	free(buffer);
	memcpy_s(countfiles, sizeof(UINT), &count, sizeof(UINT));
	return NO_ERROR;
}
inline DWORD colectDlg::CopyDelete(wchar_t* path, wchar_t* files, wchar_t* pointer[], UINT countfiles, UINT action, wchar_t* destination)
{
	wchar_t* filedd = (wchar_t*)malloc(MAX_PATH);
	if (filedd == nullptr)
	{
		return -1;
	}
	ZeroMemory(filedd, MAX_PATH);
	for (UINT i = 0; i < countfiles; i++)
	{
		switch (action)
		{
		case 1:
		{
			swprintf_s(filedd, (MAX_PATH / 2)-2, L"%s\\%s\0", path, pointer[i]);
			DeleteFile(filedd);
			break;
		} case 2:
		{
			if (destination == nullptr)
			{
				goto skip;
			}
			wchar_t filedd2[MAX_PATH] = { 0 };
			swprintf_s(filedd, (MAX_PATH / 2)-2, L"%s\\%s\0", path, pointer[i]);
			swprintf_s(filedd2, (MAX_PATH / 2)-2, L"%s\\%s\0", destination, pointer[i]);
			CopyFile(filedd, filedd2, false);
		skip:
			break;
		}
		}
	}
	free(filedd);
	return NO_ERROR;
}
template <size_t size>
inline DWORD colectDlg::GetFiles(char* path, const char filepattern[], char* files, int sizeofarray, ULONG (&filessize)[size], ULONG (&fileslen)[size], char* pointer[], UINT* countfiles)
{
	UINT count=0;
	BOOL retval = 0;
	DWORD errorcode = 0;
	WIN32_FIND_DATAA data;
	UINT size1 = *(&filessize + 1) - filessize;
	ZeroMemory(files, sizeofarray-1);
	ZeroMemory(countfiles, size1-1);
	ZeroMemory(fileslen, size1-1);
	for (UINT i = 0; i < size1 - 1; i++)
	{
		filessize[i] = 0;
		fileslen[i] = 0;
	}
	char* buffer = (char*)malloc(MAX_PATH);
	if (buffer == nullptr)
	{
		return -1;
	}
	ZeroMemory(buffer, MAX_PATH);
	sprintf_s(buffer, MAX_PATH-3, "%s\\%s", path, filepattern);
	HANDLE filex = FindFirstFileA(buffer, &data);

	if (filex == INVALID_HANDLE_VALUE)
	{
		errorcode = GetLastError();
		if (errorcode == ERROR_FILE_NOT_FOUND)
		{
			goto endfile2;
		}
		else if (errorcode == ERROR_INVALID_NAME)
		{
			free(buffer);
			return errorcode;
		}
		else
		{
			free(buffer);
			return errorcode;
		}
	}

	if (!strcmp(data.cFileName, "."))
	{
		retval = FindNextFileA(filex, &data);
		if (retval != 0)
		{
			if (!strcmp(data.cFileName, ".."))
			{
				retval = FindNextFileA(filex, &data);
				if (retval != 0)
				{
					goto nxt;
				}
				else
				{
					errorcode = GetLastError();
					if (errorcode == ERROR_NO_MORE_FILES)
					{
						goto endfile2;
					}
				}
			}
		}
		else
		{
			errorcode = GetLastError();
			if (errorcode == ERROR_NO_MORE_FILES)
			{
				goto endfile2;
			}
		}
	}
nxt:
	strcat_s(files, sizeofarray / 2, data.cFileName);
	count++;
	fileslen[count - 1] = strlen(data.cFileName);
	for (unsigned int i = 0; i < 59; i++)
	{
		retval = FindNextFileA(filex, &data);
		if (retval != 0)
		{
			strcat_s(files, sizeofarray / 2, "\n");
			strcat_s(files, sizeofarray / 2, data.cFileName);
			count++;
			fileslen[count - 1] = strlen(data.cFileName);
		}
		else
		{
			errorcode = GetLastError();
			if (errorcode == ERROR_NO_MORE_FILES)
			{
				goto endfile2;
			}
		}
	}
endfile2:
	FindClose(filex);
	ULONG len = fileslen[0];
	for (ULONG p = 0; p < count; p++)
	{
		if (files[len] == *"\n")
		{

			files[len] = *"\0";
			len = len + fileslen[p] + 1;
		}
	}
	len = 0;
	char* filedd = (char*)malloc(MAX_PATH);
	if (filedd == nullptr)
	{
		free(buffer);
		return -1;
	}
	ZeroMemory(filedd, MAX_PATH);
	for (ULONG i = 0; i < count; i++)
	{
		int ret;
		LARGE_INTEGER x;
		pointer[i] = &files[len];
		sprintf_s(filedd, MAX_PATH-3, "%s\\%s", path, pointer[i]);
		HANDLE h = CreateFileA(filedd, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (h == INVALID_HANDLE_VALUE)
		{
			goto skiphandle;
		}
		ret = GetFileSizeEx(h, &x);
		if (ret == 0)
		{
			filessize[i] = 0;
		}
		else
		{
			filessize[i] = (ULONG)x.QuadPart;
		}
		CloseHandle(h);
	skiphandle:
		len = len + fileslen[i] + 1;
	}
	free(filedd);
	free(buffer);
	memcpy_s(countfiles, sizeof(UINT), &count, sizeof(UINT));
	return NO_ERROR;
}
inline DWORD colectDlg::CopyDelete(char* path, char* files, char* pointer[], UINT countfiles, UINT action, char* destination)
{
	char* filedd = (char*)malloc(MAX_PATH);
	if (filedd == nullptr)
	{
		return -1;
	}
	ZeroMemory(filedd, MAX_PATH);
	for (UINT i = 0; i < countfiles; i++)
	{
		switch (action)
		{
		case 1:
		{
			sprintf_s(filedd, MAX_PATH-3, "%s\\%s\0", path, pointer[i]);
			DeleteFileA(filedd);
			break;
		} case 2:
		{
			if (destination == nullptr)
			{
				goto skip;
			}
			char filedd2[MAX_PATH] = { 0 };
			sprintf_s(filedd, MAX_PATH-3, "%s\\%s\0", path, pointer[i]);
			sprintf_s(filedd2, MAX_PATH-3, "%s\\%s\0", destination, pointer[i]);
			CopyFileA(filedd, filedd2, false);
		skip:
			break;
		}
		}
	}
	free(filedd);
	return NO_ERROR;
}

#endif