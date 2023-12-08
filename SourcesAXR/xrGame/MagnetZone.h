#pragma once
#include "customzone.h"
#include "script_export_space.h"

class CMagnetZone :
    public CCustomZone
{
private:
	typedef		CCustomZone					inherited;

protected:
	//сила импульса вт€гивани€ в зону (дл€ веса 100 кг)
	float			m_fThrowInImpulse;
	//сила импульса вт€гивани€ в зону дл€ живых существ
	float			m_fThrowInImpulseAlive;
	//коэфф. зат€гивани€ (чем меньше, тем плавнее зат€гивает)
	float			m_fThrowInAtten;

public:

	virtual void	Load(LPCSTR section);

	//воздействие зоной на объект
	virtual void	Affect(SZoneObjectInfo* O);
	virtual void	AffectPull(CPhysicsShellHolder* GO, const Fvector& throw_in_dir, float dist);
	virtual void	AffectPullAlife(CEntityAlive* EA, const Fvector& throw_in_dir, float dist);
	virtual void	AffectPullDead(CPhysicsShellHolder* GO, const Fvector& throw_in_dir, float dist);
	virtual void	ThrowInCenter(Fvector& C);

	DECLARE_SCRIPT_REGISTER_FUNCTION

};
add_to_type_list(CMagnetZone)
#undef script_type_list
#define script_type_list save_type_list(CMagnetZone)

