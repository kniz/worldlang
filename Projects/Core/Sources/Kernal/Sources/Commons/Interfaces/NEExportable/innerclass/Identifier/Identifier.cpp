#include "../../NEExportable.hpp"
#include "../../../../../Modules/Kernal/Kernal.hpp"

namespace NE
{
	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEExportable::Identifier::Identifier()
		: NEObject()
	{
		release();
	}

	NE_DLL NEExportable::Identifier::Identifier(const NETString& identifier_string_with_dot_delimiter)
		: NEObject()
	{
		release();

		setIdentifier(identifier_string_with_dot_delimiter);
	}

	NE_DLL NEExportable::Identifier::Identifier(const NETString& value_name, const NETString& value_developer, int value_revision)
		: NEObject()
	{
		release();
		_name = value_name;
		_developer = value_developer;
		_revision = value_revision;
	}


	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEExportable::Identifier::Identifier(const Identifier& source)
		:NEObject(source)
	{
		_assign(source);
	}



	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEExportable::Identifier::~Identifier()
	{

	}

	

	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	const NEExportable::Identifier NE_DLL &NEExportable::Identifier::operator=(const Identifier& source)
	{
		return _assign(source);
	}



	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	bool NE_DLL NEExportable::Identifier::operator==(const Identifier& source) const
	{
		if(this == &source) return true;
		if(_name != source._name) return false;
		if(_revision != source._revision) return false;
		if(_developer != source._developer) return false;

		return true;
	}



	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	bool NE_DLL NEExportable::Identifier::operator!=(const Identifier& source) const
	{
		return !(operator==(source));
	}



	type_result NEExportable::Identifier::setIdentifier(const NETString& identifier_string_with_dot_delimiter)
	{
		NETStringSet splited;
		identifier_string_with_dot_delimiter.split(_T("."), splited);

		switch(splited.getLength())
		{
		case 3:
			_revision = splited[2].toInt();
		case 2:
			_developer = splited[1];
		case 1:
			_name = splited[0];
			break;

		default:
			KERNAL_ERROR(" : ")
			return RESULT_TYPE_ERROR;
		}		

		return RESULT_SUCCESS;
	}

	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NE_DLL NEExportable::Identifier::release()
	{
		_name.release();
		_revision = 0;
		_developer.release();
	}



	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//				2011-07-09	이태훈	추가		식별자는 Length가 0일 경우, not valid
	//												로 간주한다.
	//	---------------------------------------------------------------------------------
	type_result NE_DLL NEExportable::Identifier::isValid() const
	{
		type_result result = _name.isValid();
		if(NEResult::hasError(result)) return result;
		if(_name.getLength() <= 0) return RESULT_TYPE_ERROR | RESULT_INVALID_DATA;
		if(_revision < 0) return RESULT_TYPE_ERROR | RESULT_INVALID_DATA;
		result = _developer.isValid();
		if(NEResult::hasError(result)) return result;
		if(_developer.getLength() <= 0) return RESULT_TYPE_ERROR | RESULT_INVALID_DATA;

		return RESULT_SUCCESS;
	}


	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEBinaryFileSaver NE_DLL &NEExportable::Identifier::serialize(NEBinaryFileSaver& saver) const
	{
		return saver << _name << _revision << _developer ;
	}



	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEBinaryFileLoader NE_DLL &NEExportable::Identifier::serialize(NEBinaryFileLoader& loader)
	{
		return loader >> _name >> _revision >> _developer;
	}



	//	---------------------------------------------------------------------------------
	//	설명:		"이름"과 "제작자"가 같은지 만을 비교한다.
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	bool NE_DLL NEExportable::Identifier::isSameModule(const Identifier& source) const
	{
		if(_name != source._name) return false;
		if(_developer != source._developer) return false;

		return true;
	}



	//	---------------------------------------------------------------------------------	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	const NEExportable::Identifier& NEExportable::Identifier::_assign(const Identifier& source)
	{
		if(this == &source) return *this;

		_name = source._name;
		_revision = source._revision;
		_developer = source._developer;		

		return *this;
	}
	
	NETString NE_DLL &NEExportable::Identifier::getName()
	{
		return _name;
	}

	const NETString NE_DLL &NEExportable::Identifier::getName() const
	{
		return _name;
	}

	NETString NE_DLL &NEExportable::Identifier::getDeveloper()
	{
		return _developer;
	}

	const NETString NE_DLL &NEExportable::Identifier::getDeveloper() const
	{
		return _developer;
	}

	int NE_DLL NEExportable::Identifier::getRevision() const
	{
		return _revision;
	}

	void NE_DLL NEExportable::Identifier::setRevision(type_count new__revision)
	{
		_revision = new__revision;
	}
}
