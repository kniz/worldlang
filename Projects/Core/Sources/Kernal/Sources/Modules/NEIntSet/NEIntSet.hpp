#pragma once

#include "../NETArray/NETArray.hpp"

namespace NE
{
	template
	class NE_DLL NETArray<type_int, false, type_int, NEType::NEINT_SET>;
	typedef NETArray<type_int, false, type_int, NEType::NEINT_SET> NEIntSet;
}
