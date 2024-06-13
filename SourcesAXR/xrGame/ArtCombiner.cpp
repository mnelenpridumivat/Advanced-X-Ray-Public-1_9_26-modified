#include "stdafx.h"
#include "ArtCombiner.h"

void CArtCombiner::Load(LPCSTR section)
{
	CArtefact::Load(section);
	CArtContainer::Load(section);
}

BOOL CArtCombiner::net_Spawn(CSE_Abstract* DC)
{
	return CArtefact::net_Spawn(DC);
}

void CArtCombiner::save(NET_Packet& output_packet)
{
	CArtefact::save(output_packet);
	CArtContainer::save(output_packet);
}

void CArtCombiner::load(IReader& input_packet)
{
	CArtefact::load(input_packet);
	CArtContainer::load(input_packet);
}

u32 CArtCombiner::Cost() const
{
	auto res = CArtefact::Cost();
	res += CArtContainer::Cost();
	return res;
}

float CArtCombiner::Weight() const
{
	auto res = CArtefact::Weight();
	res += CArtContainer::Weight();
	return res;
}

float CArtCombiner::GetHealthPower() const
{
	auto base = CArtefact::GetHealthPower();

	for (const auto& artefact : m_sArtefactsInside)
	{
		base += artefact->GetHealthPower();
	}

	return base;
}

float CArtCombiner::GetRadiationPower() const
{
	auto base = CArtefact::GetRadiationPower();

	for (const auto& artefact : m_sArtefactsInside)
	{
		base += artefact->GetRadiationPower();
	}

	return base;
}

float CArtCombiner::GetSatietyPower() const
{
	auto base = CArtefact::GetSatietyPower();

	for (const auto& artefact : m_sArtefactsInside)
	{
		base += artefact->GetSatietyPower();
	}

	return base;
}

float CArtCombiner::GetPowerPower() const
{
	auto base = CArtefact::GetPowerPower();

	for (const auto& artefact : m_sArtefactsInside)
	{
		base += artefact->GetPowerPower();
	}

	return base;
}

float CArtCombiner::GetBleedingPower() const
{
	auto base = CArtefact::GetBleedingPower();

	for (const auto& artefact : m_sArtefactsInside)
	{
		base += artefact->GetBleedingPower();
	}

	return base;
}

float CArtCombiner::AdditionalInventoryWeight() const
{
	auto base = CArtefact::AdditionalInventoryWeight();

	for (const auto& artefact : m_sArtefactsInside)
	{
		base += artefact->AdditionalInventoryWeight();
	}

	return base;
}

float CArtCombiner::GetImmunity(ALife::EHitType hit_type)
{
	auto base = m_ArtefactHitImmunities.GetHitImmunity(hit_type);

	for (const auto& artefact : m_sArtefactsInside)
	{
		base += artefact->GetImmunity(hit_type);
	}
	return base;
}
