/*	Name:			NiRenderer
**	Description:	Abstract Layer for the rendering system. Inherited by machine specific renderer.
**	Inheritance:	NiRefObject::NiObject::
**	Size:			210?
**	vTable:			00A7D6A4
**	vTable size:	5F
**	Constructor:	00701700
**	Includes:		NiAlphaAccumulator, NiPropertyState, NiDynamicEffect, NiCriticalSection, NiColor, NiRenderTargetGroup
*/	

#pragma once

#include "obse\nodes\NiObject.h"
//#include "NiAlphaAccumulator.h"		// todo
//#include "NiPropertyState.h"		// todo
//#include "NiDynamicEffect.h"		// todo
#include "obse\nodes\NiCriticalSection.h"
//#include "NiColor.h"
#include "obse\nodes\NiRenderTargetGroup.h"

namespace v1_2_416
{
	class NiColor;
	class NiAlphaAccumulator;
	class NiPropertyState;
	class NiDynamicEffect;

	class NiRenderer: public NiObject
	{
	public:

		NiRenderer();
		~NiRenderer();

		virtual	bool					func_13(int i1);			
		virtual	char					*GetDeviceDebugInfo(void);	// = 0
		virtual	UInt32					ReturnVar05E0(void);	// = 0
		virtual void					SetClearZ(float z);	// = 0
		virtual float					GetClearZ(void);	// = 0
		virtual void					SetClearColorRGBA(NiColor *color);	// = 0
		virtual	void					SetClearColourRGB(NiColor *color);	// = 0
		virtual NiColor					*GetClearColorRGBA(void);	// = 0
		virtual void					SetClearStencil(UInt32 stencil);	// = 0
		virtual UInt32					GetClear(void);	// = 0
		virtual void					func_1D(void);	// = 0
		virtual void					func_1E(void);	// = 0
		virtual NiRenderTargetGroup		*GetRenderTargetGroup1(void);	// = 0
		virtual NiRenderTargetGroup		*GetRenderTargetGroup2(void);	// = 0
		virtual void	func_21(void);	// = 0
		virtual void	func_22(void);	// = 0
		virtual	void	func_23(void);	// = 0		
		virtual	void	func_24(void);	// = 0
		virtual	void	func_25(void);	// = 0
		virtual void	func_26(int i1);
		virtual void	func_27(void);	// = 0
		virtual void	func_28(void);	// = 0
		virtual	void	func_29(void);	// = 0
		virtual void	func_2A(void);	// = 0
		virtual void	func_2B(void);	// = 0
		virtual bool	func_2C(int i1,int i2,int i3,int i4);
		virtual void	func_2D(void);	// = 0
		virtual void	func_2E(void);	// = 0
		virtual void	func_2F(void);	// = 0
		virtual void	func_30(void);	// = 0
		virtual void	func_31(void);	// = 0
		virtual void	func_32(void);	// = 0
		virtual	void	func_33(void);	// = 0		
		virtual	void	func_34(void);	// = 0
		virtual	void	func_35(void);	// = 0
		virtual BOOL	FastCopy(UInt32 u1, UInt32 u2, UInt32 u3, UInt32 u4, UInt32 FilterType);	// = 0
		virtual BOOL	Copy(UInt32 u1, UInt32 u2, UInt32 u3, UInt32 u4, UInt32 FilterType);	// = 0
		virtual void	func_38(void);	// = 0
		virtual	void	func_39(void);	// = 0
		virtual void	func_3A(void);	// = 0
		virtual void	func_3B(void);	// = 0
		virtual void	func_3C(void);	// = 0
		virtual void	func_3D(void);	// = 0
		virtual void	func_3E(void);	// = 0
		virtual void	func_3F(void);	// = 0
		virtual bool	func_40(int i1);
		virtual void	func_41(void);	// = 0
		virtual void	func_42(void);	// = 0
		virtual	void	func_43(void);	// = 0		
		virtual	void	func_44(void);	// = 0
		virtual	void	func_45(void);	// = 0
		virtual void	func_46(void);	// = 0
		virtual void	func_47(void);	// = 0
		virtual void	func_48(void);	// = 0
		virtual	void	func_49(void);	// = 0
		virtual void	func_4A(void);	
		virtual void	func_4B(void);	
		virtual void	func_4C(void);	// = 0
		virtual void	func_4D(void);	// = 0
		virtual void	func_4E(void);	// = 0
		virtual void	func_4F(void);	// = 0
		virtual void	func_50(void);	// = 0
		virtual void	func_51(void);	// = 0
		virtual void	func_52(void);	// = 0
		virtual	void	func_53(void);	// = 0		
		virtual	void	func_54(int i1,int i2);
		virtual	void	func_55(void);	
		virtual void	func_56(void *v1);
		virtual void	func_57(void *v1);
		virtual void	func_58(void);	// = 0
		virtual	void	func_59(void);	// = 0
		virtual void	func_5A(void);	// = 0
		virtual void	func_5B(void);	// = 0
		virtual void	func_5C(void);	// = 0
		virtual void	func_5D(void);	// = 0
		virtual void	func_5E(void);	// = 0
		
		NiAlphaAccumulator			*pAlphaAccumulator;		// 008
		NiPropertyState				*pPropertyState;		// 00C
		NiDynamicEffect				*pDynamicEffect;		// 010
		UInt32						var014;					// 014
		UInt32						var018;					// 018
		UInt32						var01C;					// 01C
		UInt32						var020;					// 020
		UInt32						var024;					// 024
		UInt32						var028;					// 028
		UInt32						var02C;					// 02C
		UInt32						var030;					// 030
		UInt32						var034;					// 034
		UInt32						var038;					// 038
		UInt32						var03C;					// 03C
		UInt32						var040;					// 040
		UInt32						var044;					// 044
		UInt32						var048;					// 048
		UInt32						var04C;					// 04C
		UInt32						var050;					// 050
		UInt32						var054;					// 054
		UInt32						var058;					// 058
		UInt32						var05C;					// 05C
		UInt32						var060;					// 060
		UInt32						var064;					// 064
		UInt32						var068;					// 068
		UInt32						var06C;					// 06C
		UInt32						var070;					// 070
		UInt32						var074;					// 074
		UInt32						var078;					// 078
		UInt32						var07C;					// 07C
		NiCriticalSection			CritSection1;			// 080
		NiCriticalSection			CritSection2;			// 100
		NiCriticalSection			CritSection3;			// 180
		UInt32						SceneStatus;			// 200
		UInt32						AllowRendering;			// 204
		UInt32						var208;					// 208
		UInt8						var20C;					// 20C
		UInt8						var20D;					// 20D
		UInt16						pad20E;					// 20E

	};
}
		
		