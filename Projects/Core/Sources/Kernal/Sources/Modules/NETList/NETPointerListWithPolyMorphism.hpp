//	---------------------------------------------------------------------------------
//	클래스명:	NETList<T*>
//	설명	:	템플릿 인자로 포인터를 사용하고, 그 포인터가 각각 독립된 인스턴스를
//				가리키는 LinkedList를 원할때 구현되는 클래스.
//				즉, 템플릿 인자가 포인터라고 할지라도 단순히 포인터를 가지고 있는
//				LinkedList라면 NETList<T*>가 사용될 것이다.
//				이는, 2번째 템플릿인자인
//	관계	:	기반클래스.			NETCollector
//				일반 템플릿 클래스.	NETList<T*>
//	특성	:	2번째 템플릿 인자인 bool pointerUseNewInstance가 true란?
//					:	포인터를 deepcopy한다는 것을 말한다.
//						예를들어, NENode a; 의 주소인 &a를 놓고 pointerUseNewInstance
//						가 true일때와 false일때의 동작의 차이를 살펴보자.
//							1. NETList<T*, false> 일 때 
//								: 포인터가 복사되어 엘리먼트로 들어간다. 단지 그 뿐이다.
//							2. This 일 때
//								: 포인터가 가리키는 인스턴스까지 복사되어 들어간다.
//								포인터로부터 복사된 엘리먼트는 포인터와는 별도의 인스
//								턴스를 가진다.
//						This의 이와 같은 동작은 T* 다형성을 구현하고자 할때
//						제대로 사용된다. 
//	알고리즘:	NETList<T*>와 동일하다. 해당 헤더파일을 참고할 것.
//	사용방법:	NETList<T*>와 동일하다. 해당 헤더파일을 참고할 것.
//	메모	:	
//	히스토리:	2011-07-07	이태훈	개발 완료	
//	---------------------------------------------------------------------------------
//	템플릿클래스
//	Typename으로 클래스를 넣어 정의되기 위해서는 다음의 조건을 만족시켜야한다.
//		operator!=가 정의되어야 한다. (NETList.inl(250)참고)
//		operator==가 정의되어야 한다.
//		operator=가 정의되어야 한다.
//		생성자(int)가 정의되어야 한다. (NETList.hpp(22)참고)
//		기본생성자가 정의되어야 한다.
#pragma once

namespace NE
{
	template <typename T>
	class NETList<T*, true> : public NETCollector<T*>
	{
		typedef NETList<T*, true> _This;

		NE_DECLARE_INTERFACE(_This, NETCollector<T*>)

			//	내부클래스:
	public:
#include "innerclass/PointerIteratorWithPolyMorphism/PointerIteratorWithPolyMorphism.hpp"

		//	스코프 선언:
	public:
		using Super::push;
		using Super::find;
		using Super::setElement;

		//	생성자:
	public:
		NETList();
		NETList(const This& source);

		//	소멸자:
	public:
		virtual ~NETList();

		//	연산자 중첩:
	public:		
		const This& operator=(const This& source); 
		This operator+(const This& source) const;
		bool operator==(const This& source) const;
		bool operator!=(const This& source) const;
		const This& operator+=(const This& source);

		//	인터페이스:
		//		상속:
		//			NETCollector:
	public:		
		virtual const T& getElement(type_index index) const; 
		virtual T& getElement(type_index index); 
		virtual type_result setElement(type_index index, const T* const source);
		virtual type_index insert(type_index index, const T* const source);
		virtual type_index remove(type_index index);		
		virtual type_index find(const T* const source) const;
		virtual type_index push(const T* const source);
		virtual type_index pop();
		//			NEObject:
	public:
		virtual type_result isValid() const; 
		virtual void release();

		//		고유 인터페이스:
	public:
		type_index pushFront(const T* const source);
		type_index pushFront(const T& source);
		type_index insert(type_index index, const T& source);
		type_index popFront();
		type_index push(const This& source);
		type_index pushFront(const This& source);
		Iterator* getIterator(type_index index);
		const Iterator* getIterator(type_index index) const;

		//	내부함수:
	private:
		const This& _assign(const This& source);
		void _release();
		type_count _getUnitCount() const;
		Iterator* _getBeforeTail();

		//	멤버변수:
	private:
		Iterator* _head;
	};
}

#include "NETPointerListWithPolyMorphism.inl"
