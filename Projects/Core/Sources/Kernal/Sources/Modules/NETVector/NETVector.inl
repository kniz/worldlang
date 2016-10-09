///	@brief	A kind of @see NETCollector that manage element on linear.
///	@detail	It's based on traditional C Array and can be expandable automatically.
///			Because of this linearistic trait, All elements will be shift to remove
///			vacant space when TVector is inserting or removing.					
///
///			When you want to define to vectorize something abstracted, 
///			You need to take combination with @see NETDeeper or @see NETShallower.
///			please refer them for further information.
//	사용방법:	정의 방법
//					:	템플릿 인자 InsideType의 조건
//							조건 1.	NEObject를 상속해야한다. 
//									NEObject::clone()를 사용하기 때문이다.
//							조건 2. 
//				type_bool pointerUseNewInstance란?
//					:	false일때 InsideType가 포인터일 경우, 포인터가 새로운 인스턴스를 가리키도록
//						하지않고, shallowcopy만을 사용하겠다는 의미다.
//						true일때는 NEPointerList.hpp를 참고하라.
//				기본적으로 NETCollector의 함수를 모두 사용가능하다. (참조 할 것)
//				기본 인터페이스
//					1. push(InsideType*)			:	포인터의 형태로 삽입이 가능하다.
//					2. pushFront(InsideType*)	:	포인터의 형태로 삽입이 가능하다.
//					3. push(NETList&)	:	리스트 전부를 통째로 삽입한다.
//					4. pushFront(NETList&)
/*
				외향(Outside)과 내향(Inside) 타입이 서로 다른 Collector 생성 방법:
					1. 타입이 다른 경우, NETVector은 추상클래스로서 선언된다.
					2. 다음의 함수들은 파생클래스에서 채워야한다.
						1. 복사생성자
						2. virtual release
						3. virtual insert
						3. virtual remove
						4. virtual getElement(index) const
						5. virtual getElement(index)
						6. virtual setElement
						7. virtual clone
						8. virtual find
*/
//	메모	:	
//	히스토리:	2011-07-07	이태훈	개발 완료	
//	---------------------------------------------------------------------------------
#pragma once

//	include:
#include "../NETClass/NETClass.inl"
#include "../NETReservedCollector/NETReservedCollector.inl"
#include "../NETIterator/NETIterator.inl"

namespace NE
{
	template <typename T>
	class NETVector : public NETReservedCollector<T>
	{	
		typedef NETVector<T> _This;
		
		NE_DECLARE_INTERFACE_ONLY(_This, NETReservedCollector<T>)

	protected:
		class Iterator : public NETIterator<T>
		{
			NE_DECLARE_CLASS_ONLY(Iterator, NETIterator<T>)

		public:
			Iterator(_This& owner, type_index new_index);

		public:
			type_bool operator==(const This& rhs) const;
			virtual type_bool operator<(const This& rhs) const;
			virtual type_bool operator>(const This& rhs) const;

		public:
			virtual const T& get() const;
			virtual T& get();
			virtual type_bool isEnd() const;
			virtual type_result next(type_index step_for_next);
			virtual type_result back(type_index step_for_back);
			//		NELengthedObject:
			virtual type_index getLength() const;
			//		NEObject:
			virtual void release();
			virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
			virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
			virtual type_result isValid() const;

		public:
			_This& getOwner();
			const _This& getOwner() const;
			type_result setIndex(type_index new_index);
			type_index getIndex() const;

		private:
			NETWeakBinder<_This> _owner;	//	we'll keep track of owner-instance for checking its validness.
			type_index _index;
		};
		class CIterator : public NETCIterator<T>
		{
			NE_DECLARE_CLASS_ONLY(CIterator, NETCIterator<T>)

		public:
			CIterator(const _This& owner, type_index new_index);

		public:
			type_bool operator==(const This& rhs) const;		
			virtual type_bool operator<(const This& rhs) const;
			virtual type_bool operator>(const This& rhs) const;	

		public:
			virtual const T& get() const;
			virtual type_bool isEnd() const;
			virtual type_result next(type_index step_for_next);
			virtual type_result back(type_index step_for_back);
			//		NELengthedObject:
			virtual type_index getLength() const;
			//		NEObject:
			virtual void release();
			virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
			virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
			virtual type_result isValid() const;

		public:
			const _This& getOwner() const;
			type_result setIndex(type_index new_index);
			type_index getIndex() const;

		private:
			NETWeakBinder<const _This> _owner;	//	we'll keep track of owner-instance for checking its validness.
			type_index _index;
		};

	public:
		NETVector();
		NETVector(type_count size);
		NETVector(const This& source);
		virtual ~NETVector();

	public:
		const This& operator=(const This& source); 
		type_bool operator==(const This& source) const;
		type_bool operator!=(const This& source) const;
		const This& operator+=(const This& source);
		This operator+(const This& source) const;
		
		//	Interfaces:
		//		Virtuals:
	public:
		//		NETReservedCollector:
		virtual type_result create(type_index new_size);
		virtual type_result resize(type_index new_size);
		//		NETCollector:
		virtual NETBinder<NETCIterator<T>> getIterator(type_index index) const;
		virtual NETBinder<NETIterator<T>> getIterator(type_index index);
		virtual NETBinder<NETIterator<T>> insert(const NETCIterator<T>& where, const T& source);
		virtual NETBinder<NETIterator<T>> insert(const NETCIterator<T>& where, const NETCIterator<T>& from, const NETCIterator<T>& end);
		virtual NETBinder<NETIterator<T>> remove(const NETCIterator<T>& from, const NETCIterator<T>& end);
		//			We're overriding below ones because of optimization: 
		virtual T& getElement(type_index index);
		virtual const T& getElement(type_index index) const;		
		//			NEObject:
		virtual type_result isValid() const; 
		virtual void release(); 
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const; 		
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);

	private:
		const This& _assign(const This& source);
		type_bool _isValid(const CIterator& iterator) const;
		void _release();

		//	멤버변수:
	protected:
		T*	_data;
	};
}