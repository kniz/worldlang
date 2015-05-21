#include "NEModule.hpp"
#include "../Kernal/Kernal.hpp"

namespace NE
{
	//	--------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEModule::NEModule()
		: NENamedUnit(NECodeType::MODULE_SCRIPT, NECodeType::MODULE_NAME), 
		_is_argument_fetched(false), _owner(0x00), _index(NE_INDEX_ERROR)		
	{
		_release();
	}		



	//	--------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	--------------------------------------------------------------------------------
	NE_DLL NEModule::NEModule(const NEModule& source)
		: NENamedUnit(source), _is_argument_fetched(false), _owner(0x00), _index(NE_INDEX_ERROR)
	{
		_assign(source);
	}


	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEModule::~NEModule()
	{

	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	bool NE_DLL NEModule::operator==(const NEModule& source) const
	{
		if(this == &source) return true;
		if(NENamedUnit::operator==(source) == false) return false;		
		if(_is_argument_fetched != source._is_argument_fetched) return false;
		
		return true;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	bool NE_DLL NEModule::operator!=(const NEModule& source) const
	{
		return !(operator==(source));
	}


	
	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEBinaryFileLoader NE_DLL &NEModule::serialize(NEBinaryFileLoader& loader)
	{
		NENamedUnit::serialize(loader);

		return loader >> getArguments();
	}

	NEBinaryFileSaver& NEModule::serialize(NEBinaryFileSaver& saver) const
	{
		NENamedUnit::serialize(saver);

		/*
			Argument의 저장:
				NEKeyNameBinder::serialize를 참고 해보면 상위클래스인 NEKeyBinder를 호출하지 않는다.
				이는 의도적인 행동으로, 바인딩 결과물인 NEKeyBinder 객체의 데이터를 공유하지 않기 위함이다.
					"상위클래스의 바인딩결과 정보는 공유(저장 및 로드)할 수 없다" 
				에 따라, 매 로드시마다 바인딩을 시도 하게 된다.
		*/
		return saver << getArguments();
	}


	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEType::Type NE_DLL NEModule::getType() const
	{
		return NEType::NEMODULE;
	}


	type_result NE_DLL NEModule::_onFetchModule()
	{
		return RESULT_SUCCESS | RESULT_ABORT_ACTION;
	}

	void NEModule::release()
	{
		SuperClass::release();

		_release();
	}

	type_result NEModule::isValid() const
	{
		type_result result = SuperClass::isValid();
		if(NEResult::hasError(result)) return result;
		result = _arguments.isValid();
		if(NEResult::hasError(result)) return result;

		return RESULT_SUCCESS;
	}

	const NEModule& NEModule::operator=(const ThisClass& rhs)
	{
		if(this == &rhs) return *this;

		SuperClass::operator=(rhs);

		return _assign(rhs);
	}

	void NEModule::_release()
	{
		_arguments.release();
		_is_argument_fetched = false;
	}

	type_result NEModule::_onFetchArguments(NEArgumentList& tray)
	{
		return RESULT_SUCCESS;
	}

	//	인스턴스가 indexedModuleSet에 추가될때 1번 호출된다.
	type_result NEModule::initialize()
	{
		getArguments();	//	Argument 등록을 위해서 호출한다.

		return _onInitialize();
	}

	NEModule& NEModule::_assign(const ThisClass& rhs)
	{
		if(this == &rhs) return *this;

		_is_argument_fetched = false;	//	인스턴스가 바뀌었으므로 새로 가져와야 한다

		return *this;
	}

	type_result NEModule::_onExecute()
	{
		return RESULT_SUCCESS;
	}

	type_result NEModule::execute()
	{
		//	pre:
		//		Enable 체크:
		if( ! isEnable()) return RESULT_SUCCESS | RESULT_ABORT_ACTION;
		//		외부 바인딩:
		getArguments().bind();	//	내부에서 Binding이 되어있으면 시도하지 않는다.
		//		로컬 스택 등록:
		NENodeManager::LocalStack& localstack = Kernal::getInstance().getNodeManager().getLocalStack();
		//			ModuleCodeSet에서도 로컬스택을 조정하는데, 왜 여기서도 스택을 조정하는가:
		//				ModuleCodeSet::execute()를 수행하지않고, ModuleCodeSet[n].execute()를 하는 경우가
		//				있기 때문이다.
		NEModuleCodeSet& before_stage_moduleset = localstack.getRecentModuleSet();
		localstack._setRecentModuleSet(getOwner());




		//	main:
		NEArgumentSet& args = getArguments();
		for (int n = 0; n < args.getLength(); n++)
			args[n]._onPrepareExecute();

		type_result result = _onExecute();

		for (int n = 0; n < args.getLength(); n++)
			args[n]._onPostExecute();
		localstack._setRecentModuleSet(before_stage_moduleset);
		return result;
	}

	type_result NEModule::_onInitialize()
	{
		return RESULT_SUCCESS;
	}

	const NEArgumentSet& NEModule::getArguments() const
	{
		ThisClass* unconsted = const_cast<ThisClass*>(this);

		return unconsted->getArguments();
	}

	NEArgumentSet& NEModule::getArguments()
	{
		if( ! _is_argument_fetched)
		{
			NEArgumentList tray;
			_onFetchArguments(tray);

			_arguments.create(tray.getLength());
			for(NEArgumentList::Iterator* e=tray.getIterator(0);
				e; e=e->getNext())
				_arguments.push(e->getValue());

			_is_argument_fetched = true;
		}

		return _arguments;
	}

	NEModuleCodeSet& NEModule::getOwner()
	{
		return *_owner;
	}

	const NEModuleCodeSet& NEModule::getOwner() const
	{
		return *_owner;
	}
}