#ifdef DEVELOPER
#	ifdef _DEBUG
#		define _DLL_ENTRYPOINT_STRING	"?registerPanelDevDbg@NE@@YG?AV?$NETList@PAVNEPanel@NE@@$00$0HIFKIMA@@1@XZ"
#	else
#		define _DLL_ENTRYPOINT_STRING	"?registerPanelDev@NE@@YG?AV?$NETList@PAVNEPanel@NE@@$00$0HIFKIMA@@1@XZ"
#	endif
#else
#	define _DLL_ENTRYPOINT_STRING		"?registerPanel@NE@@YG?AV?$NETList@PAVNEPanel@NE@@$00$0HIFKIMA@@1@XZ"
#endif
