#pragma once

#include "../NEWString/NEWString.hpp"
#include "../NETList/NETList.hpp"

namespace NE
{
	template
	class NE_DLL NETList<NEWString, false, NEType::NEWSTRING_LIST>;
	typedef NETList<NEWString, false, NEType::NEWSTRING_LIST> NEWStringList;
}
