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

		// ��ǰҳ��
		void SetCurrentPageIndex(int iPageIndex);
		int GetCurrentPageIndex() { return _iCurrentPageIndex; };
		// һ�ο���չʾ����ҳ
		void SetDisplayPageCount(int iPageCount);
		int GetDisplayPageCount() { return _iDisplayPageCount; };
		// �ܹ��ж���ҳ��
		void SetTotalPageCount(int iPageCount);
		int GetTotalPage() { return _iTotalPageCount; };

		// ���·�ҳ�ؼ�
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

		// ҳ�������С
		int _iNumberFont;
		// ��ǰҳ��,��1��ʼ����
		int _iCurrentPageIndex;
		// �ܹ�ҳ����
		int _iTotalPageCount;
		// һ��չʾ��ҳ����Ĭ��Ϊ7�������޸�
		int _iDisplayPageCount;

		// ��Ҫ��ʾ��ҳ��ؼ�����
		std::vector<COptionUI*>* _listShowPageNumbers;
	};
}
#endif // __UIFLIP_H__

