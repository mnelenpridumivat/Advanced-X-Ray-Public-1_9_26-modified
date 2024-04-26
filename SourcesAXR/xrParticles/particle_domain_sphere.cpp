#include "stdafx.h"
#include "particle_domain_sphere.h"

#include "particle_core.h"

//static constexpr PAPI::pVector vHalf(0.5, 0.5, 0.5);

ICF PAPI::pVector RandVec()
{
	return PAPI::pVector(drand48(), drand48(), drand48());
}

BOOL PAPI::pDomainSphere::Within(const pVector& pos) const
{
	pVector rvec(pos - p1);
	float rSqr = rvec.length2();
	return rSqr <= radius1Sqr && rSqr >= radius2Sqr;
}

void PAPI::pDomainSphere::Generate(pVector& pos) const
{
	// Place on [-1..1] sphere
	pos = RandVec() - vHalf;
	pos.normalize_safe();

	// Scale unit sphere pos by [0..r] and translate
	// (should distribute as r^2 law)
	if (radius1 == radius2)
		pos = p1 + pos * radius1;
	else
		pos = p1 + pos * (radius2 + drand48() * (radius1 - radius2));
}

void PAPI::pDomainSphere::transform(PAPI::pDomain* domain, const Fmatrix& m)
{
	m.transform_tiny(p1, domain->p1);
}

void PAPI::pDomainSphere::transform_dir(PAPI::pDomain* domain, const Fmatrix& m)
{
	Fmatrix M = m;
	M.c.set(0, 0, 0);
	transform(domain, M);
}

PAPI::pDomainSphere::pDomainSphere(PDomainEnum dtype,
	float a0, float a1, float a2,
	float a3, float a4, float a5,
	float a6, float a7, float a8)
{
	p1 = pVector(a0, a1, a2);
	if (a3 > a4)
	{
		radius1 = a3; radius2 = a4;
	}
	else
	{
		radius1 = a4; radius2 = a3;
	}
	radius1Sqr = radius1 * radius1;
	radius2Sqr = radius2 * radius2;
}
