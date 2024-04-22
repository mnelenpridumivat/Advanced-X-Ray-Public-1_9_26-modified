#pragma once
#include "UIStatic.h"
#include "UIWndCallback.h"

class CUIGlobalMapSpot;
class CUIMapWnd;

class CUICustomMap : public CUIStatic, public CUIWndCallback
{
protected:	
	shared_str		m_name;

	Frect			m_BoundRect_;// real map size (meters)
	Flags16			m_flags;
	enum EFlags{	eLocked	=(1<<0),};
	float			m_pointer_dist;
	Frect			m_workingArea;
public:
	Frect&			WorkingArea						() {return m_workingArea;}
	Frect			m_prevRect;
	shared_str		m_texture;
	shared_str		m_shader_name;

					CUICustomMap					();
	~CUICustomMap					() override;

	virtual void	SetActivePoint					(const Fvector &vNewPoint);
	
	void			Initialize						(shared_str name, LPCSTR sh_name);
	virtual Fvector2 ConvertRealToLocal				(const Fvector2& src, bool for_drawing);// meters->pixels (relatively own left-top pos)
	Fvector2		ConvertLocalToReal				(const Fvector2& src, Frect const& bound_rect);
	Fvector2		ConvertRealToLocalNoTransform	(const Fvector2& src, Frect const& bound_rect);// meters->pixels (relatively own left-top pos)

	virtual bool	GetPointerTo					(const Fvector2& src, float item_radius, Fvector2& pos, float& heading);//position and heading for drawing pointer to src pos

	void			FitToWidth						(float width);
	void			FitToHeight						(float height);
	Fvector2		GetCurrentZoom					()const					{return Fvector2().set(GetWndRect().height()/BoundRect().height(), GetWndRect().width()/BoundRect().width());}
	const Frect&	BoundRect						()const					{return m_BoundRect_;}
	virtual void	OptimalFit						(const Frect& r);

	const shared_str& MapName						() {return m_name;}
	virtual CUIGlobalMapSpot*	GlobalMapSpot		() {return nullptr;}

	void	Draw							() override;
	void	Update							() override;
	void	SendMessage						(CUIWindow* pWnd, s16 msg, void* pData) override;
	virtual bool	IsRectVisible					(Frect r);
	virtual	bool	NeedShowPointer					(Frect r);
			bool	Locked							()				{return !!m_flags.test(eLocked);}
			void	SetLocked						(bool b)		{m_flags.set(eLocked,b);}
			void	SetPointerDistance				(float d)		{m_pointer_dist=d;};
			float	GetPointerDistance				()				{return m_pointer_dist;};
protected:
	virtual void	Init_internal					(const shared_str& name, CInifile& pLtx, const shared_str& sect_name, LPCSTR sh_name);
	virtual void	UpdateSpots						() {};
};


class CUIGlobalMap: public CUICustomMap
{
	typedef  CUICustomMap inherited;

	shared_str		m_prev_active_map;
	CUIMapWnd*		m_mapWnd;
	float			m_minZoom;
	float			m_max_zoom;
public:
	Fvector2 ConvertRealToLocal		(const Fvector2& src, bool for_drawing) override;// pixels->pixels (relatively own left-top pos)

					CUIGlobalMap			(CUIMapWnd*	pMapWnd);
	~CUIGlobalMap			() override;
	
	IC void			SetMinZoom				(float zoom){m_minZoom=zoom;}
	IC float		GetMinZoom				(){return m_minZoom;}
	IC float		GetMaxZoom				(){return m_max_zoom;}
	IC void			SetMaxZoom				(float zoom){m_max_zoom = zoom;}

	bool	OnMouseAction					(float x, float y, EUIMessages mouse_action) override;

	CUIMapWnd*		MapWnd					() {return m_mapWnd;}
	void			MoveWndDelta			(const Fvector2& d);

	float			CalcOpenRect			(const Fvector2& center_point, Frect& map_desired_rect, float tgt_zoom);

	void			ClipByVisRect			();
	void	Update					() override;
	void			Initialize				();
protected:
	void	Init_internal			(const shared_str& name, CInifile& pLtx, const shared_str& sect_name, LPCSTR sh_name) override;
};

class CUILevelMap: public CUICustomMap
{
	typedef  CUICustomMap inherited;

	CUIMapWnd*					m_mapWnd;
	Frect						m_GlobalRect;			// virtual map size (meters)
								CUILevelMap			(const CUILevelMap &obj) {}

			CUILevelMap			&operator=			(const CUILevelMap &obj) {}
public:
								CUILevelMap			(CUIMapWnd*);
	~CUILevelMap		() override;
	const Frect&				GlobalRect			() const								{return m_GlobalRect;}
	void				Draw				() override;
	void				Show				(bool status) override;
	void				Update				() override;
	bool				OnMouseAction				(float x, float y, EUIMessages mouse_action) override;
	void				SendMessage			(CUIWindow* pWnd, s16 msg, void* pData) override;
	
	Frect						CalcWndRectOnGlobal	();
	CUIMapWnd*					MapWnd				() {return m_mapWnd;}

	void			OnFocusLost			() override;

protected:
	void				UpdateSpots			() override;
	void				Init_internal		(const shared_str& name, CInifile& pLtx, const shared_str& sect_name, LPCSTR sh_name) override;
};

class CUIMiniMap: public CUICustomMap
{
	typedef  CUICustomMap inherited;

public:
								CUIMiniMap			();
	~CUIMiniMap			() override;
	void				Draw				() override;
	bool				GetPointerTo		(const Fvector2& src, float item_radius, Fvector2& pos, float& heading) override;//position and heading for drawing pointer to src pos
	bool				NeedShowPointer		(Frect r) override;
	bool				IsRectVisible		(Frect r) override;
protected:
	void				UpdateSpots			() override;
	void				Init_internal		(const shared_str& name, CInifile& pLtx, const shared_str& sect_name, LPCSTR sh_name) override;
};
