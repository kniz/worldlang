#pragma once

#include "../NEHeader/NEHeader.hpp"
#include "../../Units/NECode/NECode.hpp"

namespace NE
{
	class NE_DLL NEScriptHeader : public NEHeader
	{
		NE_DECLARE_CLASS(NEScriptHeader, NEHeader)

		//	friend 선언
		friend class ScriptManager;

		//	생성자:
	public:
		NEScriptHeader();
		NEScriptHeader(const This& source);

		//	소멸자:
	public:
		virtual ~NEScriptHeader();

	public:
		const NEScriptHeader& operator=(const This& source);
		type_bool operator==(const This& source) const;
		type_bool operator!=(const This& source) const;

		//	인터페이스:
		//		상속:
		//			NEScriptHeader:	
	public:
		const NECode& getMaxCode(const NECodeType& type) const;
		type_result setMaxCode(const NECode& source);
		type_result setMaxNodeLength(type_index max_node_length);
		type_index getMaxNodeLength() const;
		type_result setMaxModuleLength(type_index max_module_length);
		type_index getMaxModuleLength() const;
		type_result setMaxKeyLength(type_index max_key_length);
		type_index getMaxKeyLength() const;
		//			NEObject:
	public:
		virtual void release();
		virtual type_result isValid() const;
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);

	private:
		const NEScriptHeader& _assign(const This& source);
		void _release();
		NECode& _getMaxCode(const NECodeType& type);

	protected:
		NECode	_max_scriptcode,
				_max_namecode,
				_max_groupcode,
				_max_prioritycode;
		type_index _max_node_length;
		type_index _max_module_length;
		type_index _max_key_length;
	};
}