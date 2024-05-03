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
#include "../xrParticles/psystem.h"

BOOL CFlamethrowerTraceCollision::hit_callback(collide::rq_result& result, LPVOID params)
{
	FlamethrowerTraceData* pData = static_cast<FlamethrowerTraceData*>(params);
	if(!result.O)
	{
		pData->HitDist = result.range;
		return false;
	}
	return true;
}

BOOL CFlamethrowerTraceCollision::test_callback(const collide::ray_defs& rd, CObject* object, LPVOID params)
{
	FlamethrowerTraceData* pData = static_cast<FlamethrowerTraceData*>(params);

	if(object)
	{
		CEntity* entity = smart_cast<CEntity*>(object);
		if(!entity)
		{
			return true;
		}
		if(entity->ID() == pData->TracedObj->GetParentWeapon()->H_Parent()->ID())
		{
			return false;
		}
	}
	return true;
}

void CFlamethrowerTraceCollision::UpdateParticles()
{
	if (!m_particles)		return;

	Fmatrix particles_pos = Fmatrix();
	particles_pos.c.set(m_position);

	VERIFY(_valid(particles_pos));

	m_particles->SetXFORM(particles_pos);

	m_particles->Manual_UpdateSize(GetCurrentRadius()*m_RadiusCollisionCoeff);
	float NewAlpha;
	if(IsCollided())
	{
		NewAlpha = (m_LifeTimeCollidedMax - std::max(m_current_time, m_LifeTimeCollidedMax - m_FlameFadeTime)) / m_FlameFadeTime;
	} else
	{
		NewAlpha = (m_LifeTime - std::max(m_current_time, m_LifeTime - m_FlameFadeTime)) / m_FlameFadeTime;
	}
	m_particles->Manual_UpdateAlpha(NewAlpha);

	if (!m_particles->IsAutoRemove() && !m_particles->IsLooped()
		&& !m_particles->PSI_alive())
	{
		m_particles->Stop();
		CParticlesObject::Destroy(m_particles);
	}
}

void CFlamethrowerTraceCollision::Update_Air(float DeltaTime)
{

	Fmatrix particles_pos = Fmatrix();
	particles_pos.c.set(m_position);

	VERIFY(_valid(particles_pos));

	m_particles->SetXFORM(particles_pos);

	float interpTime = std::min(m_current_time / m_RadiusMaxTime, 1.0f);
	RadiusCurrent = m_RadiusMin + (m_RadiusMax - m_RadiusMin) * interpTime;
	clamp(RadiusCurrent, m_RadiusMin, m_RadiusMax);

	m_particles->Manual_UpdateSize(GetCurrentRadius() * m_RadiusCollisionCoeff);

	if (!IsCollided()) {
		m_GravityVelocity += m_GravityAcceleration * DeltaTime;
		auto old_pos = m_position;
		m_position = m_position + m_direction * m_Velocity * DeltaTime - Fvector{ 0.0f, m_GravityVelocity * DeltaTime, 0.0f };
		collide::rq_results storage;
		collide::ray_defs RD(old_pos, m_position, CDB::OPT_FULL_TEST, collide::rqtBoth);
		FlamethrowerTraceData data;
		data.TracedObj = this;
		m_direction = m_position - old_pos;
		m_direction.normalize();
		if (Level().ObjectSpace.RayQuery(storage, RD, CFlamethrowerTraceCollision::hit_callback, &data, CFlamethrowerTraceCollision::test_callback, nullptr))
		{
			m_position = old_pos + m_direction * data.HitDist;
			m_State = ETraceState::AirToGround;
			VERIFY2(m_RadiusCollided > 0.01, "Too small RadiusCollided in flamethrower config!");
			RadiusOnCollide = RadiusCurrent;
			m_time_on_collide = m_current_time;
			m_particles->Stop(false);
			CParticlesObject::Destroy(m_particles);
			m_particles_ground = CParticlesObject::Create(*m_sFlameParticlesGround, false);
			particles_pos.c.set(m_position);
			m_particles_ground->SetXFORM(particles_pos);
			m_particles_ground->Manual_UpdateSize(m_RadiusCollided * m_RadiusCollisionCoeff);
			m_particles_ground->Play(false);
		}
	}
	if(m_current_time >= m_LifeTime)
	{
		m_State = ETraceState::End;
	}
}

void CFlamethrowerTraceCollision::Update_AirToGround(float DeltaTime)
{
	float interpTime = (m_current_time - m_time_on_collide) / m_RadiusCollidedInterpTime;
	if(interpTime >= 1.0f)
	{
		m_State = ETraceState::Ground;
		interpTime = 1.0f;
	}
	//RadiusCurrent = RadiusOnCollide + (m_RadiusCollided - RadiusOnCollide) * interpTime;
	const float AlphaValue = 1.0f - std::pow(1.0f - interpTime, 2.0f);
	//if(!m_particles_ground)
	//{
	//	m_particles_ground = CParticlesObject::Create(*m_sFlameParticlesGround, false);
	//	m_particles_ground->Play(false);
	//}
	m_particles_ground->Manual_UpdateAlpha(AlphaValue);
	RadiusCurrent = std::max(RadiusOnCollide, AlphaValue * m_RadiusCollided);

	m_particles_ground->Manual_UpdateSize(m_RadiusCollided * m_RadiusCollisionCoeff);
}

void CFlamethrowerTraceCollision::Update_Ground(float DeltaTime)
{
	if (m_current_time >= m_LifeTimeCollidedMax)
	{
		m_current_time = 0;
		m_State = ETraceState::End;
	}
}

void CFlamethrowerTraceCollision::Update_End(float DeltaTime)
{
	const float interpTime = 1.0f - (m_current_time / m_RadiusCollidedInterpTime);
	if(interpTime <= 0)
	{
		Deactivate();
		return;
	}
	const float AlphaValue = 1.0f - std::pow(1.0f - interpTime, 2.0f);
	if (m_particles) {
		m_particles->Manual_UpdateAlpha(AlphaValue);
	}
	if (m_particles_ground) {
		m_particles_ground->Manual_UpdateAlpha(AlphaValue);
	}
	//RadiusCurrent = AlphaValue;
}

CFlamethrowerTraceCollision::CFlamethrowerTraceCollision(CFlamethrowerTraceManager* flamethrower) : m_flamethrower(flamethrower)
{
}

CFlamethrowerTraceCollision::~CFlamethrowerTraceCollision()
{
	if (IsActive()) {
		Deactivate();
	}
}

void CFlamethrowerTraceCollision::Load(LPCSTR section)
{
	m_RadiusMin = pSettings->r_float(section, "RadiusMin");
	m_RadiusMax = pSettings->r_float(section, "RadiusMax");
	m_RadiusCollided = pSettings->r_float(section, "RadiusCollided");
	m_RadiusCollidedInterpTime = pSettings->r_float(section, "RadiusCollidedInterpTime");
	m_RadiusCollisionCoeff = pSettings->r_float(section, "RadiusCollisionCoeff");
	m_RadiusMaxTime = pSettings->r_float(section, "RadiusMaxTime");
	m_Velocity = pSettings->r_float(section, "Velocity");
	m_LifeTime = pSettings->r_float(section, "LifeTime");
	m_LifeTimeCollidedMax = pSettings->r_float(section, "LifeTimeCollidedMax");
	m_FlameFadeTime = pSettings->r_float(section, "FlameFadeTime");
	m_GravityAcceleration = pSettings->r_float(section, "GravityAcceleration");

	// flames
	m_sFlameParticles = pSettings->r_string(section, "flame_particles");
	m_sFlameParticlesGround = pSettings->r_string(section, "earth_flame_particles");
}

inline CFlamethrower* CFlamethrowerTraceCollision::GetParentWeapon() const
{
	return m_flamethrower->GetParent();
}

bool CFlamethrowerTraceCollision::IsReadyToUpdateCollisions()
{
	//return true;
	if(m_State == ETraceState::Idle)
	{
		m_State == ETraceState::Air;
		return false;
	}
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
	return RadiusCurrent;
	/*if (!IsActive()) {
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
	return CurRadius;*/
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
	if (m_State == ETraceState::Idle) {
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
	m_State = ETraceState::Air;
	//feel_touch_update(m_position, GetCurrentRadius());
	m_LastUpdatedPos = m_position;
	m_particles = CParticlesObject::Create(*m_sFlameParticles, false);
	m_particles->Play(false);
}

void CFlamethrowerTraceCollision::Deactivate()
{

#ifdef DEBUG
	if(Next)
	{
		Next->Prev = nullptr;
		Next = nullptr;
	}
	if (Prev)
	{
		Prev->Next = nullptr;
		Prev = nullptr;
	}
#endif
	m_State = ETraceState::Idle;
	m_GravityVelocity = 0.0f;
	m_current_time = 0.0f;
	m_time_on_collide = 0.0f;
	RadiusOnCollide = 0.0f;
	if (m_particles) {
		m_particles->Stop();
		CParticlesObject::Destroy(m_particles);
	}
	if (m_particles_ground) {
		m_particles_ground->Stop();
		CParticlesObject::Destroy(m_particles_ground);
	}
}

void CFlamethrowerTraceCollision::Update(float DeltaTime)
{
	switch (m_State)
	{
	case ETraceState::Idle:
		{
			return;
		}
	case ETraceState::Air:
		{
		Update_Air(DeltaTime);
			break;
		}
	case ETraceState::AirToGround:
		{
		Update_AirToGround(DeltaTime);
			break;
		}
	case ETraceState::Ground:{
			Update_Ground(DeltaTime);
			break;
		}
	case ETraceState::End:
		{
		Update_End(DeltaTime);
			break;
		}
	}
	m_current_time += DeltaTime;
	m_last_update_time += DeltaTime;
	/*if (!IsActive()) {
		return;
	}
	m_current_time += DeltaTime;
	m_last_update_time += DeltaTime;
	if ((!IsCollided() && m_current_time > m_LifeTime)
		|| (IsCollided() && m_current_time > m_LifeTimeCollidedMax)) {
		Deactivate();
		return;
	}
	if (!IsCollided()) {
		m_GravityVelocity += m_GravityAcceleration * DeltaTime;
		auto old_pos = m_position;
		m_position = m_position + m_direction * m_Velocity * DeltaTime - Fvector{ 0.0f, m_GravityVelocity * DeltaTime, 0.0f };
		collide::rq_results storage;
		collide::ray_defs RD(old_pos, m_position, CDB::OPT_FULL_TEST, collide::rqtBoth);
		FlamethrowerTraceData data;
		data.TracedObj = this;
		m_direction = m_position - old_pos;
		m_direction.normalize();
		if (Level().ObjectSpace.RayQuery(storage, RD, CFlamethrowerTraceCollision::hit_callback, &data, CFlamethrowerTraceCollision::test_callback, nullptr))
		{
			m_position = old_pos + m_direction * data.HitDist;
			m_IsCollided = true;
			VERIFY2(m_RadiusCollided > 0.01, "Too small RadiusCollided in flamethrower config!");
			RadiusOnCollide = RadiusCurrent;
			m_time_on_collide = m_current_time;
		}
	}

	if (!IsActive()) {
		RadiusCurrent = 0.0f;
	}else if (IsCollided()) {
		float interpTime = std::min((m_current_time - m_time_on_collide)/m_RadiusCollidedInterpTime, 1.0f);
		RadiusCurrent = RadiusOnCollide+(m_RadiusCollided-RadiusOnCollide)*interpTime;
		clamp(RadiusCurrent, m_RadiusMin, m_RadiusCollided);
	} else if (m_current_time <= m_RadiusMaxTime) {
		float interpTime = std::min(m_current_time / m_RadiusMaxTime, 1.0f);
		RadiusCurrent = m_RadiusMin + (m_RadiusMax - m_RadiusMin) * interpTime;
		clamp(RadiusCurrent, m_RadiusMin, m_RadiusMax);
	}*/

//#ifdef DEBUG
//	Level().BulletManager().AddBulletMoveChunk(old_pos, m_position);
//#endif

	//UpdateParticles();

}

CFlamethrowerTraceManager::CFlamethrowerTraceManager(CFlamethrower* flamethrower) : m_flamethrower(flamethrower)
{

#ifdef DEBUG
	Level().BulletManager().MarkFlamethrowerTraceToDraw(this);
#endif
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
#ifdef DEBUG
	if(LastLaunched && LastLaunched->IsActive())
	{
		auto PrevLoc = LastLaunched->GetCurrentPosition();
		auto CurR = LastLaunched->GetCurrentRadius();
		auto dists = LastLaunched->GetCurrentPosition().distance_to_sqr(StartPos);
		if (dists <= CurR * CurR) {
			return;
		}
	}
#endif
	auto First = CollisionsPool.front();
	if(First->IsActive())
	{
		First = xr_new<CFlamethrowerTraceCollision>(this);
		First->Load(CollisionSection.c_str());
	} else
	{
		CollisionsPool.pop_front();
	}

#ifdef DEBUG
	if(LastLaunched && LastLaunched->IsActive())
	{
		LastLaunched->Next = First;
		First->Prev = LastLaunched;
	}
	LastLaunched = First;
#endif
	First->SetTransform(StartPos, StartDir);
	First->Activate();
	CollisionsPool.push_back(First);
	//Msg("Current collisions num in pool: [%d]", CollisionsPool.size());
}
