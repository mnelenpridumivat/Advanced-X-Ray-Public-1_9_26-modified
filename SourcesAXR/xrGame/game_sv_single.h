#pragma once

#include "game_sv_base.h"

class xrServer;
class CALifeSimulator;

class	game_sv_Single				: public game_sv_GameState
{
private:
	typedef game_sv_GameState inherited;

protected:
	CALifeSimulator					*m_alife_simulator;

public:
									game_sv_Single			();
	~game_sv_Single			() override;

	LPCSTR				type_name				() const override { return "single";};
	void				Create					(shared_str& options) override;
//	virtual		CSE_Abstract*		get_entity_from_eid		(u16 id);


	void				OnCreate				(u16 id_who) override;
	BOOL				OnTouch					(u16 eid_who, u16 eid_what, BOOL bForced = FALSE) override;
	void				OnDetach				(u16 eid_who, u16 eid_what) override;

	// Main
	void				Update					() override;
	ALife::_TIME_ID		GetStartGameTime		() override;
	ALife::_TIME_ID		GetGameTime				() override;
	float				GetGameTimeFactor		() override;
	void				SetGameTimeFactor		(const float fTimeFactor) override;
	void				SetGameTimeFactor		(ALife::_TIME_ID GameTime, const float fTimeFactor) override;;// override;

	ALife::_TIME_ID		GetEnvironmentGameTime	() override;
	float				GetEnvironmentGameTimeFactor		() override;
	void				SetEnvironmentGameTimeFactor		(const float fTimeFactor) override;

	bool				change_level			(NET_Packet &net_packet, ClientID sender) override;
	void				save_game				(NET_Packet &net_packet, ClientID sender) override;
	bool				load_game				(NET_Packet &net_packet, ClientID sender) override;
	void				reload_game				(NET_Packet &net_packet, ClientID sender) override;
	void				switch_distance			(NET_Packet &net_packet, ClientID sender) override;
	BOOL				CanHaveFriendlyFire		() override {return FALSE;}
	void				teleport_object			(NET_Packet &packet, u16 id) override;
	void				add_restriction			(NET_Packet &packet, u16 id) override;
	void				remove_restriction		(NET_Packet &packet, u16 id) override;
	void				remove_all_restrictions	(NET_Packet &packet, u16 id) override;
	bool				custom_sls_default		() override {return !!m_alife_simulator;};
	void				sls_default				() override;
	shared_str			level_name				(const shared_str &server_options) const override;
	void				on_death				(CSE_Abstract *e_dest, CSE_Abstract *e_src) override;
				void				restart_simulator		(LPCSTR saved_game_name);

	IC			xrServer			&server					() const
	{
		VERIFY						(m_server);
		return						(*m_server);
	}

	IC			CALifeSimulator		&alife					() const
	{
		VERIFY						(m_alife_simulator);
		return						(*m_alife_simulator);
	}
};
