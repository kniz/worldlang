#include "NENamedUnit.hpp"

namespace NE
{
	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NENamedUnit::NENamedUnit()
		: NEExecutableUnit(), _namecode(NECodeType::NAME), _scriptcode(NE_HAS_NO_SCRIPTCODE, NECodeType::SCRIPT, true)// 상위 생성자
	{
		_release();
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NENamedUnit::NENamedUnit(type_code namecode)
		: NEExecutableUnit(), _namecode(namecode, NECodeType::NAME, true), _scriptcode(NE_HAS_NO_SCRIPTCODE, NECodeType::SCRIPT, true)
	{
		
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NENamedUnit::NENamedUnit(const NENamedUnit& source)
		: NEExecutableUnit(source), _namecode(source._namecode), _scriptcode(source._scriptcode)
	{	
		_assign(source);
		
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NENamedUnit::~NENamedUnit()
	{

	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	bool NE_DLL NENamedUnit::operator==(const NENamedUnit& source) const
	{
		if(this == &source) return true;
		if(NEExecutableUnit ::operator==(source) == false) return false;
		if(_namecode != source._namecode) return false;
		if(_scriptcode != source._scriptcode) return false;

		return true;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	bool NE_DLL NENamedUnit::operator!=(const NENamedUnit& source) const
	{
		return !(operator==(source));
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	const NENamedUnit NE_DLL &NENamedUnit::operator=(const NENamedUnit& source)
	{
		NEExecutableUnit ::operator=(source);

		return _assign(source);
	}



	const NECode NE_DLL &NENamedUnit::getScriptCode() const
	{
		return _scriptcode;
	}

	

	//	---------------------------------------------------------------------------------
	//	설명	:	_namecode는 고유의 식별코드다. 같은 _scriptcode(스크립트)를 갖는 노드는 존재
	//				할 수 있으나, 같은 _namecode를 갖는 노드는 없다.
	//				물론 네임코드가 없는 노드도 있다.
	//	동작조건:
	//	메모	:	_namecode가 0이라면 없는 것으로 간주한다.(더미)
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	const NECode NE_DLL &NENamedUnit::getNameCode() const 
	{
		return _namecode;
	}	



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NE_DLL NENamedUnit::release()
	{
		NEExecutableUnit ::release();

		_release();
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEBinaryFileSaver NE_DLL &NENamedUnit::serialize(NEBinaryFileSaver& saver) const 
	{
		NEExecutableUnit ::serialize(saver);

		return saver << _namecode << _scriptcode;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEBinaryFileLoader NE_DLL &NENamedUnit::serialize(NEBinaryFileLoader& loader)
	{
		NEExecutableUnit ::serialize(loader);

		return loader >> _namecode >> _scriptcode;
	}



	type_result NE_DLL NENamedUnit::isValid() const
	{
		if(_scriptcode.getCode() < NE_HAS_NO_SCRIPTCODE) return RESULT_TYPE_ERROR;
		if(_namecode.getCode() < 0) return RESULT_TYPE_ERROR;
		
		return RESULT_SUCCESS;
	}
	
	
	
	
	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NENamedUnit::_release()
	{
		/*
			scriptcode값은 변경하면 안된다.
		*/
		_namecode.release();
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	const NENamedUnit& NENamedUnit::_assign(const NENamedUnit& source)
	{
		//	pre:
		if(this == &source) return *this;

		_scriptcode = source._scriptcode;
		_namecode = source._namecode;

		return *this;
	}

	type_result NENamedUnit::setNameCode(const NECode& new_namecode)
	{
		_namecode = new_namecode;
		
		return RESULT_SUCCESS;
	}
}
