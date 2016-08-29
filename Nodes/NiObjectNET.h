/*	Name:			NiObjectNET
**	Description:	Adds descriptors to an object.
**	Inheritance:	NiRefObject::NiObject::
**	Size:			18
**	vTable:			00A7D5BC
**	vTable size:	13
**	Constructor:	006FFD30
**	Includes:		NiObject, NiExtraData
*/	

#pragma once

#include "NiObject.h"
#include "NiExtraData.h"

namespace v1_2_416
{
	class NiObjectNET: public NiObject
	{
	public:
		NiObjectNET();
		~NiObjectNET();

		const char			* m_pcName;							// 008
		NiObject			*unk00C;							// 00C
		NiExtraData			**ExtraDataList;					// 010 An array of extra objects
		UInt16				ExtraDataSize;						// 014 Number of objects in the above array
		UInt16				ExtraDataMaxSize;					// 016 Maximum size of the above array
	};
}