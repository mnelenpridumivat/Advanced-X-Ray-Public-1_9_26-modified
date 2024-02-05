#pragma once
#include "game_cl_base.h"
#include "script_export_space.h"

class game_cl_Single :public game_cl_GameState
{
	typedef game_cl_GameState	inherited;
public :
										game_cl_Single			();
	CUIGameCustom*			createGameUI			() override;
	char*					getTeamSection			(int Team) override;
	bool					IsServerControlHits		() override {return true;};

	ALife::_TIME_ID			GetStartGameTime		() override;
	ALife::_TIME_ID			GetGameTime				() override;
	float					GetGameTimeFactor		() override;
	void					SetGameTimeFactor		(const float fTimeFactor) override;

	ALife::_TIME_ID		GetEnvironmentGameTime		() override;
	float				GetEnvironmentGameTimeFactor() override;
				void				SetEnvironmentGameTimeFactor(ALife::_TIME_ID GameTime, const float fTimeFactor) override;
	void				SetEnvironmentGameTimeFactor(const float fTimeFactor) override;

	void		OnDifficultyChanged		();
};


// game difficulty
enum ESingleGameDifficulty{
	egdNovice			= 0,
	egdStalker			= 1,
	egdVeteran			= 2,
	egdMaster			= 3,
	egdCount,
	egd_force_u32		= static_cast<u32>(-1)
};

extern ESingleGameDifficulty g_SingleGameDifficulty;
xr_token		difficulty_type_token	[ ];

typedef enum_exporter<ESingleGameDifficulty> CScriptGameDifficulty;
add_to_type_list(CScriptGameDifficulty)
#undef script_type_list
#define script_type_list save_type_list(CScriptGameDifficulty)




