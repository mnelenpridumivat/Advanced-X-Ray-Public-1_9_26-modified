////////////////////////////////////////////////////////////////////////////
//	Module 		: script_engine_export.cpp
//	Created 	: 01.04.2004
//  Modified 	: 22.06.2004
//	Author		: Dmitriy Iassenev
//	Description : XRay Script Engine export
////////////////////////////////////////////////////////////////////////////

#include "pch_script.h"

#define SCRIPT_REGISTRATOR
#include "script_export_space.h"
#include "script_engine_export.h"
#include <vector>
#include <functional>

//#define _DEBUG

#pragma optimize("s",on)
template <typename TList> struct Register
{
	ASSERT_TYPELIST(TList);

	static void _Register(lua_State *L)
	{
		Register<TList::Tail>::_Register(L);
#ifdef XRGAME_EXPORTS
#	ifdef _DEBUG
		Msg("Exporting %s",typeid(TList::Head).name());
#	endif
#endif
		TList::Head::script_register(L);
	}
};

#undef _DEBUG

template <> struct Register<Loki::NullType>
{
	static void _Register(lua_State *L)
	{
	}
};

template <typename T1, typename T2>
struct TypePair {
	typedef T1	first;
	typedef T2	second;
};

template <typename TFullList> struct DynamicCast
{
	ASSERT_TYPELIST(TFullList);

	template <typename TList, typename T> struct Helper2
	{
		typedef typename TList::Head Head;

		static void Register(lua_State *L)
		{
			Helper2<TList::Tail,T>::Register(L);
			declare<Loki::SuperSubclassStrict<Head,T>::value>();
		}

		template <bool _1>
		static void declare()
		{
		}

		template <>
		static void declare<true>()
		{
			Msg		("Exporting function to cast from \"%s\" to \"%s\"",typeid(T).name(),typeid(Head).name());
		}
	};

	template <typename T> struct Helper2<Loki::NullType,T>
	{
		static void Register(lua_State *L)
		{
		}
	};

	template <typename TList> struct Helper
	{
		static void Register(lua_State *L)
		{
			Helper<TList::Tail>::Register(L);
			Helper2<TFullList,TList::Head>::Register(L);
		}
	};

	template <> struct Helper<Loki::NullType>
	{
		static void Register(lua_State *L)
		{
		}
	};

	static void Register(lua_State *L)
	{
		Helper<TFullList>::Register(L);
	}
};

//#define EXPORT_CLASS(Class) Class::script_register(lua_State *L)

void export_classes	(lua_State *L)
{
	//EXPORT_CLASS(Class);

	/*CGameGraph::script_register(L);
	gamespy_gp_account_manager::script_register(L);
	gamespy_gp_suggest_nicks_cb::script_register(L);
	gamespy_gp_account_operation_cb::script_register(L);
	gamespy_gp_account_profiles_cb::script_register(L);
	gamespy_gp_found_email_cb::script_register(L);
	CScriptActionBase::script_register(L);
	CScriptActionPlanner::script_register(L);
	CActor::script_register(L);
	//CAI_Crow::script_register(L);
	CAnomalPseudoGigant::script_register(L);
	CAI_Bloodsucker::script_register(L);
	CAI_Boar::script_register(L);
	CBurer::script_register(L);
	CCat::script_register(L);
	CChimera::script_register(L);
	CController::script_register(L);
	CAI_Dog::script_register(L);
	CAI_Flesh::script_register(L);
	CFracture::script_register(L);
	CPoltergeist::script_register(L);
	CAI_PseudoDog::script_register(L);
	CPsyDog::script_register(L);
	CPsyDogPhantom::script_register(L);
	CPseudoGigant_orig::script_register(L);
	CSnork::script_register(L);
	CTushkano::script_register(L);
	CZombie::script_register(L);
	CAI_Stalker::script_register(L);
	CAI_Trader::script_register(L);
	CALifeMonsterDetailPathManager::script_register(L);
	CALifeMonsterMovementManager::script_register(L);
	CALifeMonsterPatrolPathManager::script_register(L);
	//CALifeOnlineOfflineGroupBrain::script_register(L);
	CALifeSimulator::script_register(L);
	CALifeSmartTerrainTask::script_register(L);
	CArtefact::script_register(L);
	DLL_PureScript::script_register(L);
	ISheduledScript::script_register(L);
	IRenderableScript::script_register(L);
	ICollidableScript::script_register(L);
	CObjectScript::script_register(L);
	CBlendScript::script_register(L);
	IRender_VisualScript::script_register(L);
	IKinematicsAnimatedScript::script_register(L);
	CCar::script_register(L);
	CClientSpawnManager::script_register(L);
	console_registrator::script_register(L);
	CCoverPoint::script_register(L);
	demo_info::script_register(L);
	demo_player_info::script_register(L);
	CEF_Storage::script_register(L);
	CExplosive::script_register(L);
	CF1::script_register(L);
	fs_registrator::script_register(L);
	CGameTask::script_register(L);
	CScriptGameDifficulty::script_register(L);
	CGameGraph::script_register(L);
	CHairsZone::script_register(L);
	CHangingLamp::script_register(L);
	CHelicopter::script_register(L);
	CHolderCustom::script_register(L);
	key_binding_registrator::script_register(L);
	CLevel::script_register(L);
	gamespy_gp_profile::script_register(L);
	gamespy_gp_login_operation_cb::script_register(L);
	gamespy_gp_login_manager::script_register(L);
	CMemoryInfo::script_register(L);
	CMincer::script_register(L);
	CMosquitoBald::script_register(L);
	CParticleParams::script_register(L);
	CPatrolPathParams::script_register(L);
	CPhraseDialogExporter::script_register(L);
	//CPHCallOnStepCondition::script_register(L);
	//CPHExpireOnStepCondition::script_register(L);
	//CPHConstForceAction::script_register(L);
	CPhysicObject::script_register(L);
	cphysics_element_scripted::script_register(L);
	cphysics_joint_scripted::script_register(L);
	cphysics_shell_scripted::script_register(L);
	cphysics_world_scripted::script_register(L);
	gamespy_profile_store_operation_cb::script_register(L);
	profile_data_script_registrator::script_register(L);
	gamespy_profile_profile_store::script_register(L);
	CScriptPropertyEvaluator::script_register(L);
	CPropertyStorage::script_register(L);
	//CRadioactiveZone::script_register(L);
	CRGD5::script_register(L);
	CSavedGameWrapper::script_register(L);
	CScope::script_register(L);
	CScriptActionCondition::script_register(L);
	CScriptAnimationAction::script_register(L);
	CScriptBinderObject::script_register(L);
	CScriptEffector::script_register(L);
	CScriptEntityAction::script_register(L);
	CScriptGameObject::script_register(L);
	CScriptHit::script_register(L);
	lanim_registrator::script_register(L);
	CScriptMonsterAction::script_register(L);
	CScriptMonsterHitInfo::script_register(L);
	CScriptMovementAction::script_register(L);
	CScriptObjectAction::script_register(L);
	CScriptParticles::script_register(L);
	CScriptParticleAction::script_register(L);
	CScriptRenderDevice::script_register(L);
	CScriptSound::script_register(L);
	CScriptSoundAction::script_register(L);
	CScriptSoundInfo::script_register(L);
	UIRegistrator::script_register(L);
	CScriptWatchAction::script_register(L);
	CScriptWorldPropertyWrapper::script_register(L);
	CScriptWorldStateWrapper::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);
	::script_register(L);*/

	/*CScriptZone::script_register(L);
	CSmartZone::script_register(L);
	CActor::script_register(L);
	CAI_Stalker::script_register(L);
	CHelicopter::script_register(L);
	CPhysicObject::script_register(L);
	CHangingLamp::script_register(L);
	CAI_Bloodsucker::script_register(L);
	CAI_Boar::script_register(L);
	CAI_Dog::script_register(L);
	CAI_Flesh::script_register(L);
	CAI_PseudoDog::script_register(L);
	CBurer::script_register(L);
	CCat::script_register(L);
	CChimera::script_register(L);
	CController::script_register(L);
	CFracture::script_register(L);
	CPoltergeist::script_register(L);
	CPseudoGigant_orig::script_register(L);
	CAnomalPseudoGigant::script_register(L);
	CZombie::script_register(L);
	CSnork::script_register(L);
	CTushkano::script_register(L);
	CPsyDog::script_register(L);
	CPsyDogPhantom::script_register(L);
	CTorch::script_register(L);
	CScope::script_register(L);
	CStalkerOutfit::script_register(L);
	CWeaponBinoculars::script_register(L);
	CWeaponKnife::script_register(L);
	CWeaponBM16::script_register(L);
	CWeaponGroza::script_register(L);
	CWeaponSVD::script_register(L);
	CWeaponAK74::script_register(L);
	CWeaponLR300::script_register(L);
	CWeaponHPSA::script_register(L);
	CWeaponPM::script_register(L);
	CWeaponRG6::script_register(L);
	CWeaponRPG7::script_register(L);
	CWeaponShotgun::script_register(L);
	CWeaponSVU::script_register(L);
	CWeaponUSP45::script_register(L);
	CWeaponVal::script_register(L);
	CWeaponVintorez::script_register(L);
	CWeaponWalther::script_register(L);
	CHairsZone::script_register(L);
	CMosquitoBald::script_register(L);
	CMincer::script_register(L);
	CMincer::script_register(L);
	CF1::script_register(L);
	CRGD5::script_register(L);*/
	//CFoodItem::script_register(L);
	//CBattery::script_register(L);
	//CAntigasFilter::script_register(L);
	//CRepairKit::script_register(L);
	//CInventoryBox::script_register(L);
	//CExplosiveItem::script_register(L);

	Register<script_type_list>::_Register(L);

//	DynamicCast<script_type_list>::Register(L);
//	Register<Loki::TL::DerivedToFrontAll<script_type_list>::Result>::_Register(L);
}
