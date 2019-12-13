#ifndef __UIICON_H__
#define __UIICON_H__

namespace DirectUI {

//////////////////////////////////////////////////////////////////////////  
//  CIconUI  
	class DirectUI_API CIconUI : public CControlUI
	{
	public:
		CIconUI(void);
		~CIconUI(void);

		LPCTSTR GetClass() const;
		LPVOID  GetInterface(LPCTSTR pstrName);
		void    SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

		void    SetPos(RECT rc);
		void    SetInset(RECT rc);
		void    SetVisible(bool bVisible);
		void    SetInternVisible(bool bVisible);
		void    DoPaint(HDC hDC, const RECT& rcPaint);
		void    DoEvent(TEventUI& event);
	private:
		CUIString  m_iconImage;
		RECT       m_insetRect;
	};

} // namespace DirectUI

#endif // __UIICON_H__
