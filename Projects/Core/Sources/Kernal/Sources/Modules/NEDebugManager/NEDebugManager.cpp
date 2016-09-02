#include "NEDebugManager.hpp"
#include "../Kernal/Kernal.hpp"
#include "define/define.hpp"

namespace NE
{

#ifdef DEVELOPER

	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEDebugManager::NEDebugManager()
		: Super()
	{
		// 생성자에는 아무것도 실행하면 안된다. 싱글톤에 속해있기 때문이다.
		_release();
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEDebugManager::NEDebugManager(const This& source)
		: Super(source)
	{
		_assign(source);
	}

	

	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEDebugManager::~NEDebugManager()
	{
		_closeLogFile();		
		closeConsole();
	}
	
	const NEDebugManager NE_DLL &NEDebugManager::operator=(const This& source)
	{
		if(this == &source) return *this;
		Super::operator=(source);
		
		return *this;
	}

	type_bool NE_DLL NEDebugManager::isDebugModeEnabled() const
	{
		return _debug_mode_enabled;
	}

	void NE_DLL NEDebugManager::setDebugMode(type_bool debug_mode_enabled)
	{
		_debug_mode_enabled = debug_mode_enabled;
	}

	type_bool NE_DLL NEDebugManager::isConsoleEnabled() const
	{
		return _console_enabled;
	}

	void NE_DLL NEDebugManager::setConsoleEnabled(type_bool enable)
	{
		_console_enabled = enable;
	}

	type_bool NE_DLL NEDebugManager::isLogEnabled() const
	{
		return _log_enabled;
	}

	void NE_DLL NEDebugManager::setLogEnabled(type_bool enable)
	{
		_log_enabled = enable;
	}

	type_bool NE_DLL NEDebugManager::isMessageBoxEnabled() const
	{
		return _messagebox_enabled;
	}

	void NE_DLL NEDebugManager::setMessageBoxEnabled(type_bool enable)
	{
		_messagebox_enabled = enable;
	}

	type_bool NE_DLL NEDebugManager::isDebugWindowEnabled() const
	{
		return _debugwindow_enabled;
	}

	void NE_DLL NEDebugManager::setDebugWindowEnabled(type_bool enable)
	{
		_debugwindow_enabled = enable;
	}

	type_bool NE_DLL NEDebugManager::isErrorLevelEnabled() const
	{
		return _error_enabled;
	}

	void NE_DLL NEDebugManager::setErrorLevelEnabled(type_bool enable)
	{
		_error_enabled = enable;
	}

	type_bool NE_DLL NEDebugManager::isWarningLevelEnabled() const
	{
		return _warning_enabled;
	}

	void NE_DLL NEDebugManager::setWarningLevelEnabled(type_bool enable)
	{
		_warning_enabled = enable;
	}

	type_bool NE_DLL NEDebugManager::isInformationLevelEnabled() const
	{
		return _information_enabled;
	}

	void NE_DLL NEDebugManager::setInformationLevelEnabled(type_bool enable)
	{
		_information_enabled = enable;
	}

	NEDebugManager::FlagSet NE_DLL &NEDebugManager::getFlagSet()
	{
		return _flagset;
	}

	const NEDebugManager::FlagSet NE_DLL &NEDebugManager::getFlagSet() const
	{
		return _flagset;
	}




	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	type_result NE_DLL NEDebugManager::initialize()
	{
		Super::initialize();

		_release();
		return _initialize();
	}		



	//	---------------------------------------------------------------------------------
	//	설명	:	INI로부터 NEDebugManager의 INI정보와 모듈의 Flag를 가져온다.
	//	동작조건:	
	//	메모	:	
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	type_result NE_DLL NEDebugManager::execute()
	{
		return RESULT_SUCCESS;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEBinaryFileSaver NE_DLL &NEDebugManager::serialize(NEBinaryFileSaver& saver) const
	{
		Super::serialize(saver);

		return saver;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEBinaryFileLoader NE_DLL &NEDebugManager::serialize(NEBinaryFileLoader& loader)
	{
		Super::serialize(loader);

		return loader;
	}


	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	type_result NE_DLL NEDebugManager::isValid() const
	{		
		type_result result = Super::isValid();
		if(NEResult::hasError(result)) return result | MODULE_IS_NOT_VALID;
		result = _flagset.isValid();
		if(NEResult::hasError(result)) return result | FLAGSET_IS_NOT_VALID;

		return RESULT_SUCCESS;
	}



	void NE_DLL NEDebugManager::release()
	{
		Super::release();

		_release();
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	모듈의 헤더를 내보낸다. 헤더는 클래스에 이미 정의되어서 컴파일된다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	const NEHeader NE_DLL &NEDebugManager::getHeader() const
	{
		static NEHeader _header;

		if(_header.isValid() != RESULT_NOTHING)
		{
			//	아직 초기화가 안되었음
			_header.getName() = _T(_NAME);
			_header.getDeveloper() = _T(_DEVELOPER);
			_header.setRevision(_REVISION);
			_header.getReleaseDate() = _T(_DATE);
			_header.getVersion() = _T(_VERSION);
			_header.getComment() = _T(_COMMENT);
			_header.setMaxErrorCodeCount(This::END_OF_ERROR_CODE - 1);
		}

		return _header;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	INI로부터 NEDebugManager의 Flag와 각 모듈의 Flag를 가져온다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NE_DLL NEDebugManager::loadFromINI()
	{
		_loadFlagFromINI();
		_loadFlagSetFromINI();	
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	INI에 NEDebugManager의 Flag와 각 모듈의 Flag를 저장한다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NE_DLL NEDebugManager::saveToINI() const
	{
		_saveFlagToINI();
		_saveFlagSetToINI();
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	주어진 디버그 메세지를 출력한다.
	//				출력 방법은 4가지다.
	//	동작조건:	_debug_mode_enabled가 false 일 경우.
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NE_DLL NEDebugManager::alert(NETString debug_message)
	{
		if(_debug_mode_enabled == false) return;

		printDebugWindow(debug_message);
		printMessageBox(debug_message);
		writeLogFile(debug_message);
		printConsole(debug_message);
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	디버그 창에 출력한다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NE_DLL NEDebugManager::printDebugWindow(NETString message) const
	{
		OutputDebugString(message.toCharPointer());
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	메세지박스에 출력한다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NE_DLL NEDebugManager::printMessageBox(NETString message) const
	{
		MessageBox(NE_NULL, message.toCharPointer(), _T("DEBUG"), MB_OK);
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	로그에 기록한다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NE_DLL NEDebugManager::writeLogFile(NETString message)
	{
		//	pre:
		if(_saver.isFileOpenSuccess() == false) 
			_openLogFile();



		//	main:
		_saver.writeString(message.toCharPointer());
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	콘솔창에 기록한다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NE_DLL NEDebugManager::printConsole(NETString message)
	{
		//	pre:		
		openConsole();



		//	main:
#ifdef _UNICODE
		std::wcout << message.toCharPointer();
#else
		std::cout << message.toCharPointer();
#endif
	}



	type_result NEDebugManager::_transitionToResult(NEResult::Level level) const
	{
		switch (level)
		{
		case NEResult::LEVEL_ERROR:			return RESULT_TYPE_ERROR;
		case NEResult::LEVEL_WARNING:		return RESULT_TYPE_WARNING;
		case NEResult::LEVEL_INFORMATION:	return RESULT_TYPE_INFORMATION;
		}

		return RESULT_SUCCESS;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	주어진 모듈의 정보와 허락된 Flag를 참고하여 디버그 메세지를 Printf 형식의,
	//				문자열로 변환해 출력한다.
	//	동작조건:
	//	메모	:	매크로가 존재하며, 주로 매크로에 의해서 호출되는 함수다.
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	type_result NE_DLL _cdecl NEDebugManager::alert(const NEIdentifier& identifier, NEResult::Level level, LPCTSTR printf_type_string, ...)
	{	//	배경:
		//		채널:
		//			모듈은 추가될때 아이디(= _id )를 부여 받는다.
		//			이 아이디 정보를 이용해서 INI로부터 flag가 읽혀진다.
		//			_flagset[ 모듈scriptcode ]에는 해당 모듈의 디버그 메세지의 flag가 기록되어있다.
		//
		//		Flag:
		//			Flag는 다음과 같다.
		//				0x00	없음
		//				0x01	log를 남김
		//				0x02	콘솔창에 출력
		//				0x04	메세지 박스에 출력
		//				0x08	디버그 창에 출력
		//			Flag는 중복 될 수 있다.
		//			예)	0x15의 경우는 1 + 2 + 4 + 8 로써, 모든 장소에 메세지를 출력한다.

		//	pre:
		//		에러체크:
		if( ! isDebugModeEnabled()) return _transitionToResult(level);
		if (printf_type_string == NE_NULL) return _transitionToResult(level);
		if (isAcceptedLevel(level) == false) return _transitionToResult(level);
		if (_debug_mode_enabled == false) return _transitionToResult(level);
		if (!&Kernal::getInstance()) return _transitionToResult(level);
		//		버퍼:
		const Flag* flag = NE_NULL;
		//		타겟팅:		
		if(identifier == Kernal::getInstance().getHeader())
		{	//	커널에서 에러메세지가 발생한 경우는 _flagset을 사용할 수 없다:
			flag = &(Kernal::getInstance().getSettings().getDebugFlag());
		}
		else
		{	//	일반적인 경우는 _flagset 사용이 가능:
			const Super& module = Kernal::getInstance().getModuleManager().getModule(identifier);
			//		파라메터 검사:
			if(! &module ){ return KERNAL_ERROR(" : ");}
			//		메시지 출력 준비:				
			//			모듈의 아이디 획득:
			type_code index = module.getScriptCode();
			//					못찾았다면 종료:
			if(index < 0){return KERNAL_ERROR(" : ");}
			if (index > _flagset.getLengthLastIndex()) return _transitionToResult(level);
			//					찾았다면:
			//						Flag 획득:
			flag = &(_flagset[index]);
		}		



		//	main:
		//		날짜와 시간정보 붙임:	파라메터인 포맷(= printf_type_string ) 앞에 날짜와 시간을 적는다.
		NETString merged_message = _T("\n") + _getDate() + _T("\t") + _getTime() + printf_type_string;
		//		가변인자 생성:
		//			최종적으로 전달하게될 버퍼 생성:
		NETString message;
		//			가변인자가 적용될 버퍼생성:
		TCHAR message_buffer[_DEFAULT_TCHAR_FINAL_BUFFER_SIZE] = {0, };
		//			가변인자 적용:
		//				가변인자 포인터 생성:
		va_list variable_list;
		//				가변인자 포인터에 값 삽입:
		va_start(variable_list, printf_type_string);
		//				가변인자값이 적용된 메세지 생성:
		_vstprintf_s(message_buffer, _DEFAULT_TCHAR_FINAL_BUFFER_SIZE, merged_message.toCharPointer(), variable_list);
		//				가변인자 포인터 해제:
		va_end(variable_list);

		//			최종버퍼에 가변인자 버퍼 삽입:
		message = message_buffer;



		//	post:
		//		Flag에 의해 일괄 메세지 출력:	모듈의 채널을 이용해서 메세지 출력한다
		if(flag->isDebugWindowShown() && _debugwindow_enabled)
			printDebugWindow(message);
		if(flag->isMessageBoxShown() && _messagebox_enabled)
			printMessageBox(message);
		if(flag->isLogShown() &&	_log_enabled)
			writeLogFile(message);
		if(flag->isConsoleShown() && _console_enabled)
			printConsole(message);

		return _transitionToResult(level);
	}

	type_bool NE_DLL NEDebugManager::isConsoleOpened() const
	{
		return (GetStdHandle(STD_OUTPUT_HANDLE) != NE_NULL);
	}


	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	type_result NEDebugManager::_initialize()
	{
		_loadFlagFromINI();
		_loadFlagSetFromINI();

		return RESULT_SUCCESS;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	콘솔창을 생성한다.
	//	동작조건:	NEDebugManager의 Flag중 콘솔창이 true 일 경우
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	type_result NE_DLL NEDebugManager::openConsole()
	{	
		//	pre:
		if(isConsoleOpened()) return RESULT_TYPE_INFORMATION | RESULT_ABORT_ACTION | CONSOLE_HAS_ALREADY_OPENED;



		//	main:
		//		타겟팅:
		const Kernal::ModifiableSettings& settings = Kernal::getInstance().getSettings();
		//		콘솔창 OPEN:
		FILE *file = NE_NULL;
		AllocConsole();
		//		콘솔창에 읽기 쓰기 기능 부여:
		freopen_s(&file, "CONOUT$", "wt", stdout);
		//		소멸시 콘솔창을 닫기 위한 정보 보존:
		_did_i_open_the_console = true;
		//		콘솔창 open시 기본메세지 출력:
		std::cout << _DEFAULT_CONSOLE_WINDOW_BOOT_MESSAGE;		
#ifdef _UNICODE
		NEString converted_string(settings.getLocale());
		std::wcout.imbue( std::locale(converted_string.toCharPointer()) );
#else
		std::cout.imbue( std::locale(settings.getLocale().toCharPointer()) );		
#endif



		//	post:
		return RESULT_SUCCESS;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	콘솔창을 닫는다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	type_result NE_DLL NEDebugManager::closeConsole()
	{
		//	pre:
		/*
			이 시점에서 에러메세지를 남기지 못한다. 왜냐하면 소멸자에서 closeConsole()을
			호출 하기 때문에 소멸도중 메세지를 호출하지 못하기 때문이다.
		*/
		if( ! isConsoleOpened()) return RESULT_TYPE_WARNING | RESULT_ABORT_ACTION;
		if( ! _did_i_open_the_console) return RESULT_SUCCESS;



		//	main
		if(FreeConsole() == NE_ERROR_0)
			return RESULT_TYPE_WARNING | RESULT_ACCESS_DENIED | COULD_NOT_CLOSE_CONSOLE;

		return RESULT_SUCCESS;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-08-03	이태훈	작성
	//	---------------------------------------------------------------------------------
	LPCTSTR NE_DLL NEDebugManager::getErrorMessage(type_errorcode errorcode) const
	{
		switch(errorcode)
		{
		case MODULE_IS_NOT_VALID:
			return _T("잘못된 Module");
		case FLAGSET_IS_NOT_VALID:
			return _T("잘못된 FlagSet");
		case CONSOLE_HAS_ALREADY_OPENED:
			return _T("콘솔 윈도우 로드 실패");
		case COULD_NOT_CLOSE_CONSOLE:
			return _T("콘솔 윈도우 언로드 실패");
		default:
			return _T("알수 없는 에러");
		}
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	type_bool NE_DLL NEDebugManager::isAcceptedLevel(NEResult::Level level) const
	{
		if(	level <= NEResult::LEVEL_START	||
			level >= NEResult::LEVEL_END	)
			return false;

		if(level == NEResult::LEVEL_ERROR && _error_enabled == false)
			return false;
		else if(level == NEResult::LEVEL_WARNING && _warning_enabled == false)
			return false;
		else if(level == NEResult::LEVEL_INFORMATION && _information_enabled == false)
			return false;

		return true;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	로그파일을 순차모드로 open 한다.
	//	동작조건:
	//	메모	:	FileAccess를 사용한다.
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NEDebugManager::_openLogFile()
	{	//	pre:
		//		폴더가 존재하는지 확인:	없다면 생성한다
		const Kernal::ModifiableSettings& settings = Kernal::getInstance().getSettings();
		_checkFolderExist();



		//	main:
		//		open할 파일의 경로 획득:	경로는 미리 정의되어있다. (= define )		
		NETString log_path = settings.getLogDirectory() + _T("\\") + _generateFilename() + _T(".") + settings.getLogExtractor();

		//		파일 열기:
		//			Flag 설정:	Append 모드
		_saver.flag = NEFILESAVERFLAG_APPEND_AT_END_OF_FILE;
		//			Open:
		_saver.setPath(log_path.toCharPointer());
		_saver.open();
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	Log파일을 저장할 폴더가 존재하는지 확인한다.
	//				만약 폴더가 존재하지 않는다면 폴더를 생성한다.
	//	동작조건:
	//	메모	:	NEFileSystem을 사용한다.
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NEDebugManager::_checkFolderExist() const // use NEFileSystem library
	{	
		const Kernal::ModifiableSettings& settings = Kernal::getInstance().getSettings();

		//	pre:
		//		NEFileSystem에 경로 삽입:
		NEFileSystem filesystem(settings.getLogDirectory().toCharPointer()); // 예) "log/"
		filesystem.findFile();



		//	main:
		//		조건1:	폴더가 존재한다면
		const NEFileSystem::TaskUnit& task = filesystem.getLastElement();
		if( &task && task.isFileInformationFilledIn())
			if(task.getFoundFileInformation().dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
				return;



		//	post:
		//		폴더생성:	폴더가 없을 경우
		//					밑의 ALERT은 무한루프를 돌게 만들기 때문에 삭제한다.		
		filesystem.createDirectory(settings.getLogDirectory().toCharPointer());

	}



	//	---------------------------------------------------------------------------------
	//	설명	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NETString NEDebugManager::_generateFilename() const
	{
		//	main:
		//		버퍼 생성:
		TCHAR file_buffer[_FILE_BUFFER_SIZE] = {0,};

		//		현재 날짜 구하기
		time_t rawtime; 
		time(&rawtime);
		tm timeinfo;
		localtime_s(&timeinfo, &rawtime);

		//		파일명 생성:	지정된 포맷과 구한 날짜 정보를 이용한다
		_tcsftime(file_buffer, _FILE_BUFFER_SIZE, _T( _LOG_FILE_FORMAT ) ,&timeinfo);



		//	post:
		return NETString(file_buffer);
	}



	//	---------------------------------------------------------------------------------
	//	설명	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NETString NEDebugManager::_getDate() const
	{
		TCHAR date_buffer[_DATE_BUFFER_SIZE] = {0, };
		_tstrdate_s(date_buffer);

		return NETString(date_buffer);
	}



	//	---------------------------------------------------------------------------------
	//	설명	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NETString NEDebugManager::_getTime() const
	{
		TCHAR time_buffer[_TIME_BUFFER_SIZE] = {0, };
		_tstrtime_s(time_buffer);

		return NETString(time_buffer);
	}


	void NEDebugManager::_release()
	{
		_flagset.release();
		_debug_mode_enabled = _DEFAULT_DEBUG_MODE;
		//closeConsole();
		_console_enabled = _DEFAULT_OPEN_CONSOLE;
		_log_enabled = _DEFAULT_OPEN_LOG;;
		_messagebox_enabled = _DEFAULT_OPEN_MESSAGEBOX;
		_debugwindow_enabled = _DEFAULT_OPEN_DEBUGWINDOW;
		_error_enabled = _DEFAULT_ENABLE_ERROR;
		_information_enabled = _DEFAULT_ENABLE_INFORMATION;
		_warning_enabled = _DEFAULT_ENABLE_WARNING;
		_saver.release();		
		_did_i_open_the_console = false;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NEDebugManager::_closeLogFile()
	{
		_saver.close();
	}	



	//	---------------------------------------------------------------------------------
	//	설명	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NEDebugManager::_loadFlagFromINI()
	{
		_release();
		//	main:	DebugManager의 Flag를 INI로부터 읽어온다.
		//			INI에 없을 경우, 자동으로 false로 지정된다
		//	_debug_mode_enabled:
		{
			//	데이터 로드:
			type_bool loaded_data = false;
			type_result result = _loadFlag(_T(_DEBUGMODE_EXTRACTOR), loaded_data);
			//	결과 분석:
			//		에러가 없다면:
			if(NEResult::hasError(result) == false)
				_debug_mode_enabled = loaded_data;
			//		에러가 있다면, _initializeFlag에서 세팅된 디폴트값이 들어간다.
		}
		//	enable_error:
		{
			//	데이터 로드:
			type_bool loaded_data = false;
			type_result result = _loadFlag(_T(_ERRORENABLE_EXTRACTOR), loaded_data);
			//	결과 분석:
			//		에러가 없다면:
			if(NEResult::hasError(result) == false)
				_error_enabled = loaded_data;		
			//		에러가 있다면, _initializeFlag에서 세팅된 디폴트값이 들어간다.
		}
		//	enable_warning:
		{
			//	데이터 로드:
			type_bool loaded_data = false;
			type_result result = _loadFlag(_T(_WARNINGENABLE_EXTRACTOR), loaded_data);
			//	결과 분석:
			//		에러가 없다면:
			if(NEResult::hasError(result) == false)				
				_warning_enabled = loaded_data;		
			//		에러가 있다면, _initializeFlag에서 세팅된 디폴트값이 들어간다.
		}
		//	enable_information:
		{
			//	데이터 로드:
			type_bool loaded_data = false;
			type_result result = _loadFlag(_T(_INFORMATIONENABLE_EXTRACTOR), loaded_data);
			//	결과 분석:
			//		에러가 없다면:
			if(NEResult::hasError(result) == false)
				//		데이터를 INI로부터 할당:
				_information_enabled = loaded_data;		
			//		에러가 있다면, _initializeFlag에서 세팅된 디폴트값이 들어간다.
		}
		//	open_log:
		{
			//	데이터 로드:
			type_bool loaded_data = false;
			type_result result = _loadFlag(_T(_OPENLOG_EXTRACTOR), loaded_data);
			//	결과 분석:
			//		에러가 없다면:
			if(NEResult::hasError(result) == false)
				//		데이터를 INI로부터 할당:
				_log_enabled = loaded_data;		
			//		에러가 있다면, _initializeFlag에서 세팅된 디폴트값이 들어간다.
		}
		//	open_messagebox:
		{
			//	데이터 로드:
			type_bool loaded_data = false;
			type_result result = _loadFlag(_T(_OPENMESSAGEBOX_EXTRACTOR), loaded_data);
			//	결과 분석:
			//		에러가 없다면:
			if(NEResult::hasError(result) == false)
				_messagebox_enabled = loaded_data;		
			//		에러가 있다면, _initializeFlag에서 세팅된 디폴트값이 들어간다.
		}
		//	open_debugwindow:
		{
			//	데이터 로드:
			type_bool loaded_data = false;
			type_result result = _loadFlag(_T(_OPENDEBUGWINDOW_EXTRACTOR), loaded_data);
			//	결과 분석:
			//		에러가 없다면:
			if(NEResult::hasError(result) == false)
				_debugwindow_enabled = loaded_data;		
			//		에러가 있다면, _initializeFlag에서 세팅된 디폴트값이 들어간다.
		}
		//	open_console:
		{
			//	데이터 로드:
			type_bool loaded_data = false;
			type_result result = _loadFlag(_T(_OPENCONSOLE_EXTRACTOR), loaded_data);
			//	결과 분석:
			//		에러가 없다면:
			if(NEResult::hasError(result) == false)
				_console_enabled = loaded_data;		
			//		에러가 있다면, _initializeFlag에서 세팅된 디폴트값이 들어간다.
		}		
	}



	//	---------------------------------------------------------------------------------
	//	설명	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NEDebugManager::_loadFlagSetFromINI()
	{
		//	pre:
		const Kernal::ModifiableSettings& settings = Kernal::getInstance().getSettings();
		const SuperSet& moduleset = Kernal::getInstance().getModuleManager().getModuleSet();
		_flagset.create(moduleset.getLength());



		//	main:		
		//		모듈 Flag 로드:
		for(type_index n=0; n < moduleset.getLength() ;n++)
		{
			//	타겟팅:
			//		모듈:
			const Super& target = moduleset.getElement(n);
			//	Flag 할당:
			//		버퍼 생성:
			TCHAR flag_value = 0;
			//		INI로부터 버퍼에 할당:
			type_result result = _loadModuleDebugFlag(target.getHeader(), flag_value);
			//		결과 분석:
			//			에러가 있다면:
			if(NEResult::hasError(result) == true)
			{
				Flag flag(_DEFAULT_MODULE_FLAG);
				//				디폴트 값으로 할당:
				_flagset.push(flag);
			}
			else	//	없다면:
			{
				Flag flag(flag_value);
				//				로드한 버퍼를 할당:
				_flagset.push(flag);
			}
		}
	}



	//	---------------------------------------------------------------------------------
	//	설명	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NEDebugManager::_saveFlagToINI() const
	{	
		_saveFlag(_debug_mode_enabled, _T(_DEBUGMODE_EXTRACTOR));
		_saveFlag(_error_enabled, _T(_ERRORENABLE_EXTRACTOR));
		_saveFlag(_warning_enabled, _T(_WARNINGENABLE_EXTRACTOR));
		_saveFlag(_information_enabled, _T(_INFORMATIONENABLE_EXTRACTOR));
		_saveFlag(_console_enabled, _T(_OPENCONSOLE_EXTRACTOR));
		_saveFlag(_log_enabled, _T(_OPENLOG_EXTRACTOR));
		_saveFlag(_messagebox_enabled, _T(_OPENMESSAGEBOX_EXTRACTOR));
		_saveFlag(_debugwindow_enabled, _T(_OPENDEBUGWINDOW_EXTRACTOR));
	}



	//	---------------------------------------------------------------------------------
	//	설명	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NEDebugManager::_saveFlagSetToINI() const
	{
		const Kernal::ModifiableSettings& settings = Kernal::getInstance().getSettings();
		const SuperSet& moduleset = Kernal::getInstance().getModuleManager().getModuleSet();

		for(type_index n=0; n < moduleset.getLength() ;n++) // 0번 인덱스는 더미 모듈이다.
		{			
			const Super& target = moduleset.getElement(n);

			_saveModuleDebugFlag(target);
		}
	}



	//	---------------------------------------------------------------------------------
	//	설명	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	type_result NEDebugManager::_loadModuleDebugFlag(const NEIdentifier& identifier, NE_OUT TCHAR& loaded_data)
	{
		//	pre:
		NEINIManager& ini = Kernal::getInstance().getINIManager();



		//	main:
		//		버퍼생성:
		NETString buffer;
		//		INI로부터 Fetch:
		type_result result = ini.readModuleIniString(identifier, _T(_MODULE_FLAG_EXTRACTOR), buffer);
		//		가져온 데이터를 TCHAR로 변환:
		if(NEResult::hasError(result))
			loaded_data = _DEFAULT_MODULE_FLAG;
		else
			loaded_data = static_cast<TCHAR>(buffer.toInt());



		//	post:
		return result;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NEDebugManager::_saveModuleDebugFlag(const Super& module) const
	{
		NEINIManager& ini = Kernal::getInstance().getINIManager();

		const Flag& flag = _flagset.getElement(module.getScriptCode());
		if ( ! &flag)
		{
			KERNAL_ERROR(" Flag가 존재하지 않습니다.");
			return;
		}
		//	왜 flag를 int형으로 형변환 하는가?:
		//		flag를 그대로 NETString으로 형변환 할 수 있지만, 
		//		그리하면 INI에서 유저가 수정불가능한 문자가 되어 나온다.
		//		int형으로 형변환 하면 숫자의 형태로 나오므로 수정이 가능해진다.
		int data = static_cast<int>(flag.getFlag());

		ini.writeModuleIniString(module.getHeader(), _T(_MODULE_FLAG_EXTRACTOR), data); // int data ---> NEString
	}



	//	---------------------------------------------------------------------------------
	//	설명	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	type_result NEDebugManager::_loadFlag(LPCTSTR search_string, NE_OUT type_bool& loaded_data)
	{
		NEINIManager& ini = Kernal::getInstance().getINIManager();
		NETString loaded;



		//	main:
		//		데이터 가져옴:
		//			INI로부터 문자열 획득:
		type_result result = ini.readModuleIniString(getHeader(), search_string, loaded);
		//			획득한 문자열을 type_bool로 변환:
		if(	loaded == _T("true")	||
			loaded == _T("TRUE")	)
			loaded_data = true;
		else
			loaded_data = false;



		//	post:
		return result;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NEDebugManager::_saveFlag(type_bool flag, LPCTSTR search_string) const
	{
		NEINIManager& ini = Kernal::getInstance().getINIManager();

		if(flag)
			ini.writeModuleIniString(getHeader(), search_string, _T("true"));
		else
			ini.writeModuleIniString(getHeader(), search_string, _T("false"));
	}

	const NEDebugManager& NEDebugManager::_assign( const This& source )
	{
		if(this == &source) return *this;

		_debug_mode_enabled = source._debug_mode_enabled;
		_console_enabled = source._console_enabled;
		_log_enabled = source._log_enabled;
		_messagebox_enabled = source._messagebox_enabled;
		_debugwindow_enabled = source._debugwindow_enabled;
		_error_enabled = source._error_enabled;
		_warning_enabled = source._warning_enabled;
		_information_enabled = source._information_enabled;
		_flagset = source._flagset;

		return *this;
	}

#else

	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEDebugManager::NEDebugManager()
		: NEDebugManager()
	{
		// 생성자에는 아무것도 실행하면 안된다. 싱글톤에 속해있기 때문이다.
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEDebugManager::NEDebugManager(const NEDebugManager& source)
		: NEDebugManager()
	{

	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEDebugManager::~NEDebugManager()
	{

	}



	//	---------------------------------------------------------------------------------
	//	설명	:	INI로부터 NEDebugManager의 INI정보와 모듈의 Flag를 가져온다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	type_result NE_DLL NEDebugManager::execute()
	{
		return RESULT_SUCCESS;
	}




	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEBinaryFileSaver NE_DLL &NEDebugManager::serialize(NEBinaryFileSaver& saver) const
	{
		NEDebugManager::serialize(saver);

		return saver;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEBinaryFileLoader NE_DLL &NEDebugManager::serialize(NEBinaryFileLoader& loader)
	{
		NEDebugManager::serialize(loader);

		return loader;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	type_result NE_DLL NEDebugManager::isValid() const
	{		
		type_result result = NEDebugManager::isValid();
		if(NEResult::hasError(result) == true) return result;

		return RESULT_SUCCESS;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	void NE_DLL NEDebugManager::initialize()
	{
		//	멤버함수 초기화
		NEDebugManager::initialize();	
	}		



	//	---------------------------------------------------------------------------------
	//	설명	:	모듈의 헤더를 내보낸다. 헤더는 클래스에 이미 정의되어서 컴파일된다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	const NEExportable::Header NE_DLL &NEDebugManager::getHeader() const
	{
		static NEExportable::Header _header;

		if(_header.isValid() != RESULT_NOTHING)
		{
			//	아직 초기화가 안되었음
			_header.identifier.getName() = _T(_NAME);
			_header.identifier.getDeveloper() = _T(_DEVELOPER);
			_header.identifier.getRevision() = _REVISION;
			_header.date = _T(_DATE);
			_header.getVersion()  = _T(_VERSION);
			_header.getComment() = _T(_COMMENT);
		}

		return _header;
	}	

#endif
}
