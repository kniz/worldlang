#pragma once

#include "../NEPanel/NEPanel.hpp"

namespace NE
{
	template
	class NE_DLL NETList<NEPanel*, true, NEType::NEPANEL_LIST>;
	typedef NETList<NEPanel*, true, NEType::NEPANEL_LIST> NEPanelList;
}
