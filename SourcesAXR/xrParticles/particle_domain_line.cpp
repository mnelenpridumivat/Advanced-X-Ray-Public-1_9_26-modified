#include "stdafx.h"
#include "particle_domain_line.h"

#include "particle_core.h"

static constexpr PAPI::pVector vHalf(0.5, 0.5, 0.5);

ICF PAPI::pVector RandVec()
{
	return PAPI::pVector(drand48(), drand48(), drand48());
}

BOOL PAPI::pDomainLine::Within(const pVector& pos) const
{
	return FALSE; // XXX Is there something better?
}

void PAPI::pDomainLine::Generate(pVector& pos) const
{
	pos = p1 + p2 * drand48();
}

void PAPI::pDomainLine::transform(PAPI::pDomain* domain, const Fmatrix& m)
{
	m.transform_tiny(p1, domain->p1);
	m.transform_dir(p2, domain->p2);
}

void PAPI::pDomainLine::transform_dir(PAPI::pDomain* domain, const Fmatrix& m)
{
	Fmatrix M = m;
	M.c.set(0, 0, 0);
	transform(domain, M);
}

PAPI::pDomainLine::pDomainLine(PDomainEnum dtype,
	float a0, float a1, float a2,
	float a3, float a4, float a5,
	float a6, float a7, float a8)
{
	p1 = pVector(a0, a1, a2);
	pVector tmp(a3, a4, a5);
	// p2 is vector3 from p1 to other endpoint.
	p2 = tmp - p1;
}
