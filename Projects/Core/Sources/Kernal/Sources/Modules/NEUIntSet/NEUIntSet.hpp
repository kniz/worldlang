#pragma once

#include "../NETArray/NETArray.hpp"

namespace NE
{
	template
	class NE_DLL NETArray<type_uint, false, type_uint, NEType::NEUINT_SET>;
	typedef NETArray<type_uint, false, type_uint, NEType::NEUINT_SET> NEUIntSet;
}
