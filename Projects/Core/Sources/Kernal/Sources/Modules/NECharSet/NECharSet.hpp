#pragma once

#include "../NETArray/NETArray.hpp"

namespace NE
{
	template
	class NE_DLL NETArray<type_char, false, type_char, NEType::NECHAR_SET>;
	typedef NETArray<type_char, false, type_char, NEType::NECHAR_SET> NECharSet;
}