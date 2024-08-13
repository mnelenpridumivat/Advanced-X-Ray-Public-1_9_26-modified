#pragma once

namespace GameObject {
	enum ECallbackType {
		eTradeStart = static_cast<u32>(0),
		eTradeStop,
		eTradeSellBuyItem,
		eTradePerformTradeOperation,

		eZoneEnter,
		eZoneExit,
		eExitLevelBorder,
		eEnterLevelBorder,
		eDeath,

		ePatrolPathInPoint,

		eInventoryPda,
		eInventoryInfo,
		eArticleInfo,
		eTaskStateChange,
		eMapLocationAdded,

		eUseObject,

		eHit,

		eSound,

		eActionTypeMovement,
		eActionTypeWatch,
		eActionTypeRemoved,
		eActionTypeAnimation,
		eActionTypeSound,
		eActionTypeParticle,
		eActionTypeObject,
		eActionTypeWeaponFire,

		eActorSleep,

		eHelicopterOnPoint,
		eHelicopterOnHit,
		eHelicopterOnSamHit,

		eOnItemTake,
		eOnItemDrop,

		eScriptAnimation,
		
		eTraderGlobalAnimationRequest,
		eTraderHeadAnimationRequest,
		eTraderSoundEnd,

		eInvBoxItemTake,
		eWeaponNoAmmoAvailable,

		eShieldOn,
		eShieldOff,
		eJump,

		//Alundaio: added defines
		eActorHudAnimationEnd,
		//AVO: custom callbacks

		// input
		eKeyPress,
		eKeyRelease,
		eKeyHold,

		eMouseMove,
		eMouseWheel,

		// inventory
		eItemToBelt,
		eItemToSlot,
		eItemToRuck,

		// weapon
		eOnWeaponZoomIn,
		eOnWeaponZoomOut,
		eOnWeaponJammed,
		eOnWeaponFired,
		eOnWeaponMagazineEmpty,

		// vehicle
		eAttachVehicle,
		eDetachVehicle,
		eUseVehicle,

		eOnFootStep,
		//-AVO

		//Dance Maniac
		eOnActorJump,

		//eOnWeaponLowered,	 //For safemode
		//eOnWeaponRaised,	 //For safemode

		eDangerousMaterialTouch,

		eDummy = static_cast<u32>(-1),
	};
};

