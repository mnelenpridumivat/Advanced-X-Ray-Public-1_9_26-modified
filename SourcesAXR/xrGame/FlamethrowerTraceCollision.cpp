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
				// в кого попали?
				if (actor && IsGameTypeSingle()/**/ || stalker/**/) {
					// попали в актера или сталкера
					Fsphere S = cform->getSphere();
					entity->XFORM().transform_tiny(S.P);
					float dist = rd.range;
					// проверим попали ли мы в описывающую сферу 
					if (Fsphere::rpNone != S.intersect_full(pData->TracedObj->GetPosition(), pData->TracedObj->GetDirection(), dist))
					{
						// да попали, найдем кто стрелял
						bool play_whine = true;
						CObject* initiator = Level().Objects.net_Find(pData->TracedObj->GetParentWeapon()->H_Parent()->ID());
						if (actor) {
							// попали в актера
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

CFlamethrowerTraceCollision::CFlamethrowerTraceCollision(CFlamethrowerTraceManager* flamethrower) : m_flamethrower(flamethrower)
{
}

CFlamethrowerTraceCollision::~CFlamethrowerTraceCollision()
{
}

inline CFlamethrower* CFlamethrowerTraceCollision::GetParentWeapon() const
{
	return m_flamethrower->GetParent();
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
}

void CFlamethrowerTraceCollision::Deactivate()
{
	m_IsActive = false;
	m_IsCollided = false;
	m_GravityVelocity = 0.0f;
	m_current_time = 0.0f;
}

void CFlamethrowerTraceCollision::Update(float DeltaTime)
{
	if (!IsActive()) {
		return;
	}
	m_current_time += DeltaTime;
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

}

void CFlamethrowerTraceManager::UpdateOverlaps(float DeltaTime)
{

	for (auto& elem : CollisionsPool) {
		elem->Update(DeltaTime);
		if (!elem->IsActive()) {
			continue;
		}
		elem->feel_touch_update(elem->GetPosition(), elem->GetCurrentRadius());
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
