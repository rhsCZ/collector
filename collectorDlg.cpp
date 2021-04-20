
// collectorDlg.cpp: soubor implementace
//

#include "pch.h"
#include "framework.h"
#include "collector.h"
#include "collectorDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// Dialog colectDlg

colectDlg::colectDlg(CWnd* pParent /*=nullptr*/)
: CDialogEx(IDD_COLLECTOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void colectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(colectDlg, CDialogEx)
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_REFRESH, &colectDlg::GetDrives)
ON_BN_CLICKED(IDC_GEN, &colectDlg::OnBnClickedGen)
ON_BN_CLICKED(IDCANCEL, &colectDlg::OnBnClickedCancel)
END_MESSAGE_MAP()

BOOL colectDlg::OnInitDialog()
{
	colectDlg::ShowWindow(SW_SHOW);
	colectDlg::RedrawWindow();
	colectDlg::CenterWindow();
	CDialogEx::OnInitDialog();
	if (colectDlg::IsWindowVisible() != 0)
	{
		seldisk = (CComboBox*)GetDlgItem(IDC_SELDISK);
		prog = (CProgressCtrl*)GetDlgItem(IDC_PROG);
		prog->ShowWindow(SW_HIDE);
		prog->SetRange(0, 100);
		prog->SetPos(0);
		GetDrives();
	}
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	return TRUE;  
}

void colectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // kontext zařízení pro kreslení

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Zarovnat ikonu v obdélníku klienta na střed
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Vykreslit ikonu
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
	}
HCURSOR colectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
/*bool colectDlg::ExtractResource(uint16_t ResourceID, wchar_t* OutputFileName, wchar_t* path, const wchar_t* ResType)
{
try
{
HRSRC hResource = FindResource(nullptr, MAKEINTRESOURCE(ResourceID), ResType);
if (hResource == nullptr)
{
return false;
}

HGLOBAL hFileResource = LoadResource(nullptr, hResource);
if (hFileResource == nullptr)
{
return false;
}

void* lpFile = LockResource(hFileResource);
if (lpFile == nullptr)
{
return false;
}

std::uint32_t dwSize = SizeofResource(nullptr, hResource);
if (dwSize == 0)
{
return false;
}
wchar_t paths[MAX_UNICODE_PATH];
swprintf_s(paths, L"%s\\%s", path, OutputFileName);
HANDLE hFile = CreateFile(paths, GENERIC_READ | GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
HANDLE hFilemap = CreateFileMapping(hFile, nullptr, PAGE_READWRITE, 0, dwSize, nullptr);
if (hFilemap == nullptr)
{
return false;
}

void* lpBaseAddress = MapViewOfFile(hFilemap, FILE_MAP_WRITE, 0, 0, 0);
if (lpBaseAddress == nullptr)
{
goto skip;
}
CopyMemory(lpBaseAddress, lpFile, dwSize);
UnmapViewOfFile(lpBaseAddress);
skip:
CloseHandle(hFilemap);
CloseHandle(hFile);

return true;
}
catch (...) {}
return false;
}*/
void colectDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
}
void colectDlg::OnBnClickedGen()
{
	prog->ShowWindow(SW_SHOW);
	bool dmpok = false;
	bool evtok = false;
	ULONG ret;
	DWORD errorcode = 0;
	CString drv;
	wchar_t* drive;
	wchar_t date[60] = { L"\0" };
	char zipfilechar[MAX_PATH] = { "\0" };
	bool exported = false;
	char temp[MAX_PATH] = { "\0" };
	GetEnvironmentVariableA("TEMP", temp, MAX_PATH);
	sprintf_s(zipfilechar, "%s\\sample.zip", temp);
	Zipper zip(zipfilechar);
	files = (char*)malloc(1000);
	if (files == nullptr)
	{
		goto end;
	}
	ZeroMemory(files, 1000);
	filest = (wchar_t*)malloc(1000);
	if (filest == nullptr)
	{
		free(files);
		goto end;
	}
	ZeroMemory(filest, 1000);
	wchar_t* windir = (wchar_t*)malloc(MAX_PATH);
	if (windir == nullptr)
	{
		free(files);
		free(filest);
		goto end;
	}
	ZeroMemory(windir, MAX_PATH);
	wchar_t* evtx = (wchar_t*)malloc(MAX_PATH);
	if (evtx == nullptr)
	{
		free(windir);
		free(files);
		free(filest);
		goto end;
	}
	ZeroMemory(evtx, MAX_PATH);
	wchar_t* tempdir = (wchar_t*)malloc(MAX_PATH);
	if (tempdir == nullptr)
	{
		free(files);
		free(filest);
		free(windir);
		free(evtx);
		goto end;
	}
	ZeroMemory(tempdir, MAX_PATH);
	wchar_t* tempdir2 = (wchar_t*)malloc(MAX_PATH);
	if (tempdir2 == nullptr)
	{
		free(files);
		free(filest);
		free(windir);
		free(evtx);
		free(tempdir);
		goto end;
	}
	ZeroMemory(tempdir2, MAX_PATH);
	wchar_t* dmppath = (wchar_t*)malloc(MAX_PATH);
	if (dmppath == nullptr)
	{
		free(files);
		free(filest);
		free(windir);
		free(evtx);
		free(tempdir);
		free(tempdir2);
		goto end;
	}
	ZeroMemory(dmppath, MAX_PATH);
	wchar_t* buffer = (wchar_t*)malloc(MAX_PATH);
	if (buffer == nullptr)
	{
		free(files);
		free(filest);
		free(windir);
		free(evtx);
		free(tempdir);
		free(dmppath);
		free(tempdir2);
		goto end;
	}
	ZeroMemory(buffer, MAX_PATH);
	wchar_t* zipfile = (wchar_t*)malloc(MAX_PATH);
	if (zipfile == nullptr)
	{
		free(files);
		free(filest);
		free(windir);
		free(evtx);
		free(tempdir);
		free(tempdir2);
		free(dmppath);
		free(buffer);
		goto end;
	}
	ZeroMemory(zipfile, MAX_PATH);
	wchar_t* zipfile2 = (wchar_t*)malloc(MAX_PATH);
	if (zipfile2 == nullptr)
	{
		free(files);
		free(filest);
		free(windir);
		free(evtx);
		free(tempdir);
		free(tempdir2);
		free(dmppath);
		free(buffer);
		free(zipfile);
		goto end;
	}
	ZeroMemory(zipfile2, MAX_PATH);
	seldisk->GetLBText(seldisk->GetCurSel(), drv);
	drive = (wchar_t*)drv.GetString();
	GetDateFormatEx(LOCALE_NAME_SYSTEM_DEFAULT, NULL, NULL, L"dd'.'MM'.'yyyy", date, 30, NULL);
	GetEnvironmentVariable(L"TEMP", buffer, (MAX_PATH / 2) - 2);
	swprintf_s(zipfile, (MAX_PATH / 2) - 2, L"%s\\sample.zip", buffer);
	swprintf_s(tempdir, (MAX_PATH / 2) - 2, L"%s\\pchelpcolect", buffer);
	swprintf_s(windir, (MAX_PATH / 2) - 2, L"%sWindows", drive);
	swprintf_s(dmppath, (MAX_PATH / 2) - 2, L"%s\\Minidump", windir);
	GetEnvironmentVariable(L"USERPROFILE", buffer, (MAX_PATH / 2) - 2);
	swprintf_s(zipfile2, (MAX_PATH / 2) - 2, L"%s\\Desktop\\gen_%s.zip", buffer, date);
	ret = GetFileAttributes(windir);
	prog->SetPos(10);
	errorcode = GetLastError();
	if (!wcscmp(drive, L"X:\\") && winpe == true)
	{
		wchar_t buftext[500] = { L"\0" };
		swprintf_s(buftext, L"Nemůžeš nic extrahovat z Win PE!!");
		MessageBox(buftext, L"ERROR!!", MB_OK | MB_ICONERROR | MB_APPLMODAL);
		free(files);
		free(filest);
		free(windir);
		free(evtx);
		free(tempdir);
		free(tempdir2);
		free(buffer);
		free(dmppath);
		free(zipfile);
		free(zipfile2);
		goto end;
	}
	if (ret != FILE_ATTRIBUTE_DIRECTORY && ret == INVALID_FILE_ATTRIBUTES)
	{
		free(files);
		free(filest);
		free(windir);
		free(evtx);
		free(tempdir);
		free(tempdir2);
		free(buffer);
		free(dmppath);
		free(zipfile);
		free(zipfile2);
		wchar_t buftext[200] = { L"\0" };
		swprintf_s(buftext, L"Nebyla nalezena Žádná instalace Windows na disku %s", drive);
		MessageBox(buftext, L"ERROR!!", MB_OK | MB_ICONERROR | MB_APPLMODAL);
		zip.close();
		goto end;
	}
	else if (ret == FILE_ATTRIBUTE_DIRECTORY)
	{
		goto continu;
	}
	else
	{
		free(files);
		free(filest);
		free(windir);
		free(evtx);
		free(tempdir);
		free(tempdir2);
		free(buffer);
		free(dmppath);
		free(zipfile);
		free(zipfile2);
		zip.close();
		wchar_t buftext[200] = { L"\0" };
		swprintf_s(buftext, L"Neznáma chyba\nerrorcode=%lu", errorcode);
		MessageBox(buftext, L"ERROR!!", MB_OK | MB_ICONERROR | MB_APPLMODAL);
		goto end;
	}
continu:;
	prog->SetPos(20);
	ret = GetFileAttributes(dmppath);
	if (ret == FILE_ATTRIBUTE_DIRECTORY)
	{
		dmpok = true;
		ret = CreateDirectory(tempdir, NULL);
		errorcode = GetLastError();
		if (ret != 0)
		{
			goto next;
		}
		else if (ret == 0)
		{
			if (errorcode == ERROR_ALREADY_EXISTS)
			{
				GetFiles(tempdir, L"*.*", filest, 1000, filesizet, fileslent, filespointert, &countFilest);
				CopyDelete(tempdir, filest, filespointert, countFilest, 1);
				goto next;
			}
			else if (errorcode == ERROR_PATH_NOT_FOUND)
			{
				free(files);
				free(filest);
				free(windir);
				free(evtx);
				free(tempdir);
				free(tempdir2);
				free(dmppath);
				free(buffer);
				free(zipfile);
				free(zipfile2);
				wchar_t buftext[500] = { L"\0" };
				swprintf_s(buftext, L"Nelze vytvořit složku ve složce %s", tempdir);
				MessageBox(buftext, L"ERROR!!", MB_OK | MB_ICONERROR | MB_APPLMODAL);
				zip.close();
				goto end;
			}
		}
	}
	else
	{
		dmpok = false;
		wchar_t buftext[200] = { L"\0" };
		swprintf_s(buftext, L"Nebyly nalazeny žádné Minidumpy");
		MessageBox(buftext, L"INFO", MB_OK | MB_ICONINFORMATION | MB_APPLMODAL);
		goto next;
	}
next:;
	if (!wcscmp(drive, L"C:\\") && winpe == false)
	{
		wchar_t logtmp[MAX_PATH] = { L"\0" };
		swprintf_s(logtmp, L"%s\\System.evtx", tempdir);
		ret = EvtExportLog(NULL, L"System", NULL, logtmp, EvtExportLogChannelPath);
		if (ret == 0)
		{
			errorcode = GetLastError();
			wchar_t buftext[200] = { L"\0" };
			swprintf_s(buftext, L"Nelze zkopírovat System.evtx!!\nerrorcode=%lu", errorcode);
			MessageBox(buftext, L"INFO!!", MB_OK | MB_ICONINFORMATION | MB_APPLMODAL);
		}
		else
		{
			evtok = true;
			exported = true;
		}
	}
	else
	{
		
		size_t converted = 0;
		wchar_t logtmp[MAX_PATH] = { L"\0" };
		wchar_t evt[MAX_PATH] = { L"\0" };
		swprintf_s(evt, L"%sWindows\\System32\\winevt\\Logs\\System.evtx", drive);
		swprintf_s(logtmp, L"%s\\System.evtx", tempdir);
		//swprintf_s(logpath, L"%s",logdir);
		ret = EvtExportLog(NULL, evt, NULL, logtmp, EvtExportLogFilePath);
		if (ret == 0)
		{
			errorcode = GetLastError();
			wchar_t buftext[200] = { L"\0" };
			swprintf_s(buftext, L"Nelze zkopírovat System.evtx!!\nerrorcode=%lu", errorcode);
			MessageBox(buftext, L"INFO!!", MB_OK | MB_ICONINFORMATION | MB_APPLMODAL);
		}
		else
		{
			evtok = true;
			exported = true;
		}

	}
	
	prog->SetPos(30);
	GetFiles(dmppath, L"*.dmp", filest, 1000, filesizet, fileslent, filespointert, &countFilest);
	if (!evtok && !dmpok && countFilest == 0)
	{
		free(files);
		free(filest);
		free(windir);
		free(evtx);
		free(tempdir);
		free(tempdir2);
		free(dmppath);
		free(buffer);
		free(zipfile);
		free(zipfile2);
		wchar_t buftext[200] = { L"\0" };
		swprintf_s(buftext, L"Nebyly nalazeny minidumpy a nelze zkopírovat System.evtx,\nproto se nevytvoří žádný soubor .zip");
		MessageBox(buftext, L"ERROR!!", MB_OK | MB_ICONERROR | MB_APPLMODAL);
		goto end;
	}
	if (exported)
	{
		wchar_t buf[MAX_PATH] = { L"\0" };
		swprintf_s(buf, L"%s\\System.evtx", tempdir);
		ifstream filein(buf, ios::binary);
		if (filein.is_open())
		{
			zip.add(filein, "Events/System.evtx");
			//ZipFile::AddFile(convert, tests, "Events/System.evtx");
			filein.close();
		}
	}
	prog->SetPos(50);
	for (ULONG i = 0; i < countFilest; i++)
	{
		if (countFilest <= 8)
		{
			prog->SetPos(prog->GetPos()+5);
		}
		else
		{
			prog->SetPos(prog->GetPos() + 2);
		}
		wchar_t file[MAX_PATH] = { L"\0" };
		char destfile[MAX_PATH] = { "\0" };
		swprintf_s(file, L"%s\\%s", dmppath, filespointert[i]);
		sprintf_s(destfile, "MiniDumps/%ws", filespointert[i]);
		if (filesizet[i] > 0)
		{
			ifstream filein(file, ios::binary);
			if(filein.is_open())
			{ 
				zip.add(filein, destfile);
				//ZipFile::AddFile(convert, file, destfile);
				filein.close();
			}
		}
	}
	zip.close();
	CopyFile(zipfile,zipfile2,false);
	prog->SetPos(90);
	//errorcode = GetLastError();
	GetFiles(tempdir, L"*.*", filest, 1000, filesizet, fileslent, filespointert, &countFilest);
	CopyDelete(tempdir, filest, filespointert, countFilest, 1);
	prog->SetPos(100);
	DeleteFileA(zipfilechar);
	free(files);
	free(filest);
	free(windir);
	free(evtx);
	free(tempdir);
	free(tempdir2);
	free(dmppath);
	free(buffer);
	free(zipfile);
	free(zipfile2);
	prog->ShowWindow(SW_HIDE);
	wchar_t buftext[200];
	swprintf_s(buftext, L"Na ploše se úspěšně vytvořil gen_%s.zip.\nTento soubor stačí přidat do příspěvku v sekci BSOD na fóru pc-help.cz", date);
	MessageBox(buftext, L"INFO!!", MB_OK | MB_ICONINFORMATION | MB_APPLMODAL);
	end:
	Sleep(1);
}

void colectDlg::OnBnClickedCancel()
{
	CDialogEx::OnDestroy();
	CDialogEx::OnCancel();
}
void colectDlg::GetDrives()
{
	seldisk->ResetContent();
	wchar_t drivenames[300] = { L'\0' };
	DWORD drives = 0;
	drives = GetLogicalDriveStringsW(sizeof(drivenames) / 2, drivenames);
	ULONG count = drives / 4;
	wchar_t* ptr[50] = { nullptr };
	ULONG p = 0;
	for (ULONG i = 0; i < count; i++)
	{
		ptr[i] = &drivenames[p];
		p = p + 4;
	}
	for (ULONG i = 0; i < count; i++)
	{
		UINT type = GetDriveType(ptr[i]);
		if (type != DRIVE_UNKNOWN && type != DRIVE_NO_ROOT_DIR && type != DRIVE_REMOTE && type != DRIVE_CDROM && type != DRIVE_RAMDISK)
		{
			seldisk->AddString(ptr[i]);
		}
	}
	unsigned int cdrive = seldisk->GetCount();
	unsigned int sel = 0;
	for (unsigned int i = 0; i < count; i++)
	{
		wchar_t buf[20] = { L"\0" };
		seldisk->GetLBText(i, buf);
		if (!wcscmp(buf, L"C:\\"))
		{
			sel = i;
		}
	}
	seldisk->SetCurSel(sel);
}