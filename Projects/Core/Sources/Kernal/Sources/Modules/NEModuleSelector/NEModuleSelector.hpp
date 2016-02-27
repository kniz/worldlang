#pragma once

#include "../NETModuleSelector/NETModuleSelector.hpp"
#include "../NENodeSelector/NENodeSelector.hpp"
#include "../NEModuleCodeSetKey/NEModuleCodeSetKey.hpp"

namespace NE
{
	template
	class NE_DLL NETModuleSelector<NENodeSelector, NEType::NEMODULE_SELECTOR>;
	typedef NETModuleSelector<NENodeSelector, NEType::NEMODULE_SELECTOR> NEModuleSelector;
}	