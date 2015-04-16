#include "Headers.hpp"

Kernal* kernal = 0;
Editor* editor = 0;

NEString fetch_com_line()
{
	char buffer[_MAX_BUFFER];

	cin.getline(buffer, _MAX_BUFFER);

	return buffer;
}
Kernal::Factory factory;
Editor::Factory editor_factory;
class CreateFactory : public TestCase
{
public:
	CreateFactory() : TestCase("configure settings of kernel factory instance") {}
	virtual bool onTest()
	{

		Kernal::ModifiableSettings& settings = factory.getDefaultSettings();
		settings.getINIFullPath() = "./NodeCUI.ini";
		settings.setModuleDirectory("Modules");
		settings.setLogDirectory("Logs");
		settings.setScriptDirectory("Scripts");
		settings.setNodeDirectory("Nodes");

		return true;
	}
};
class ManagerIdentifierSetting : public TestCase
{
public:
	ManagerIdentifierSetting() : TestCase("push manager's identifier to settings") {}
	virtual bool onTest()
	{
		factory.getNodeManagerIdentifier() = NEExportable::Identifier("NEStandardNodeManager", "haku", 1);
		factory.getScriptManagerIdentifier() = NEExportable::Identifier("NEStandardScriptManager", "haku", 1);

		NEString inputed;
		// 	do {
		// 		cout	<< "\t\t- INI-file : " << settings.getINIFullPath() << endl
		// 				<< "\t\t- Modules  : " << settings.getModuleDirectory() << endl
		// 				<< "\t\t- Logs     : " << settings.getLogDirectory() << endl
		// 				<< "\t\t- Scripts  : " << settings.getScriptDirectory() << endl
		// 				<< "\t\t- NodeData : " << settings.getNodeDirectory() << endl;
		// 
		// 		cout << "\t\t> are these correct?(y/n) > ";
		// 		inputed = fetch_com_line();
		// 		if(inputed == "N" || inputed == "n")
		// 		{
		// 			system("cls");
		// 			cout << "- 새로운 INI 파일명과 경로(skip 입력시 통과): \n\t";
		// 			NEString& new_inipath = fetch_com_line();
		// 			if(new_inipath != "skip")
		// 				settings.getINIFullPath() = new_inipath;
		// 
		// 			cout << "- 새로운 모듈 디렉토리(skip 입력시 통과) : \n\t";
		// 			NEString& new_module = fetch_com_line();
		// 			if(new_module != "skip")
		// 				settings.setModuleDirectory(new_module);
		// 
		// 			cout << "- 새로운 로그 디렉토리(skip 입력시 통과) : \n\t";
		// 			NEString& new_log = fetch_com_line();
		// 			if(new_log != "skip")
		// 				settings.setLogDirectory(new_log);
		// 
		// 			cout << "- 새로운 스크립트 디렉토리(skip 입력시 통과) : \n\t";
		// 			NEString& new_script = fetch_com_line();
		// 			if(new_script != "skip")
		// 				settings.setScriptDirectory(new_script);
		// 
		// 			cout << "- 새로운 노드 디렉토리(skip 입력시 통과) : \n\t";
		// 			NEString& new_node = fetch_com_line();
		// 			if(new_node != "skip")
		// 				settings.setNodeDirectory(new_node);
		// 		}		
		// 	} while(inputed == "n" || inputed == "N")

		return true;
	}

};


class CreateKernel : public TestCase
{
public:
	CreateKernel() : TestCase("instantiate kernel object from factory") {}
	virtual bool onTest()
	{
		kernal = new Kernal(factory.create());

		return kernal != 0x00;
	}
};
class RegisterKernel : public TestCase
{
public:
	RegisterKernel() : TestCase("registering kernel...") {}
	virtual bool onTest()
	{
		return ! NEResult::hasError(Kernal::setInstance(*kernal));
	}
};
class InitializeKernel : public TestCase
{
public:
	InitializeKernel() : TestCase("initializing with settings above.") {}
	virtual bool onTest()
	{
		return ! NEResult::hasError(Kernal::getInstance().initialize());
	}
};
class CreateEditorFactory : public TestCase
{
public:
	CreateEditorFactory() : TestCase("configure settings of editor factory") {}
	virtual bool onTest()
	{
		editor_factory.getDefaultSettings().setPanelDirectory(".\\Panels");
		editor_factory.getDefaultSettings().setLoadFromINI(true);
		return true;
	}
};
class EditorManagerIdentifierSetting : public TestCase
{
public:
	EditorManagerIdentifierSetting() : TestCase("push manager's identifier to editor settings") {}
	virtual bool onTest()
	{
		editor_factory.getPanelManagerIdentifier() = NEExportable::Identifier("NEStandardPanelManager", "haku", 1);
		editor_factory.getScriptEditorIdentifier() = NEExportable::Identifier("NEStandardScriptEditor", "haku", 1);
		editor_factory.getEventHandlerIdentifier() = NEExportable::Identifier("CooeeHandler", "kniz", 1);
		return true;
	}
};
class CreateEditor : public TestCase
{
public:
	CreateEditor() : TestCase("instantiate editor object from factory") {}
	virtual bool onTest()
	{
		editor = new Editor(editor_factory.create());
		return true;
	}
};
class RegisterEditor: public TestCase
{
public:
	RegisterEditor() : TestCase("registering editor...") {}
	virtual bool onTest()
	{
		return ! NEResult::hasError(Editor::setInstance(*editor));
	}
};
class InitializeEditor : public TestCase
{
public:
	InitializeEditor() : TestCase("initializing editor with settings above.") {}
	virtual bool onTest()
	{
		return ! NEResult::hasError(Editor::getInstance().initialize());
	}
};
class CreateScript : public TestCase
{
public:
	CreateScript() : TestCase("make a empty script for starting") {}
	virtual bool onTest()
	{
		if( &Editor::getInstance()	&&
			&Editor::getInstance().getScriptEditor()) 
		{
			NEScriptHeader& header = Editor::getInstance().getScriptEditor().getScriptHeader();
			header.getName() = "unnamed";
			header.getDeveloper() = "anonymous";
			header.setRevision(1);
			return true;
		}

		return false;
	}
};
class CheckManager : public TestCase
{
public:
	CheckManager() : TestCase("check if managers are attached to obj well or not") {}
	virtual bool onTest()
	{
		Kernal* kernel = &Kernal::getInstance();
		if( ! kernel) return false;
		NENodeManager* noder = &kernal->getNodeManager();
		NEScriptManager* scr = &kernal->getScriptManager();
		if( ! noder) return false;
		if( ! scr) return false;
		Editor* edit = &Editor::getInstance();
		if( ! edit) return false;
		NEScriptEditor* sced = &edit->getScriptEditor();
		NEPanelManager* pan = &edit->getPanelManager();
		NEEventHandler* hand = &edit->getEventHandler();	
		if( ! sced)	return false;
		if( ! pan)	return false;
		if( ! hand)	return false;

		return true;
	}
};

void init_kern()
{
	cout	<< _VERSION_STRING
		<< "\tby " << _DEVELOPER << "\n"
		<< "\ton " << _DATE << "\n\n";	

	CreateFactory().test();
	ManagerIdentifierSetting().test();
	CreateKernel().test();
	RegisterKernel().test();
	InitializeKernel().test();
	CreateEditorFactory().test();
	EditorManagerIdentifierSetting().test();
	CreateEditor().test();
	RegisterEditor().test();
	InitializeEditor().test();
	CreateScript().test();
	CheckManager().test();	
}

void init_wins() {
	system("cls");
	using namespace LG;

	LG::Core::getWindowList().pushFront(NodeSetTerminal());
	LG::Core::getWindowList().pushFront(MessageWindow(NEString(_VERSION_STRING) + "\n\tby " + _DEVELOPER + "\n\ton " + _DATE, WHITE, LIGHTRED));
}

void end_kern()
{
	delete &Editor::getInstance();
	delete &Kernal::getInstance();
}

void _catchGlobalKey()
{
	switch(LG::Core::inputed)
	{
	case MAP:
		if(dynamic_cast<Planetarium*>(&LG::Core::getWindowList()[0]) == 0)
			LG::Core::open(Planetarium());
		break;

	case COMMAND:
		LG::Core::open(CommandInputWindow());
		break;

	case LG::F5:	//	F5:		디버깅 새로 시작
		::Core::commander.command("run -new");
		break;

	case LG::F8:	//	F8:		디버깅 계속
		::Core::commander.command("run");
		break;

	case LG::F11:	//	F11:	한번만 실행
		::Core::commander.command("run 1");
		break;

	case LG::TAB:
		::Core::commander.command("observe");
		break;
	}

	LG::Core::inputed = 0;
}

BOOL controlHandler(DWORD type)
{
	switch (type)
	{
	case CTRL_C_EVENT:
	case CTRL_CLOSE_EVENT:
		LG::Core::inputed = COPY;
		return TRUE;
	}

	return FALSE;	//	do bubble handler

}

int main()
{
	SetConsoleCtrlHandler((PHANDLER_ROUTINE)controlHandler, TRUE);

	Running running;

#ifdef _UNICODE
	std::wcin.imbue( std::locale("korean") );
	std::wcout.imbue( std::locale("korean") );
#endif

	NE_MEMORYLEAK

		init_kern();
	system("pause");

	NENodeCodeSet& ns = Editor::getInstance().getScriptEditor().getScriptNodes();
	NEModuleCodeSet& ms = ns[0].getModuleSet();
	const NEModuleSet& mms = Kernal::getInstance().getModuleManager().getModuleSet();

	LG::Core::setWindowList(::Core::script_windows);

	init_wins();

	::Core::initializeWindows(::Core::debug_windows);

	LG::Window& window = LG::Core::getWindowList()[0];
	window.onUpdateData();
	LG::Core::getWindowList().draw();
	LG::Core::back_buffer.draw();
	NEEventHandler& handler = Editor::getInstance().getEventHandler();

	while(::Core::script_windows.getLength() > 0) 
	{
		LG::Core::back_buffer.readyBufferToDraw();
		type_result is_key_pressed = false;

		if(::Core::test_running_count)
		{
			LG::Core::sendKeyPipe();

			if(LG::Core::inputed == CLOSE)
			{
				LG::Core::inputed = 0;				
				::Core::test_running_count = 0;
			}			
			else
			{
				if(::Core::test_running_count > 0)
					::Core::test_running_count--;

				Kernal::getInstance().getNodeManager().execute();
			}
		}
		else
		{
			if(LG::Core::sendKeyPipe())
			{			
				LG::WindowList& wins = LG::Core::getWindowList();
				if(&wins[0])
					wins[0].onKeyPressed(LG::Core::inputed);
				_catchGlobalKey();
			}

			LG::Core::collectGarbages(LG::Core::getWindowList());

			if(LG::Core::getWindowList().getLength() > 0)
			{			
				LG::Core::getWindowList()[0].onUpdateData();
				LG::Core::getWindowList().draw();
				if(::Core::test_running_count)
					running.onDraw();
				LG::Core::back_buffer.draw();
			}
		}
	}

	end_kern();

	return 0;
}