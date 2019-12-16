#ifndef __UIFLIP_H__
#define __UIFLIP_H__

#pragma once

#include <vector>

namespace DirectUI
{
	class DirectUI_API CFlipUI : public CContainerUI
	{
	public:
		CFlipUI();
		~CFlipUI();

	public:
		virtual LPCTSTR GetClass() const;
		virtual LPVOID GetInterface(LPCTSTR pstrName);

		void Initialize();
		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

		// 当前页码
		void SetCurrentPageIndex(int iPageIndex);
		int GetCurrentPageIndex() { return _iCurrentPageIndex; };
		// 一次可以展示多少页
		void SetDisplayPageCount(int iPageCount);
		int GetDisplayPageCount() { return _iDisplayPageCount; };
		// 总共有多少页码
		void SetTotalPageCount(int iPageCount);
		int GetTotalPage() { return _iTotalPageCount; };

		// 更新分页控件
		void UpdateShowPageNumbers();

	protected:
		typedef bool (CFlipUI::*PFunctionNotify)(LPVOID);
		void AddNotify(LPCTSTR name, PFunctionNotify pNotify);

		bool Notify(LPVOID pParam);

	protected:
		CHorizontalLayoutUI* _pHorizMain;
		CVerticalLayoutUI* _pVerticalOut;
		CButtonUI* _pBtnPrevPage;
		CButtonUI* _pBtnNextPage;

		CUIString _strPrevPageImage;
		CUIString _strPrevPageHotImage;
		CUIString _strNextPageImage;
		CUIString _strNextPageHotImage;
		CUIString _strNumberSelectedImage;

		// 页码字体大小
		int _iNumberFont;
		// 当前页码,从1开始计数
		int _iCurrentPageIndex;
		// 总共页码数
		int _iTotalPageCount;
		// 一次展示的页数，默认为7，可以修改
		int _iDisplayPageCount;

		// 需要显示的页码控件容器
		std::vector<COptionUI*>* _listShowPageNumbers;
	};
}
#endif // __UIFLIP_H__

