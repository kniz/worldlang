#pragma once

#include "../NETArray/NETArray.hpp"

namespace NE
{
	template
	class NE_DLL NETArray<type_wchar, false, type_wchar, NEType::NEWCHAR_SET>;
	typedef NETArray<type_wchar, false, type_wchar, NEType::NEWCHAR_SET> NEWCharSet;
}
