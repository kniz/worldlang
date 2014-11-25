#include "NEExportable.hpp"

namespace NE
{
	LPCTSTR NE_DLL NEExportable::getErrorMessage(type_errorcode errorcode) const
	{
		return _T("ERROR UNEXPECTED");
	}

	const NEExportable::ModuleHeader& NEExportable::getHeader() const
	{
		static NEExportable::ModuleHeader _header = _onRequestHeader();

		return _header;
	}
}