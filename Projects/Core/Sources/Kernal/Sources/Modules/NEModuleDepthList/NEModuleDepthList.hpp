#pragma once

#include "../NETList/NETList.hpp"
#include "../../Commons/Units/NEModuleDepthUnit/NEModuleDepthUnit.hpp"
#include "../NETShallower/NETShallower.hpp"

namespace NE
{
	template
	class NE_DLL NETShallower<NETList<NEModuleDepthUnit>>>;
	typedef NETShallower<NETList<NEModuleDepthUnit>>> NEModuleDepthList;
}