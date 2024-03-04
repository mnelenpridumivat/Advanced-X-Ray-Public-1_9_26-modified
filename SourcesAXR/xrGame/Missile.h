#pragma once
#include "hud_item_object.h"
#include "HudSound.h"

struct dContact;
struct SGameMtl;
class CMissile : public CHudItemObject
{
	typedef CHudItemObject inherited;
public:
	enum EMissileStates{
		eThrowStart = eLastBaseState+1,
		eReady,
		eThrow,
		eThrowEnd,
		eThrowQuick,
	};
							CMissile					();
	~CMissile					() override;

	BOOL			AlwaysTheCrow				() override { return TRUE; }
	void			render_item_ui					() override;
	bool			render_item_ui_query					() override;

	void			reinit						() override;
	CMissile*		cast_missile				() override {return this;}

	void 			Load						(LPCSTR section) override;
	BOOL 			net_Spawn					(CSE_Abstract* DC) override;
	void 			net_Destroy					() override;

	void 			UpdateCL					() override;
	void 			shedule_Update				(u32 dt) override;

	void 			OnH_A_Chield				() override;
	void 			OnH_B_Independent			(bool just_before_destroy) override;

	void 			OnEvent						(NET_Packet& P, u16 type) override;

	void 			OnAnimationEnd				(u32 state) override;
	void			OnMotionMark				(u32 state, const motion_marks&) override;


	virtual void 			Throw();
	virtual void 			Destroy();

	bool 			Action						(u16 cmd, u32 flags) override;

	virtual void 			State						(u32 state);
	void 			OnStateSwitch				(u32 S) override;
	bool			GetBriefInfo				(II_BriefInfo& info) override;

protected:
	virtual void			UpdateFireDependencies_internal	();
	void			UpdateXForm						() override;
	void					UpdatePosition					(const Fmatrix& trans);
	void					spawn_fake_missile				();

	void			OnActiveItem		() override;
	void			OnHiddenItem		() override;

	//для сети
	void			net_Relcase			(CObject* O ) override;
protected:

	//время нахождения в текущем состоянии
	u32						m_dwStateTime;
	bool					m_throw;
	
	//время уничтожения
	u32						m_dwDestroyTime;
	u32						m_dwDestroyTimeMax;

	Fvector					m_throw_direction;
	Fmatrix					m_throw_matrix;

	CMissile				*m_fake_missile;

	//параметры броска
	
	float m_fMinForce, m_fConstForce, m_fMaxForce, m_fForceGrowSpeed;
//private:
	bool					m_constpower;
	float					m_fThrowForce;

	bool					m_bIsContactGrenade;
	bool					m_bQuickThrowActive;
	CGameObject*			m_pOwner;
protected:
	//относительная точка и направление вылета гранаты
	Fvector					m_vThrowPoint;
	Fvector					m_vThrowDir;

protected:
			void			setup_throw_params		();
public:
	Fvector const&			throw_point_offset		() const {return m_vThrowPoint;}
	void			activate_physic_shell	() override;
	void			setup_physic_shell		() override;
	void			create_physic_shell		() override;
	IC		void			set_destroy_time		(u32 delta_destroy_time) {m_dwDestroyTime = delta_destroy_time + CRenderDevice::GetInstance()->dwTimeGlobal;}
	void			PH_A_CrPr				() override;

			void			SetQuickThrowActive		(bool status) { m_bQuickThrowActive = status; }

protected:
	u32						m_ef_weapon_type;

public:
	u32				ef_weapon_type			() const override;
	IC		u32				destroy_time			() const { return m_dwDestroyTime; }
	IC		int				time_from_begin_throw	() const { return (CRenderDevice::GetInstance()->dwTimeGlobal + m_dwDestroyTimeMax - m_dwDestroyTime); }
	static	void			ExitContactCallback		(bool& do_colide,bool bo1,dContact& c,SGameMtl *material_1,SGameMtl* material_2);
};