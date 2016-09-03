#pragma once

#include "../NELengthedObject/NELengthedObject.hpp"

namespace NE
{
	class NE_DLL NEIteratorBase : public NELengthedObject
	{
		NE_DECLARE_INTERFACE_ONLY(NEIteratorBase, NELengthedObject)

	public:
		const NEObject& get() const;
		virtual NEObject& get() = 0;
		virtual type_bool isEnd() const = 0;
		virtual type_bool isBegin() const = 0;
		virtual NEObject& next();
	};
}
