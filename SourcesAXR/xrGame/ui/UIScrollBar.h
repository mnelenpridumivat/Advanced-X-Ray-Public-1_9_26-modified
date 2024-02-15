#pragma once
#include "uiwindow.h"

class CUI3tButton;
class CUIScrollBox;
class CUIFrameLineWnd;

class CUIScrollBar :
	public CUIWindow,
	public IMetaClass
{
	DECLARE_METACLASS1(CUIScrollBar, CUIWindow)
private:
	typedef CUIWindow inherited;
protected:

	CUI3tButton*	m_DecButton;
	CUI3tButton*	m_IncButton;
	CUIScrollBox*	m_ScrollBox;
	CUIFrameLineWnd* m_FrameBackground;

	float			m_hold_delay;
	int				m_iScrollPos;

	int				m_iStepSize;

	int				m_iMinPos;
	int				m_iMaxPos;

	int				m_iPageSize;

	int				m_ScrollWorkArea;
	bool			m_b_enabled;
	bool			m_bIsHorizontal;

	int				m_mouse_state;

	bool			ScrollInc			(bool by_scrollbox=false);
	bool			ScrollDec			(bool by_scrollbox=false);
	virtual void	UpdateScrollBar		();

	u32				ScrollSize			(){return _max( 1, m_iMaxPos - m_iMinPos - m_iPageSize + 1 );}
	virtual void	ClampByViewRect		();
	virtual void	SetPosScrollFromView(float view_pos, float view_width, float view_offs);
	int				PosViewFromScroll	(int view_size, int view_offs);
	void			SetScrollPosClamped	(int iPos);

	bool			IsRelevant			();
public:
					CUIScrollBar		();

			void	SetEnabled			(bool b)			{m_b_enabled = b;if(!m_b_enabled)Show(m_b_enabled);}
			bool	GetEnabled			()					{return m_b_enabled;}
	void	Show				(bool b) override;
	void	Enable				(bool b) override;
	virtual	void	InitScrollBar		(Fvector2 pos, float length, bool bIsHorizontal, LPCSTR profile = "default");

	void	SendMessage			(CUIWindow *pWnd, s16 msg, void *pData) override;
	bool	OnMouseAction				(float x, float y, EUIMessages mouse_action) override;
	bool 	OnMouseDown			(int mouse_btn) override;
	virtual	bool	OnMouseDownEx		();
	void	OnMouseUp			(int mouse_btn) override;
	bool	OnKeyboardHold		(int dik) override;

	void	Draw				() override;

	void	SetWidth			(float width) override;
	void	SetHeight			(float height) override;

	void	Reset				() override;
	void			Refresh				();
	void			SetStepSize			(int step);
	IC int			GetStepSize			() { return m_iStepSize; }
	void 			SetRange			(int iMin, int iMax);
	void 			GetRange			(int& iMin, int& iMax) {iMin = m_iMinPos;  iMax = m_iMaxPos;}
	int 			GetMaxRange			() {return m_iMaxPos;}
	int 			GetMinRange			() {return m_iMinPos;}

	void			SetPageSize			(int iPage) { m_iPageSize = _max(0,iPage); UpdateScrollBar();}
	int				GetPageSize			() {return m_iPageSize;}

	void			SetScrollPos		(int iPos) { SetScrollPosClamped(iPos); UpdateScrollBar();}
	int				GetScrollPos		() {return _max(m_iMinPos,m_iScrollPos);}
	
	void			TryScrollInc		(bool by_scrollbox=false);
	void			TryScrollDec		(bool by_scrollbox=false);
};
