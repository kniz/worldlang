#pragma once

#include "../NETArray/NETArray.hpp"

namespace NE
{
	template
	class NE_DLL NETArray<type_short, false, type_short, NEType::NESHORT_SET>;
	typedef NETArray<type_short, false, type_short, NEType::NESHORT_SET> NEShortSet;
}
