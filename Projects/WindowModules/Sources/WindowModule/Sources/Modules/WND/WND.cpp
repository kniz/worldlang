#include "WND.hpp"
#include "define/define.hpp"

namespace NE
{
	MSG WND::_message_from_wnd_proc;

	NE_DLL WND::WND()
		: NEModule(), _hwnd(NE_NULL), _parent_hwnd(NE_NULL)
	{
		
	}

	NE_DLL WND::WND(const WND& source)
		: NEModule(source), _hwnd(NE_NULL), _parent_hwnd(NE_NULL)
	{
		_assign(source);
	}

	NE_DLL WND::~WND()
	{
		_release();
	}

	/*
		initialize는 처음 인스턴스가 생성될때 호출된다.
		( * 즉, 모듈 매니져에서 처음으로 발생)

		그 이후로는 복사생성자 -> serialize(loader)만 호출되므로,
		intiailize에 기본값을 할당해놓으면 스크립트파일에서 값을 명시하지 않은 경우에
		자동으로 기본값이 놓여지게 될것이다.
	*/
	type_result NE_DLL WND::initialize()
	{
		/*
			initialize의 구현과 _release의 구현이 일치하므로 여기서는
			특별하게 _release를 호출한다.
		*/
		SuperClass::initialize();

		_release();
	
		return RESULT_SUCCESS;
	}

	/*
		윈도우 모듈은 복잡한 "저장/로드" 구조를 지녀야 한다.

		1. 이는 "로드를 했다고 하더라도" 윈도우가 이미 생성되버린다면, "스타일" 을 적용할수
		없으며.

		2. 윈도우가 생성되지 않은 상태에서 로드를 해버리고 바로 시스템을 재개한다면, "윈도
		우가 생성되지 않은 채로" 구동되기 때문이다.

		즉, 다음과 같은 처리를 해줘야한다.
			1. 윈도우가 생성되었는가?
				예		->	스타일은 이외의 데이터를 읽은 후, 변경을 가해준다.
				아니오	->	기존의 방식처럼 데이터를 읽어서 적용해준다.
	*/
	NEBinaryFileSaver NE_DLL &WND::serialize(NEBinaryFileSaver& saver) const
	{
		//	pre:
		NEModule::serialize(saver);

		

		//	main:
		if(_hwnd)
		{
			saver << (bool) true;
			WINDOWPLACEMENT placement;
			placement.length = sizeof(WINDOWPLACEMENT);
			GetWindowPlacement(_hwnd, &placement);
			RECT& rect = placement.rcNormalPosition;
			saver	<< rect.left << rect.top << rect.right - rect.left << rect.bottom - rect.top
					<< placement.showCmd;
		}
		else
			saver << (bool) false;
		


		//	post:
		return saver;
	}

	NEBinaryFileLoader NE_DLL &WND::serialize(NEBinaryFileLoader& loader)
	{
		NEModule::serialize(loader);

		//	main:
		bool had_file_window_states_when_serialized = false;		
		loader >> had_file_window_states_when_serialized;
		if(had_file_window_states_when_serialized)
		{
			loader 	>> _saved_x >> _saved_y >> _saved_width >> _saved_height
					>> _saved_command_show;
		}

		return loader;
	}
	
	HWND NE_DLL WND::getHWND() const
	{
		return _hwnd;
	}

	HWND NE_DLL WND::getParentHWND() const
	{
		return _parent_hwnd;
	}

	type_result NE_DLL WND::destroy()
	{
		type_result result = RESULT_SUCCESS;

		if(_hwnd)
		{
			if( ! DestroyWindow(_hwnd))	//	ERROR = false
				result = RESULT_TYPE_ERROR;

			_hwnd = NE_NULL;
			_parent_hwnd = NE_NULL;
		}

		return result;
	}

	void WND::_release()
	{
		destroy();
		/*
			왜 값을 -1로 할당하는가?
				밑의 값은 serialize에서 값이 존재했을때만 사용되는 변수이기 때문이다.
		*/
		_saved_x = NE_ERROR_MINUS1;
		_saved_y = NE_ERROR_MINUS1;
		_saved_width = NE_ERROR_MINUS1;
		_saved_height = NE_ERROR_MINUS1;
		_saved_command_show = NE_ERROR_MINUS1;
	}

	/*
		윈도우 생성이 아직 되지 않았다는 가정하에, 각 요소들을 assign 한다.
	*/
	const WND& WND::_assign(const WND& source)
	{
		if(this == &source) return *this;
		if(_hwnd)
			ALERT_WARNING(" : 이미 윈도우가 생성되어 있음. hWnd를 shallow copy 함")



		//	main:
		_hwnd = source._hwnd;
		_parent_hwnd = source._parent_hwnd;
		_saved_x = source._saved_x;
		_saved_y = source._saved_y;
		_saved_width = source._saved_width;
		_saved_height = source._saved_height;
		_saved_command_show = source._saved_command_show;

		return *this;
	}

	bool WND::_hasSavedStatesAssigned()
	{
		return (	_saved_x != NE_ERROR_MINUS1				&&
					_saved_y != NE_ERROR_MINUS1				&&
					_saved_width != NE_ERROR_MINUS1			&&
					_saved_height != NE_ERROR_MINUS1		&&
					_saved_command_show != NE_ERROR_MINUS1	);					
	}

	type_result WND::changeDomain(HWND insert_after, int x, int y, int width, int height, UINT flag)
	{
		if( ! _hwnd)
		{
			ALERT_ERROR(" : 윈도우 핸들이 없다.")

			return RESULT_TYPE_ERROR;
		}



		//	main:
		if( ! SetWindowPos(_hwnd, insert_after, x, y, width, height, flag))	//	error = 0
			return RESULT_TYPE_ERROR;



		//	post:
		return RESULT_SUCCESS;
	}

	type_result WND::changeShowCommand(int style)
	{
		if( ! _hwnd)
		{
			ALERT_ERROR(" : 윈도우 핸들이 없다.")

			return RESULT_TYPE_ERROR;
		}



		//	main:
		ShowWindow(_hwnd, style);

		if( ! UpdateWindow(_hwnd))	//	error = 0
			return RESULT_TYPE_ERROR;



		//	post:
		return RESULT_SUCCESS;
	}

	type_result NE_DLL WND::changeText(const NETString& new_text)
	{
		if( ! _hwnd) 
		{
			ALERT_ERROR(" : 윈도우 핸들이 없다.")

			return RESULT_TYPE_ERROR;
		}

		if(SetWindowText(_hwnd, new_text.toCharPointer()) == NE_ERROR_0)
			return RESULT_TYPE_ERROR;

		return RESULT_SUCCESS;
	}

	LRESULT CALLBACK WND::_wndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
	{
		_message_from_wnd_proc.hwnd = hWnd;
		_message_from_wnd_proc.message = iMessage;
		_message_from_wnd_proc.wParam = wParam;
		_message_from_wnd_proc.lParam = lParam;		
		
		return DefWindowProc(hWnd, iMessage, wParam, lParam);
	}

	type_result WND::_onFetchArguments(NEArgumentInterfaceList& tray) const
	{
		arg_x.getDefault() = 0;
		arg_y.getDefault() = 0;
		arg_width.getDefault() = 640;
		arg_height.getDefault() = 480;
		arg_how_to_show_window.getDefault() = 5;
		
		tray.push(&arg_x);
		tray.push(&arg_y);
		tray.push(&arg_width);
		tray.push(&arg_height);
		return tray.push(&arg_how_to_show_window);		
	}

}