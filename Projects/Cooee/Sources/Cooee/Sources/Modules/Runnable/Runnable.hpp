#include "../Commander/Commander.hpp"

class Runnable
{
private:
	Runnable();
	~Runnable();
	
public:
	NETString& getCurrentWorkPosition();
	const NETString getCurrentWorkPosition() const;
	bool isStillRunning() const;
	void setRunning(bool runnable);
	void execute();
	void printError(LPCTSTR contents) const;
	void printError(const NETString& contents) const;
	void printModuleHeader(const NEExportable::ModuleHeader& header) const;
	void printNEScriptHeader(const NEScriptEditor& editor) const;
	void printNEScriptHeader(const NEScriptHeader& header) const;
	Commander& getCommander();
	const Commander& getCommander() const;
	NEObject& getObjectFrom(const NETString& work_position) const;
	void printNodeSetKey(const NENodeCodeSetKey& key) const;
	void printModuleSetKey(const NEModuleCodeSetKey& key) const;
	void printNodeCollector(const NENodeCollector& collector) const;
	void printListFrom(const NEObject& object) const;
	void printNode(const NENode& node) const;
	void printModule(const NEModule& module) const;
	void printKey(const NEKey& key) const;
	void printCodeType(NECodeType::CodeType type) const;
	void printNodeSelector(const NENodeSelector& selector) const;
	void printModuleSelector(const NEModuleSelector& selector) const;
	void printKeySelector(const NEKeySelector& selector) const;
	void printObject(const NETString& path) const;
	void printComponentSet(const NEComponentSet& componentset) const;
	void modifyCode(NECodeType::CodeType type, type_code max_code, type_result(NEScriptEditor::*insert_method)(type_code), type_result(NEScriptEditor::*remove_method)(type_code), NETStringList& bank);
	void modifyNode(NENode& node) const;
	void modifyModule(NEModule& module) const;
	void modifyComponent(NEPanel& panel, type_index index) const;
	void flushStdIo() const;
	void print(NEEnlistableManager& manager);
	void _analyzeCommandAndBranch(const NETString& commandline);	
	
protected:	
	type_index _fetchIndex(const NETString& message, type_index max_index, type_index min_index = 0) const;
	void _printPrompt() const;
	NETString _fetchCommandLine() const;
	void _analyzeBranchResult(const NETString& command, type_result result) const;
	void _initialize();
	void _printHeader(const NEExportable::Header& header) const;
	type_index _getPositionTypeAndIndex(const NETString& position, NE_OUT int& type) const;
	NEObject& _searchNodeSet(NENodeCodeSet& nodeset, NETStringSet& work_position) const;
	NEObject& _searchModuleSet(NEModuleCodeSet& moduleset, NETStringSet& work_position) const;
	NEObject& _searchKeySet(NEKeyCodeSet& keyset, NETStringSet& work_position) const;

public:
	static Runnable& get()
	{
		if( ! _runnable)
			_runnable = new Runnable();

		return *_runnable;
	}
	static void terminate()
	{
		delete _runnable;
	}

protected:
	Kernal* _kernal;
	Editor* _editor;
	NETString _current_work_position;
	bool _is_still_running;
	Commander _commander;
	
	static Runnable* _runnable;
};	
