#pragma once

#include "../NETArray/NETArray.hpp"

namespace NE
{
	template
	class NE_DLL NETArray<type_bool, false, type_bool, NEType::NEBOOLEAN_SET>;
	typedef NETArray<type_bool, false, type_bool, NEType::NEBOOLEAN_SET> NEBooleanSet;
}
