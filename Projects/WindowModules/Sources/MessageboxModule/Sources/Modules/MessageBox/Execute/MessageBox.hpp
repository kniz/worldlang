#pragma once

#include "../../../Includes/Includes.hpp"

namespace NE
{
	class NE_DLL MessageBox : public NEModule
	{
	public:
		#include "innerclass/ErrorCode/ErrorCode.hpp"

	public:
		MessageBox();
		MessageBox(const MessageBox& source);

	public:
		virtual ~MessageBox();

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const;
		virtual LPCTSTR getErrorMessage(type_errorcode errorcode) const;

	public:
		virtual NEObject& clone() const;

	private:
		type_result _onExecute();
		virtual type_result _onArgumentFetched();

	private:
		NEArgumentTemplate<NETStringKey> _message;
		NEArgumentTemplate<NETStringKey> _title;
	};
}
