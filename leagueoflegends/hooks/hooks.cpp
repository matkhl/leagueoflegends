#include "../stdafx.h"

namespace hooks
{
	std::vector<const char*> renderTypeNames = { "D3D9",  "D3D11" };
	std::vector<int> renderTypesIds = { 1, 3 };

	void CheckType(int renderType, const char* typeName)
	{
		if (kiero::init((kiero::RenderType::Enum)renderType) == kiero::Status::Success) globals::renderType = typeName;
	}

	int Init(int index)
	{
		CheckType(renderTypesIds[index], renderTypeNames[index]);

		if (globals::renderType)
		{
			hooks::impl::Init();
			return 1;
		}

		return 0;
	}
}