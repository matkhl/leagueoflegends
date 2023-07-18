#include "../stdafx.h"

namespace hooks
{
	void CheckType(kiero::RenderType::Enum renderType, const char* typeName)
	{
		if (kiero::init(renderType) == kiero::Status::Success) globals::renderType = typeName;
	}

	int Init()
	{
		CheckType(kiero::RenderType::Enum::D3D9, "D3D9");
		
		if (globals::renderType)
		{
			std::cout << SP_STRING("Using ") << globals::renderType << std::endl;
			hooks::impl::Init();
			return 1;
		}
		else
		{
			std::cout << SP_STRING("RenderType not supported\n(press detach key)") << std::endl;
			return 0;
		}
	}
}