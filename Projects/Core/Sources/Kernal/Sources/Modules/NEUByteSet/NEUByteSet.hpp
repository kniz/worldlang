#pragma once

#include "../NETArray/NETArray.hpp"

namespace NE
{
	template
	class NE_DLL NETArray<type_ubyte, false, type_ubyte, NEType::NEUBYTE_SET>;
	typedef NETArray<type_ubyte, false, type_ubyte, NEType::NEUBYTE_SET> NEUByteSet;
}
