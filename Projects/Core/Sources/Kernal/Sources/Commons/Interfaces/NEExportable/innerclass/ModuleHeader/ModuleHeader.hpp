//	---------------------------------------------------------------------------------
//	클래스명:	NEExportable::ModuleHeader
//	설명	:	모듈의 헤더를 나타낸다.
//	관계	:	기반클래스.			Identifier
//				소유되는 클래스.	NEModule
//	특성	:	중첩클래스.
//	알고리즘:	
//	사용방법:	
//	메모	:	
//	히스토리:	2011-07-07	이태훈	개발 완료	
//				2011-07-09	이태훈	추가		버전 호환성 추가
//												version_compatibilities에 들어가 있는 
//												버전들은 하위 버전으로써, 이 모듈로도
//												실행이 가능하다는 뜻이다.
//				2014-11-19	이태훈	추가		ArgumentComments를 추가했다.
//	---------------------------------------------------------------------------------
//
//	ArgumentsComments는 왜 ModuleHeader에 있는가:
//		Argument에 대한 내용이므로 ArgumentTemplate에 있는게 더 적합하지 않나?
//			이유1.	ArgumentTemplate에 두어야 하는 이유는 개념의 위치상 그렇다는 점이다.
//					그러나 이 경우 ModuleHeader도 정보를 기록하는 곳이므로 여기에 둔다고 
//					해도 크게 무리는 없다.
//			이유2.	Argument의 내용은 모든 Argument가 공유해야하는 단 하나의 정보가 되어야
//					한다. 어짜피 같은 내용이므로 전역변수를 쓰든, static을 쓰든 메모리사용
//					을 낭비해서는 안된다.
//					ModuleHeader는 그 구조를 이미 갖추고 있었으므로 여기에 두면 여러모로
//					추가 코딩을 할 필요가 사라진다.
//			이유3.	ArgumentTemplate에 두면, Argument가 내부 바인딩을 통해서 인스턴스가
//					생성되어야 정보를 가져올 수 있게 된다.
//					즉, 외부에서 initialize가 호출되어야 한다는 얘긴데, 이 없이도 정보를
//					가져올 수 있어야 한다. ModuleManager에 있는 모듈들은 initialize가
//					되지 않기 때문이다.
class NE_DLL ModuleHeader : public Header
{
	NE_DECLARE_CLASS(ModuleHeader, Header)

	//	생성자:
public:
	ModuleHeader();
	ModuleHeader(const ModuleHeader& source);

	//	소멸자:
public:
	virtual ~ModuleHeader();

	//	연산자 중첩:
public:
	const ModuleHeader& operator=(const ModuleHeader& source);
	bool operator==(const ModuleHeader& source) const;
	bool operator!=(const ModuleHeader& source) const;
	
public:
	NETStringSet& getModuleDependencies();
	const NETStringSet& getModuleDependencies() const;
	NEIntSet& getRevisionCompatibilities();
	const NEIntSet& getRevisionCompatibilities() const;
	type_count getMaxErrorCodeCount() const;
	void setMaxErrorCodeCount(type_count error_code);
	NETStringSet& getArgumentsComments();
	const NETStringSet& getArgumentsComments() const;

	//	인터페이스:
	//		상속:
	//			NEObject:
public:
	virtual void release();
	virtual type_result isValid() const;
	virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
	virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);

	//	내부함수:
private:	
	const ModuleHeader& _assign(const ModuleHeader& source);

	//	멤버변수:
protected:
	NETStringSet _module_dependencies; // 이 모듈이 의존하는 모듈
	NEIntSet _revision_compatibilities; // 호환 가능한 버전. 여기에 표시된 하위 버전은, 이 모듈로도 사용이 가능하다는 뜻.
	int _max_errorcode_count;
	NETStringSet _arguments_comments;
};
