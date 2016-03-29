#include "../../Kernal.hpp"

namespace NE
{
	NE_DLL Kernal::Settings::Settings()
		: Super()
	{

	}

	NE_DLL Kernal::Settings::Settings(const This& source)
		: Super(source)
	{
		_assign(source);
	}

	NE_DLL Kernal::Settings::~Settings()
	{
		
	}

	const Kernal::Settings NE_DLL &Kernal::Settings::operator=(const This& source)
	{
		return _assign(source);
	}

	bool NE_DLL Kernal::Settings::operator==(const This& source) const
	{
		if(this == &source) return true;
		if(_title != source._title) return false;
		if(_executable_platforms != source._executable_platforms) return false;
		if(_ini_fullpath != source._ini_fullpath) return false;
		if(_ini_forms != source._ini_forms) return false;
		if(_log_extractor != source._log_extractor) return false;
		if(_module_directory != source._module_directory) return false;
		if(_script_extractor != source._script_extractor) return false;
		if(_node_extractor != source._node_extractor) return false;
		if(_main_script_index != source._main_script_index) return false;
		if(_is_kernal_using_unicode != source._is_kernal_using_unicode) return false;
		if(_is_loading_from_ini != source._is_loading_from_ini) return false;
		
		return true;
	}

	bool NE_DLL Kernal::Settings::operator!=(const This& source) const
	{
		return ! (operator==(source));
	}

	void NE_DLL Kernal::Settings::release()
	{
		_title.release();
		_locale_compatibilities.release();
		_executable_platforms.release();
		_ini_forms.release();
		_ini_fullpath.release();
		_module_directory.release();
		_log_extractor.release();
		_script_extractor.release();
		_node_extractor.release();
		_main_script_index = NE_NULL;
		_is_kernal_using_unicode = false;
		_is_loading_from_ini = false;
	}

	type_result NE_DLL Kernal::Settings::isValid() const
	{
		type_result result = _locale_compatibilities.isValid();
		if(NEResult::hasError(result)) return result;
		result = _title.isValid();
		if(NEResult::hasError(result)) return result;
		result = _executable_platforms.isValid();
		if(NEResult::hasError(result)) return result;
		result = _ini_fullpath.isValid();
		if(NEResult::hasError(result)) return result;
		result = _ini_forms.isValid();
		if(NEResult::hasError(result)) return result;
		result = _module_directory.isValid();
		if(NEResult::hasError(result)) return result;
		result = _script_extractor.isValid();
		if(NEResult::hasError(result)) return result;
		result = _node_extractor.isValid();
		if(NEResult::hasError(result)) return result;
		result = _log_extractor.isValid();
		if(NEResult::hasError(result)) return result;
		if(_title.getLength() <= 0) return RESULT_TYPE_ERROR;
		if(_executable_platforms.getLength() <= 0) return RESULT_TYPE_ERROR;
		if(_ini_fullpath.getLength() <= 0) return RESULT_TYPE_ERROR;
		if(_ini_forms.getLength() <= 0) return RESULT_TYPE_ERROR;
		if(_module_directory.getLength() <= 0) return RESULT_TYPE_ERROR;
		if(_script_extractor.getLength() <= 0) return RESULT_TYPE_ERROR;
		if(_log_extractor.getLength() <= 0) return RESULT_TYPE_ERROR;
		if(_node_extractor.getLength() <= 0) return RESULT_TYPE_ERROR;		
		if(_main_script_index < 0) return RESULT_TYPE_ERROR;
		if(_module_directory.getLength() <= 0) return RESULT_TYPE_ERROR;
		if(_ini_fullpath.getLength() <= 0) return RESULT_TYPE_ERROR;

		return RESULT_SUCCESS;
	}

	NEBinaryFileSaver NE_DLL &Kernal::Settings::serialize(NEBinaryFileSaver& saver) const
	{
		return saver	<< _title << _locale_compatibilities 
						<< _executable_platforms << _ini_fullpath
						<< _ini_forms << _module_directory
						<< _script_extractor	<< _node_extractor
						<< _log_extractor << _main_script_index << _is_kernal_using_unicode
						<< _is_loading_from_ini;
	}

	NEBinaryFileLoader NE_DLL &Kernal::Settings::serialize(NEBinaryFileLoader& loader)
	{
		return loader	>> _title >> _locale_compatibilities 
						>> _executable_platforms >> _ini_fullpath
						>> _ini_forms >> _module_directory
						>> _script_extractor	>> _node_extractor
						>> _log_extractor >> _main_script_index >> _is_kernal_using_unicode
						>> _is_loading_from_ini;
	}

	const Kernal::Settings& Kernal::Settings::_assign(const This& source)
	{
		if(this == &source) return *this;
		_title = source._title;
		_locale_compatibilities = source._locale_compatibilities;
		_executable_platforms = source._executable_platforms;
		_ini_fullpath = source._ini_fullpath;
		_ini_forms = source._ini_forms;
		_module_directory = source._module_directory;
		_script_extractor = source._script_extractor;
		_node_extractor = source._node_extractor;
		_log_extractor = source._log_extractor;
		_main_script_index = source._main_script_index;
		_is_kernal_using_unicode = source._is_kernal_using_unicode;
		_is_loading_from_ini = source._is_loading_from_ini;

		return *this;
	}


	const NETString NE_DLL &Kernal::Settings::getTitle() const
	{
		return _title;
	}

	const NETStringSet NE_DLL &Kernal::Settings::getLocaleCompatibilities() const
	{
		return _locale_compatibilities;
	}

	const NETStringSet NE_DLL &Kernal::Settings::getExecutablePlatfroms() const
	{
		return _executable_platforms;
	}

	const NETString NE_DLL &Kernal::Settings::getINIFullPath() const
	{
		return _ini_fullpath;
	}

	const NETString NE_DLL &Kernal::Settings::getINIForms() const
	{
		return _ini_forms;
	}

	const NETString NE_DLL &Kernal::Settings::getLogExtractor() const
	{
		return _log_extractor;
	}

	const NETString NE_DLL &Kernal::Settings::getModuleDirectory() const
	{
		return _module_directory;
	}

	const NETString NE_DLL &Kernal::Settings::getScriptExtractor() const
	{
		return _script_extractor;
	}

	const NETString NE_DLL &Kernal::Settings::getNodeExtractor() const
	{
		return _node_extractor;
	}

	int NE_DLL Kernal::Settings::getMainScriptIndex() const
	{
		return _main_script_index;
	}
	
	bool NE_DLL Kernal::Settings::isKernalUsingUnicode() const
	{
		return _is_kernal_using_unicode;
	}
	
	NETString NE_DLL &Kernal::Settings::getTitle()
	{
		return _title;
	}

	NETStringSet NE_DLL &Kernal::Settings::getLocaleCompatibilities()
	{
		return _locale_compatibilities;
	}

	NETStringSet NE_DLL &Kernal::Settings::getExecutablePlatfroms()
	{
		return _executable_platforms;
	}

	NETString NE_DLL &Kernal::Settings::getINIFullPath()
	{
		return _ini_fullpath;
	}

	NETString NE_DLL &Kernal::Settings::getINIForms()
	{
		return _ini_forms;
	}

	NETString NE_DLL &Kernal::Settings::getLogExtractor()
	{
		return _log_extractor;
	}

	type_result NE_DLL Kernal::Settings::setModuleDirectory(const NETString& module_directory)
	{
		//	pre:
		if( ! &module_directory)
		{
			KERNAL_WARNING(" : ")
			return RESULT_TYPE_WARNING;
		}
		if(module_directory.getLength() <= 0)
		{
			KERNAL_WARNING(" : ")
			return RESULT_TYPE_WARNING;
		}
		
		
		
		//	main:
		_module_directory = module_directory;
		
		
		
		//	post:
		return _fixWhenDirectoryHasNotSlashAtTheEnd(_module_directory);
	}

	NETString NE_DLL &Kernal::Settings::getScriptExtractor()
	{
		return _script_extractor;
	}

	NETString NE_DLL &Kernal::Settings::getNodeExtractor()
	{
		return _node_extractor;
	}
	
	void NE_DLL Kernal::Settings::setKernalUsingUnicode(bool use_unicode)
	{
		_is_kernal_using_unicode = use_unicode;
	}

	void NE_DLL Kernal::Settings::setMainScriptIndex(type_index index)
	{
		_main_script_index = index;
	}
	
	bool NE_DLL Kernal::Settings::isLoadedFromINI() const
	{
		return _is_loading_from_ini;
	}

	void NE_DLL Kernal::Settings::setLoadFromINI( bool enable )
	{
		_is_loading_from_ini = enable;
	}
	
	type_result Kernal::Settings::_fixWhenDirectoryHasNotSlashAtTheEnd(NETString& directory_string_to_be_validate) const
	{
		//	pre:
		if( ! &directory_string_to_be_validate					||
			directory_string_to_be_validate.getLength() <= 0	||
			directory_string_to_be_validate == ""				)
		{
			directory_string_to_be_validate = ".\\";
			return KERNAL_WARNING(" : 경로를 입력하지 않아, 현재경로로 대체합니다.");
		}



		//	main:
		type_index last_index = directory_string_to_be_validate.getLengthLastIndex() - 1; // 마지막 글자는 널문자이기 때문에 -1 한다.
		TCHAR last_word = directory_string_to_be_validate[last_index];
		if(	last_word != _T('/')	&&
			last_word != _T('\\')	)
			directory_string_to_be_validate += _T("\\");		

		return RESULT_SUCCESS;
	}
}
