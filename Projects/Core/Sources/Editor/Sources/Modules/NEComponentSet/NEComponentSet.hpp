#pragma once

#include "../NEComponent/NEComponent.hpp"

namespace NE
{
	template
	class NE_DLL NETArray<NEComponent*, true, NEComponent*, NEType::NECOMPONENT_SET>;
	typedef NETArray<NEComponent*, true, NEComponent*, NEType::NECOMPONENT_SET> NEComponentSet;
}
