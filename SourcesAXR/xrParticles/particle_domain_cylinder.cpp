#include "stdafx.h"
#include "particle_domain_cylinder.h"

#include "particle_core.h"

//static constexpr PAPI::pVector vHalf(0.5, 0.5, 0.5);

ICF PAPI::pVector RandVec()
{
	return PAPI::pVector(drand48(), drand48(), drand48());
}

BOOL PAPI::pDomainCylinder::Within(const pVector& pos) const
{
	// This is painful and slow. Might be better to do quick
	// accept/reject tests.
	// Let p2 = vector3 from base to tip of the cylinder
	// x = vector3 from base to test point
	// x . p2
	// dist = ------ = projected distance of x along the axis
	// p2. p2 ranging from 0 (base) to 1 (tip)
	//
	// rad = x - dist * p2 = projected vector3 of x along the base
	// p1 is the apex of the cone.

	pVector x(pos - p1);

	// Check axial distance
	// radius2Sqr stores 1 / (p2.p2)
	float dist = (p2 * x) * radius2Sqr;
	if (dist < 0.0f || dist > 1.0f)
		return FALSE;

	// Check radial distance; scale radius along axis for cones
	pVector xrad = x - p2 * dist; // Radial component of x
	float rSqr = xrad.length2();

	return (rSqr <= radius1Sqr && rSqr >= _sqr(radius2));
}

void PAPI::pDomainCylinder::Generate(pVector& pos) const
{
	// For a cone, p2 is the apex of the cone.
	float dist = drand48(); // Distance between base and tip
	float theta = drand48() * 2.0f * float(M_PI); // Angle around axis
	// Distance from axis
	float r = radius2 + drand48() * (radius1 - radius2);

	float x = r * _cos(theta); // Weighting of each frame vector3
	float y = r * _sin(theta);

	pos = p1 + p2 * dist + u * x + v * y;
}

void PAPI::pDomainCylinder::transform(PAPI::pDomain* domain, const Fmatrix& m)
{
	m.transform_tiny(p1, domain->p1);
	m.transform_dir(p2, domain->p2);
	m.transform_dir(u, domain->u);
	m.transform_dir(v, domain->v);
}

void PAPI::pDomainCylinder::transform_dir(PAPI::pDomain* domain, const Fmatrix& m)
{
	Fmatrix M = m;
	M.c.set(0, 0, 0);
	transform(domain, M);
}

PAPI::pDomainCylinder::pDomainCylinder(PDomainEnum dtype,
	float a0, float a1, float a2,
	float a3, float a4, float a5,
	float a6, float a7, float a8)
{
	// p2 is a vector3 from p1 to the other end of cylinder.
	// p1 is apex of cone.

	p1 = pVector(a0, a1, a2);
	pVector tmp(a3, a4, a5);
	p2 = tmp - p1;

	if (a6 > a7)
	{
		radius1 = a6; radius2 = a7;
	}
	else
	{
		radius1 = a7; radius2 = a6;
	}
	radius1Sqr = _sqr(radius1);

	// Given an arbitrary nonzero vector3 n, make two orthonormal
	// vectors u and v forming a frame [u,v,n.normalize()].
	pVector n = p2;
	float p2l2 = n.length2(); // Optimize this.
	n.normalize_safe();

	// radius2Sqr stores 1 / (p2.p2)
	// XXX Used to have an actual if.
	radius2Sqr = p2l2 ? 1.0f / p2l2 : 0.0f;

	// Find a vector3 orthogonal to n.
	pVector basis(1.0f, 0.0f, 0.0f);
	if (_abs(basis * n) > 0.999)
		basis = pVector(0.0f, 1.0f, 0.0f);

	// Project away N component, normalize and cross to get
	// second orthonormal vector3.
	u = basis - n * (basis * n);
	u.normalize_safe();
	v = n ^ u;
}
