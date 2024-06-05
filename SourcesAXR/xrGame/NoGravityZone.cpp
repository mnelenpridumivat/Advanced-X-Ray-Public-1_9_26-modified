#include "stdafx.h"
#include "nogravityzone.h"
#include "../xrphysics/physicsshell.h"
#include "entity_alive.h"
#include "PHMovementControl.h"
//#include "PhWorld.h"
#include "CharacterPhysicsSupport.h"
//extern CPHWorld	*ph_world;
#include "Actor.h"
#include "debug_renderer.h"
#include "../xrphysics/IPHWorld.h"

void CNoGravityZone::Affect(SZoneObjectInfo* O)
{
	CPhysicsShellHolder* sh = smart_cast<CPhysicsShellHolder*>(O->object);
	if (!sh || AffectedObjects.find(O->object) == AffectedObjects.end())
	{
		return;
	}
	auto& ObjectData = AffectedObjects[O->object];
	CPhysicsShell* shell = sh->PPhysicsShell();
	if (shell && shell->isActive())
	{
		CPhysicsElement* e = shell->get_ElementByStoreOrder(static_cast<u16>(Random.randI(0, shell->get_ElementsNumber())));
		ObjectData.Time += Device.fTimeDelta;
		switch (ObjectData.State)
		{
		case EAffectedObjectState::Raise:
			{
				shell->set_ApplyByGravity(false);
				//e->applyImpulse({ 0.0f, 1.0f, 0.0f }, e->getMass() * fixed_step * RaiseAcceleration);
				auto vec = GetMoveVector(O->object->Position(), EAffectedObjectState::Raise);
				//e->applyForce(vec.GetNormalizedCopy(), vec.magnitude());
				e->applyImpulse(vec.GetNormalizedCopy(), e->getMass() * fixed_step /* vec.magnitude() */ * RaiseAcceleration);
				if(ObjectData.Time > RaiseTime)
				{
					ObjectData.Time -= RaiseTime;
					ObjectData.State = EAffectedObjectState::Pull;
				}
			}
		case EAffectedObjectState::Pull:
			{
				shell->set_ApplyByGravity(false);
				//e->applyImpulse({ 0.0f, -1.0f, 0.0f }, e->getMass() * fixed_step * PullAcceleration);
				auto vec = GetMoveVector(O->object->Position(), EAffectedObjectState::Pull);
				//e->applyForce(vec.GetNormalizedCopy(), vec.magnitude());
				e->applyImpulse(vec.GetNormalizedCopy(), e->getMass() * fixed_step /* vec.magnitude()*/ * RaiseAcceleration);
				if (ObjectData.Time > PullTime)
				{
					ObjectData.Time -= PullTime;
					ObjectData.State = EAffectedObjectState::Idle;
				}
			}
		case EAffectedObjectState::Idle:
			{
				shell->set_ApplyByGravity(true);
				if (ObjectData.Time > IdleTime)
				{
					ObjectData.Time -= IdleTime;
					ObjectData.State = EAffectedObjectState::Raise;
				}
			}
		}

	} else if (!O->nonalive_object)
	{
		CEntityAlive* ea = smart_cast<CEntityAlive*>(O->object);
		CPHMovementControl* mc = ea->character_physics_support()->movement();
		//CPhysicsElement* e = shell->get_ElementByStoreOrder(static_cast<u16>(Random.randI(0, shell->get_ElementsNumber())));
		ObjectData.Time += Device.fTimeDelta;
		switch (ObjectData.State)
		{
		case EAffectedObjectState::Raise:
		{
			//mc->AddControlVel(GetMoveVector(ea->Position(), EAffectedObjectState::Raise));
			auto vec = GetMoveVector(ea->Position(), EAffectedObjectState::Raise);
			{
				Fvector vel;
				mc->GetCharacterVelocity(vel);
				Msg("%f %f %f", vec.x, vec.y, vec.z);
			}
#ifdef DEBUG
			{
				if(smart_cast<CActor*>(ea))
				{
					PlayerState = EAffectedObjectState::Raise;
				}
			}
#endif
			auto vel = mc->GetVelocity();
			Fvector CenterPos = GetTargetPos(EAffectedObjectState::Raise);
			//Center(CenterPos);
			vel = vel*(std::min(ea->Position().distance_to(CenterPos) / (Radius()*1.0f), 1.0f)*0.1f+0.9f);
			mc->SetVelocity(vel);
			mc->AddControlVel(vec);
			//mc->AddControlVel({ 0.0f, /*mc->GetMass() * fixed_step * */ RaiseAcceleration , 0.0f });
			//mc->ApplyImpulse(vec.GetNormalizedCopy(), mc->GetMass() * fixed_step /* vec.magnitude() */ * RaiseAcceleration);
			//mc->ApplyImpulse({ 0.0f, 1.0f, 0.0f }, mc->GetMass() * fixed_step * RaiseAcceleration);
			if (ObjectData.Time > RaiseTime)
			{
				mc->SetApplyGravity(static_cast<BOOL>(false));
				mc->SetForcedPhysicsControl(true);
				ObjectData.Time -= RaiseTime;
				ObjectData.State = EAffectedObjectState::Pull;
			}
			break;
		}
		case EAffectedObjectState::Pull:
		{
			auto vec = GetMoveVector(ea->Position(), EAffectedObjectState::Pull);
			//mc->AddControlVel(vec);
			//mc->AddControlVel(GetMoveVector(ea->Position(), EAffectedObjectState::Pull));
			//mc->AddControlVel({ 0.0f, -/*mc->GetMass() * fixed_step * */ PullAcceleration , 0.0f });
			//mc->ApplyImpulse({ 0.0f, -1.0f, 0.0f }, mc->GetMass() * fixed_step * PullAcceleration);
			mc->ApplyImpulse(vec.GetNormalizedCopy(), mc->GetMass() * fixed_step /* vec.magnitude() */ * RaiseAcceleration);
#ifdef DEBUG
			{
				if (smart_cast<CActor*>(ea))
				{
					PlayerState = EAffectedObjectState::Pull;
				}
			}
#endif
			//if (ObjectData.Time > PullTime)
			if (mc->Environment() == CPHMovementControl::peOnGround)
			{
				mc->SetApplyGravity(static_cast<BOOL>(true));
				mc->SetForcedPhysicsControl(false);
				//ObjectData.Time -= PullTime;
				ObjectData.Time = 0.0f;
				ObjectData.State = EAffectedObjectState::Idle;
			}
			break;
		}
		case EAffectedObjectState::Idle:
		{
#ifdef DEBUG
			{
				if (smart_cast<CActor*>(ea))
				{
					PlayerState = EAffectedObjectState::Idle;
				}
			}
#endif
			if (ObjectData.Time > IdleTime)
			{
				ObjectData.Time -= IdleTime;
				ObjectData.State = EAffectedObjectState::Raise;
				mc->SetApplyGravity(static_cast<BOOL>(false));
				mc->SetForcedPhysicsControl(true);
				mc->JumpV({ 0.0f, 0.0f, 0.0f });
				mc->SetVelocity({0.0f, 0.0f, 0.0f});
				auto vec = GetMoveVector(ea->Position(), EAffectedObjectState::Raise);
				mc->ApplyImpulse(vec.GetNormalizedCopy(), mc->GetMass() * fixed_step /* vec.magnitude() */ * RaiseAcceleration);
			}
			break;
		}
		}
		/*if(!val&&mc->Environment()==CPHMovementControl::peOnGround)
		{
			Fvector gn;
			mc->GroundNormal(gn);
			mc->ApplyImpulse(gn,mc->GetMass()*physics_world()->Gravity()*fixed_step);

		}*/
	}
}

#ifdef DEBUG
void CNoGravityZone::OnRender()
{
	inherited::OnRender();
	if(PlayerState == EAffectedObjectState::Idle)
	{
		return;
	}
	Fvector TargetPos = GetTargetPos(PlayerState);
	u32 Color = color_xrgb(0, 0, 0);
	Fmatrix l_sphere;
	l_sphere.scale(1, 1, 1);
	l_sphere.translate_add(TargetPos);
	Level().debug_renderer().draw_ellipse(l_sphere, Color);
	//Fmatrix
	Level().debug_renderer().draw_line(Fidentity, PlayerPos, PlayerPos + (NormDir * Power), color_xrgb(0,0,0));
}
#endif

void CNoGravityZone::enter_Zone(SZoneObjectInfo& io)
{
	inherited::enter_Zone(io);
	switchGravity(io,false);
	AffectedObjects[io.object] = { EAffectedObjectState::Idle , IdleTime + 0.01f };
	if (!io.nonalive_object) {
		CEntityAlive* ea = smart_cast<CEntityAlive*>(io.object);
		CPHMovementControl* mc = ea->character_physics_support()->movement();
		//mc->ApplyImpulse({ 0.0f, 0.1f, 0.0f }, 1.0f);
		mc->JumpV({ 0.0f, 0.0f, 0.0f });
	}

}
void CNoGravityZone::exit_Zone(SZoneObjectInfo& io)
{
	AffectedObjects.erase(io.object);
	switchGravity(io,true);
	inherited::exit_Zone(io);
#ifdef DEBUG
	{
		if (smart_cast<CActor*>(io.object))
		{
			PlayerState = EAffectedObjectState::Idle;
		}
	}
#endif
}

void CNoGravityZone::UpdateWorkload(u32 dt)
{
	OBJECT_INFO_VEC_IT i=m_ObjectInfoMap.begin(),e=m_ObjectInfoMap.end();
	/*for (; e != i; i++)
	{
		switchGravity(*i, false);
	}*/
	AffectObjects();
}

Fvector CNoGravityZone::GetMoveVector(Fvector ObjPos, EAffectedObjectState State)
{
	Fvector TargetPos = GetTargetPos(State);
	Fvector CenterPos;
	Center(CenterPos);
	//float power = (Radius() < TargetPos.distance_to(ObjPos)) ? 0 : (1.f - m_fAttenuation * (TargetPos.distance_to(ObjPos) / Radius()) * (TargetPos.distance_to(ObjPos) / Radius()));
	float power = 1.0f - TargetPos.distance_to(ObjPos) / (Radius() * 2);
	float rel_power = (power < 0.0f) ? 0.0f : power;
	//float rel_power = RelativePower(TargetPos.distance_to(ObjPos), Radius());
	//float rel_power = (Radius() - CenterPos.distance_to(ObjPos)) / Radius();
	//float rel_power = 1;
	float throw_power = m_fThrowInImpulseAlive * rel_power * rel_power * rel_power * rel_power * rel_power;
	Fvector Delta = (TargetPos - ObjPos).GetNormalizedCopy();
	//float Speed = (0.1f * PullCurveCoeff * std::pow(TargetPos.distance_to(ObjPos), 2));
	//float Speed = (0.1f * PullCurveCoeff * TargetPos.distance_to(ObjPos));
#ifdef DEBUG
	//if (bDebug) {
	//	Msg("%f %f %f", (Delta * throw_power).x, (Delta * throw_power).y, (Delta * throw_power).z);
	//}
	PlayerPos = ObjPos;
	NormDir = Delta;
	Power = throw_power;
#endif
	return Delta * throw_power;
}

Fvector CNoGravityZone::GetTargetPos(EAffectedObjectState State)
{
	Fvector TargetPos;
	Center(TargetPos);
	switch (State) {
	case EAffectedObjectState::Raise:
	{
		TargetPos.y += Radius() * 0.8f;
		break;
	}
	case EAffectedObjectState::Pull:
	{
		TargetPos.y -= Radius();
		break;
	}
	}
	return TargetPos;
}

void CNoGravityZone::switchGravity(SZoneObjectInfo& io, bool val)
{
	if(io.object->getDestroy()) return;
	CPhysicsShellHolder* sh= smart_cast<CPhysicsShellHolder*>(io.object);
	if(!sh)return;
	CPhysicsShell* shell=sh->PPhysicsShell();
	if(shell&&shell->isActive())
	{
		shell->set_ApplyByGravity(val);
		/*if(!val&&shell->get_ApplyByGravity())
		{
			CPhysicsElement* e=shell->get_ElementByStoreOrder(static_cast<u16>(Random.randI(0, shell->get_ElementsNumber())));
			if(e->isActive()){
				e->applyImpulseTrace(Fvector().random_point(e->getRadius()),Fvector().random_dir(),shell->getMass()*physics_world()->Gravity()*fixed_step,e->m_SelfID);

			}
			return;
		}*/
		//shell->SetAirResistance(0.f,0.f);
		//shell->set_DynamicScales(1.f);
		return;
	}
	if(!io.nonalive_object)
	{
		CEntityAlive* ea=smart_cast<CEntityAlive*>(io.object);
		CPHMovementControl*mc=ea->character_physics_support()->movement();
		mc->SetApplyGravity(static_cast<BOOL>(val));
		mc->SetForcedPhysicsControl(!val);
		/*if(!val&&mc->Environment()==CPHMovementControl::peOnGround)
		{
			Fvector gn;
			mc->GroundNormal(gn);
			mc->ApplyImpulse(gn,mc->GetMass()*physics_world()->Gravity()*fixed_step);
			
		}*/
	}
}
