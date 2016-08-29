/*	Name:			NiRefObject
**	Description:	Keeps track of the reference counting for each class. Like IUnknown.
**	Inheritance:	Base Class
**	Size:			08
**	vTable:			00A3FCF8
**	vTable size:	01
**	Constructor:	inline?
**	Includes:		
*/	

#pragma once

#include "MiscNiDataTypes.h"
#include "NiRefObject.h"

/* Base class. Keeps track of the reference count of a class.
*/

namespace v1_2_416
{
	void NiRefObject::AddRef()
	{
		m_uiRefCount++;			// Oblivion code uses InterlockedIncrement
		return;
	}

	UInt32 NiRefObject::Release()
	{
		if (m_uiRefCount>0)
			m_uiRefCount--;		// Oblivion code uses InterlockedDecrement
		return(m_uiRefCount);
	}

	UInt32 NiRefObject::GetRefCount()
	{
		return(m_uiRefCount);
	}
		
		// static UInt32	m_uiGlobalObjectCount				// loc: 00B3FD64
}
		
		