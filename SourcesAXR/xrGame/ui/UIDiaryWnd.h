//=============================================================================
//  Filename:   UIDiaryWnd.h
//	Created by Roman E. Marchenko, vortex@gsc-game.kiev.ua
//	Copyright 2004. GSC Game World
//	---------------------------------------------------------------------------
//  Encyclopedia window
//=============================================================================

#pragma once

#include "UIWindow.h"

#include "../encyclopedia_article_defs.h"

class CEncyclopediaArticle;
class CUIFrameWindow;
class CUIFrameLineWnd;
class CUIListWnd;
class CUIAnimatedStatic;
class CUIStatic;
class CUIListBoxCOP;
class CUIDiaryCore;
class CUIScrollView;
class CUITreeViewItem;

class CUIDiaryWnd: public CUIWindow
{
private:
	typedef CUIWindow inherited;
	enum {eNeedReload=(1<<0),};
	Flags16				m_flags;
public:
						CUIDiaryWnd					();
	~CUIDiaryWnd				() override;

	virtual void		Init						();
	void		Show						(bool status) override;
	void		SendMessage					(CUIWindow *pWnd, s16 msg, void* pData = nullptr) override;
	void		Draw						() override;

	void				AddArticle					(shared_str, bool bReaded);
	void				DeleteArticles				();
	bool				HasArticle					(shared_str);

	void				ReloadArticles				();
	virtual void		ResetAll					();
protected:
	u32					prevArticlesCount;
	// Элементы графического оформления

	CUIFrameLineWnd*	UIBackground;
	CUIFrameLineWnd*	UIDiaryIdxBkg;
	CUIFrameLineWnd*	UIDiaryInfoBkg;
	CUIStatic*			UIDiaryIdxHeader;
	CUIStatic*			UIDiaryInfoHeader;
	CUIAnimatedStatic*	UIAnimation;
	CUIStatic*			UIArticleHeader;

	// Хранилище статей
	typedef xr_vector<CEncyclopediaArticle*> ArticlesDB;
	typedef ArticlesDB::iterator ArticlesDB_it;

	ArticlesDB			m_ArticlesDB;
	CGameFont*			m_pTreeRootFont;
	u32					m_uTreeRootColor;
	CGameFont*			m_pTreeItemFont;
	u32					m_uTreeItemColor;

	CUIListWnd*			UIIdxList;
	CUIScrollView*		UIInfoList;

	void				SetCurrentArtice(CUITreeViewItem *pTVItem);
};
