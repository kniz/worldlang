#pragma once

#include "../NETArray/NETArray.hpp"

namespace NE
{
	template
	class NE_DLL NETArray<type_float, false, type_float>;
	typedef NETArray<type_float, false, type_float> NEFloatSet;
}
