#pragma once

#include "../NETArray/NETArray.hpp"

namespace NE
{
	template
	class NE_DLL NETArray<type_byte, false, type_byte, NEType::NEBYTE_SET>;
	typedef NETArray<type_byte, false, type_byte, NEType::NEBYTE_SET> NEByteSet;
}
