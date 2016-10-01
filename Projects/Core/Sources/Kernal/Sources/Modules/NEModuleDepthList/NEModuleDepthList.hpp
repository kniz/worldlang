#pragma once

#include "../NETList/NETList.hpp"
#include "../../Commons/Units/NEModuleDepthUnit/NEModuleDepthUnit.hpp"
#include "../NETWeakBinder/NETWeakBinder.hpp"

namespace NE
{
	template
	class NE_DLL NETList<NETWeakBinder<NEModuleDepthUnit>>;
	typedef NETList<NETWeakBinder<NEModuleDepthUnit>> NEModuleDepthList;
}