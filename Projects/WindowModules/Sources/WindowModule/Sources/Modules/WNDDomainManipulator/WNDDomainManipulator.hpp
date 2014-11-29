#pragma once

#include "../WND/WND.hpp"

namespace NE
{

	class Window;

	class NE_DLL WNDDomainManipulator : public WND
	{
	public:
		typedef WND SuperClass;
		typedef WNDDomainManipulator ThisClass;
	public:
		NEITArgument<NEModuleSelector> arg_window_selector;
		NEITArgument<NEByteKey> arg_hwnd_inserted_after;		

	public:
#include "innerclass/ErrorCode/ErrorCode.hpp"

	public:
		WNDDomainManipulator();
		WNDDomainManipulator(const WNDDomainManipulator& source);

	public:
		virtual ~WNDDomainManipulator();

	public:
		const WNDDomainManipulator& operator=(const WNDDomainManipulator& source);

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const;
		virtual LPCTSTR getErrorMessage(type_errorcode errorcode) const;

	public:
		virtual NEObject& clone() const;

	protected:
		virtual type_result _onFetchArguments(NEArgumentInterfaceList& tray) const;
		virtual type_result _onExecute();

	protected:
		HWND _convertHwndFromIndicator(type_byte indicator);
	};
}