////////////////////////////////////////////////////////////////////////////////
//	Module		:	cta_game_artefact.h
//	Created		:	19.12.2007
//	Modified	:	19.12.2007
//	Autor		:	Alexander Maniluk
//	Description	:	Artefact object for Capture The Artefact game mode
////////////////////////////////////////////////////////////////////////////////

#ifndef CTA_GAME_ARTEFACT
#define CTA_GAME_ARTEFACT

#include "Artefact.h"
#include "game_base.h"

class game_cl_CaptureTheArtefact;
class	CtaGameArtefact :
		public	CArtefact
{
public:
						CtaGameArtefact				();
						~CtaGameArtefact			() override;

	virtual		bool	Action						(s32 cmd, u32 flags);
						void	OnStateSwitch				(u32 S) override;
						void	OnAnimationEnd				(u32 state) override;
						void	UpdateCLChild				() override;
						bool	CanTake						() const override;
	//virtual		void	net_Export					(NET_Packet& P);
						void				PH_A_CrPr			() override;
	//virtual void				Interpolate			();
protected:
						void	CreateArtefactActivation	() override;
	virtual		void	InitializeArtefactRPoint	();
	//virtual		BOOL	net_Relevant				();
private:
				bool	IsMyTeamArtefact			();
	typedef CArtefact inherited;
	game_cl_CaptureTheArtefact*			m_game;
	Fvector3 const *					m_artefact_rpoint;
	ETeam								m_my_team;
}; //class CtaGameArtefact

#endif //CTA_GAME_ARTEFACT