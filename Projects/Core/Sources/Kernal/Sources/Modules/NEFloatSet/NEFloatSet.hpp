#pragma once

#include "../NETArray/NETArray.hpp"

namespace NE
{
	template
	class NE_DLL NETArray<type_float, false, type_float, NEType::NEFLOAT_SET>;
	typedef NETArray<type_float, false, type_float, NEType::NEFLOAT_SET> NEFloatSet;
}
