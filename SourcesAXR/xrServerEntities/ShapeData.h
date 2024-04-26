#pragma once

#include <algorithm>
#include <xutility>

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

		ICF shape_data(){}

		ICF shape_data& operator=(const shape_data& other)
		{
			sphere = other.sphere;
			box = other.box;
			return *this;
		}
	};
	struct shape_def
	{
		u8			type;
		shape_data	data;

		ICF shape_def(){}

		ICF shape_def(const shape_def& other)
		{
			type = other.type;
			data = other.data;
		}

		ICF shape_def& operator=(const shape_def& other)
		{
			type = other.type;
			data = other.data;
			return *this;
		}
	};
    DEFINE_VECTOR					(shape_def,ShapeVec,ShapeIt);
	ShapeVec						shapes;

	ICF CShapeData& operator=(const CShapeData& other)
	{
		std::copy(other.shapes.begin(), other.shapes.end(), shapes.begin());
		return *this;
	}
};