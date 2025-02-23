#pragma once

#include "../xrCore/xr_deque.h"
#include "xr_level_controller.h"

class CUIWindow;
class CUIStatic;
class CUISequenceItem;
class CUIXml;
class IUISequenceVideoItem;

class CUISequencer :public pureFrame, public pureRender,	public IInputReceiver
{
protected:
	CUIWindow*				m_UIWindow;
	ref_sound				m_global_sound;
	xr_deque<CUISequenceItem*> m_sequencer_items;
	pcstr					m_name;

	bool					GrabInput			();
	CUISequenceItem*		GetNextItem			();
	shared_str				m_start_lua_function;
	shared_str				m_stop_lua_function;

public:
	IInputReceiver*			m_pStoredInputReceiver;
							CUISequencer		();
	void					Start				(LPCSTR tutor_name);
	void					Stop				();
	void					Next				();

	void					Destroy				();				//be careful

	void	_BCL	OnFrame				() override;
	void			OnRender			() override;
	CUIWindow*				MainWnd				()				{return m_UIWindow;}
	bool					IsActive			()				{return !!m_flags.test(etsActive);}


	//IInputReceiver
	void			IR_OnMousePress		(int btn) override;
	void			IR_OnMouseRelease	(int btn) override;
	void			IR_OnMouseHold		(int btn) override;
	void			IR_OnMouseMove		(int x, int y) override;
	void			IR_OnMouseStop		(int x, int y) override;

	void			IR_OnKeyboardPress	(int dik) override;
	void			IR_OnKeyboardRelease(int dik) override;
	void			IR_OnKeyboardHold	(int dik) override;

	void			IR_OnMouseWheel		(int direction) override;
	void			IR_OnActivate		(void) override;
			bool			Persistent			() {return !!m_flags.test(etsPersistent);}
			pcstr			GetTutorName		() { return m_name; }

	fastdelegate::FastDelegate0<>	m_on_destroy_event;
	
	enum {	
		etsNeedPauseOn		= (1<<0),
		etsNeedPauseOff		= (1<<1),
		etsStoredPauseState	= (1<<2),
		etsPersistent		= (1<<3),
		etsPlayEachItem		= (1<<4),
		etsActive			= (1<<5),
		etsOverMainMenu		= (1<<6),
	};
	Flags32					m_flags;
};

class CUISequenceItem
{
	xr_vector<int>			m_disabled_actions;
protected:
	enum {	
		etiNeedPauseOn		= (1<<0),
		etiNeedPauseOff		= (1<<1),
		etiStoredPauseState	= (1<<2),
		etiCanBeStopped		= (1<<3),
		etiGrabInput		= (1<<4),
		etiNeedPauseSound	= (1<<5),
		etiStoredCursorState= (1<<6),
		etiSkipSceneRendering=(1<<7),
		eti_last = 8,
	};
	xr_vector<shared_str>	m_start_lua_functions;
	xr_vector<shared_str>	m_stop_lua_functions;
	luabind::functor<void>	m_onframe_functor;

	Flags32					m_flags;
	CUISequencer*			m_owner;

	virtual float			current_factor		(){return 1;}
public:
							CUISequenceItem		(CUISequencer* owner):m_owner(owner){m_flags.zero();}
	virtual					~CUISequenceItem	(){}
	virtual void			Load				(CUIXml* xml, int idx)=0;

	virtual void			Start				();
	virtual bool			Stop				(bool bForce=false)=0;

	virtual void			Update				();
	virtual void			OnRender			()=0;
	virtual void			OnKeyboardPress		(int dik)=0;
	virtual void			OnMousePress		(int btn)=0;

	virtual bool			IsPlaying			()=0;

	bool					AllowKey			(int dik);
	bool					GrabInput			(){return !!m_flags.test(etiGrabInput);}

	shared_str				m_check_lua_function;
	shared_str				m_onframe_lua_function;
};

class CUISequenceSimpleItem: public CUISequenceItem
{
	typedef CUISequenceItem	inherited;
	struct SSubItem{
		CUIStatic*			m_wnd;
		float				m_start;
		float				m_length;
		bool				m_visible;
	public:
		virtual void		Start				();
		virtual void		Stop				();
	};
	DEFINE_VECTOR			(SSubItem,SubItemVec,SubItemVecIt);
	SubItemVec				m_subitems;
	struct SActionItem{
		EGameActions			m_action;
		shared_str				m_functor;
		bool					m_bfinalize;
	};
public:
	CUIWindow*				m_UIWindow;
	ref_sound				m_sound;
	float					m_time_start;
	float					m_time_length;
	string64				m_pda_section;
	Fvector2				m_desired_cursor_pos;
	int						m_continue_dik_guard;
	xr_vector<SActionItem>	m_actions;
public:
							CUISequenceSimpleItem(CUISequencer* owner):CUISequenceItem(owner){}
	~CUISequenceSimpleItem() override;
	void			Load				(CUIXml* xml,int idx) override;

	void			Start				() override;
	bool			Stop				(bool bForce=false) override;

	void			Update				() override;
	void			OnRender			() override;
	void			OnKeyboardPress		(int dik) override;
	void			OnMousePress		(int btn) override;

	bool			IsPlaying			() override;
protected:
	float			current_factor		() override;
};

class CUISequenceVideoItem: public CUISequenceItem
{
	typedef CUISequenceItem	inherited;
	ref_sound				m_sound;
	FactoryPtr<IUISequenceVideoItem>	m_texture;
	enum {	
		etiPlaying			= (1<<(eti_last+0)),
		etiNeedStart		= (1<<(eti_last+1)),
		etiDelayed			= (1<<(eti_last+2)),
		etiBackVisible		= (1<<(eti_last+3)),
	};
	float					m_delay;
	CUIStatic*				m_wnd;
	CUIStatic*				m_wnd_bg;
	u32						m_time_start;
	u32						m_sync_time;
public:
							CUISequenceVideoItem(CUISequencer* owner);
	~CUISequenceVideoItem() override;
	void			Load				(CUIXml* xml,int idx) override;

	void			Start				() override;
	bool			Stop				(bool bForce=false) override;

	void			Update				() override;
	void			OnRender			() override;
	void			OnKeyboardPress		(int dik) override {}
	void			OnMousePress		(int btn) override {};

	bool			IsPlaying			() override;
};
