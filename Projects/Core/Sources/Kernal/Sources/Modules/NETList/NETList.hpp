//	---------------------------------------------------------------------------------
//	클래스명:	NETList
//	설명	:	LinkedList의 형태로 데이터를 관리하는 클래스.
//	관계	:	기반클래스.			NETCollector
//				중첩하는 클래스.	Iterator
//	특성	:	LinkedList의 특성을 그대로 구현한다. 각 엘리먼트는 추가/삽입/삭제의
//				부하가 적은 반면, "검색"에 취약하다.
//				Iterator은 외부에서 사용이 가능하다.
//	알고리즘:	중첩된 클래스. Iterator은 다음 엘리먼트를 가리키는, NETList의 최소단위다.
//				이 Iterator을 이용해서 List를 관리한다.
//				만약 포인터를 삽입했을 경우, 해당 포인터로부터 가상복사생성자인 clone
//				을 호출해서 DeepCopy 한다.
//	사용방법:	정의 방법
//					:	템플릿 인자 T의 조건
//							조건 1.	NEObject를 상속해야한다. 
//									NEObject::clone()를 사용하기 때문이다.
//							조건 2. 
//				bool pointerUseNewInstance란?
//					:	false일때 T가 포인터일 경우, 포인터가 새로운 인스턴스를 가리키도록
//						하지않고, shallowcopy만을 사용하겠다는 의미다.
//						true일때는 NEPointerList.hpp를 참고하라.
//				기본적으로 NETCollector의 함수를 모두 사용가능하다. (참조 할 것)
//				기본 인터페이스
//					1. push(T*)			:	포인터의 형태로 삽입이 가능하다.
//					2. pushFront(T*)	:	포인터의 형태로 삽입이 가능하다.
//					3. push(NETList&)	:	리스트 전부를 통째로 삽입한다.
//					4. pushFront(NETList&)
//					5. getIterator()		:	Iterator을 외부에서 접근한다. const로만 사용할 것을
//											권장한다.
//	메모	:	
//	히스토리:	2011-07-07	이태훈	개발 완료	
//	---------------------------------------------------------------------------------
#pragma once

//	include:
#include "../NETCollector/NETCollector.hpp"
#include "../../Commons/Interfaces/NESpecifiedInsertable/NESpecifiedInsertable.hpp"

namespace NE
{
	template <typename T, bool pointerUseNewInstance = false>
	class NETList : public NETCollector<T>, NESpecifiedInsertable<T>
	{
		typedef NETCollector<T> SuperClass;
		typedef NETList<T, pointerUseNewInstance> ThisClass;
		//	내부클래스:
	public:
#include "innerclass/Iterator/Iterator.hpp"

		//	생성자:
	public:
		NETList();	
		NETList(const NETList<T, pointerUseNewInstance>& source);

		//	소멸자:
	public:
		virtual ~NETList();

		//	연산자 중첩:
	public:
		const NETList<T, pointerUseNewInstance, type>& operator=(const NETList<T, pointerUseNewInstance, type>& source); 
		NETList<T, pointerUseNewInstance, type> operator+(const NETList<T, pointerUseNewInstance, type>& source) const;
		bool operator==(const NETList<T, pointerUseNewInstance, type>& source) const;
		bool operator!=(const NETList<T, pointerUseNewInstance, type>& source) const;
		const NETList<T, pointerUseNewInstance, type>& operator+=(const NETList<T, pointerUseNewInstance, type>& source);

		//	인터페이스:
		//		상속:
		//			NETCollector:
	public:		
		virtual const T& getElement(type_index index) const; 
		virtual T& getElement(type_index index); 
		virtual type_result setElement(type_index index, const T& source);  		
		virtual type_index insert(type_index index, const T& source);
		virtual type_index remove(type_index index);
		virtual type_index find(const T& source) const;
		virtual type_index push(const T& source);
		virtual type_index pop();
		//			NEObject:
	public:
		virtual NEObject& clone() const;
		virtual type_result isValid() const; 
		virtual void release(); 
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const; 		
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
		virtual NEType::Type getType() const;

		//		고유 인터페이스:
	public:
		type_index pushFront(const T& source);
		type_index popFront();
		type_result push(const NETList<T, pointerUseNewInstance, type>& source);
		type_result pushFront(const NETList<T, pointerUseNewInstance, type>& source);
		Iterator* getIterator(type_index index);
		const Iterator* getIterator(type_index index) const;

		//	내부함수:
	private:
		const NETList<T, pointerUseNewInstance, type>& _assign(const NETList<T, pointerUseNewInstance, type>& source);
		void _release();
		type_count _getUnitCount() const;
		Iterator* _getBeforeTail();

		//	멤버변수:
	private:
		Iterator* _head;
	};
}

#include "NETList.inl"
#include "NETPointerList.hpp"
#include "NETPointerListWithPolyMorphism.hpp"
