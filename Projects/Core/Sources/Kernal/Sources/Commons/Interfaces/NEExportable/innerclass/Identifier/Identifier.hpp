//	---------------------------------------------------------------------------------
//	클래스명:	NEExportable::Identifier
//	설명	:	모듈의 식별자를 나타낸다.
//	관계	:	기반클래스.			NEObject
//				소유되는 클래스.	NEModule
//	특성	:	중첩클래스.
//	알고리즘:	
//	사용방법:	
//	메모	:	Revision과 Version의 차이?
//					:	Revision은 개정된 횟수를 말하며 Version은 해당 Revision의 수치를
//						의미한다.
//						예를들어 Revision 1의 버전이 1.00 일때, Revision 2의 버전은 
//						1.5가 될 수도, 2.0이 될 수도 있다. 버전 표기는 제작자가 자유롭
//						게 해도 상관없으나, Revision은 개정할때마다 + 1씩 올려주는 것이
//						표준이다.
//	히스토리:	2011-07-07	이태훈	개발 완료	
//	---------------------------------------------------------------------------------
class NE_DLL Identifier : public NEObject
{
	NE_DECLARE_CLASS(Identifier, NEObject)

	//	생성자:
public:
	Identifier();
	Identifier(const NETString& identifier_string_with_dot_delimiter);
	Identifier(const NETString& value_name, const NETString& value_developer, int value_revision);
	Identifier(const Identifier& source);

	//	소멸자:
public:
	virtual ~Identifier();

	//	연산자 중첩:
public:
	const Identifier& operator=(const Identifier& source);
	bool operator==(const Identifier& source) const;
	bool operator!=(const Identifier& source) const;
	
public:
	type_result setIdentifier(const NETString& identifier_string_with_dot_delimiter);
	NETString& getName();
	const NETString& getName() const;
	NETString& getDeveloper();
	const NETString& getDeveloper() const;
	int getRevision() const;
	void setRevision(type_count new_revision);

	//	인터페이스:
	//		상속:
	//			NEObject:
public:
	virtual void release();
	virtual type_result isValid() const;
	virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
	virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
	bool isSameModule(const Identifier& source) const;

	//	내부함수:
private:
	const Identifier& _assign(const Identifier& source);

	//	멤버변수:
protected:
	NETString _name; // 모듈명
	int _revision; // 개정횟수
	NETString _developer; // 제작자	
};
