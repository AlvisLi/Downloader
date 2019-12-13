// AppDemo.cpp : 定义应用程序的入口点。
//
#include "stdafx.h"
#include "Downloader.h"
#include "MainFrame.h"

// 此代码模块中包含的函数的前向声明: 
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken = 0;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

	DirectUI::CPaintManagerUI::SetInstance(hInstance);
	DirectUI::CPaintManagerUI::SetResourcePath(DirectUI::CPaintManagerUI::GetInstancePath() + _T("\\skin"));
	MainFrame mainFrame;
	CPaintManagerUI::MessageLoop();

	GdiplusShutdown(gdiplusToken);

	return 0;
}
