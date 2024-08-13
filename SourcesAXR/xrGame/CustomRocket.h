//////////////////////////////////////////////////////////////////////
// CustomRocket.h:	������, ������� �������� RocketLauncher 
//					(����� ������, ��������� � ���������� ��������)
//////////////////////////////////////////////////////////////////////

#pragma once

#include "physic_item.h"
#include "../xrphysics/PHUpdateObject.h"

class CRocketLauncher;
struct dContact;
struct SGameMtl;
struct SRoketContact
{
	bool contact;
	Fvector pos;
	Fvector up;
	SRoketContact()
	{
		contact = false;
	}
};

class CCustomRocket : public CPhysicItem,
	public CPHUpdateObject
{
private:
	typedef CPhysicItem inherited;
	friend CRocketLauncher;
public:
	//////////////////////////////////////////////////////////////////////////
	//	Generic
	//////////////////////////////////////////////////////////////////////////

	CCustomRocket(void);
	~CCustomRocket(void) override;

	void Load(LPCSTR section) override;
	BOOL net_Spawn(CSE_Abstract* DC) override;
	void net_Destroy() override;
	BOOL						AlwaysTheCrow() override { return TRUE; }

	void reinit() override;
	void reload(LPCSTR section) override;

	void OnH_A_Independent() override;
	void OnH_B_Independent(bool just_before_destroy) override;
	void OnH_B_Chield() override;
	void OnH_A_Chield() override;
	void UpdateCL() override;

	BOOL UsedAI_Locations() override { return	(FALSE); }
	virtual bool Useful() const { return (m_eState == eInactive); }

	void renderable_Render() override { inherited::renderable_Render(); }

	//�������� ���������� ��������
	void			activate_physic_shell() override;
	void			create_physic_shell() override;

	void			PhDataUpdate(float step) override;
	void			PhTune(float step) override;

	//////////////////////////////////////////////////////////////////////////
	//	Rocket Properties
	//////////////////////////////////////////////////////////////////////////
public:
#ifdef DEBUG
	CGameObject* owner() { return m_pOwner; }
#endif
	virtual	void			StartEngine();
	virtual	void			StopEngine();
	virtual	void			UpdateEngine();
	virtual	void			UpdateEnginePh();

	virtual	void			StartFlying();
	virtual	void			StopFlying();

	virtual	void			SetLaunchParams(const Fmatrix& xform,
		const Fvector& vel,
		const Fvector& angular_vel);

	void			OnEvent(NET_Packet& P, u16 type) override;
	bool					m_bLaunched;
protected:
	//��������� �� ��������� RocketLauncher - ������� �������� ������
	CGameObject* m_pOwner;

	SRoketContact			m_contact;
	//��������� ������� �������� RocketLauncher-�� ����� ������
	Fmatrix					m_LaunchXForm;
	Fvector					m_vLaunchVelocity;
	Fvector					m_vLaunchAngularVelocity;

	enum ERocketState {
		eInactive,		//������ ��������� � ���������� � ���������
		eEngine,		//������� ���������
		eFlying,		//������ �����
		eCollide		//��������� ������������ � ������������
	};

	//������� ��������� ������
	ERocketState m_eState;

	//��������� ������������
	bool		m_bEnginePresent;
	//����� ������ ��������� � ������� ������
	int			m_dwEngineWorkTime;
	//���� ������ ��������� (������ �������� � �������)
	float		m_fEngineImpulse;
	float		m_fEngineImpulseUp;
	//������� ����� ������ ���������
	int			m_dwEngineTime;

	//��������� ������������
	virtual void			Contact(const Fvector& pos, const Fvector& normal);
	void			PlayContact();
	static	void			ObjectContactCallback(bool& do_colide, bool bo1, dContact& c, SGameMtl* /*material_1*/, SGameMtl* /*material_2*/);

	virtual bool IsEngineInfinite(){return false;}


	//////////////////////////////////////////////////////////////////////////
	//	Lights
	//////////////////////////////////////////////////////////////////////////
protected:
	//����, ��� ��������� ����� ���� ��������
	bool			m_bLightsEnabled;
	//����, ��� ��������� ����� �����������
	//������ � ����������
	bool			m_bStopLightsWithEngine;
	//��������� �� ����� ������ � ������ ���������
	ref_light		m_pTrailLight;
	Fcolor			m_TrailLightColor;
	float			m_fTrailLightRange;
	ref_sound		m_flyingSound;

protected:
	virtual void	StartLights();
	virtual void	StopLights();
	virtual void	UpdateLights();
    
	
	//////////////////////////////////////////////////////////////////////////
	//	Particles
	//////////////////////////////////////////////////////////////////////////
protected:	
	//��� ��������� ���������
	shared_str			m_sEngineParticles;
	CParticlesObject*	m_pEngineParticles;
	//��� ��������� ������
	shared_str			m_sFlyParticles;
	CParticlesObject*	m_pFlyParticles;

	Fvector				m_vPrevVel;
	float				m_time_to_explode;
#ifdef	DEBUG
	float				gbg_rocket_speed1;
	float				gbg_rocket_speed2;
#endif
protected:
	virtual void		StartEngineParticles();
	virtual void		StopEngineParticles();
	virtual void		StartFlyParticles();
	virtual void		StopFlyParticles();

	virtual void		UpdateParticles();
#ifdef DEBUG
	void		deactivate_physics_shell () override;
#endif
};