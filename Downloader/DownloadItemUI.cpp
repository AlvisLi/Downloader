#include "stdafx.h"
//#include "../data/ITDataDef.h"
//#include "../data/ITDownloadUserData.h"
//#include "../common/strconv2.h"
#include "DownloadItemUI.h"
//#include "../core/FileHandle.h"
#include <ShlObj.h>
#include <shellapi.h>
#include <vector>

//////////////////////////////////////////////////////////////////////////
DownloadItemUI::DownloadItemUI(DirectUI::CPaintManagerUI* pPaintManager)
{
	DirectUI::CDialogBuilder builder;
	DirectUI::CContainerUI* pRootUI = static_cast<DirectUI::CContainerUI*>(builder.Create(_T("DownloadItem.xml"), 0, this, pPaintManager));
	if (NULL == pRootUI)
	{
		MessageBox(nullptr, _T("º”‘ÿ∆§∑Ù ß∞‹"), _T("DownloadItem.xml"), MB_OK);
		ExitProcess(1);
	}

	Add(pRootUI);
	SetFixedWidth(380);
	SetFixedHeight(60);

	m_pLabelAppLogoUI = static_cast<CLabelUI*>(FindSubControl(_T("app_single_logo")));
	m_pLabelAppNameUI = static_cast<CLabelUI*>(FindSubControl(_T("app_single_name")));
	m_pLabelAppSizeUI = static_cast<CLabelUI*>(FindSubControl(_T("app_single_size")));

	m_pLabelAppDownloadSpeedUI = static_cast<CLabelUI*>(FindSubControl(_T("app_signle_download_speed")));
	m_pLabelAppDownloadProgressPercentUI = static_cast<CLabelUI*>(FindSubControl(_T("app_signle_download_progress_percent")));

	m_pSliderDownloadAppUI = static_cast<CSliderUI*>(FindSubControl(_T("app_single_download_slider")));

	m_pVoxDownloadInProgressUI = static_cast<CVerticalLayoutUI*>(FindSubControl(_T("app_single_download_inprogress")));
	m_pVoxDownloadCompleteUI = static_cast<CVerticalLayoutUI*>(FindSubControl(_T("app_single_download_complete")));

	AddNotify(_T("btn_app_delete"), &DownloadItemUI::Notify);
	AddNotify(_T("btn_app_opend_folder"), &DownloadItemUI::Notify);
}


void DownloadItemUI::AddNotify(LPCTSTR name, PFunctionNotify pNotify)
{
	CControlUI * pControl = FindSubControl(name);
	if (pControl)
	{
		pControl->OnNotify += MakeDelegate(this, pNotify);
	}
}

bool DownloadItemUI::Notify(LPVOID pParam)
{
	TNotifyUI* pNotify = static_cast<TNotifyUI*>(pParam);
	if (pNotify != nullptr)
	{
		CUIString controlName = pNotify->pSender->GetName();
		CUIString notifyType = pNotify->sType;

		if (notifyType == DUI_MSGTYPE_CLICK)
		{
			if (controlName == _T("btn_app_delete"))
			{
				DeleteAppByName(m_strAppName);
			}
			else if (controlName == _T("btn_app_opend_folder"))
			{
				OpenAppFolderByName(m_strAppName);
			}
		}
	}

	return true;
}

DirectUI::CControlUI* DownloadItemUI::CreateControl(LPCTSTR pstrClass)
{
	return nullptr;
}

void DownloadItemUI::DeleteAppByName(std::string strName)
{
	//std::map<std::string, ITDownloadAppPtr> mapApps = ITDOWNLOADUSERDATA().m_mapDownloadAppsMap;
	//auto iter = mapApps.find(m_strAppName);
	//if (iter != mapApps.end())
	//{
	//	// …æ≥˝logo
	//	std::string strLogoPath = (*iter).second->logoLocalPath;
	//	DeleteFileA(strLogoPath.c_str());

	//	std::string strFullPath = (*iter).second->appLocalPath;
	//	std::vector<std::string> paths = strconv::split(strFullPath, "\\");
	//	std::string downloadFolder = strFullPath;
	//	std::string downloadFolderNew;
	//	downloadFolderNew = downloadFolder.substr(0, downloadFolder.size() - paths.at(paths.size() - 1).size());

	//	ITDOWNLOADUSERDATA().DeleteDownloadAppInfoByName(m_strAppName);
	//	if (::PathIsDirectoryA(downloadFolderNew.c_str()))
	//	{
	//		std::string* item = new std::string();
	//		item->append(downloadFolderNew);
	//		PostMessage(SoftwareLibraryApp::Instance().GetMainFrame(), ITSOFTWARE_LIBRARY_MESSAGE_DELETE_FOLDER_BY_TIMER, (WPARAM)(item), 0);
	//		//FileHandle::removeDir(downloadFolderNew.c_str());
	//	}

	//	PostMessage(SoftwareLibraryApp::Instance().GetMainFrame(), ITSOFTWARE_LIBRARY_MESSAGE_DOWNLOAD_APP_REFRESH_LIST, 0, 0);
	//}
}

void DownloadItemUI::OpenAppFolderByName(std::string strName)
{
	//std::map<std::string, ITDownloadAppPtr> mapApps = ITDOWNLOADUSERDATA().m_mapDownloadAppsMap;
	//auto iter = mapApps.find(m_strAppName);
	//if (iter != mapApps.end())
	//{
	//	std::string strFullPath = (*iter).second->appLocalPath;
	//	std::wstring strFullPathW = strconv::a2w(strFullPath);
	//	//if (CheckIfExistFile(strFullPathW))
	//	{
	//		ITEMIDLIST *pidl = ILCreateFromPath(strFullPathW.c_str());
	//		if (pidl)
	//		{
	//			SHOpenFolderAndSelectItems(pidl, 0, 0, 0);
	//			ILFree(pidl);
	//		}
	//		else
	//		{
	//			TCHAR param[_MAX_PATH + 64] = { 0 };
	//			_tcscat(param, _T("/select, "));
	//			_tcscat(param, /*"C:\\Windows\\regedit.exe"*/strFullPathW.c_str());
	//			ShellExecute(NULL, _T("open"), _T("explorer.exe"), param, NULL, SW_SHOWNORMAL);
	//		}
	//	}
	//}
}

bool DownloadItemUI::CheckIfExistFile(std::wstring strFullPathW)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	hFind = FindFirstFile(strFullPathW.c_str(), &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE) 
	{
		return false;
	}
	else 
	{
		FindClose(hFind);
		return true;
	}
}

void DownloadItemUI::SetAppName(std::string strName)
{
	m_strAppName = strName;

	//std::map<std::string, ITDownloadAppPtr> mapApps = ITDOWNLOADUSERDATA().m_mapDownloadAppsMap;
	//auto iter = mapApps.find(m_strAppName);
	//if (iter != mapApps.end())
	//{
	//	ITDownloadAppPtr appInfo = (*iter).second;

	//	if (m_pLabelAppNameUI != nullptr)
	//	{
	//		m_pLabelAppNameUI->SetText(strconv::a2w(m_strAppName).c_str());
	//		m_pLabelAppNameUI->SetToolTip(strconv::a2w(m_strAppName).c_str());
	//	}

	//	if (appInfo != nullptr && m_pLabelAppLogoUI != nullptr)
	//	{
	//		m_pLabelAppLogoUI->SetEnabled(true);
	//		std::string strFlag = "file= '";
	//		strFlag.append(appInfo->logoLocalPath);
	//		strFlag.append("' dest = '0,0,48,48'  corner = '10,10,10,10'");
	//		m_pLabelAppLogoUI->SetAttribute(L"bkimage", strconv::a2w(strFlag).c_str());
	//		//m_pLabelAppLogoUI->SetBkImage(strconv::a2w(appInfo->logoLocalPath).c_str());
	//	}

	//	HANDLE handle = CreateFile(strconv::a2w(appInfo->appLocalPath).c_str(), FILE_READ_EA,
	//		FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
	//	if (handle != INVALID_HANDLE_VALUE)
	//	{
	//		double size = (double)GetFileSize(handle, NULL);
	//		CloseHandle(handle);

	//		CUIString strSize;
	//		double dSize = size;
	//		dSize = size / (double)1024;
	//		if ((dSize / (double)1024) / (double)1024 > 1)
	//		{
	//			strSize.Format(_T("%.2fG"), (dSize / (double)1024) / (double)1024);
	//		}
	//		else
	//		if (dSize / (double)1024 > 1)
	//		{
	//			strSize.Format(_T("%.2fMB"), dSize / (double)1024);
	//		}
	//		else
	//		{
	//			strSize.Format(_T("%.2fKB"), dSize);
	//		}

	//		m_pLabelAppSizeUI->SetText(strSize);
	//	}

	//	if (access(appInfo->logoLocalPath.c_str(), 0))
	//	{
	//		if (m_pLabelAppLogoUI != nullptr)
	//		{
	//			m_pLabelAppLogoUI->SetEnabled(false);

	//			std::string strPath = SoftwareLibraryPath::GetAppPathA();
	//			strPath.append("skin\\manager_app_single\\logo_default.png");
	//			m_pLabelAppLogoUI->SetAttribute(L"bkimage", strconv::a2w(strPath).c_str());
	//		}
	//	}
	//}
}

std::string DownloadItemUI::GetAppName()
{
	return m_strAppName;
}

void DownloadItemUI::SetStatus(DownloadAppStatus status)
{
	m_enumDownloadAppStatus = status;
	
	switch (m_enumDownloadAppStatus)
	{
	case DownloadApp_Ready:
	{
		if (m_pVoxDownloadInProgressUI != nullptr && m_pVoxDownloadCompleteUI != nullptr)
		{
			m_pVoxDownloadInProgressUI->SetVisible(true);
			m_pVoxDownloadCompleteUI->SetVisible(false);
		}
	}
	break;

	case DownloadApp_In_Progress:
	{
		if (m_pVoxDownloadInProgressUI != nullptr && m_pVoxDownloadCompleteUI != nullptr)
		{
			m_pVoxDownloadInProgressUI->SetVisible(true);
			m_pVoxDownloadCompleteUI->SetVisible(false);
		}
	}
	break;

	case DownloadApp_Complete:
	{
		if (m_pVoxDownloadInProgressUI != nullptr && m_pVoxDownloadCompleteUI != nullptr)
		{
			if (m_pLabelAppDownloadSpeedUI != nullptr)
			{
				m_pLabelAppDownloadSpeedUI->SetText(L"0.00KB/s");
			}

			if (m_pLabelAppDownloadProgressPercentUI != nullptr)
			{
				m_pLabelAppDownloadProgressPercentUI->SetText(L"0%");
			}

			if (m_pSliderDownloadAppUI != nullptr)
			{
				m_pSliderDownloadAppUI->SetValue(0);
			}

			m_pVoxDownloadInProgressUI->SetVisible(false);
			m_pVoxDownloadCompleteUI->SetVisible(true);
		}
		break;
	}

	default:
		break;
	}
}

void DownloadItemUI::SetDownloadSpeed(double dValue)
{
	CUIString strSpeed;
	dValue = dValue / 1024;
	if (dValue / 1024 > 1)
	{
		strSpeed.Format(_T("%.2fMB/s"), dValue / 1024);
	}
	else
	{
		strSpeed.Format(_T("%.0fKB/s"), dValue);
	}

	if (m_pLabelAppDownloadSpeedUI != nullptr)
	{
		m_pLabelAppDownloadSpeedUI->SetText(strSpeed);
	}
}

void DownloadItemUI::SetProgress(int progress)
{
	/*int proApp = progress;
	if (proApp < 0)
	{
		proApp = 0;
	}
	else if (proApp > 100)
	{
		proApp = 100;
	}

	if (m_pSliderDownloadAppUI != nullptr)
	{
		m_pSliderDownloadAppUI->SetValue(proApp);
	}

	if (m_pLabelAppDownloadProgressPercentUI != nullptr)
	{
		std::string strPro = std::to_string(proApp);
		strPro.append("%");
		m_pLabelAppDownloadProgressPercentUI->SetText(strconv::a2w(strPro).c_str());
	}

	RefreshAppSizeByName(m_strAppName);*/
}

void DownloadItemUI::RefreshAppSizeByName(std::string strName)
{
	/*std::map<std::string, ITDownloadAppPtr> mapApps = ITDOWNLOADUSERDATA().m_mapDownloadAppsMap;
	auto iter = mapApps.find(m_strAppName);
	if (iter != mapApps.end())
	{
		HANDLE handle = CreateFile(strconv::a2w((*iter).second->appLocalPath).c_str(), FILE_READ_EA,
			FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
		if (handle != INVALID_HANDLE_VALUE)
		{
			double size = (double)GetFileSize(handle, NULL);
			CloseHandle(handle);

			CUIString strSize;
			double dSize = size;
			dSize = size / (double)1024;
			if ((dSize / (double)1024) / (double)1024 > 1)
			{
				strSize.Format(_T("%.2fG"), (dSize / (double)1024) / (double)1024);
			}
			else
				if (dSize / (double)1024 > 1)
				{
					strSize.Format(_T("%.2fMB"), dSize / (double)1024);
				}
				else
				{
					strSize.Format(_T("%.2fKB"), dSize);
				}

			m_pLabelAppSizeUI->SetText(strSize);
		}
	}*/
}