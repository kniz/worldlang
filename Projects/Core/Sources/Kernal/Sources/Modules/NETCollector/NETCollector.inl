//	---------------------------------------------------------------------------------
//	클래스명:	NETCollector
//	설명	:	데이터를 관리하는 자료구조를 나타낸다.
//	관계	:	기반클래스.	NEObject
//	특성	:	데이터를 관리하는 핵심적인 함수가 가상함수로 되어있기 때문에 쉽게 
//				다형성이 가능하다.
//	알고리즘:	
//	사용방법:	기본 인터페이스
//					1.	getSize()	:	데이터의 최종 크기
//					2.	getLength()	:	데이터의 현재 길이
//					3.	push()		:	데이터를 제일 뒤에 추가
//					4.	pushFront()	:	데이터를 가장 앞에 추가
//					5.	pop()		:	가장 뒤의 데이터를 하나 삭제
//					6.	popFront()	:	맨 앞의 데이터를 하나 삭제
//
//				가상 함수
//					1.	insert()	:	데이터를 임의의 인덱스에 위치에 삽입
//					2.	remove()	:	임의의 인덱스에 위치하는 데이터를 삭제
//					3.	match()		:	주어진 원소와 일치하는 원소를 Collector에서
//										검색. (내부적으로 operator==를 실시한다)
//					4.	getElement():	주어진 인덱스에 해당하는 원소에 접근한다.
//					5.	setElement():	주어진 인덱스와 엘리먼트로 데이터를 대체한다.
//										추가가 아니다.
//	메모	:	
//	히스토리:	2011-07-07	이태훈	개발 완료	
//	---------------------------------------------------------------------------------
#pragma once

//	include:
#include "../NEObject/NEObject.hpp"
#include "../NETClass/NETClass.inl"

namespace NE
{

	template<typename OutsideType>
	class NETCollector : public NELengthedObject 
	{
		NE_DECLARE_INTERFACE_ONLY(NETCollector<OutsideType>, NELengthedObject)

		//	생성자:
	public:
		NETCollector();
		NETCollector(const NETCollector& source);

		//	소멸자:
	public:
		virtual ~NETCollector();	

		//	연산자 중첩:
	public:
		const NETCollector<OutsideType>& operator=(const NETCollector<OutsideType>& source); 
		type_bool operator==(const NETCollector<OutsideType>& source) const;
		type_bool operator!=(const NETCollector<OutsideType>& source) const;

		//	접근자:	변수가 존재한다면 복사생성자를 구현한다. 구현한 복사생성자는 파생클래스에서 호출됨
	public:
		type_index getLength() const;

		//	인터페이스:
		//		상속:
	public:
		virtual NETConstIterator<OutsideType> getIterator(type_index index) const = 0; 
		virtual NETIterator<OutsideType> getIterator(type_index index) = 0;
		virtual type_index push(const OutsideType& source) = 0;
		virtual type_index pop() = 0;

		//			NEObject:
	public:
		virtual void release(); 
		virtual type_result isValid() const; 
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);

		//		고유 인터페이스:
	public:
		template <typename Functor>
		OutsideType& match(Functor functor = NETInstanceMatcher<OutsideType>(), NE_OUT type_index& matched_index = type_index()) const;
		template <typename Functor>
		const OutsideType& match(Functor functor = NETInstanceMatcher<OutsideType>(), NE_OUT type_index& matched_index = type_index()) const;
		type_result push(const NETIterator<OutsideType>& from, const NETIterator<OutsideType>& end);
		type_result push(const NETCollector<OutsideType>& source);
		NETConstIterator<OutsideType> getIterator() const;
		NETIterator<OutsideType> getIterator();

		//	내부함수:
	private: 
		const NETCollector<OutsideType>& _assign(const NETCollector<OutsideType>& source);
		void _release();

		//	멤버변수:
	protected:
		type_index _length;
	}; 
}

#include "NETPointerCollector.inl"