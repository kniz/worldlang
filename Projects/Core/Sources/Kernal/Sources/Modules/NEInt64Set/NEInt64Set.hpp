#pragma once

#include "../NETArray/NETArray.hpp"

namespace NE
{
	template
	class NE_DLL NETArray<type_int64, false, type_int64, NEType::NEINT64_SET>;
	typedef NETArray<type_int64, false, type_int64, NEType::NEINT64_SET> NEInt64Set;
}
