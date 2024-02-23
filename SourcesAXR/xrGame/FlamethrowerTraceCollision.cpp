#include "stdafx.h"
#include "FlamethrowerTraceCollision.h"
#include "CustomMonster.h"
#include "../xrphysics/iphworld.h"
#include "Flamethrower.h"
#include "../xrEngine/xr_collide_form.h"
#include "ai/stalker/ai_stalker.h"
#include "Actor.h"
#include "debug_renderer.h"
#include "Level_Bullet_Manager.h"
#include "seniority_hierarchy_space.h"

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

void CFlamethrowerTraceCollision::UpdateParticles()
{
	if (!m_particles)		return;

	Fmatrix particles_pos = Fmatrix();
	//particles_pos.set(XFORM);
	particles_pos.c.set(m_position);

	VERIFY(_valid(particles_pos));

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

void CFlamethrowerTraceCollision::SetTransform(const Fvector& StartPos, const Fvector& StartDir)
{
	//XFORM = StartPos;
	//invXFORM = XFORM.invert();
	//StartPos.getXYZ(m_position);
	m_position = StartPos;
	m_direction = StartDir;
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
	//feel_touch_update(m_position, GetCurrentRadius());
	m_LastUpdatedPos = m_position;
	m_particles = CParticlesObject::Create(*m_sFlameParticles, false);
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
	//invXFORM.transform(old_pos);
	m_position = m_position + m_direction *m_Velocity* DeltaTime - Fvector{ 0.0f, m_GravityVelocity * DeltaTime, 0.0f };
	auto new_pos = m_position;
	//invXFORM.transform(new_pos);
	Msg("pos = [%f, %f, %f]", new_pos.x, new_pos.y, new_pos.z);
	//m_position = m_position.add(m_direction.mul(m_Velocity * DeltaTime)).sub({ 0.0f, m_GravityVelocity * DeltaTime, 0.0f });
	collide::rq_results storage;
	collide::ray_defs RD(old_pos, new_pos, CDB::OPT_FULL_TEST, collide::rqtBoth);
#ifdef DEBUG
	Level().BulletManager().AddBulletMoveChunk(old_pos, new_pos);
#endif
	FlamethrowerTraceData data;
	data.TracedObj = this;
	Level().ObjectSpace.RayQuery(storage, RD, CFlamethrowerTraceCollision::hit_callback, &data, CFlamethrowerTraceCollision::test_callback, NULL);
	//m_direction = m_position.sub(old_pos).normalize();
	m_direction = (new_pos - old_pos).normalize();

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

void CFlamethrowerTraceManager::feel_touch_new(CObject* O)
{
	Touch::feel_touch_new(O);
	Overlapped.push_back(smart_cast<CCustomMonster*>(O));
}

void CFlamethrowerTraceManager::feel_touch_delete(CObject* O)
{
	Touch::feel_touch_delete(O);
	Overlapped.remove(smart_cast<CCustomMonster*>(O));
}

BOOL CFlamethrowerTraceManager::feel_touch_contact(CObject* O)
{
	if (CCustomMonster* enemy = smart_cast<CCustomMonster*>(O)) {
		for (auto& elem : CollisionsPool) {
			if (!elem->IsActive() || !elem->IsReadyToUpdateCollisions()) {
				continue;
			}
			float Radius = elem->GetCurrentRadius();
			if (elem->GetPosition().distance_to_sqr(enemy->Position()) < Radius*Radius)
			{
				return true;
			}
		}
	}
	return false;
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
	Fvector Center{};
	float Radius = 0.0f;
	uint16_t Num = 0;
	for (auto& elem : CollisionsPool) {
		elem->Update(DeltaTime);
		if (!elem->IsActive() || !elem->IsReadyToUpdateCollisions()) {
			continue;
		}
		Center += elem->GetPosition();
		++Num;
		//auto Pos = elem->GetPosition();
		//elem->feel_touch_update(Pos, elem->GetCurrentRadius());
	}
	if(!Num)
	{
		return;
	}
	Center /= Num;
	for (auto& elem : CollisionsPool) {
		if (!elem->IsActive())
		{
			continue;
		}
		float Dist = Center.distance_to_sqr(elem->GetPosition());
		if(Dist > Radius)
		{
			Radius = Dist;
		}
	}
	feel_touch_update(Center, sqrt(Radius));
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

void CFlamethrowerTraceManager::LaunchTrace(const Fvector& StartPos, const Fvector& StartDir)
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
	First->SetTransform(StartPos, StartDir);
	First->Activate();
	CollisionsPool.push_back(First);
	Msg("Current collisions num in pool: [%d]", CollisionsPool.size());
}
