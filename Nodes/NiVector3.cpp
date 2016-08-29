/*	Name:			
**	Description:	
**	Inheritance:	
**	Size:			
**	vTable:			
**	vTable size:	
**	Constructor:	
**	Includes:		
*/	

#pragma once

#include "NiVector3.h"

namespace v1_2_416
{
	
	void NiVector3::Set(float x, float y, float z)
	{
		this->x=x;
		this->y=y;
		this->z=z;
		return();
	}

	void NiVector::Zero()
	{
		x=0.0;
		y=0.0;
		z=0.0;
		return();
	}



}
		
		