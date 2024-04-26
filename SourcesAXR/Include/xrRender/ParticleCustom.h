#pragma once

/*#define PSParam_Enum(...) \
enum class EParams{ \
	__VA_ARGS__ \
}; \

struct PSParamBase
{
	
};

#define PSParam_Struct(name, type) \
struct S##name{ \
private: \
	type Value; \
}; \
S##name name; \

#define PSParam_Union(...) \
union SParam{ \
	__VA_ARGS__ \
}; \

class PSDomainBase
{
public:
	virtual PSParamBase* GetValue() = 0;
};

template<typename A>
class PSDomain : PSDomainBase
{
	A Value;
};

template<typename A, typename B>
class PSDomain : PSDomainBase
{
	union Values
	{
		A TypeA;
		B TypeB;
	};
	Values Value;
};

template<typename A, typename B, typename C>
class PSDomain : PSDomainBase
{
	union Values
	{
		A TypeA;
		B TypeB;
		C TypeC;
	};
	Values Value;
};

template<typename A, typename B, typename C, typename D>
class PSDomain : PSDomainBase
{
	union Values
	{
		A TypeA;
		B TypeB;
		C TypeC;
		D TypeD;
	};
	Values Value;
};

#define PSParam_Domain(name, params, param_type) \
struct S##name: public PSDomainBase { \
	params \
	param_type \
	\
	PSParamBase* GetValue() override { \
		return nullptr; \
	} \
private: \
	EParams Param; \
	SParam Value; \
}; \
S##name name; \

#define PSParam_PAPICase(case) \
case PAPI::PD##case : { \
	PSParamBase* Value = 
} \

#define PSParam_Param(...) \
struct SDomainParam{ \
	union Domain{ \
		__VA_ARGS__ \
	}; \
	void* GetValue(){ \
		switch(DomainType){ \
		case PAPI::PDPoint: {\
			return Value.Point.GetValue(); \
		}, \
		case PAPI::PDLine: {\
			break; \
		}, \
		case PAPI::PDTriangle: {\
			break; \
		}, \
		case PAPI::PDPlane: {\
			break; \
		}, \
		case PAPI::PDBox: {\
			break; \
		}, \
		case PAPI::PDSphere: {\
			break; \
		}, \
		case PAPI::PDCylinder: {\
			break; \
		}, \
		case PAPI::PDCone: {\
			break; \
		}, \
		case PAPI::PDBlob: {\
			break; \
		}, \
		case PAPI::PDDisc: {\
			break; \
		}, \
		case PAPI::PDRectangle: {\
			break; \
		} \
		}; \
		return nullptr; \
	}; \
private: \
	PAPI::PDomainEnum DomainType; \
	Domain Value; \
}; \

PSParam_Param(
	PSParam_Domain(
		Point,
		PSParam_Enum(
			Center
		),
		PSParam_Union(
			PSParam_Struct(Center, Fvector)
		)
	)
)

PSParam_Param(
	PSParam_Domain(
		Point,
		PSParam_Enum(
			Center
		),
		PSParam_Union(
			PSParam_Struct(Center, Fvector)
		)
	)
	PSParam_Domain(
		Line,
		PSParam_Enum(
			Point1,
			Point2,
		)
		PSParam_Union(
			PSParam_Struct(Point1, Fvector)
			PSParam_Struct(Point2, Fvector)
		)
	)
	PSParam_Domain(
		Triangle,
		PSParam_Enum(
			Vertex1,
			Vertex2,
			Vertex3,
			)
		PSParam_Union(
			PSParam_Struct(Vertex1, Fvector)
			PSParam_Struct(Vertex2, Fvector)
			PSParam_Struct(Vertex3, Fvector)
		)
	)
	PSParam_Domain(
		Plane,
		PSParam_Enum(
			Origin,
			Normal,
			)
		PSParam_Union(
			PSParam_Struct(Origin, Fvector)
			PSParam_Struct(Normal, Fvector)
		)
	)
	PSParam_Domain(
		Box,
		PSParam_Enum(
			Min,
			Max,
			)
		PSParam_Union(
			PSParam_Struct(Min, Fvector)
			PSParam_Struct(Max, Fvector)
		)
	)
	PSParam_Domain(
		Sphere,
		PSParam_Enum(
			Center,
			RadiusInner,
			RadiusOuter,
			)
		PSParam_Union(
			PSParam_Struct(Center, Fvector)
			PSParam_Struct(RadiusInner, float)
			PSParam_Struct(RadiusOuter, float)
		)
	)
	PSParam_Domain(
		Cylinder,
		PSParam_Enum(
			Point1,
			Point2,
			RadiusInner,
			RadiusOuter,
			)
		PSParam_Union(
			PSParam_Struct(Point1, Fvector)
			PSParam_Struct(Point2, Fvector)
			PSParam_Struct(RadiusInner, float)
			PSParam_Struct(RadiusOuter, float)
		)
	)
	PSParam_Domain(
		Cone,
		PSParam_Enum(
			Apex,
			EndPoint,
			RadiusInner,
			RadiusOuter,
			)
		PSParam_Union(
			PSParam_Struct(Apex, Fvector)
			PSParam_Struct(EndPoint, Fvector)
			PSParam_Struct(RadiusInner, float)
			PSParam_Struct(RadiusOuter, float)
		)
	)
	PSParam_Domain(
		Blob,
		PSParam_Enum(
			Center,
			RadiusOuter,
			)
		PSParam_Union(
			PSParam_Struct(Center, Fvector)
			PSParam_Struct(RadiusOuter, float)
		)
	)
	PSParam_Domain(
		Disc,
		PSParam_Enum(
			Center,
			Normal,
			RadiusInner,
			RadiusOuter,
			)
		PSParam_Union(
			PSParam_Struct(Center, Fvector)
			PSParam_Struct(Normal, Fvector)
			PSParam_Struct(RadiusInner, float)
			PSParam_Struct(RadiusOuter, float)
		)
	)
	PSParam_Domain(
		Rectangle,
		PSParam_Enum(
			Origin,
			BasisU,
			BasisV,
		)
		PSParam_Union(
			PSParam_Struct(Origin, Fvector)
			PSParam_Struct(BasisU, Fvector)
			PSParam_Struct(BasisV, Fvector)
		)
	)
)*/

/*
struct SPSDomainPoint{
	enum class EParams
	{
		Center,
	};
	struct SCenter
	{
		Fvector Center;
	};
	EParams Param;
	SCenter Value;
};

struct SPSDomainLine{
	enum class EParams
	{
		Point1,
		Point2,
	};
	struct SPoint1
	{
		Fvector Point1;
	};
	struct SPoint2
	{
		Fvector Point2;
	};

	EParams Param;
};

enum class SPSDomainTriangleParams
{
	Vertex1,
	Vertex2,
	Vertex3,
};
struct SPSDomainTriangleVertex1
{
	Fvector Vertex1;
};
struct SPSDomainTriangleVertex2
{
	Fvector Vertex2;
};
struct SPSDomainTriangleVertex3
{
	Fvector Vertex3;
};

enum class SPSDomainPlaneParams
{
	Origin,
	Normal,
};
struct SPSDomainPlaneOrigin
{
	Fvector Origin;
};
struct SPSDomainPlaneNormal
{
	Fvector Normal;
};

enum class SPSDomainBoxParams
{
	Min,
	Max,
};
struct SPSDomainBoxMin
{
	Fvector Min;
};
struct SPSDomainBoxMax
{
	Fvector Max;
};

enum class SPSDomainSphereParams
{
	Center,
	RadiusInner,
	RadiusOuter,
};
struct SPSDomainSphereCenter
{
	Fvector Center;
};
struct SPSDomainSphereRadiusInner
{
	float RadiusInner;
};
struct SPSDomainSphereRadiusOuter
{
	float RadiusOuter;
};

enum class SPSDomainCylinderParams
{
	Point1,
	Point2,
	RadiusInner,
	RadiusOuter,
};
struct SPSDomainCylinderPoint1
{
	Fvector Point1;
};
struct SPSDomainCylinderPoint2
{
	Fvector Point2;
};
struct SPSDomainCylinderRadiusInner
{
	float RadiusInner;
};
struct SPSDomainCylinderRadiusOuter
{
	float RadiusOuter;
};


enum class SPSDomainConeParams
{
	Apex,
	EndPoint,
	RadiusInner,
	RadiusOuter,
};
struct SPSDomainConeApex
{
	Fvector Apex;
};
struct SPSDomainConeEndPoint
{
	Fvector EndPoint;
};
struct SPSDomainConeRadiusInner
{
	float RadiusInner;
};
struct SPSDomainConeRadiusOuter
{
	float RadiusOuter;
};
enum class SPSDomainBlobParams
{
	Center,
	RadiusOuter,
};
struct SPSDomainBlobCenter
{
	Fvector Center;
};
struct SPSDomainBlobRadiusOuter
{
	float RadiusOuter;
};

enum class SPSDomainDiscParams
{
	Center,
	Normal,
	RadiusInner,
	RadiusOuter,
};
struct SPSDomainDiscCenter
{
	Fvector Center;
};
struct SPSDomainDiscNormal
{
	Fvector Normal;
};
struct SPSDomainDiscRadiusInner
{
	float RadiusInner;
};
struct SPSDomainDiscRadiusOuter
{
	float RadiusOuter;
};

enum class SPSDomainRectangleParams
{
	Origin,
	BasisU,
	BasisV,
};
struct SPSDomainRectangleOrigin
{
	Fvector Origin;
};
struct SPSDomainRectangleBasisU
{
	Fvector BasisU;
};
struct SPSDomainRectangleBasisV
{
	Fvector BasisV;
};*/

/*struct SPSParamUnion
{

	union Param
	{
		void f(PAPI::PDomainEnum DomainType)
		{
			switch(DomainType)
			{
			case PAPI::PDBlob:
				{
				break;
				}
			case PAPI::PDBox:
				{
					
				}
			}
		}
	};
};*/

class IParticleCustom
{
public:
	virtual ~IParticleCustom() {;}

	virtual void Manual_UpdateSize(const Fvector& NewSize) = 0;
	virtual void Manual_UpdateAlpha(float NewAlpha) = 0;

	virtual void Manual_AddAlpha(float DeltaAlpha) = 0;
	//virtual void Manual_SetSourceDomainParam(PAPI::PDomainEnum DomainType, )

	virtual void 	OnDeviceCreate		()=0;
	virtual void 	OnDeviceDestroy		()=0;

	virtual void	UpdateParent		(const Fmatrix& m, const Fvector& velocity, BOOL bXFORM)=0;
	virtual void	OnFrame				(u32 dt)=0;

	virtual void	Play				()=0;
	virtual void	Stop				(BOOL bDefferedStop=TRUE)=0;
	virtual BOOL	IsPlaying			()=0;

	virtual u32		ParticlesCount		()=0;

	virtual float	GetTimeLimit		()=0;
	virtual BOOL	IsLooped			(){return GetTimeLimit()<0.f;}
	
	virtual const shared_str	Name		()=0;
	virtual void	SetHudMode			(BOOL b)=0;
	virtual BOOL	GetHudMode			()=0;
};