#pragma once

#include "../NETArray/NETArray.hpp"

namespace NE
{
	template
	class NE_DLL NETArray<type_double, false, type_double>;
	typedef NETArray<type_double, false, type_double> NEDoubleSet;
}
