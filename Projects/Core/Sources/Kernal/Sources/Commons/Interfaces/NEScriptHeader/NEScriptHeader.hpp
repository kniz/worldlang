#pragma once

#include "../NEExportable/NEExportable.hpp"
#include "../../Units/NECode/NECode.hpp"

namespace NE
{
	class NE_DLL NEScriptHeader : public NEExportable::Header
	{
		typedef NEExportable::Header SuperClass;
		typedef NEScriptHeader ThisClass;

		//	friend 선언
		friend class ScriptManager;

		//	생성자:
	public:
		NEScriptHeader();
		NEScriptHeader(const ThisClass& source);

		//	소멸자:
	public:
		virtual ~NEScriptHeader();

	public:
		const NEScriptHeader& operator=(const ThisClass& source);
		bool operator==(const ThisClass& source) const;
		bool operator!=(const ThisClass& source) const;

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
		virtual NEObject& clone() const;

	private:
		const NEScriptHeader& _assign(const ThisClass& source);
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