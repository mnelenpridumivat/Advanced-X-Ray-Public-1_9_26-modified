#pragma once

#include "UIStatic.h"
#include "../../xrServerEntities/script_export_space.h"


class CUIButton : public CUIStatic
{
private:
	typedef			CUIStatic				inherited;
public:
					CUIButton				();
	~CUIButton				() override {};

	bool	OnMouseAction					(float x, float y, EUIMessages mouse_action) override;
	virtual void	OnClick					();

	//прорисовка окна
	void	DrawTexture				() override;
	void	DrawText				() override;

	void	Update					() override;
	void	Enable					(bool status) override;
	bool	OnKeyboardAction				(int dik, EUIMessages keyboard_action) override;
	void	OnFocusLost				() override;

	//режимы в которых можно нажимать кнопку
	typedef enum{NORMAL_PRESS, //кнопка нажимается при 
							   //нажатии и отпускании на ней мыши
				 DOWN_PRESS    //сразу при нажатии
			} E_PRESS_MODE;

	//состояния в которых находится кнопка
	typedef enum{BUTTON_NORMAL, //кнопка никак не затрагивается
		BUTTON_PUSHED,			//в нажатом сотоянии
		BUTTON_UP				//при удерживаемой кнопки мыши 
	} E_BUTTON_STATE;


	//заново подготовить состояние
	void	Reset					() override;

	// Установка состояния кнопки: утоплена, не утоплена
	void				SetButtonState			(E_BUTTON_STATE eBtnState)	{ m_eButtonState = eBtnState; }
	E_BUTTON_STATE		GetButtonState			() const					{ return m_eButtonState;}

	// Поведение кнопки как переключателя реализовано пока только в режиме NORMAL_PRESS
	void				SetButtonAsSwitch		(bool bAsSwitch)			{ m_bIsSwitch = bAsSwitch; }

	// Работа с акселератором
	// Код акселератора берется из файла dinput.h, из DirectX SDK.
	// Например: кнопка A - код 0x1E(DIK_A)
	void				SetAccelerator			(int iAccel, int idx);
	const int			GetAccelerator			(int idx) const;
	bool				IsAccelerator			(int iAccel) const;

	void				SetPressMode			(E_PRESS_MODE ePressMode)	{m_ePressMode = ePressMode;}
	E_PRESS_MODE		GetPressMode			()							{return m_ePressMode;}

	void				SetPushOffset			(const Fvector2& offset)	{m_PushOffset = offset;}
	Fvector2			GetPushOffset			()							{return m_PushOffset;}

	shared_str			m_hint_text;
protected:
	
	E_PRESS_MODE		m_ePressMode;
	Fvector2			m_PushOffset;
	E_BUTTON_STATE		m_eButtonState;
	s16					m_uAccelerator[4];
	//bool				m_bButtonClicked;
	bool				m_bIsSwitch;

	DECLARE_SCRIPT_REGISTER_FUNCTION
};