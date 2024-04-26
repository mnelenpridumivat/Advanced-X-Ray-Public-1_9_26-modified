#pragma once

namespace PAPI {
	struct pDomain;
#pragma pack (push,4)
	struct PARTICLES_API pDomainLine
	{
		pVector 	p1, p2;			// Box vertices, Sphere center, Cylinder/Cone ends

		virtual BOOL 		Within(const pVector&) const;
		virtual void 		Generate(pVector&) const;
		// transformation
		virtual void 		transform(pDomain* domain, const Fmatrix& m);
		virtual void 		transform_dir(pDomain* domain, const Fmatrix& m);
		// This constructor is used when default constructing a
		// ParticleAction that has a pDomain.
		IC 			pDomainLine() {}
		// Construct a domain in the standard way.
		pDomainLine(PDomainEnum dtype,
			float a0 = 0.0f, float a1 = 0.0f, float a2 = 0.0f,
			float a3 = 0.0f, float a4 = 0.0f, float a5 = 0.0f,
			float a6 = 0.0f, float a7 = 0.0f, float a8 = 0.0f);
	};
#pragma pack (pop)
}