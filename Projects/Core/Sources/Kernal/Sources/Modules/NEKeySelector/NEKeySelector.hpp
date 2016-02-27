
#pragma once

#include "../NETKeySelector/NETKeySelector.hpp"
#include "../NEModuleSelector/NEModuleSelector.hpp"

namespace NE
{
	template
	class NE_DLL NETKeySelector<NENodeSelector, NEType::NEKEY_SELECTOR>;
	typedef NETKeySelector<NENodeSelector, NEType::NEKEY_SELECTOR> NEKeySelector;
}
