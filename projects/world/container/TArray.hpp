#pragma once

#include "TArray.inl"

namespace wrd
{
#define THIS TArray<T>
#define TEMPL template <typename T>

	WRD_CLASS_DEF(TEMPL, THIS)

#undef TEMPL
#undef THIS
}
