#ifndef __UICONTAINER_H__
#define __UICONTAINER_H__

#pragma once

namespace DirectUI {
/////////////////////////////////////////////////////////////////////////////////////
//

class IContainerUI
{
public:
    virtual CControlUI* GetItemAt(int nIndex) const = 0;
    virtual int GetItemIndex(CControlUI* pControl) const  = 0;
    virtual bool SetItemIndex(CControlUI* pControl, int nIndex)  = 0;
    virtual int GetCount() const = 0;
    virtual bool Add(CControlUI* pControl) = 0;
    virtual bool AddAt(CControlUI* pControl, int nIndex)  = 0;
    virtual bool Remove(CControlUI* pControl) = 0;
    virtual bool RemoveAt(int nIndex)  = 0;
    virtual void RemoveAll() = 0;
	virtual void MoveItem(int nSrcIndex, int nDesIndex) = 0;
};


/////////////////////////////////////////////////////////////////////////////////////
//
class CScrollBarUI;

class DirectUI_API CContainerUI : public CControlUI, public IContainerUI
{
public:
    CContainerUI();
    virtual ~CContainerUI();

public:
    LPCTSTR GetClass() const;
    LPVOID GetInterface(LPCTSTR pstrName);

    CControlUI* GetItemAt(int nIndex) const;
    int GetItemIndex(CControlUI* pControl) const;
    bool SetItemIndex(CControlUI* pControl, int nIndex);
    int GetCount() const;
    bool Add(CControlUI* pControl);
    bool AddAt(CControlUI* pControl, int nIndex);
    bool Remove(CControlUI* pControl);
	bool RemoveNotDestroy(CControlUI* pControl); 
    bool RemoveAt(int nIndex);
    void RemoveAll();
	void MoveItem(int nSrcIndex, int nDesIndex);

    void DoEvent(TEventUI& event);
    void SetVisible(bool bVisible = true);
    void SetInternVisible(bool bVisible = true);
    void SetMouseEnabled(bool bEnable = true);

    virtual RECT GetInset() const;
    virtual void SetInset(RECT rcInset); // 设置内边距，相当于设置客户区
    virtual int GetChildPadding() const;
    virtual void SetChildPadding(int iPadding);
    virtual bool IsAutoDestroy() const;
    virtual void SetAutoDestroy(bool bAuto);
    virtual bool IsDelayedDestroy() const;
    virtual void SetDelayedDestroy(bool bDelayed);
    virtual bool IsMouseChildEnabled() const;
    virtual void SetMouseChildEnabled(bool bEnable = true);

    virtual int FindSelectable(int nIndex, bool bForward = true) const;

    void SetPos(RECT rc);
    void DoPaint(HDC hDC, const RECT& rcPaint);

    void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

    void SetManager(CPaintManagerUI* pManager, CControlUI* pParent, bool bInit = true);
    CControlUI* FindControl(FINDCONTROLPROC Proc, LPVOID pData, UINT uFlags);

	bool SetSubControlText(LPCTSTR pstrSubControlName,LPCTSTR pstrText);
	bool SetSubControlFixedHeight(LPCTSTR pstrSubControlName,int cy);
	bool SetSubControlFixedWdith(LPCTSTR pstrSubControlName,int cx);
	bool SetSubControlUserData(LPCTSTR pstrSubControlName,LPCTSTR pstrText);

	CUIString GetSubControlText(LPCTSTR pstrSubControlName);
	int GetSubControlFixedHeight(LPCTSTR pstrSubControlName);
	int GetSubControlFixedWdith(LPCTSTR pstrSubControlName);
	const CUIString GetSubControlUserData(LPCTSTR pstrSubControlName);
	CControlUI* FindSubControl(LPCTSTR pstrSubControlName);

    virtual SIZE GetScrollPos() const;
    virtual SIZE GetScrollRange() const;
    virtual void SetScrollPos(SIZE szPos);
    virtual void LineUp();
    virtual void LineDown();
    virtual void PageUp();
    virtual void PageDown();
    virtual void HomeUp();
    virtual void EndDown();
    virtual void LineLeft();
    virtual void LineRight();
    virtual void PageLeft();
    virtual void PageRight();
    virtual void HomeLeft();
    virtual void EndRight();
    virtual void EnableScrollBar(bool bEnableVertical = true, bool bEnableHorizontal = false);
    virtual CScrollBarUI* GetVerticalScrollBar() const;
    virtual CScrollBarUI* GetHorizontalScrollBar() const;

protected:
    virtual void SetFloatPos(int nIndex);
    virtual void ProcessScrollBar(RECT rc, int cxRequired, int cyRequired);
	        void LoopAllControl(CControlUI* pControl, bool add);
protected:
    CStdPtrArray m_items;
    RECT m_rcInset;
    int m_iChildPadding;
    bool m_bAutoDestroy;
    bool m_bDelayedDestroy;
    bool m_bMouseChildEnabled;
    bool m_bScrollProcess; // 防止SetPos循环调用

    CScrollBarUI* m_pVerticalScrollBar;
    CScrollBarUI* m_pHorizontalScrollBar;
};

} // namespace DirectUI

#endif // __UICONTAINER_H__
