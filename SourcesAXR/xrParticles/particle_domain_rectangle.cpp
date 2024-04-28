#include "stdafx.h"
#include "particle_domain_rectangle.h"

#include "particle_core.h"

static constexpr PAPI::pVector vHalf(0.5, 0.5, 0.5);

ICF PAPI::pVector RandVec()
{
	return PAPI::pVector(drand48(), drand48(), drand48());
}

BOOL PAPI::pDomainRectangle::Within(const pVector& pos) const
{
	return FALSE; // XXX Is there something better?
}

void PAPI::pDomainRectangle::Generate(pVector& pos) const
{
	pos = p1 + u * drand48() + v * drand48();
}

void PAPI::pDomainRectangle::transform(PAPI::pDomain* domain, const Fmatrix& m)
{
	m.transform_tiny(p1, domain->p1);
	m.transform_dir(p2, domain->p2);
	m.transform_dir(u, domain->u);
	m.transform_dir(v, domain->v);
}

void PAPI::pDomainRectangle::transform_dir(PAPI::pDomain* domain, const Fmatrix& m)
{
	Fmatrix M = m;
	M.c.set(0, 0, 0);
	transform(domain, M);
}

PAPI::pDomainRectangle::pDomainRectangle(PDomainEnum dtype,
	float a0, float a1, float a2,
	float a3, float a4, float a5,
	float a6, float a7, float a8)
{
	p1 = pVector(a0, a1, a2);
	u = pVector(a3, a4, a5);
	v = pVector(a6, a7, a8);

	// The rest of this is needed for bouncing.
	radius1Sqr = u.length();
	pVector tu = u / radius1Sqr;
	radius2Sqr = v.length();
	pVector tv = v / radius2Sqr;

	p2 = tu ^ tv; // This is the non-unit normal.
	p2.normalize_safe(); // Must normalize it.

	// radius1 stores the d of the plane eqn.
	radius1 = -(p1 * p2);
}
