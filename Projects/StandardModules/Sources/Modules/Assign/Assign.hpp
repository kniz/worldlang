#pragma once

#include "../../Includes/Includes.hpp"

namespace NE
{
	class NE_DLL Assign : public NEModule
	{
	public:
		typedef Assign ThisClass;
		typedef NEModule SuperClass;

	public:
		NEITArgument<NEKeySelector> target;
		NEITArgument<NEKeySelector> source;

	public:
		virtual type_result _onFetchArguments(NEArgumentInterfaceList& tray) const
		{
			tray.push(target);
			tray.push(source);

			return tray;
		}

	public:
		virtual const NEExportable::ModuleHeader& getHeader() const
		{
			static NEExportable::ModuleHeader _header;

			if(_header.isValid() != RESULT_NOTHING)
			{
				_header.getName() = _T("Assign");
				_header.getDeveloper() = _T("kniz");
				_header.setRevision(1);
				_header.getComment() = _T("0번: 할당될 대상들\n1번: 할당할 값(단, Primitive 단일 타입만 가능하다)");
				_header.getVersion()  = _T("0.0.1a");
				_header.getReleaseDate() = _T("2013-10-15");
				_header.getModuleDependencies().create(0);
				_header.setMaxErrorCodeCount(0);
			}

			return _header;
		}		

	public:
		virtual type_result execute();	

	public:
		virtual NEObject& clone() const
		{
			return *(new Assign(*this));
		}
	};
}