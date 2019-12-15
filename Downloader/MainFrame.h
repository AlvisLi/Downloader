#pragma once

#include <thread>
#include <memory>

class MainFrame : public DirectUI::CWindowUI
{
public:
	MainFrame();
	~MainFrame();
	MainFrame(MainFrame const &) = delete;
	void operator=(MainFrame const&) = delete;

// public:
// 	static MainFrame& GetInstance()  //c++11实现单例模式
// 	{
// 		static MainFrame intance;
// 		return intance;
// 	}

public:
	
	virtual DirectUI::CUIString GetSkinFolder();
	virtual DirectUI::CUIString GetSkinFile();
	virtual LPCTSTR   GetWindowClassName() const;
	virtual void      Notify(DirectUI::TNotifyUI& msg);
	virtual LRESULT   ResponseDefaultKeyEvent(WPARAM wParam);
	virtual CControlUI* CreateControl(LPCTSTR pstrClass);

	virtual LRESULT HandleMessage(UINT message, WPARAM wParam, LPARAM lParam);
	virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	virtual LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	virtual void InitWindow();
	virtual void OnFinalMessage(HWND hWnd);

	void RefreshDownloadItemList();
	
protected:
	//CEditUI* _pUrlUI = nullptr;
	CUIString _url;
	CButtonUI* _pMaxUI = nullptr;
	CButtonUI* _pRestoreUI = nullptr;
	CTabLayoutUI* _pTabUI = nullptr;
	CGifAnimUI* _pGifUI = nullptr;
	//WkeUI* _pWkeUI = nullptr;

	CListUI* m_listDownloadItem = nullptr;
};

