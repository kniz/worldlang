#pragma once

#include "../NETArray/NETArray.hpp"

namespace NE
{
	template
	class NE_DLL NETArray<type_char, false, type_char>;
	typedef NETArray<type_char, false, type_char> NECharSet;
}