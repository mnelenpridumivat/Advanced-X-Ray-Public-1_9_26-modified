#pragma once

#include "UIEditBox.h"
#include "UIListBox.h"
#include "UIInteractiveBackground.h"
#include "UIOptionsItem.h"

class CUIListBoxItem;

class CUIComboBox : public CUIWindow, public CUIOptionsItem, public pureRender
{
	friend class CUIXmlInit;
	typedef enum{
		LIST_EXPANDED, 
		LIST_FONDED    
	} E_COMBO_STATE;
	
	xr_vector<int>		m_disabled;
public:
						CUIComboBox				();
	~CUIComboBox			() override;
	// CUIOptionsItem
	void	SetCurrentOptValue	() override;	// opt->current
	void	SaveBackUpOptValue	() override;	// current->backup
	void	SaveOptValue		() override;	// current->opt
	void	UndoOptValue		() override;	// backup->current
	bool	IsChangedOptValue	() const override;	// backup!=current

	void	OnRender					() override; // only for list-box

			LPCSTR		GetText					();
			LPCSTR		GetTextOf				(int index);
			void		SetText					(LPCSTR text);

			void		SetListLength			(int length);
			void		SetVertScroll			(bool bVScroll = true){m_list_box.SetFixedScrollBar(bVScroll);};
	CUIListBoxItem*		AddItem_				(LPCSTR str, int _data);
			void		InitComboBox			(Fvector2 pos, float width);
			void		SetItemIDX				(int idx);
			void		SetItemToken			(int tok);

	void		SendMessage				(CUIWindow *pWnd, s16 msg, void* pData = nullptr) override;
	void		OnFocusLost				() override;
	void		OnFocusReceive			() override;
			int			CurrentID				()	{return m_itoken_id;}
			void		disable_id				(int id);
			void		enable_id				(int id);
protected:
	bool		OnMouseAction					(float x, float y, EUIMessages mouse_action) override;
	virtual void		OnBtnClicked			();
			void		ShowList				(bool bShow);
			void		OnListItemSelect		();
	void		Update					() override;
	void		Draw					() override;
			void		ClearList				();

			u32			GetSize					();

protected:
	bool				m_bInited;
	int					m_iListHeight;
	int					m_itoken_id;
	E_COMBO_STATE		m_eState;
	int					m_opt_backup_value;


	CUI_IB_FrameLineWnd	m_frameLine;
	CUITextWnd			m_text;
	CUIFrameWindow		m_list_frame;

	u32					m_textColor[2];
public:
	CUIListBox			m_list_box;
	void				SetTextColor			(u32 color)			{m_textColor[0] = color;};
	void				SetTextColorD			(u32 color)			{m_textColor[1] = color;};

protected:	
	DECLARE_SCRIPT_REGISTER_FUNCTION
};