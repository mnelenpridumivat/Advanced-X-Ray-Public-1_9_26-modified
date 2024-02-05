///////////////////////////////////////////////////////////////
// BlackGraviArtifact.h
// BlackGraviArtefact - �������������� ��������, 
// ����� �� ��� � �������, �� ��� ��������� ����
///////////////////////////////////////////////////////////////

#pragma once
#include "GraviArtifact.h"
#include "../xrEngine/feel_touch.h"
#include "PhysicsShellHolder.h"
DEFINE_VECTOR (CPhysicsShellHolder*, GAME_OBJECT_LIST, GAME_OBJECT_LIST_it);

class CBlackGraviArtefact: public CGraviArtefact,
						   public Feel::Touch
{
private:
	collide::rq_results		rq_storage;

private:
	typedef CGraviArtefact inherited;
public:
	CBlackGraviArtefact(void);
	~CBlackGraviArtefact(void) override;

	BOOL net_Spawn			(CSE_Abstract* DC) override;

	void Load				(LPCSTR section) override;

	void Hit				(SHit* pHDS) override;

	void feel_touch_new		(CObject* O) override;
	void feel_touch_delete	(CObject* O) override;
	BOOL feel_touch_contact	(CObject* O) override;

protected:
	void	net_Relcase		(CObject* O ) override;
	void	UpdateCLChild	() override;

	//�������������� ���� �� ���� �������� � ���� ������������
	void GraviStrike();

	GAME_OBJECT_LIST m_GameObjectList;


	//�������� �������� ��������������
	float m_fImpulseThreshold;
	//������ �������� ���������
	float m_fRadius;
	//������� ������������ ���������� ���������
	float m_fStrikeImpulse;

	//����, ���� ��� �������� ������� ��� 
	//� ������ ����� ��������� ������
	bool m_bStrike;	

	shared_str	m_sParticleName;
};
