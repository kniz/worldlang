#pragma once

#include "../NETArray/NETArray.hpp"

namespace NE
{
	template
	class NE_DLL NETArray<type_ushort, false, type_ushort>;
	typedef NETArray<type_ushort, false, type_ushort> NEUShortSet;
}
