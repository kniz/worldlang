#include "../../Kernal.hpp"
#include "../../define/define.hpp"

namespace NE
{
	NE_DLL Kernal::Factory::Factory()
		: Super()
	{
		initialize();
	}

	NE_DLL Kernal::Factory::Factory(const Settings& base_settings)
		: Super()
	{
		_settings.Settings::operator=(base_settings);
	}

	NE_DLL Kernal::Factory::Factory(const This& source)
		: Super(source)
	{
		_assign(source);
	}

	NE_DLL Kernal::Factory::~Factory()
	{

	}

	const Kernal::Factory NE_DLL &Kernal::Factory::operator=(const This& source)
	{
		if(this == &source) return *this;

		return _assign(source);
	}

	bool NE_DLL Kernal::Factory::operator==(const This& source) const
	{
		if(this == &source) return true;
		if(_node_manager_identifier != source._node_manager_identifier) return false;
		if(_script_manager_identifier != source._script_manager_identifier) return false;
		if(_settings != source._settings) return false;

		return true;
	}

	bool NE_DLL Kernal::Factory::operator!=(const This& source) const
	{
		return ! operator==(source);
	}

	type_result NE_DLL Kernal::Factory::initialize()
	{
		//	pre:
		release();



		//	main:
		//		_default_settings:
		_settings.getTitle() = _DEFAULT_TITLE;		
		_settings.getLocaleCompatibilities().create(_DEFAULT_LOCALE_COMPATIBILITIES_COUNT);
		_settings.getLocaleCompatibilities().push(_T(_DEFAULT_LOCALE));
		_settings.getExecutablePlatfroms().create(_DEFAULT_EXECUTABLE_PLATFORMS_COUNT);
		_settings.getExecutablePlatfroms().push(_T(_DEFAULT_EXECUTABLE_PLATFORMS));
		_settings.getINIFullPath() = _T(_DEFAULT_INI_FULLPATH);
		_settings.getINIForms()= _T(_DEFAULT_INI_FORMS);
		_settings.getLogExtractor() = _T(_DEFAULT_LOG_EXTRACTOR);
		_settings.getScriptExtractor() = _T(_DEFAULT_SCRIPT_EXTRACTOR);
		_settings.getNodeExtractor() = _T(_DEFAULT_NODE_EXTRACTOR);
		_settings.setModuleDirectory(_T(_DEFAULT_MODULE_DIRECTORY));
		_settings.setLogDirectory(_T(_DEFAULT_LOG_DIRECTORY));
		_settings.setScriptDirectory(_T(_DEFAULT_SCRIPT_DIRECTORY));
		_settings.setNodeDirectory(_T(_DEFAULT_NODE_DIRECTORY));		
		_settings.setKernalUsingUnicode(_DEFAULT_IS_KERNAL_USING_UNICODE);
		_settings.setMainScriptIndex(_DEFAULT_MAIN_SCRIPT_INDEX);
		_settings.setLoadFromINI(_DEFAULT_LOAD_FROM_INI);
		_settings.getDebugFlag() = _DEFAULT_DEBUG_FLAG;
		_settings.getLocale() = _T(_DEFAULT_LOCALE);
		_node_manager_identifier.getName() = _T(_DEFAULT_NODE_MANAGER_IDENTIFIER_NAME);
		_node_manager_identifier.getDeveloper() = _T(_DEFAULT_NODE_MANAGER_IDENTIFIER_DEVELOPER);
		_node_manager_identifier.setRevision(_DEFAULT_NODE_MANAGER_IDENTIFIER_REVISION);
		_script_manager_identifier.getName() = _T(_DEFAULT_SCRIPT_MANAGER_IDENTIFIER_NAME);
		_script_manager_identifier.getDeveloper() = _T(_DEFAULT_SCRIPT_MANAGER_IDENTIFIER_DEVELOPER);
		_script_manager_identifier.setRevision(_DEFAULT_SCRIPT_MANAGER_IDENTIFIER_REVISION);

		return RESULT_SUCCESS;
	}

	void NE_DLL Kernal::Factory::release()
	{
		_node_manager_identifier.release();
		_script_manager_identifier.release();
		_settings.release();
	}

	type_result NE_DLL Kernal::Factory::isValid() const
	{
		type_result result = _node_manager_identifier.isValid();
		if(NEResult::hasError(result)) return result;
		result = _script_manager_identifier.isValid();
		if(NEResult::hasError(result)) return result;
		result = _settings.isValid();
		if(NEResult::hasError(result)) return result;

		return RESULT_SUCCESS;
	}

	NEBinaryFileSaver NE_DLL &Kernal::Factory::serialize(NEBinaryFileSaver& saver) const
	{
		return saver << _node_manager_identifier << _script_manager_identifier << _settings;
	}

	NEBinaryFileLoader NE_DLL &Kernal::Factory::serialize(NEBinaryFileLoader& loader)
	{
		return loader >> _node_manager_identifier >> _script_manager_identifier >> _settings;
	}

	Kernal NE_DLL Kernal::Factory::create()
	{
		//	main:
		Kernal kernal;
		kernal._script_manager_identifier = _script_manager_identifier;
		kernal._node_manager_identifier = _node_manager_identifier;
		kernal._settings = _settings;
		kernal._default_settings = _settings;

		return kernal;
	}
	
	NEExportable::Identifier NE_DLL &Kernal::Factory::getNodeManagerIdentifier()
	{
		return _node_manager_identifier;
	}

	const NEExportable::Identifier NE_DLL &Kernal::Factory::getNodeManagerIdentifier() const
	{
		return _node_manager_identifier;
	}

	NEExportable::Identifier NE_DLL &Kernal::Factory::getScriptManagerIdentifier()
	{
		return _script_manager_identifier;
	}

	const NEExportable::Identifier NE_DLL &Kernal::Factory::getScriptManagerIdentifier() const
	{
		return _script_manager_identifier;
	}

	Kernal::ModifiableSettings NE_DLL &Kernal::Factory::getDefaultSettings()
	{
		return _settings;
	}

	const Kernal::ModifiableSettings NE_DLL &Kernal::Factory::getDefaultSettings() const
	{
		return _settings;
	}
	
	const Kernal::Factory& Kernal::Factory::_assign(const This& source)
	{
		if(this == &source) return *this;

		_script_manager_identifier = source._script_manager_identifier;
		_node_manager_identifier = source._node_manager_identifier;
		_settings = source._settings;

		return *this;
	}
}
