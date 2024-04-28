#include "stdafx.h"
#include "particle_domain_plane.h"

#include "particle_core.h"

static constexpr PAPI::pVector vHalf(0.5, 0.5, 0.5);

ICF PAPI::pVector RandVec()
{
	return PAPI::pVector(drand48(), drand48(), drand48());
}

BOOL PAPI::pDomainPlane::Within(const pVector& pos) const
{
	// Distance from plane = n * p + d
	// Inside is the positive half-space.
	return pos * p2 >= -radius1;
}

void PAPI::pDomainPlane::Generate(pVector& pos) const
{
	// How do I sensibly make a point on an infinite plane?
	pos = p1;
}

void PAPI::pDomainPlane::transform(PAPI::pDomain* domain, const Fmatrix& m)
{
	m.transform_tiny(p1, domain->p1);
	m.transform_dir(p2, domain->p2);
	// radius1 stores the d of the plane eqn.
	radius1 = -(p1 * p2);
}

void PAPI::pDomainPlane::transform_dir(PAPI::pDomain* domain, const Fmatrix& m)
{
	Fmatrix M = m;
	M.c.set(0, 0, 0);
	transform(domain, M);
}

PAPI::pDomainPlane::pDomainPlane(PDomainEnum dtype,
	float a0, float a1, float a2,
	float a3, float a4, float a5,
	float a6, float a7, float a8)
{
	p1 = pVector(a0, a1, a2);
	p2 = pVector(a3, a4, a5);
	p2.normalize_safe(); // Must normalize it.

	// radius1 stores the d of the plane eqn.
	radius1 = -(p1 * p2);
}
