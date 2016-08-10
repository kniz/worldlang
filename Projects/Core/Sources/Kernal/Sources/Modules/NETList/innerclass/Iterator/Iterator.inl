//	---------------------------------------------------------------------------------
//	클래스명:	NETList::Iterator
//	설명	:	NETList에 사용되는 Iterator을 나타내는 클래스.
//	관계	:	중첩클래스.	NETList
//	특성	:	NETList에 friend 선언
//				Iterator은 외부에도 공개된다.
//	알고리즘:	메모리 할당, 해제는 NETList에서 일어나고 Iterator은 데이터를 가지고 있는
//				역할만 수행한다.
//	사용방법:	getNext(),	data
//	메모	:	
//	히스토리:	2011-07-07	이태훈	개발 완료	
//	---------------------------------------------------------------------------------
class Iterator
{
	NE_DECLARE_CLASS(Iterator, NEAdam)

	//	프렌드 선언:
	friend class NETList;

	//	생성자:
public:
	Iterator(const T& source, Iterator* next);

public:
	~Iterator();

	//	접근자:
public:
	T& getValue();
	const T& getValue() const;
	void setValue(const T& source);
	const Iterator* getNext() const;
	Iterator* getNext();

	//	멤버변수:	
protected:	
	T _value;
	Iterator* _next;
};