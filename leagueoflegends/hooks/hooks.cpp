#include "../stdafx.h"

namespace hooks
{
	void CheckType(int renderType, const char* typeName)
	{
		if (kiero::init((kiero::RenderType::Enum)renderType) == kiero::Status::Success) globals::renderType = typeName;
	}

	int Init()
	{
		std::vector<int> renderTypes = { 3, 1 };
		std::vector<const char*> renderTypeNames = { "D3D11", "D3D9" };

		for (int i = 0; i < renderTypes.size(); i++)
		{
			CheckType(renderTypes[i], renderTypeNames[i]);
			if (globals::renderType)
				break;
		}
		
		if (globals::renderType)
		{
			hooks::impl::Init();
			return 1;
		}
		else
		{
			LOG("RenderType not supported (press detach key)");
			return 0;
		}
	}
}