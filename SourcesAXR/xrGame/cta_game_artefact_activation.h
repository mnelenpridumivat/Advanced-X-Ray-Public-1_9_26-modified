////////////////////////////////////////////////////////////////////////////////
//	Module		:	cta_game_artefact.h
//	Created		:	19.12.2007
//	Modified	:	19.12.2007
//	Autor		:	Alexander Maniluk
//	Description	:	Artefact object for Capture The Artefact game mode
////////////////////////////////////////////////////////////////////////////////
#ifndef CTA_GAME_ARTEFACT_ACTIVATION
#define CTA_GAME_ARTEFACT_ACTIVATION

#include "artefact_activation.h"

class	CtaArtefactActivation :
	public SArtefactActivation,
	public IMetaClass
{
	DECLARE_METACLASS1(CtaArtefactActivation, SArtefactActivation)
public:
							CtaArtefactActivation	(CArtefact* af, u32 owner_id);
	virtual					~CtaArtefactActivation	();

							void		UpdateActivation		() override;
							void		Load					() override;
							void		Start					() override;
							void		Stop					() override;
							void		ChangeEffects			() override;
							void		UpdateEffects			() override;
							void		SpawnAnomaly			() override;
							void		PhDataUpdate			(float step) override;
private:
	typedef		SArtefactActivation		inherited;
}; // class CtaArtefactActivation
		

#endif // CTA_GAME_ARTEFACT_ACTIVATION
