#ifndef __UILABEL_H__
#define __UILABEL_H__

#pragma once

#include <GdiPlus.h>
#pragma comment( lib, "GdiPlus.lib" )
using namespace Gdiplus;
class DirectUI_API Gdiplus::RectF;
struct DirectUI_API Gdiplus::GdiplusStartupInput;

namespace DirectUI
{
	class DirectUI_API CLabelUI : public CControlUI
	{
	public:
		CLabelUI();
		~CLabelUI();

		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);

		void SetTextStyle(UINT uStyle);
		UINT GetTextStyle() const;
		void SetTextColor(DWORD dwTextColor);
		DWORD GetTextColor() const;
		void SetDisabledTextColor(DWORD dwTextColor);
		DWORD GetDisabledTextColor() const;
		void SetFont(int index);
		int GetFont() const;
		RECT GetTextPadding() const;
		void SetTextPadding(RECT rc);
		bool IsShowHtml();
		void SetShowHtml(bool bShowHtml = true);
		bool IsIgnoreCaption();
		void SetIgnoreCaption(bool ignoreCaption);

		SIZE EstimateSize(SIZE szAvailable);
		void DoEvent(TEventUI& event);
		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

		void PaintText(HDC hDC);

		void		SetEnabledEffect(bool _EnabledEffect);
		bool		GetEnabledEffect();
		void		SetText(LPCTSTR pstrText);
		CUIString	GetText() const;
		void		SetTransShadow(int _TransShadow);
		int			GetTransShadow();
		void		SetTransShadow1(int _TransShadow);
		int			GetTransShadow1();
		void		SetTransText(int _TransText);
		int			GetTransText();
		void		SetTransText1(int _TransText);
		int			GetTransText1();
		void		SetTransStroke(int _TransStroke);
		int			GetTransStroke();
		void		SetGradientLength(int _GradientLength);
		int			GetGradientLength();
		void		SetTextRenderingHintAntiAlias(int _TextRenderingHintAntiAlias);
		int			GetTextRenderingHintAntiAlias();
		void		SetShadowOffset(int _offset,int _angle);
		RectF		GetShadowOffset();
		void		SetTextColor1(DWORD _TextColor1);
		DWORD		GetTextColor1();
		void		SetTextShadowColorA(DWORD _TextShadowColorA);
		DWORD		GetTextShadowColorA();
		void		SetTextShadowColorB(DWORD _TextShadowColorB);
		DWORD		GetTextShadowColorB();
		void		SetStrokeColor(DWORD _StrokeColor);
		DWORD		GetStrokeColor();
		void		SetGradientAngle(int _SetGradientAngle);
		int			GetGradientAngle();
		void		SetEnabledStroke(bool _EnabledStroke);
		bool		GetEnabledStroke();
		void		SetEnabledShadow(bool _EnabledShadowe);
		bool		GetEnabledShadow();
		void		SetMemoryData(bool bMemoryData);
		bool		LoadImage(LPCTSTR bitmap, HBITMAP hBitmap, DWORD mask = 0);
		bool		LoadImage(LPCTSTR bitmap, LPBYTE pData, DWORD dwSize, DWORD mask = 0);
	protected:
		DWORD	m_dwTextColor;
		DWORD	m_dwDisabledTextColor;
		int		m_iFont;
		UINT	m_uTextStyle;
		RECT	m_rcTextPadding;
		bool	m_bShowHtml;
		bool	m_bMemoryData;
			
		int						m_hAlign;
		int						m_vAlign;
		int						m_TransShadow;
		int						m_TransShadow1;
		int						m_TransText;
		int						m_TransText1;
		int						m_TransStroke;
		int						m_GradientLength;
		int						m_GradientAngle;
		bool					m_EnableEffect;
		bool					m_EnabledStroke;
		bool					m_EnabledShadow;
		DWORD					m_dwTextColor1;
		DWORD					m_dwTextShadowColorA;
		DWORD					m_dwTextShadowColorB;
		DWORD					m_dwStrokeColor;
		RectF					m_ShadowOffset;
		CUIString				m_TextValue;
		ULONG_PTR				m_gdiplusToken;
		GdiplusStartupInput		m_gdiplusStartupInput;
		TextRenderingHint		m_TextRenderingHintAntiAlias;

		bool                    m_ignoreCaption; 
	};
}

#endif // __UILABEL_H__