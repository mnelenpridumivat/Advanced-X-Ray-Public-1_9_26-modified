#ifndef ACTOR_MP_CLIENT_H
#define ACTOR_MP_CLIENT_H

#include "actor.h"
#include "actor_mp_state.h"
#include "anticheat_dumpable_object.h"

class CActorMP :
	public IAnticheatDumpable,
	public CActor,
	public IMetaClass
{
	DECLARE_METACLASS2(CActorMP, CActor, IAnticheatDumpable)
private:
	typedef CActor			inherited;

private:
	actor_mp_state_holder	m_state_holder;
	//bool					m_i_am_dead;
	float					prev_cam_inert_value;
	static const float		cam_inert_value;

private:
			void			fill_state			(actor_mp_state &state);
			void			process_packet		(net_update		&N);
			void			postprocess_packet	(net_update_A	&packet);

public:
							CActorMP			();
	void			net_Export			(NET_Packet		&packet) override;
	void			net_Import			(NET_Packet		&packet) override;
	BOOL			net_Relevant		() override;
	void			OnEvent				(NET_Packet		&packet, u16 type) override;
	void			Die					(CObject		*killer) override;
	void			DumpActiveParams	(shared_str const & section_name, CInifile & dst_ini) const override;
	shared_str const 		GetAnticheatSectionName	() const override { return "mp_actor"; };
	void			On_SetEntity		() override;
	void			On_LostEntity		() override;
protected:
	void			cam_Set					(EActorCameras style) override;
			void			use_booster				(NET_Packet &packet);
};

#endif // ACTOR_MP_CLIENT_H