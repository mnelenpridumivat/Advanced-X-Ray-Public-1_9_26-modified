#include "stdafx.h"
#include "particle_domain_triangle.h"

#include "particle_core.h"

static constexpr PAPI::pVector vHalf(0.5, 0.5, 0.5);

ICF PAPI::pVector RandVec()
{
	return PAPI::pVector(drand48(), drand48(), drand48());
}

BOOL PAPI::pDomainTriangle::Within(const pVector& pos) const
{
	return FALSE; // XXX Is there something better?
}

void PAPI::pDomainTriangle::Generate(pVector& pos) const
{
	float r1 = drand48();
	float r2 = drand48();
	if (r1 + r2 < 1.0f)
		pos = p1 + u * r1 + v * r2;
	else
		pos = p1 + u * (1.0f - r1) + v * (1.0f - r2);
}

void PAPI::pDomainTriangle::transform(PAPI::pDomain* domain, const Fmatrix& m)
{
	m.transform_tiny(p1, domain->p1);
	m.transform_dir(p2, domain->p2);
	m.transform_dir(u, domain->u);
	m.transform_dir(v, domain->v);
}

void PAPI::pDomainTriangle::transform_dir(PAPI::pDomain* domain, const Fmatrix& m)
{
	Fmatrix M = m;
	M.c.set(0, 0, 0);
	transform(domain, M);
}

PAPI::pDomainTriangle::pDomainTriangle(PDomainEnum dtype,
	float a0, float a1, float a2,
	float a3, float a4, float a5,
	float a6, float a7, float a8)
{
	p1 = pVector(a0, a1, a2);
	pVector tp2 = pVector(a3, a4, a5);
	pVector tp3 = pVector(a6, a7, a8);

	u = tp2 - p1;
	v = tp3 - p1;

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
