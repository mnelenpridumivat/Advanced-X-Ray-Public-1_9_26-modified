#ifndef ShapeDataH
#define ShapeDataH

struct CShapeData:
	public IMetaClass
{
	DECLARE_METACLASS(CShapeData)
public:
	enum{
    	cfSphere=0,
        cfBox
    };
	union shape_data
	{
		Fsphere		sphere;
		Fmatrix		box;
	};
	struct shape_def
	{
		u8			type;
		shape_data	data;
	};
    DEFINE_VECTOR					(shape_def,ShapeVec,ShapeIt);
	ShapeVec						shapes;
};

#endif