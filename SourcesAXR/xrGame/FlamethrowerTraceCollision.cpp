#include "stdafx.h"
#include "FlamethrowerTraceCollision.h"
#include "CustomMonster.h"
#include "../xrphysics/iphworld.h"
#include "Flamethrower.h"
#include "../xrEngine/xr_collide_form.h"
#include "ai/stalker/ai_stalker.h"
#include "Actor.h"

BOOL CFlamethrowerTraceCollision::hit_callback(collide::rq_result& result, LPVOID params)
{
	FlamethrowerTraceData* pData = static_cast<FlamethrowerTraceData*>(params);
	return false;
}

BOOL CFlamethrowerTraceCollision::test_callback(const collide::ray_defs& rd, CObject* object, LPVOID params)
{
	FlamethrowerTraceData* pData = static_cast<FlamethrowerTraceData*>(params);

	/*
	* H_Parent()->ID(),
	*		ID()
	*/

	bool bRes = TRUE;
	if (object) {
		CEntity* entity = smart_cast<CEntity*>(object);
		if (entity && entity->g_Alive() && (entity->ID() != pData->TracedObj->GetParentWeapon()->H_Parent()->ID())) {
			ICollisionForm* cform = entity->collidable.model;
			if ((NULL != cform) && (cftObject == cform->Type())) {

				// TODO: add check for big enemies (like pseudogiant)
				return false;

				CActor* actor = smart_cast<CActor*>(entity);
				CAI_Stalker* stalker = smart_cast<CAI_Stalker*>(entity);
				// � ���� ������?
				if (actor && IsGameTypeSingle()/**/ || stalker/**/) {
					// ������ � ������ ��� ��������
					Fsphere S = cform->getSphere();
					entity->XFORM().transform_tiny(S.P);
					float dist = rd.range;
					// �������� ������ �� �� � ����������� ����� 
					if (Fsphere::rpNone != S.intersect_full(pData->TracedObj->GetPosition(), pData->TracedObj->GetDirection(), dist))
					{
						// �� ������, ������ ��� �������
						bool play_whine = true;
						CObject* initiator = Level().Objects.net_Find(pData->TracedObj->GetParentWeapon()->H_Parent()->ID());
						if (actor) {
							// ������ � ������
							float hpf = 1.f;
							float ahp = actor->HitProbability();

							float					game_difficulty_hit_probability = actor->HitProbability();
							CAI_Stalker* stalker = smart_cast<CAI_Stalker*>(initiator);
							if (stalker)
							{
								hpf = stalker->SpecificCharacter().hit_probability_factor();
							}

							float					dist_factor = 1.f;
							ahp = dist_factor * game_difficulty_hit_probability + (1.f - dist_factor) * 1.f;

							if (Random.randF(0.f, 1.f) > (ahp * hpf)) {
								bRes = FALSE;	// don't hit actor
								play_whine = true;		// play whine sound
							}
							else {
								// real test actor CFORM
								//Level().BulletManager().m_rq_results.r_clear();

								/*if (cform->_RayQuery(rd, Level().BulletManager().m_rq_results)) {
									bRes = TRUE;		// hit actor
									play_whine = false;	// don't play whine sound
								}
								else {
									bRes = FALSE;	// don't hit actor
									play_whine = true;		// play whine sound
								}*/
							}
						}
						// play whine sound
						if (play_whine)
						{
							Fvector					pt;
							//pt.mad(bullet->bullet_pos, bullet->dir, dist);
							//Level().BulletManager().PlayWhineSound(bullet, initiator, pt);

							luabind::functor<void> m_functor;
							if (ai().script_engine().functor("mfs_functions.on_play_whine_sound", m_functor))
								m_functor();
						}
					}
					else
					{
						// don't test this object again (return FALSE)
						bRes = FALSE;
					}

				}
			}
		}
	}

	return bRes;
}

void CFlamethrowerTraceCollision::UpdateParticles()
{
	if (!m_particles)		return;

	Fmatrix particles_pos;
	particles_pos.set(XFORM);
	particles_pos.c.set(m_position);

	m_particles->SetXFORM(particles_pos);

	if (!m_particles->IsAutoRemove() && !m_particles->IsLooped()
		&& !m_particles->PSI_alive())
	{
		m_particles->Stop();
		CParticlesObject::Destroy(m_particles);
	}
}

CFlamethrowerTraceCollision::CFlamethrowerTraceCollision(CFlamethrowerTraceManager* flamethrower) : m_flamethrower(flamethrower)
{
}

CFlamethrowerTraceCollision::~CFlamethrowerTraceCollision()
{
}

void CFlamethrowerTraceCollision::Load(LPCSTR section)
{
	m_RadiusMin = pSettings->r_float(section, "RadiusMin");
	m_RadiusMax = pSettings->r_float(section, "RadiusMax");
	m_RadiusCollided = pSettings->r_float(section, "RadiusCollided");
	m_RadiusMaxTime = pSettings->r_float(section, "RadiusMaxTime");
	m_Velocity = pSettings->r_float(section, "Velocity");
	m_LifeTime = pSettings->r_float(section, "LifeTime");

	string256 full_name;
	// flames
	strconcat(sizeof(full_name), full_name, "", "flame_particles");
	m_sFlameParticles = pSettings->r_string(section, full_name);
}

inline CFlamethrower* CFlamethrowerTraceCollision::GetParentWeapon() const
{
	return m_flamethrower->GetParent();
}

bool CFlamethrowerTraceCollision::IsReadyToUpdateCollisions()
{
	float Dist = GetCurrentRadius()*0.8;
	if(IsCollided())
	{
		if(m_last_update_time > 0.2)
		{
			m_last_update_time = 0.0f;
			return true;
		}
		return false;
	}
	return m_position.distance_to_sqr(m_LastUpdatedPos) > Dist*Dist;
}

float CFlamethrowerTraceCollision::GetCurrentRadius()
{
	if (!IsActive()) {
		return 0.0f;
	}
	if (IsCollided()) {
		return m_RadiusCollided;
	}
	if (m_current_time > m_RadiusMaxTime) {
		return m_RadiusMax;
	}
	float CurRadius = m_RadiusMin + (m_RadiusMax - m_RadiusMin) * (m_current_time / m_RadiusMaxTime);
	clamp(CurRadius, m_RadiusMin, m_RadiusMax);
	return CurRadius;
}

void CFlamethrowerTraceCollision::SetTransform(const Fmatrix& StartPos)
{
	XFORM = StartPos;
	StartPos.getXYZ(m_position);
	StartPos.transform_dir(m_direction);
}

void CFlamethrowerTraceCollision::feel_touch_new(CObject* O)
{
	if (!m_IsActive) {
		return;
	}
	if (CCustomMonster* Casted = smart_cast<CCustomMonster*>(O)) {
		m_flamethrower->RegisterOverlapped(Casted);
	}
}

void CFlamethrowerTraceCollision::feel_touch_delete(CObject* O)
{
	if (CCustomMonster* Casted = smart_cast<CCustomMonster*>(O)) {
		m_flamethrower->UnregisterOverlapped(smart_cast<CCustomMonster*>(O));
	}
}

BOOL CFlamethrowerTraceCollision::feel_touch_contact(CObject* O)
{
	return false;
}

void CFlamethrowerTraceCollision::Activate()
{
	m_IsActive = true;
	feel_touch_update(m_position, GetCurrentRadius());
	m_LastUpdatedPos = m_position;
	m_particles = CParticlesObject::Create(*m_sFlameParticles, true);
	m_particles->Play(false);
}

void CFlamethrowerTraceCollision::Deactivate()
{
	m_IsActive = false;
	m_IsCollided = false;
	m_GravityVelocity = 0.0f;
	m_current_time = 0.0f;
	m_particles->Stop();
	CParticlesObject::Destroy(m_particles);
}

void CFlamethrowerTraceCollision::Update(float DeltaTime)
{
	if (!IsActive()) {
		return;
	}
	m_current_time += DeltaTime;
	m_last_update_time += DeltaTime;
	if (m_current_time > m_LifeTime) {
		Deactivate();
		return;
	}
	if (IsCollided()) {
		return;
	}
	m_GravityVelocity += physics_world()->Gravity() * DeltaTime;
	auto old_pos = m_position;
	m_position = m_position.add(m_direction.mul(m_Velocity * DeltaTime)).sub({ 0.0f, m_GravityVelocity * DeltaTime, 0.0f });
	collide::rq_results storage;
	collide::ray_defs RD(old_pos, m_position, CDB::OPT_FULL_TEST, collide::rqtBoth);
	FlamethrowerTraceData data;
	data.TracedObj = this;
	Level().ObjectSpace.RayQuery(storage, RD, CFlamethrowerTraceCollision::hit_callback, &data, CFlamethrowerTraceCollision::test_callback, NULL);
	m_direction = m_position.sub(old_pos).normalize();

	UpdateParticles();

}

CFlamethrowerTraceManager::CFlamethrowerTraceManager(CFlamethrower* flamethrower) : m_flamethrower(flamethrower)
{
}

CFlamethrowerTraceManager::~CFlamethrowerTraceManager()
{
	for (auto& elem : CollisionsPool) {
		xr_delete(elem);
	}
}

void CFlamethrowerTraceManager::Load(LPCSTR section)
{
	for (auto& elem : CollisionsPool) {
		xr_delete(elem);
	}
	CollisionSection = section;
	CollisionsPool.clear();
	int StartNum = pSettings->r_u16(section, "trace_collision_num_start");
	for (int i = 0; i < StartNum; ++i) {
		auto NewCollision = xr_new<CFlamethrowerTraceCollision>(this);
		NewCollision->Load(section);
		CollisionsPool.push_back(NewCollision);
		//CollisionsDeque.push_back(NewCollision);
	}
}

void CFlamethrowerTraceManager::UpdateOverlaps(float DeltaTime)
{

	for (auto& elem : CollisionsPool) {
		elem->Update(DeltaTime);
		if (!elem->IsActive() || !elem->IsReadyToUpdateCollisions()) {
			continue;
		}
		auto Pos = elem->GetPosition();
		//elem->feel_touch_update(Pos, elem->GetCurrentRadius());
	}
}

void CFlamethrowerTraceManager::RegisterOverlapped(CCustomMonster* enemy)
{
	Overlapped.push_back(enemy);
}

void CFlamethrowerTraceManager::UnregisterOverlapped(CCustomMonster* enemy)
{
	Overlapped.remove(enemy);
}

const CFlamethrowerTraceManager::FOverlappedObjects& CFlamethrowerTraceManager::GetOverlapped()
{
	return Overlapped;
}

void CFlamethrowerTraceManager::LaunchTrace(const Fmatrix& StartPos)
{
	auto First = CollisionsPool.front();
	if(First->IsActive())
	{
		First = xr_new<CFlamethrowerTraceCollision>(this);
		First->Load(CollisionSection.c_str());
	} else
	{
		CollisionsPool.pop_front();
	}
	CollisionsPool.push_back(First);
	First->SetTransform(StartPos);
	First->Activate();
	Msg("Current collisions num in pool: [%d]", CollisionsPool.size());
}
