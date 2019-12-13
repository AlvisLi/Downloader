#include "stdafx.h"
#include "MainFrame.h"
//#include "common/strconv.h"

//////////////////////////////////////////////////////////////////////////
MainFrame::MainFrame()
{
	CreateDuiWindow(nullptr, _T("ÏÂÔØÆ÷"), UI_WNDSTYLE_FRAME, 0);
	assert(IsWindow(GetHWND()));
}

MainFrame::~MainFrame()
{
}

DirectUI::CUIString MainFrame::GetSkinFolder()
{
	return _T("");
}

DirectUI::CUIString MainFrame::GetSkinFile()
{
	return _T("MainFrame.xml");
}

LPCTSTR MainFrame::GetWindowClassName() const
{
	return _T("MainFrameUI");
}

void MainFrame::Notify(DirectUI::TNotifyUI& msg)
{
	DirectUI::CUIString controlName = msg.pSender->GetName();
	DirectUI::CUIString notifyType = msg.sType;

	if (notifyType == DUI_MSGTYPE_CLICK)
	{
		if (controlName == _T("btn_close"))
		{
			Close(1);
		}
		else if (controlName == _T("btn_minimize"))
		{
			::PostMessage(GetHWND(), WM_SYSCOMMAND, SC_MINIMIZE, 0);
		}
		else if (controlName == _T("btn_maximize"))
		{
			::PostMessage(GetHWND(), WM_SYSCOMMAND, SC_MAXIMIZE, 0);
			if (_pMaxUI)
				_pMaxUI->SetVisible(false);
			if (_pRestoreUI)
				_pRestoreUI->SetVisible(true);

		}
		else if (controlName == _T("btn_restore"))
		{
			::PostMessage(GetHWND(), WM_SYSCOMMAND, SC_RESTORE, 0);
			if (_pMaxUI)
				_pMaxUI->SetVisible(true);
			if (_pRestoreUI)
				_pRestoreUI->SetVisible(false);
		}
	}
}

LRESULT MainFrame::ResponseDefaultKeyEvent(WPARAM wParam)
{
	if (wParam == VK_ESCAPE)
	{
		Close(1);
	}

	return __super::ResponseDefaultKeyEvent(wParam);
}


LRESULT MainFrame::HandleMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_SYSCOMMAND:
	{
		auto result = __super::HandleMessage(message, wParam, lParam);
		

		if (wParam & SC_RESTORE)
		{
			if (IsMaximized(GetHWND()))
			{
				if (_pMaxUI->IsVisible())
				{
					if (_pMaxUI)
						_pMaxUI->SetVisible(false);
					if (_pRestoreUI)
						_pRestoreUI->SetVisible(true);
				}

			}
			else
			{
				if (_pRestoreUI->IsVisible())
				{
					if (_pMaxUI)
						_pMaxUI->SetVisible(true);
					if (_pRestoreUI)
						_pRestoreUI->SetVisible(false);
				}
			}
		}

		

		return result;
	}
	break;

	default:
		break;
	}
	
	
	return __super::HandleMessage(message, wParam, lParam);
}


LRESULT MainFrame::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	
	if (uMsg == WM_IME_STARTCOMPOSITION  )
	{
		HIMC hImc = ImmGetContext(m_hWnd);

		bHandled = TRUE;
		return 0;
	}

	bHandled = FALSE;
	return 0;
}

LRESULT MainFrame::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	switch (uMsg)
	{

	default:
		break;
	}

	return __super::MessageHandler(uMsg, wParam, lParam, bHandled);
}

void MainFrame::InitWindow()
{
	CenterWindow();

	_pTabUI = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("ui_tab")));
	_pMaxUI = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_maximize")));
	_pRestoreUI = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_restore")));
	_pGifUI = static_cast<CGifAnimUI*>(m_PaintManager.FindControl(_T("ui_gif")));
}

void MainFrame::OnFinalMessage(HWND hWnd)
{
	PostQuitMessage(0);
}

CControlUI* MainFrame::CreateControl(LPCTSTR pstrClass)
{
	return nullptr;
}