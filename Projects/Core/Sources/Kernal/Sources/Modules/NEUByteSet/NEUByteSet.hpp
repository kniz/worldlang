#pragma once

#include "../NETArray/NETArray.hpp"

namespace NE
{
	template
	class NE_DLL NETArray<type_ubyte, false, type_ubyte>;
	typedef NETArray<type_ubyte, false, type_ubyte> NEUByteSet;
}
