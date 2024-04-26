#include "stdafx.h"
#include "particle_domain_disc.h"

#include "particle_core.h"

//static constexpr PAPI::pVector vHalf(0.5, 0.5, 0.5);

ICF PAPI::pVector RandVec()
{
	return PAPI::pVector(drand48(), drand48(), drand48());
}

BOOL PAPI::pDomainDisc::Within(const pVector& pos) const
{
	return FALSE; // XXX Is there something better?
}

void PAPI::pDomainDisc::Generate(pVector& pos) const
{
	float theta = drand48() * 2.0f * float(M_PI); // Angle around normal
	// Distance from center
	float r = radius2 + drand48() * (radius1 - radius2);

	float x = r * _cos(theta); // Weighting of each frame vector3
	float y = r * _sin(theta);

	pos = p1 + u * x + v * y;
}

void PAPI::pDomainDisc::transform(PAPI::pDomain* domain, const Fmatrix& m)
{
	m.transform_tiny(p1, domain->p1);
	m.transform_dir(p2, domain->p2);
	m.transform_dir(u, domain->u);
	m.transform_dir(v, domain->v);
}

void PAPI::pDomainDisc::transform_dir(PAPI::pDomain* domain, const Fmatrix& m)
{
	Fmatrix M = m;
	M.c.set(0, 0, 0);
	transform(domain, M);
}

PAPI::pDomainDisc::pDomainDisc(PDomainEnum dtype,
	float a0, float a1, float a2,
	float a3, float a4, float a5,
	float a6, float a7, float a8)
{
	p1 = pVector(a0, a1, a2); // Center point
	p2 = pVector(a3, a4, a5); // Normal (not used in Within and Generate)
	p2.normalize_safe();

	if (a6 > a7)
	{
		radius1 = a6; radius2 = a7;
	}
	else
	{
		radius1 = a7; radius2 = a6;
	}

	// Find a vector3 orthogonal to n.
	pVector basis(1.0f, 0.0f, 0.0f);
	if (_abs(basis * p2) > 0.999)
		basis = pVector(0.0f, 1.0f, 0.0f);

	// Project away N component, normalize and cross to get
	// second orthonormal vector3.
	u = basis - p2 * (basis * p2);
	u.normalize_safe();
	v = p2 ^ u;
	radius1Sqr = -(p1 * p2); // D of the plane eqn.
}
