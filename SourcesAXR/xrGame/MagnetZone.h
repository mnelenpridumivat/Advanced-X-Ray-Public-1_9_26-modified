#pragma once
#include "customzone.h"
#include "script_export_space.h"

class CMagnetZone :
    public CCustomZone
{
private:
	typedef		CCustomZone					inherited;

protected:
	//���� �������� ���������� � ���� (��� ���� 100 ��)
	float			m_fThrowInImpulse;
	//���� �������� ���������� � ���� ��� ����� �������
	float			m_fThrowInImpulseAlive;
	//�����. ����������� (��� ������, ��� ������� ����������)
	float			m_fThrowInAtten;

public:

	virtual void	Load(LPCSTR section);

	//����������� ����� �� ������
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

