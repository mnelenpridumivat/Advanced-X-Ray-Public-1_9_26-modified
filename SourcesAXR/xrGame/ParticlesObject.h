#ifndef ParticlesObjectH
#define ParticlesObjectH

#include "../xrEngine/PS_instance.h"
#include "../xrParticles/particle_param_handle.h"

namespace PAPI
{
	class pVector;
}

extern const Fvector zero_vel;

class CParticlesObject		:	public CPS_Instance
{
	typedef CPS_Instance	inherited;

	u32					dwLastTime;
	void				Init				(LPCSTR p_name, IRender_Sector* S, BOOL bAutoRemove);
	void				UpdateSpatial		();

protected:
	bool				m_bLooped;			//����, ��� ������� ���������
	bool				m_bStopping;		//������� ������� Stop()

	bool m_UseOptimization = false;
	float m_OptimizationDistance = 0.0f;

protected:
	u32					mt_dt;

protected:
	~CParticlesObject	() override;

public:
						CParticlesObject	(LPCSTR p_name, BOOL bAutoRemove, bool destroy_on_game_load);

	PAPI::Handle<float> GetAlphaHandle(u32 EffectIndex);
	PAPI::Handle<PAPI::pVector> GetColorHandle(u32 EffectIndex);
	PAPI::Handle<PAPI::pVector> GetSizeHandle(u32 EffectIndex);
	PAPI::Handle<PAPI::pVector> GetVelocityHandle(u32 EffectIndex);
	PAPI::Handle<PAPI::pVector> GetRotationHandle(u32 EffectIndex);

	bool		shedule_Needed		() override {return true;};
	float		shedule_Scale		() override;
	void		shedule_Update		(u32 dt) override;
	void		renderable_Render	() override;
	void				PerformAllTheWork	(u32 dt);
	void	__stdcall	PerformAllTheWork_mt();

	void				SetOptimization(bool UseOptimization, float Distance);

	Fvector&			Position			();
	void				SetXFORM			(const Fmatrix& m);
	IC	Fmatrix&		XFORM				()	{return renderable.xform;}
	void				UpdateParent		(const Fmatrix& m, const Fvector& vel);

	void				play_at_pos			(const Fvector& pos, BOOL xform=FALSE);
	void		Play				(bool bHudMode) override;
	void				Stop				(BOOL bDefferedStop=TRUE);
	BOOL		Locked				() override { return mt_dt; }
	
	bool				IsLooped			() {return m_bLooped;}
	bool				IsAutoRemove		();
	bool				IsPlaying			();
	void				SetAutoRemove		(bool auto_remove);

	const shared_str			Name		();
public:
	static CParticlesObject*	Create		(LPCSTR p_name, BOOL bAutoRemove=TRUE, bool remove_on_game_load = true)
	{
		return xr_new<CParticlesObject>(p_name, bAutoRemove, remove_on_game_load);
	}
	static void					Destroy		(CParticlesObject*& p)
	{
		if (p){ 
			p->PSI_destroy		();
			p					= nullptr;
		}
	}
};

#endif /*ParticlesObjectH*/
