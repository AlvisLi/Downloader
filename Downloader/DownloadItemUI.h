#pragma once

class DownloadItemUI : public CContainerUI, public DirectUI::IDialogBuilderCallback
{
public:
	DownloadItemUI(DirectUI::CPaintManagerUI* pPaintManager);

public:
	typedef enum enumDownloadAppStatus
	{
		DownloadApp_Ready,
		DownloadApp_In_Progress,
		DownloadApp_Complete
	}DownloadAppStatus;

	void	SetAppName(std::string strName);
	std::string	GetAppName();
	void	SetStatus(DownloadAppStatus status);
	void	SetDownloadSpeed(double dValue);
	void	SetProgress(int progress);
	void	RefreshAppSizeByName(std::string strName);

protected:
	virtual DirectUI::CControlUI* CreateControl(LPCTSTR pstrClass);

	typedef bool (DownloadItemUI::*PFunctionNotify)(LPVOID);
	void AddNotify(LPCTSTR name, PFunctionNotify pNotify);

	bool Notify(LPVOID pParam);

	void DeleteAppByName(std::string strName);
	void OpenAppFolderByName(std::string strName);
	bool CheckIfExistFile(std::wstring strFullPathW);

private:
	std::string m_strAppName;

	CLabelUI* m_pLabelAppLogoUI = nullptr;
	CLabelUI* m_pLabelAppNameUI = nullptr;
	CLabelUI* m_pLabelAppSizeUI = nullptr;
	// 下载速度
	CLabelUI* m_pLabelAppDownloadSpeedUI = nullptr;
	// 下载完成百分比
	CLabelUI* m_pLabelAppDownloadProgressPercentUI = nullptr;
	// 下载进度条
	CSliderUI* m_pSliderDownloadAppUI = nullptr;
	CVerticalLayoutUI* m_pVoxDownloadInProgressUI = nullptr;
	CVerticalLayoutUI* m_pVoxDownloadCompleteUI = nullptr;

	DownloadAppStatus m_enumDownloadAppStatus = DownloadApp_Ready;
};

