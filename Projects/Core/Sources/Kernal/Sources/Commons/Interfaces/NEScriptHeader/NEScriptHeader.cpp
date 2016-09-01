#include "NEScriptHeader.hpp"
#include "../../../Modules/Kernal/Kernal.hpp"

namespace NE
{
	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEScriptHeader::NEScriptHeader()
		: Super(), 
		_max_namecode(0, NECodeType::NAME),
		_max_scriptcode(0, NECodeType::SCRIPT),
		_max_groupcode(0, NECodeType::GROUP),
		_max_prioritycode(0, NECodeType::PRIORITY)
	{
		_release();
	}



	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEScriptHeader::NEScriptHeader(const This& source)
		: Super(source)
	{
		_assign(source);
	}



	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEScriptHeader::~NEScriptHeader()
	{

	}



	const NEScriptHeader NE_DLL &NEScriptHeader::operator=(const NEScriptHeader& source)
	{
		Super::operator=(source);

		return _assign(source);
	}

	type_bool NE_DLL NEScriptHeader::operator==(const NEScriptHeader& source) const
	{
		if(this == &source) return true;
		if(Super::operator!=(source)) return false;
		if(_max_scriptcode != source._max_scriptcode) return false;
		if(_max_namecode != source._max_namecode) return false;
		if(_max_groupcode != source._max_groupcode) return false;
		if(_max_prioritycode != source._max_prioritycode) return false;
		if(_max_node_length != source._max_node_length) return false;
		if(_max_module_length != source._max_module_length) return false;
		if(_max_key_length != source._max_key_length) return false;

		return true;
	}

	type_bool NE_DLL NEScriptHeader::operator!=(const NEScriptHeader& source) const
	{
		return !(operator==(source));
	}

	const NEScriptHeader& NEScriptHeader::_assign(const NEScriptHeader& source)
	{
		if(this == &source) return *this;

		_max_scriptcode = source._max_scriptcode;
		_max_namecode = source._max_namecode;
		_max_groupcode = source._max_groupcode;
		_max_prioritycode = source._max_prioritycode;
		_max_node_length = source._max_node_length;
		_max_module_length = source._max_module_length;
		_max_key_length = source._max_key_length;

		return *this;
	}

	type_result NE_DLL NEScriptHeader::setMaxCode(const NECode& source)
	{
		if(NEResult::hasError(source.isValid()))
		{
			KERNAL_ERROR(" : ");
			return RESULT_TYPE_WARNING;
		}


		//	main:
		NECode* target = &_getMaxCode(source);
		if( ! &target)
		{
			KERNAL_ERROR(" : ");
			return RESULT_TYPE_ERROR;
		}

		*target = source;

		return RESULT_SUCCESS;
	}

	const NECode NE_DLL &NEScriptHeader::getMaxCode(const NECodeType& type) const
	{
		This* unconsted = const_cast<This*>(this);

		return unconsted->_getMaxCode(type);
	}

	NECode NE_DLL &NEScriptHeader::_getMaxCode(const NECodeType& type)
	{
		switch (type.getCodeType())
		{
		case NECodeType::SCRIPT:	return _max_scriptcode;
		case NECodeType::NAME:		return _max_namecode;
		case NECodeType::PRIORITY:	return _max_prioritycode;
		case NECodeType::GROUP:		return _max_groupcode;
		}

		NECode* nullpointer = 0x00;
		return *nullpointer;
	}

	void NE_DLL NEScriptHeader::release()
	{
		Super::release();

		_release();
	}

	type_result NE_DLL NEScriptHeader::isValid() const
	{
		type_result result = Super::isValid();
		if(NEResult::hasError(result)) return result;
		if(NEResult::hasError(result = _max_scriptcode.isValid())) return result;
		if(NEResult::hasError(result = _max_namecode.isValid())) return result;
		if(NEResult::hasError(result = _max_groupcode.isValid())) return result;
		if(NEResult::hasError(result = _max_prioritycode.isValid())) return result;
		if(_max_node_length < 0) return RESULT_TYPE_ERROR;
		if(_max_module_length < 0) return RESULT_TYPE_ERROR;
		if(_max_key_length < 0) return RESULT_TYPE_ERROR;

		return RESULT_SUCCESS;
	}

	NEBinaryFileSaver NE_DLL &NEScriptHeader::serialize(NEBinaryFileSaver& saver) const
	{
		Super::serialize(saver);

		return saver	<< _max_scriptcode << _max_namecode << _max_groupcode << _max_prioritycode
						<< _max_node_length << _max_module_length << _max_key_length;
	}

	NEBinaryFileLoader NE_DLL &NEScriptHeader::serialize(NEBinaryFileLoader& loader)
	{
		Super::serialize(loader);

		return loader	>> _max_scriptcode >> _max_namecode >> _max_groupcode >> _max_prioritycode
						>> _max_node_length >> _max_module_length >> _max_key_length;
	}

	void NEScriptHeader::_release()
	{
		_max_scriptcode.release();
		_max_namecode.release();
		_max_groupcode.release();
		_max_prioritycode.release();
		_max_node_length = 0;
		_max_module_length = 0;
		_max_key_length = 0;
	}

	type_result NEScriptHeader::setMaxNodeLength(type_index max_node_length)
	{
		if(max_node_length < 0)
		{
			KERNAL_ERROR(" : ");
			return RESULT_TYPE_WARNING;
		}

		_max_node_length = max_node_length;
		return RESULT_SUCCESS;
	}

	NE::type_index NEScriptHeader::getMaxNodeLength() const
	{
		return _max_node_length;
	}

	type_result NEScriptHeader::setMaxModuleLength(type_index max_module_length)
	{
		if(max_module_length < 0)
		{
			KERNAL_ERROR(" : ");
			return RESULT_TYPE_WARNING;
		}

		_max_module_length = max_module_length;
		return RESULT_SUCCESS;
	}

	type_index NEScriptHeader::getMaxModuleLength() const
	{
		return _max_module_length;
	}

	type_result NEScriptHeader::setMaxKeyLength(type_index max_key_length)
	{
		if(max_key_length < 0)
		{
			KERNAL_ERROR(" : ");
			return RESULT_TYPE_WARNING;
		}

		_max_key_length = max_key_length;
		return RESULT_SUCCESS;
	}

	NE::type_index NEScriptHeader::getMaxKeyLength() const
	{
		return _max_key_length;
	}
}