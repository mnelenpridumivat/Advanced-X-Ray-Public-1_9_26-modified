//////////////////////////////////////////////////////////////////////////
// GraviZone.h:		гравитационна€ аномали€
//////////////////////////////////////////////////////////////////////////
//					состоит как бы из 2х зон
//					одна зат€гивает объект, друга€ взрывает и 
//					все неживые объекты (предметы и трупы)
//					поднимает в воздух и качает там какое-то
//					врем€
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "customzone.h"
#include "ai/monsters/telekinesis.h"



class CBaseGraviZone :
	public CCustomZone,
	public IMetaClass
{
	DECLARE_METACLASS1(CBaseGraviZone, CCustomZone)
private:
	typedef		CCustomZone					inherited;

public:
					CBaseGraviZone(void);
	~CBaseGraviZone(void) override;

	void	Load (LPCSTR section) override;

	BOOL	net_Spawn		(CSE_Abstract* DC) override;
	void	net_Destroy		() override;
	void	net_Relcase		(CObject* O) override;


	//воздействие зоной на объект
	void	Affect(SZoneObjectInfo* O) override;
	virtual void	AffectPull(CPhysicsShellHolder* GO,const Fvector& throw_in_dir,float dist);
	virtual void	AffectPullAlife(CEntityAlive* EA,const Fvector& throw_in_dir,float dist);
	virtual void	AffectPullDead(CPhysicsShellHolder* GO,const Fvector& throw_in_dir,float dist);
	virtual void	AffectThrow(SZoneObjectInfo* O, CPhysicsShellHolder* GO,const Fvector& throw_in_dir,float dist);
	virtual void	ThrowInCenter(Fvector& C);
	virtual bool	CheckAffectField(CPhysicsShellHolder* GO,float dist_to_radius);
	void	shedule_Update		(u32 dt) override;
	bool	BlowoutState() override;
	bool	IdleState() override;

	virtual float	BlowoutRadiusPercent(CPhysicsShellHolder* /*GO*/){return m_fBlowoutRadiusPercent;}
protected:
	void	exit_Zone(SZoneObjectInfo& io) override;
	virtual CTelekinesis& Telekinesis()						=0;
protected:
	//сила импульса вт€гивани€ в зону (дл€ веса 100 кг)
	float			m_fThrowInImpulse;
	//сила импульса вт€гивани€ в зону дл€ живых существ
	float			m_fThrowInImpulseAlive;
	//коэфф. зат€гивани€ (чем меньше, тем плавнее зат€гивает)
	float			m_fThrowInAtten;
	//радиус действи€ выброса (в процентах от всего)
	float			m_fBlowoutRadiusPercent;


	//параметры телекинеза	
	float			m_fTeleHeight;
	u32				m_dwTimeToTele;
	u32				m_dwTelePause;
	u32				m_dwTeleTime;

	//им€ партиклов телекинеза
	void			PlayTeleParticles(CGameObject* pObject);
	void			StopTeleParticles(CGameObject* pObject);

	shared_str		m_sTeleParticlesBig;
	shared_str		m_sTeleParticlesSmall;
};

class CGraviZone	: public CBaseGraviZone
{
	typedef		CBaseGraviZone				inherited;
	CTelekinesis m_telekinesis;
protected:
	CTelekinesis& Telekinesis() override {return m_telekinesis;}
public:
						CGraviZone		(void)			{}
	~CGraviZone		(void) override {}
};