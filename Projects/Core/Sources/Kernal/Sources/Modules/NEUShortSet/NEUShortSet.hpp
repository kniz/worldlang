#pragma once

#include "../NETArray/NETArray.hpp"

namespace NE
{
	template
	class NE_DLL NETArray<type_ushort, false, type_ushort, NEType::NEUSHORT_SET>;
	typedef NETArray<type_ushort, false, type_ushort, NEType::NEUSHORT_SET> NEUShortSet;
}
