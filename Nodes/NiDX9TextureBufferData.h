/*	Name:			NiDX9TextureBufferData
**	Description:	Contains the D3D surface data for a texture
**	Inheritance:	NiDX92DBufferData - Can't find constructor so inherit from NiRefObject
**	Size:			0x18
**	vTable:			0x00A898E4
**	vTable size:	0x10
**	Constructor:	0x0076D9B0
**	Includes:		Ni2DBuffer, IDirect3DSurface9
*/	

#pragma once

#include "NiRefObject.h"
#include "MiscNiDataTypes.h"
#include "D3D9.h"


namespace v1_2_416
{
	class Ni2DBuffer;

	class NiDX9TextureBufferData:public NiRefObject
	{
	public:

		NiDX9TextureBufferData();
		~NiDX9TextureBufferData();

		virtual UInt32	GetWidth(void);											// 01
		virtual UInt32	GetHeight(void);										// 02
		virtual UInt32	GetVar10(void);											// 03
		virtual	NiRTTI	*GetType(void);											// 04
		virtual	UInt32	func05(void);											// 05 - returns false
		virtual	UInt32	func06(void);											// 06 - returns false
		virtual	UInt32	func07(void);											// 07 - returns false
		virtual	UInt32	func08(void);											// 08 - returns false
		virtual	UInt32	func09(void);											// 09 - returns false
		virtual	UInt32	func0A(void);											// 0A - returns false
		virtual bool	ReleaseTextures1(void);											// 0B - calls function 0f and returns true
		virtual UInt32	func0C(UInt32 u1);										// 0C - returns false
		virtual bool	SetRenderTarget(void *u1, UInt32 RenderTargetIndex);	// 0D
		virtual bool	func0E(UInt32 u1);										// 0E - returns false
		virtual void	ReleaseTextures2(void);									// 0F
		
		Ni2DBuffer			*ParentData;			// 08
		IDirect3DSurface9	*SurfaceTexture;		// 0C
		UInt32				var10;					// 10
		void				*UnkD3DData;			// 14
	};
}
		
		