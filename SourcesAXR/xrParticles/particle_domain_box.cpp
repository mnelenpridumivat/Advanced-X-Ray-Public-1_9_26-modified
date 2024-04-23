#include "stdafx.h"
#include "particle_domain_box.h"

#include "particle_core.h"

static constexpr PAPI::pVector vHalf(0.5, 0.5, 0.5);

ICF PAPI::pVector RandVec()
{
	return PAPI::pVector(drand48(), drand48(), drand48());
}

BOOL PAPI::pDomainBox::Within(const pVector& pos) const
{
	return !((pos.x < p1.x) || (pos.x > p2.x) ||
			(pos.y < p1.y) || (pos.y > p2.y) ||
			(pos.z < p1.z) || (pos.z > p2.z));
}

void PAPI::pDomainBox::Generate(pVector& pos) const
{
	// Scale and translate [0,1] random to fit box
	pos.x = p1.x + (p2.x - p1.x) * drand48();
	pos.y = p1.y + (p2.y - p1.y) * drand48();
	pos.z = p1.z + (p2.z - p1.z) * drand48();
}

void PAPI::pDomainBox::transform(PAPI::pDomain* domain, const Fmatrix& m)
{
	Fbox* bb_dest = (Fbox*)&p1;
	Fbox* bb_from = (Fbox*)&domain->p1;
	bb_dest->xform(*bb_from, m);
}

void PAPI::pDomainBox::transform_dir(PAPI::pDomain* domain, const Fmatrix& m)
{
	Fmatrix M = m;
	M.c.set(0, 0, 0);
	transform(domain, M);
}

PAPI::pDomainBox::pDomainBox(PDomainEnum dtype,
	float a0, float a1, float a2,
	float a3, float a4, float a5,
	float a6, float a7, float a8)
{
	// p1 is the min corner. p2 is the max corner.
	if (a0 < a3)
	{
		p1.x = a0; p2.x = a3;
	}
	else
	{
		p1.x = a3; p2.x = a0;
	}
	if (a1 < a4)
	{
		p1.y = a1; p2.y = a4;
	}
	else
	{
		p1.y = a4; p2.y = a1;
	}
	if (a2 < a5)
	{
		p1.z = a2; p2.z = a5;
	}
	else
	{
		p1.z = a5; p2.z = a2;
	}
}
