#pragma once

#include "../NETArray/NETArray.hpp"

namespace NE
{
	template
	class NE_DLL NETArray<type_double, false, type_double, NEType::NEDOUBLE_SET>;
	typedef NETArray<type_double, false, type_double, NEType::NEDOUBLE_SET> NEDoubleSet;
}
