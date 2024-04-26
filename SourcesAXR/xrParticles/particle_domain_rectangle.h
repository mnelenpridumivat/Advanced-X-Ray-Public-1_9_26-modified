#pragma once

namespace PAPI {
	struct pDomain;
#pragma pack (push,4)
	struct PARTICLES_API pDomainRectangle
	{
		pVector 	p1, p2;			// Box vertices, Sphere center, Cylinder/Cone ends
		pVector 	u, v;			// Orthonormal basis vectors for Cylinder/Cone
		float 		radius1;		// Outer radius
		float 		radius1Sqr;		// Used for fast Within test of spheres,
		float 		radius2Sqr;		// and for mag. of u and v vectors for plane.

		virtual BOOL 		Within(const pVector&) const;
		virtual void 		Generate(pVector&) const;
		// transformation
		virtual void 		transform(pDomain* domain, const Fmatrix& m);
		virtual void 		transform_dir(pDomain* domain, const Fmatrix& m);
		// This constructor is used when default constructing a
		// ParticleAction that has a pDomain.
		IC 			pDomainRectangle() {}
		// Construct a domain in the standard way.
		pDomainRectangle(PDomainEnum dtype,
			float a0 = 0.0f, float a1 = 0.0f, float a2 = 0.0f,
			float a3 = 0.0f, float a4 = 0.0f, float a5 = 0.0f,
			float a6 = 0.0f, float a7 = 0.0f, float a8 = 0.0f);
	};
#pragma pack (pop)
}