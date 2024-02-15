#ifndef UILISTBOXITEMMSGCHAIN_H_INCLUDED
#define UILISTBOXITEMMSGCHAIN_H_INCLUDED

#include "UIListBoxItem.h"

class CUIListBoxItemMsgChain : 
	public CUIListBoxItem,
	public IMetaClass
{
	DECLARE_METACLASS1(CUIListBoxItemMsgChain, CUIListBoxItem)
	typedef CUIListBoxItem inherited;
public:
					CUIListBoxItemMsgChain	(float height) : CUIListBoxItem(height) {};
	~CUIListBoxItemMsgChain	() override {};

	bool	OnMouseDown				(int mouse_btn) override;
};

#endif //#ifndef UILISTBOXITEMMSGCHAIN_H_INCLUDED