#include "stdafx.h"
#include "particle_domain_Blob.h"

#include "particle_core.h"

//static constexpr PAPI::pVector vHalf(0.5, 0.5, 0.5);

ICF PAPI::pVector RandVec()
{
	return PAPI::pVector(drand48(), drand48(), drand48());
}

BOOL PAPI::pDomainBlob::Within(const pVector& pos) const
{
	pVector x(pos - p1);
	// return exp(-0.5 * xSq * Sqr(oneOverSigma)) * ONEOVERSQRT2PI * oneOverSigma;
	float Gx = expf(x.length2() * radius2Sqr) * radius2;
	return (drand48() < Gx);
}

void PAPI::pDomainBlob::Generate(pVector& pos) const
{
	pos.x = p1.x + NRand(radius1);
	pos.y = p1.y + NRand(radius1);
	pos.z = p1.z + NRand(radius1);
}

void PAPI::pDomainBlob::transform(PAPI::pDomain* domain, const Fmatrix& m)
{
	m.transform_tiny(p1, domain->p1);
}

void PAPI::pDomainBlob::transform_dir(PAPI::pDomain* domain, const Fmatrix& m)
{
	Fmatrix M = m;
	M.c.set(0, 0, 0);
	transform(domain, M);
}

PAPI::pDomainBlob::pDomainBlob(PDomainEnum dtype,
	float a0, float a1, float a2,
	float a3, float a4, float a5,
	float a6, float a7, float a8)
{
	p1 = pVector(a0, a1, a2);
	radius1 = a3;
	float tmp = 1.f / radius1;
	radius2Sqr = -0.5f * _sqr(tmp);
	radius2 = ONEOVERSQRT2PI * tmp;
}
