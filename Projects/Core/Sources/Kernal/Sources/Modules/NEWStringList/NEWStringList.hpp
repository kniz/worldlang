#pragma once

#include "../NEWString/NEWString.hpp"
#include "../NETList/NETList.hpp"

namespace NE
{
	template
	class NE_DLL NETList<NEWString>;
	typedef NETList<NEWString> NEWStringList;
}
