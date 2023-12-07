////////////////////////////////////////////////////////////////////////////
//	Module 		: ai_rat+space.h
//	Created 	: 27.07.2004
//  Modified 	: 27.07.2004
//	Author		: Dmitriy Iassenev
//	Description : Space for monster "Rat"
////////////////////////////////////////////////////////////////////////////

#pragma once

namespace RatSpace {
	enum ERatSounds {
		eRatSoundDie = static_cast<u32>(0),
		eRatSoundInjuring,
		eRatSoundAttack,
		eRatSoundVoice,
		eRatSoundEat,
		eRatSoundDummy = static_cast<u32>(-1),
	};

	enum ERatSoundMasks {
		eRatSoundMaskAnySound	= static_cast<u32>(0),
		eRatSoundMaskDie		= static_cast<u32>(-1),
		eRatSoundMaskInjuring	= static_cast<u32>(-1),
		eRatSoundMaskVoice		= static_cast<u32>(1 << 31) | 1,
		eRatSoundMaskAttack		= static_cast<u32>(1 << 30) | 2,
		eRatSoundMaskEat		= static_cast<u32>(1 << 30) | 4,
		eRatSoundMaskDummy		= static_cast<u32>(-1),
	};
}