#pragma once

#include "UIScrollView.h"

class CUIListBoxItem;

class CUIListBox : 	
	public CUIScrollView,
	public IMetaClass
{
	DECLARE_METACLASS1(CUIListBox, CUIScrollView)
public:
					CUIListBox						();
	CUIListBoxItem* AddItem							();
	CUIListBoxItem* AddTextItem						(LPCSTR text);
	void			AddExistingItem					(CUIListBoxItem*);

	CUIListBoxItem* GetItemByTAG					(u32 tag_value);
	int				GetIdxByTAG						(u32 tag_value);
	CUIListBoxItem* GetItemByIDX					(int idx);
	CUIListBoxItem* GetItemByText					(LPCSTR text);
	CUIListBoxItem* GetSelectedItem					();

	LPCSTR			GetSelectedText					();
	LPCSTR			GetText							(int idx);
	void			MoveSelectedUp					();
	void			MoveSelectedDown				();
	void			SetSelectionTexture				(LPCSTR texture);
	void			SetItemHeight					(float h);
	float			GetItemHeight					();
	float			GetLongestLength				();

					void	SetSelected						(CUIWindow* w) override {CUIScrollView::SetSelected(w);};
		u32			GetSelectedIDX					();
		void		SetSelectedIDX					(u32 idx);
		void		SetSelectedTAG					(u32 tag_val);
		void		SetSelectedText					(LPCSTR txt);
		void		SetImmediateSelection			(bool f);

					bool		OnMouseAction							(float x, float y, EUIMessages mouse_action) override;
					void		SendMessage						(CUIWindow* pWnd, s16 msg, void* pData = 0) override;

			void			SetTextColor			(u32 color);
			u32				GetTextColor			();
			void			SetFont					(CGameFont* pFont) override;
			CGameFont*		GetFont					();

protected:
	CGameFont*		m_pFont;
	float			m_def_item_height;
	u32				m_text_color;
	shared_str		m_selection_texture;

	bool			m_bImmediateSelection;
	DECLARE_SCRIPT_REGISTER_FUNCTION
};
add_to_type_list(CUIListBox)
#undef script_type_list
#define script_type_list save_type_list(CUIListBox)