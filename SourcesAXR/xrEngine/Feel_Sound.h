#pragma once

#include "../xrGame/Metaclass.h"

class ENGINE_API CObject;

namespace Feel
{
	class	ENGINE_API Sound:
		public IMetaClass
	{
		DECLARE_METACLASS(Feel::Sound)
	public:
		virtual		void			feel_sound_new		(CObject* who, int type, CSound_UserDataPtr user_data, const Fvector& Position, float power) {};
	};
};
