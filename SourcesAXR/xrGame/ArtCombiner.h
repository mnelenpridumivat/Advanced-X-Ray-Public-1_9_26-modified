#pragma once
#include "ArtContainer.h"
#include "Artefact.h"
class CArtCombiner :
    public CArtefact,
	public CArtContainer
{
	typedef CArtefact inherited;

public:

	void			Load(LPCSTR section) override;
	BOOL			net_Spawn(CSE_Abstract* DC) override;

	void			save(NET_Packet& output_packet) override;
	void			load(IReader& input_packet) override;

	u32				Cost() const override;
	float			Weight() const override;

	virtual float GetHealthPower() const override;
	virtual float GetRadiationPower() const override;
	virtual float GetSatietyPower() const override;
	virtual float GetPowerPower() const override;
	virtual float GetBleedingPower() const override;
	virtual float AdditionalInventoryWeight() const override;

	virtual float GetImmunity(ALife::EHitType hit_type) override;

};

