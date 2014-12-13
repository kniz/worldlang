//	---------------------------------------------------------------------------------
//	클래스명:	NEStandardScriptManager
//	설명	:	스크립트를 관리하는 관리자 클래스
//	관계	:	기반클래스.	NEModule
//	특성	:	노드엔진에 반드시 포함되는 모듈의 일종
//	알고리즘:	
//	사용방법:	모듈의 독립성을 제공하는 모듈매니져와 달리 스크립트는 어떤 환경에서도
//				인덱스가 같으므로 인덱스만으로도 접근이 가능하다.
//				1.	getScriptLength	스크립트의 갯수 파악
//				2.	getScriptCode		인덱스를 통해서 스크립트에 접근
//	메모	:	
//	히스토리:	2011-07-07	이태훈	개발 완료	
//	---------------------------------------------------------------------------------
#pragma once

//	include:
#include "../../../Includes/Includes.hpp"

namespace NE
{
	class NE_DLL NEStandardScriptManager : public NEScriptManager
	{		
		typedef NEScriptManager SuperClass;
		typedef NEStandardScriptManager ThisClass;
	public:
#include "innerclass/ErrorCode/ErrorCode.hpp"
#include "innerclass/StandardNEScriptHeader/StandardNEScriptHeader.hpp"

		//	생성자:
	public:
		NEStandardScriptManager();	
		NEStandardScriptManager(const NEStandardScriptManager& source);

		//	소멸자:
	public:
		virtual ~NEStandardScriptManager();
		
	public:
		const NEStandardScriptManager& operator=(const NEStandardScriptManager& source);
		bool operator==(const NEStandardScriptManager& source) const;
		bool operator!=(const NEStandardScriptManager& source) const;

		//	인터페이스:
		//		상속:
		//			NEScriptManager:
	public:
		virtual NETString getScriptFilePath() const;
		virtual const NEScriptHeader& getNEScriptHeader() const;
		virtual const NERootNodeCodeSet& getScriptNodes() const;
	protected:
		virtual NERootNodeCodeSet& _getScriptNodes();
		virtual NEScriptHeader& _getNEScriptHeader();

		//			NEExportable:
	public:
		virtual type_result initialize();
		virtual const NEExportable::ModuleHeader& getHeader() const;
		virtual LPCTSTR getErrorMessage(type_errorcode errorcode) const;		
		//			NEUnit:
	private:
		virtual type_result execute();

		//	인터페이스:
		//		상속:
		//			NEObject:
	public:
		virtual void release();
		virtual NEObject& clone() const;
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
		virtual type_result isValid() const;

	protected:
		virtual type_result _onFetchModule();
		virtual type_result _onChangeNameCode(NENode& target, type_code new_namecode);
		virtual type_result _onChangePriorityCode(NENode& target, type_code new_prioritycode);
		virtual type_result _onChangeGroupCode(NENode& target, const NEIntSet& new_groupcodeset);
		
	private:
		const NEStandardScriptManager& _assign(const NEStandardScriptManager& source);
		void _release();
		
	protected:
		NETString _loaded_script_path;
		NETString _script_filename;
		NEScriptHeader _script_header;
		NERootNodeCodeSet _scriptset;
	};
}
