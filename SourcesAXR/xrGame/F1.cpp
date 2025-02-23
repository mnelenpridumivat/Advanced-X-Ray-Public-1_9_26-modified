#include "pch_script.h"
#include "f1.h"
#include "WeaponAmmo.h"
#include "Medkit.h"
#include "Antirad.h"
#include "FoodItem.h"
#include "BottleItem.h"
#include "ExplosiveItem.h"
#include "InventoryBox.h"
#include "Battery.h"
#include "AnomalyDetector.h"
#include "RepairKit.h"
#include "AntigasFilter.h"
#include "CustomBackpack.h"
#include "ArtefactContainer.h"
#include "SleepingBag.h"
#include "FlameCanister.h"

CF1::CF1(void) {
}

CF1::~CF1(void) {
}

using namespace luabind;

#pragma optimize("s",on)
void CF1::script_register	(lua_State *L)
{
	module(L)
	[
		class_<CF1,CGameObject>("CF1")
			.def(constructor<>()),
			//new 14.10.08 peacemaker
		class_<CWeaponAmmo,CGameObject>("CWeaponAmmo")
			.def(constructor<>()),
		class_<CFlameCanister, CGameObject>("CFlameCanister")
			.def(constructor<>()),
		class_<CMedkit,CGameObject>("CMedkit")
			.def(constructor<>()),
		class_<CAntirad,CGameObject>("CAntirad")
			.def(constructor<>()),
		class_<CFoodItem,CGameObject>("CFoodItem")
			.def(constructor<>()),
		class_<CBottleItem,CGameObject>("CBottleItem")
			.def(constructor<>()),
		class_<CInventoryBox,CGameObject>("CInventoryBox")
			.def(constructor<>()),
		class_<CExplosiveItem, CGameObject>("CExplosiveItem")
			.def(constructor<>()),
		class_<CBattery, CGameObject>("CBattery")
			.def(constructor<>()),
		class_<CAntigasFilter, CGameObject>("CAntigasFilter")
			.def(constructor<>()),
		class_<CRepairKit, CGameObject>("CRepairKit")
			.def(constructor<>()),
		class_<CDetectorAnomaly, CGameObject>("CDetectorAnomaly")
			.def(constructor<>()),
		class_<CCustomBackpack, CGameObject>("CCustomBackpack")
			.def(constructor<>()),
		class_<CArtefactContainer, CGameObject>("CArtefactContainer")
			.def(constructor<>()),
		class_<CSleepingBag, CGameObject>("CSleepingBag")
			.def(constructor<>())
	];
}

SCRIPT_EXPORT2(CF1, CObjectScript);
