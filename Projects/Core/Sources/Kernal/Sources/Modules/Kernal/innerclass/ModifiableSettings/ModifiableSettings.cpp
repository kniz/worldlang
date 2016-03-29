#include "../../../Kernal/Kernal.hpp"

namespace NE
{
	NE_DLL Kernal::ModifiableSettings::ModifiableSettings()
		: Super()
	{

	}

	NE_DLL Kernal::ModifiableSettings::ModifiableSettings(const This& source)
		: Super(source)
	{
		_assign(source);
	}

	NE_DLL Kernal::ModifiableSettings::~ModifiableSettings()
	{

	}

	const Kernal::ModifiableSettings NE_DLL &Kernal::ModifiableSettings::operator=(const This& source)
	{
		Kernal::Super::operator=(source);
		
		return _assign(source);
	}

	bool NE_DLL Kernal::ModifiableSettings::operator==(const This& source) const
	{
		if(this == &source) return true;
		if(Kernal::Super::operator!=(source)) return false;
		if(_locale != source._locale) return false;
		if(_log_directory != source._log_directory) return false;
		if(_script_directory != source._script_directory) return false;
		if(_node_directory != source._node_directory) return false;
		if(_flag != source._flag) return false;

		return true;
	}

	bool NE_DLL Kernal::ModifiableSettings::operator!=(const This& source) const
	{
		return ! (operator==(source));
	}

	void NE_DLL Kernal::ModifiableSettings::release()
	{
		_locale.release();
		_log_directory.release();
		_script_directory.release();
		_node_directory.release();
		_flag.release();
	}

	type_result NE_DLL Kernal::ModifiableSettings::isValid() const
	{
		type_result result = Kernal::Super::isValid();
		if(NEResult::hasError(result)) return result;
		result = _locale.isValid();
		if(NEResult::hasError(result)) return result;
		result = _script_directory.isValid();
		if(NEResult::hasError(result)) return result;
		result = _node_directory.isValid();
		if(NEResult::hasError(result)) return result;
		result = _log_directory.isValid();
		if(NEResult::hasError(result)) return result;
		if(_script_directory.getLength() <= 0) return RESULT_TYPE_ERROR;
		if(_node_directory.getLength() <= 0) return RESULT_TYPE_ERROR;
		if(_log_directory.getLength() <= 0) return RESULT_TYPE_ERROR;
		if(_locale_compatibilities.find(_locale) <= NE_INDEX_ERROR) return RESULT_TYPE_ERROR;
		result = _flag.isValid();
		if(NEResult::hasError(result)) return result;

		return RESULT_SUCCESS;
	}

	NEBinaryFileSaver NE_DLL &Kernal::ModifiableSettings::serialize(NEBinaryFileSaver& saver) const
	{
		Kernal::Super::serialize(saver);
	
		return saver << _locale << _script_directory << _node_directory << _log_directory << _flag;
	}

	NEBinaryFileLoader NE_DLL &Kernal::ModifiableSettings::serialize(NEBinaryFileLoader& loader)
	{
		Kernal::Super::serialize(loader);
	
		return loader >> _locale >> _script_directory >> _node_directory >> _log_directory >> _flag;
	}

	NETString NE_DLL &Kernal::ModifiableSettings::getLocale()
	{
		return _locale;
	}

	const NETString NE_DLL &Kernal::ModifiableSettings::getLocale() const
	{
		return _locale;
	}

	type_result NE_DLL Kernal::ModifiableSettings::setLogDirectory(const NETString& log_directory)
	{
		//	pre:
		if( ! &log_directory)
		{
			KERNAL_WARNING(" : ")
				return RESULT_TYPE_WARNING;
		}
		if(log_directory.getLength() <= 0)
		{
			KERNAL_WARNING(" : ")
				return RESULT_TYPE_WARNING;
		}



		//	main:
		_log_directory = log_directory;



		//	post:
		return _fixWhenDirectoryHasNotSlashAtTheEnd(_log_directory);
	}

	const NETString NE_DLL &Kernal::ModifiableSettings::getLogDirectory() const
	{
		return _log_directory;
	}

	type_result  NE_DLL Kernal::ModifiableSettings::setScriptDirectory(const NETString& script_directory)
	{
		//	pre:
		if( ! &script_directory)
		{
			KERNAL_WARNING(" : ")
				return RESULT_TYPE_WARNING;
		}
		if(script_directory.getLength() <= 0)
		{
			KERNAL_WARNING(" : ")
				return RESULT_TYPE_WARNING;
		}



		//	main:
		_script_directory = script_directory;



		//	post:
		return _fixWhenDirectoryHasNotSlashAtTheEnd(_script_directory);
	}

	const NETString NE_DLL &Kernal::ModifiableSettings::getScriptDirectory() const
	{
		return _script_directory;
	}

	type_result  NE_DLL Kernal::ModifiableSettings::setNodeDirectory(const NETString& node_directory)
	{
		//	pre:
		if( ! &node_directory)
		{
			KERNAL_WARNING(" : ")
				return RESULT_TYPE_WARNING;
		}
		if(node_directory.getLength() <= 0)
		{
			KERNAL_WARNING(" : ")
				return RESULT_TYPE_WARNING;
		}



		//	main:
		_node_directory = node_directory;



		//	post:
		return _fixWhenDirectoryHasNotSlashAtTheEnd(_node_directory);
	}

	const NETString NE_DLL &Kernal::ModifiableSettings::getNodeDirectory() const
	{
		return _node_directory;		
	}

	const Kernal::ModifiableSettings& Kernal::ModifiableSettings::_assign(const This& source)
	{
		if(this == &source) return *this;
		_locale = source._locale;
		_script_directory = source._script_directory;
		_node_directory = source._node_directory;
		_log_directory = source._log_directory;
		_flag = source._flag;

		return *this;
	}

	NEDebugManager::Flag NE_DLL &Kernal::ModifiableSettings::getDebugFlag()
	{
		return _flag;
	}

	const NEDebugManager::Flag NE_DLL &Kernal::ModifiableSettings::getDebugFlag() const
	{
		return _flag;
	}
}

