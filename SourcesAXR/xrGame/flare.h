#pragma once

class CLAItem;
class CParticlesObject;

#include "hud_item_object.h"

class CFlare :
	public CHudItemObject,
	public IMetaClass
{
	DECLARE_METACLASS1(CFlare, CHudItemObject)
private:
	typedef			CHudItemObject	inherited;
	enum FlareStates{eFlareHidden,eFlareShowing,eFlareIdle,eFlareHiding,eFlareDropping};

	CLAItem*					light_lanim;
	ref_light					light_render;
	CParticlesObject*			m_pFlareParticles;
	float						m_work_time_sec;
	void						SwitchOn						();
	void						SwitchOff						();
	void						FirePoint						(Fvector&);
	void						ParticlesMatrix					(Fmatrix&);
public:
	void				UpdateCL						() override;
	void				Load							(LPCSTR section) override;
	BOOL				net_Spawn						(CSE_Abstract* DC) override;
	void				net_Destroy						() override;

	void				OnStateSwitch					(u32 S) override;
	void				OnAnimationEnd					(u32 state) override;

	void				UpdateXForm						() override;

	void						ActivateFlare					();
	void						DropFlare						();
	bool						IsFlareActive					();
};