#pragma once

#include "uiwindow.h"
#include "../UIDialogHolder.h"
class CDialogHolder;

class CUIDialogWnd : 
	public CUIWindow,
	public IMetaClass
{
	DECLARE_METACLASS1(CUIDialogWnd, CUIWindow)
private:
	typedef CUIWindow inherited;
	CDialogHolder*					m_pParentHolder;
protected:
public:
	bool										m_bWorkInPause;
				CUIDialogWnd					();
	~CUIDialogWnd					() override;

	void Show							(bool status) override;

	bool OnKeyboardAction						(int dik, EUIMessages keyboard_action) override;
	bool OnKeyboardHold					(int dik) override;

	CDialogHolder* GetHolder					()								{return m_pParentHolder;};
			void SetHolder						(CDialogHolder* h)				{m_pParentHolder = h;};
	virtual bool StopAnyMove					()								{return true;}
	virtual bool NeedCursor						()const							{return true;}
	virtual bool NeedCenterCursor				()const							{return true;}
	virtual bool WorkInPause					()const							{return m_bWorkInPause;}
	virtual bool Dispatch						(int cmd, int param)			{return true;}
			void ShowDialog						(bool bDoHideIndicators);
			void HideDialog						();

	virtual bool IR_process						();
};
