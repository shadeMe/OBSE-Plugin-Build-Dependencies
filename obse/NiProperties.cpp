#include "NiProperties.h"

const char* BSShaderProperty::RenderPass::GetRenderPassName()
{
	typedef const char* (*_Fn)(UInt32 id);
	return ((_Fn)0x007B4920)(type);
}
