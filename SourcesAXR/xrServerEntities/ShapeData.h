#ifndef ShapeDataH
#define ShapeDataH

struct CShapeData
{
	enum{
    	cfSphere=0,
        cfBox
    };
	union shape_data
	{
		Fsphere		sphere;
		Fmatrix		box;
		ICF shape_data() {}
	};
	struct shape_def
	{
		u8			type;
		shape_data	data;

		ICF shape_def() {}

		ICF shape_def(const shape_def& other)
		{
			type = other.type;
			if (!type)
			{
				data.sphere = other.data.sphere;
			}
			else
			{
				data.box = other.data.box;
			}
		}

		ICF shape_def& operator=(const shape_def& other)
		{
			type = other.type;
			if(!type)
			{
				data.sphere = other.data.sphere;
			} else
			{
				data.box = other.data.box;
			}
			return *this;
		}
	};
    DEFINE_VECTOR					(shape_def,ShapeVec,ShapeIt);
	ShapeVec						shapes;
};

#endif