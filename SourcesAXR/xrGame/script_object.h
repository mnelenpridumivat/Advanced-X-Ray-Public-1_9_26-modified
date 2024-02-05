////////////////////////////////////////////////////////////////////////////
//	Module 		: script_object.h
//	Created 	: 06.10.2003
//  Modified 	: 14.12.2004
//	Author		: Dmitriy Iassenev
//	Description : Script object class
////////////////////////////////////////////////////////////////////////////

#pragma once

#include "gameobject.h"
#include "script_entity.h"

class CScriptObject : 
	public CGameObject,
	public CScriptEntity
{
public:
								CScriptObject			();
								~CScriptObject			() override;
								DLL_Pure			*_construct				() override;
								void				reinit					() override;
								BOOL				net_Spawn				(CSE_Abstract* DC) override;
								void				net_Destroy				() override;
								BOOL				UsedAI_Locations		() override;
								void				shedule_Update			(u32 DT) override;
								void				UpdateCL				() override;
								CScriptEntity*		cast_script_entity		() override {return this;}
};
