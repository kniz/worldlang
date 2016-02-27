#pragma once

#include "../NEString/NEString.hpp"
#include "../NETList/NETList.hpp"

namespace NE
{
	template
	class NE_DLL NETList<NEString, false, NEType::NESTRING_LIST>;
	typedef NETList<NEString, false, NEType::NESTRING_LIST> NEStringList;
}
