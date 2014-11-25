#include "NEINIManager.hpp"
#include "../Kernal/Kernal.hpp"
#include "define/define.hpp"

namespace NE
{
	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEINIManager::NEINIManager()
		: NEModule()
	{

	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEINIManager::NEINIManager(const NEINIManager& source)
		: NEModule(source)
	{
		
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEINIManager::~NEINIManager()
	{

	}



	const NEINIManager NE_DLL &NEINIManager::operator=( const NEINIManager& source )
	{
		if(this == &source) return *this;
		
		NEModule::operator=(source);
		
		return *this;
	}

	bool NE_DLL NEINIManager::operator==( const NEINIManager& source ) const
	{
		return NEModule::operator==(source);
	}

	bool NE_DLL NEINIManager::operator!=( const NEINIManager& source ) const
	{
		return NEModule::operator!=(source);
	}
	
	

	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEType::Type NE_DLL NEINIManager::getType() const
	{
		return NEType::NEINI_MANAGER;
	}

	type_result NE_DLL NEINIManager::initialize()
	{
		NEModule::initialize();

		return RESULT_SUCCESS;
	}



	//	----------------------------------------------l-----------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	//	모듈 파일로부터 모듈을 가져온다
	type_result NE_DLL NEINIManager::execute()
	{
		return RESULT_SUCCESS;
	}




	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEObject NE_DLL &NEINIManager::clone() const
	{
		return *(new NEINIManager(*this));
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	모듈의 헤더를 내보낸다. 헤더는 클래스에 이미 정의되어서 컴파일된다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEExportable::ModuleHeader NE_DLL NEINIManager::_onRequestHeader() const
	{
		static NEExportable::ModuleHeader _header;

		if(_header.isValid() != RESULT_NOTHING)
		{
			_header.getName() = _T( _NAME );
			_header.getDeveloper() = _T( _AUTHOR );
			_header.setRevision(_REVISION);
			_header.getComment() = _T( _COMMENT );
			_header.getVersion() = _T( _VERSION );
			_header.getReleaseDate() = _T( _DATE );
			_header.getModuleDependencies().create(_DEPENDENCIES_COUNT);
			_header.setMaxErrorCodeCount(NEINIManager::ERROR_CODE_END - 1);
		}

		return _header;
	}

	LPCTSTR NE_DLL NEINIManager::getErrorMessage(type_errorcode errorcode) const
	{
		switch(errorcode)
		{
		case MODULE_IS_NOT_VALID:
			return _T("잘못된 Module");

		default:
			return _T("알수 없는 에러");
		}
	}






	//	---------------------------------------------------------------------------------
	//	설명	:	통합 INI 파일에서 주어진 모듈로 구분된 영역에 데이터를 읽어온다.
	//	동작조건:
	//	메모	:	NETString으로만 가져오므로 주의하라.
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	type_result NE_DLL NEINIManager::readModuleIniString(const NEExportable::Identifier& identifier, NETString keyword, NE_OUT NETString& loaded_data) const
	{
		NETString extractor = _DEFAULT_INI_MODULE_CATEGORY_EXTRACTOR;

		return read(extractor, keyword, loaded_data);
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	통합 INI 파일에서 주어진 모듈로 구분된 영역에 데이터를 저장한다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	type_result NE_DLL NEINIManager::writeModuleIniString(const NEExportable::Identifier& identifier, NETString keyword, NETString content) const
	{			
		NETString extractor = _DEFAULT_INI_MODULE_CATEGORY_EXTRACTOR;

		return write(extractor, keyword, content);
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	통합 INI 파일에 원하는 영역, 카테고리에 데이터를 작성할 수 있다.
	//	동작조건:
	//	메모	:	권장하지 않는다.
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	type_result NE_DLL NEINIManager::write(const NETString& category, const NETString& title, const NETString& content) const
	{ 
		const Kernal::Settings& settings = Kernal::getInstance().getSettings();

		_transformUnicode();
		if(WritePrivateProfileString(category.toCharPointer(), title.toCharPointer(), 
			content.toCharPointer(), settings.getINIFullPath().toCharPointer()) == NE_ERROR_0) // 에러시 0이 나온다
		{
			KERNAL_ERROR("E201001C12 : INI에 데이터 기록 실패\n데이터 기록에 실패했습니다.\n카테고리 : %s\n키 제목 : %s\n기록 시도한 데이터 : %s", category.toCharPointer(), title.toCharPointer(), content.toCharPointer())
				return RESULT_TYPE_ERROR | RESULT_ACCESS_DENIED;
		}

		return RESULT_SUCCESS;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	통합 INI 파일에 원하는 영역, 카테고리에 데이터를 읽어올 수 있다.
	//	동작조건:
	//	메모	:	권장하지 않는다.
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	type_result NE_DLL NEINIManager::read(const NETString& category, const NETString& title, NE_OUT NETString& loaded_data) const
	{
		//	pre:
		//		타겟팅:
		const Kernal::Settings& settings = Kernal::getInstance().getSettings();
		//		버퍼 생성:
		TCHAR buffer[_DEFAULT_TCHAR_BUFFER_SIZE] = {0, };



		//	main:
		//		INI Fetch:
		if(GetPrivateProfileString(category.toCharPointer(), title.toCharPointer(), NE_NULL, buffer, 
			_DEFAULT_TCHAR_BUFFER_SIZE, settings.getINIFullPath().toCharPointer()) <= 0)
		{
			KERNAL_ERROR("E201001C13 : INI로부터 데이터 읽기 실패\n데이터를 읽어 올수 없었습니다.\n호출한 모듈에게 에러를 반환합니다. 만약, 모듈에서 에러를 대처하는 코드가 존재한다면 기본값이 세팅될 것 입니다.\n카테고리 : %s\n키 제목 : %s", category.toCharPointer(), title.toCharPointer())
			return RESULT_TYPE_ERROR | RESULT_COULDNOT_FIND_DATA;
		}
		//		버퍼를 NETString으로 변환:
		loaded_data = buffer;



		//	post:
		return RESULT_SUCCESS;
	}



	//	---------------------------------------------------------------------------------	
	//	설명	:	WritePrivateProfileString은 파일생성시 디폴트 인코딩이 ANSI로 되어있다.
	//				내부적으로는 UNICODE라도, 파일이 존재하지 않을 경우에는 ANSI로 생성되는
	//				것. 이를 방지하기 위해서, 파일이 존재하지 않을 경우에는 강제로 UNICODE로
	//				저장한다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NE_DLL NEINIManager::_transformUnicode() const
	{
		//	pre:
		if( &Kernal::getInstance() )
			if( ! Kernal::getInstance().getSettings().isKernalUsingUnicode()) return;
		if(_isUnicodeFile()) return;

		//	BOM설정을 통해서 파일을 재생성한다. (대신 기존의 설정 정보가 사라짐)
		_createNewFileAsUTF16();
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	INI가 유니코드 파일인지 확인한다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	bool NE_DLL NEINIManager::_isUnicodeFile() const
	{	//	배경:	
		//		NEINI_PATH의 속한 파일이 유니코드 파일인지 여부를 리턴한다.
		//		인코딩 여부는 파일 첫부분 2~4바이트에 기록되어있다.
		//		여기서는 UTF16, LITTLE-ENDIAN인지만 판단한다.			
		//
		//			00	00	FE	FF		UTF-32,	BIG-ENDIAN
		//			FF	FE	00	00		UTF-32,	LITTLE-ENDIAN
		//			FE	FF				UTF-16,	BIG-ENDIAN
		//			FF	FE				UTF-16,	LITTLE_ENDIAN
		//			EF	BB	BF			UTF-8
		//			기타				ANSI
		//
		//		unsigned char(0 ~ 255)로 놓고 봤을때 FF = 255이므로,
		//		char에서는 -1이 된다.
		//		FE는 -2

		//	pre:
		const Kernal::Settings& settings = Kernal::getInstance().getSettings();



		//	main:
		//		INI 바이너리 모드로 로드:
		NEBinaryFileLoader loader(settings.getINIFullPath().toCharPointer());
		loader.open(); // 내부에서 findFile 호출				

		//		파일이 없다면 false:
		if(loader.isFileOpenSuccess() == false) return false;

		//		인코딩 정보 추출:	2 Byte를 가져온다
		char buffer[2] = {0, };
		loader.execute(buffer, 2);

		//		파일 닫기:
		loader.close();

		//		조건1:	인코딩 정보 판단:	UNICODE인가?
		if(	buffer[0] == signed char(0xFF)	&& // -1은 unsigned에서 0xFF, 
			buffer[1] == signed char(0xFE)	) 
			return true;

		KERNAL_INFORMATION("I201001C11 : INI 파일이 존재 하지 않습니다.\nINI 파일이 지정된 경로에 존재하지 않는 것을 확인했습니다.\n커널에서 INI를 다시 생성할 것입니다.\n주어진 경로 : %s", settings.getINIFullPath().toCharPointer())

			return false;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	INI 파일을 유니코드의 형식으로 새로 작성한다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NE_DLL NEINIManager::_createNewFileAsUTF16() const
	{
		const Kernal::Settings& settings = Kernal::getInstance().getSettings();

		//	main:
		HANDLE	hFile		= INVALID_HANDLE_VALUE;
		DWORD	wBOM		= 0xFEFF; // little-endian이므로, 실제로는 [0] = FF, [1] = FE가 된다.
		DWORD	dwCbWritten = 0;

		//	파일 생성:
		hFile = CreateFile(settings.getINIFullPath().toCharPointer(), GENERIC_WRITE, 0, NULL, 
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		//		파일 생성 검사:
		if(hFile == INVALID_HANDLE_VALUE)
			KERNAL_ERROR("E201001C7 : INI 파일 생성 실패\n주어진 경로에 INI파일을 생성 할 수 없었습니다.\n시도한 경로:%s", settings.getINIFullPath().toCharPointer())		
		else
		{
			//	파일을 유니코드로 변환:
			//		변환에 실패( != 0 ) 했다면:
			if(WriteFile(hFile, &wBOM, sizeof(WORD), &dwCbWritten, NULL) == NE_ERROR_0) // 에러시 0
				KERNAL_ERROR("E201001C8 : INI 파일을 유니코드 파일로 변환 실패\n파일을 정상적으로 OPEN 했지만 데이터 작성에는 실패했습니다.\n운영체제의 호환성 문제나, 잘못된 파일일 수도 있습니다.\nINI파일을 삭제하고 다시 시도해보십시오\n시도한 경로 : %s", settings.getINIFullPath().toCharPointer())		
			else	//	성공했다면:
			{
				//			INI 상단 메세지 생성:	BOM으로 파일을 생성하면 첫줄이 빈줄이 된다. 그래서, 첫섹션을 채워줌
				if(WriteFile(hFile, settings.getINIForms().toCharPointer(), (settings.getINIForms().getLength())*(sizeof(TCHAR)), 
					&dwCbWritten, NULL) == NE_ERROR_0)
					KERNAL_ERROR("E201001C9 : INI 파일 상단 메세지 기록 실패\n파일을 정상적으로 OPEN해서 UNICODE로 변환했지만 상단 메세지작성에 실패했습니다.\n운영체제의 호환성 문제나, 잘못된 파일일 수도 있습니다.\nINI파일을 삭제하고 다시 시도해보십시오\n시도한 경로 : %s", settings.getINIFullPath().toCharPointer())
				else
				KERNAL_INFORMATION("I201001C10 : 새로운 INI 파일 작성 성공\nINI 파일을 지정된 경로에 성공적으로 작성했습니다.\nINI에 기록된 모든 값은 엔진의 기본값(default)로 세팅됩니다.\n생성한 경로 : %s", settings.getINIForms().toCharPointer())
			}
		}



		//	post:
		if(NULL != hFile)
		{
			CloseHandle(hFile);
			hFile = INVALID_HANDLE_VALUE;
		}
	}
}
