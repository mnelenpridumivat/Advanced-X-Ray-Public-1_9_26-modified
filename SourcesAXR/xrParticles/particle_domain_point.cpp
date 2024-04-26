#include "stdafx.h"
#include "particle_domain_point.h"

#include "particle_core.h"

//static constexpr PAPI::pVector vHalf(0.5, 0.5, 0.5);

ICF PAPI::pVector RandVec()
{
	return PAPI::pVector(drand48(), drand48(), drand48());
}

BOOL PAPI::pDomainPoint::Within(const pVector& pos) const
{
	return FALSE; // XXX Is there something better?
}

void PAPI::pDomainPoint::Generate(pVector& pos) const
{
	pos = p1;
}

void PAPI::pDomainPoint::transform(PAPI::pDomain* domain, const Fmatrix& m)
{
	m.transform_tiny(p1, domain->p1);
}

void PAPI::pDomainPoint::transform_dir(PAPI::pDomain* domain, const Fmatrix& m)
{
	Fmatrix M = m;
	M.c.set(0, 0, 0);
	transform(domain, M);
}

PAPI::pDomainPoint::pDomainPoint(PDomainEnum dtype,
	float a0, float a1, float a2,
	float a3, float a4, float a5,
	float a6, float a7, float a8)
{
	p1 = pVector(a0, a1, a2);
}
