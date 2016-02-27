namespace NE
{
	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, bool pointerUseNewInstance, NEType::Type type>
	NETList<T, pointerUseNewInstance, type>::NETList()
		:SuperClass(), _head(NE_NULL) 
	{
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, bool pointerUseNewInstance, NEType::Type type>
	NETList<T, pointerUseNewInstance, type>::NETList(const ThisClass& source)
		:SuperClass(), _head(NE_NULL)
	{
		_assign(source);
	}	



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, bool pointerUseNewInstance, NEType::Type type>
	NETList<T, pointerUseNewInstance, type>::~NETList()
	{
		_release();
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, bool pointerUseNewInstance, NEType::Type type>
	const NETList<T, pointerUseNewInstance, type>&
		NETList<T, pointerUseNewInstance, type>::operator=
		(
		const ThisClass& source
		) 
	{
		return _assign(source);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, bool pointerUseNewInstance, NEType::Type type>
	NETList<T, pointerUseNewInstance, type>
		NETList<T, pointerUseNewInstance, type>::operator+
		(
		const ThisClass& source
		) const
	{
		//	pre:
		//		파라메터 검사:
		if(source._length <= 0)	return ThisClass(*this);



		//	main:
		//		복사:
		//			임시 버퍼 생성:
		ThisClass buffer(*this);
		//			버퍼에 데이터 축적:		
		buffer.push(source);



		// post:
		return buffer;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, bool pointerUseNewInstance, NEType::Type type>
	bool  NETList<T, pointerUseNewInstance, type>::operator==(const ThisClass& source) const
	{
		//	pre:
		if(this == &source) return true;
		if(NETCollector<T>::operator==(source) == false) return false;



		//	main:
		const Iterator* iterator = getIterator(0);
		const Iterator* source_iterator	= source.getIterator(0);
		while(iterator)
		{
			if(iterator->getValue() != source_iterator->getValue())
				return false;

			iterator = iterator->getNext();
			source_iterator = source_iterator->getNext();
		}



		//	post:
		return true;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, bool pointerUseNewInstance, NEType::Type type>
	bool  NETList<T, pointerUseNewInstance, type>::operator!=(const ThisClass& source) const
	{
		return !(operator==(source));
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//				2011-11-20	이태훈	버그 수정	source가 *this일 때 발생하게될 오류 대처 추가
	//	---------------------------------------------------------------------------------
	template <typename T, bool pointerUseNewInstance, NEType::Type type>
	const NETList<T, pointerUseNewInstance, type>&
		NETList<T, pointerUseNewInstance, type>::operator+=
		(
		const ThisClass& source
		)
	{
		//	pre:
		if(source._length == NE_NULL) return *this;



		//	main:
		if(this == &source)
		{
			ThisClass buffer(*this);
			push(buffer);
		}
		else
			push(source);



		//	post:		
		return *this;	
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, bool pointerUseNewInstance, NEType::Type type>
	const T  &NETList<T, pointerUseNewInstance, type>::getElement(type_index index) const 
	{			
		T* null_pointer = NE_NULL;
		//	pre:
		//		파라메터 검사:
		if(index < 0) return *null_pointer;		
		if(index > getLengthLastIndex()) return *null_pointer;
		//		관련멤버변수 검사:
		if(_length <= 0) return *null_pointer;
		if(!_head) return *null_pointer;



		//	main:
		Iterator* pointer = _head;

		for(type_index n=0; n < index ;n++)
		{
			pointer = pointer->_next;

			if(!pointer) return *null_pointer; // 인덱스에 도달하기도 전에 끝에 도달했다
		}



		//	post:
		return pointer->getValue();
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, bool pointerUseNewInstance, NEType::Type type>
	T  &NETList<T, pointerUseNewInstance, type>::getElement(type_index index) 
	{
		T* null_pointer = NE_NULL;
		//	pre:
		//		파라메터 검사:
		if(index < 0) return *null_pointer;		
		if(index > getLengthLastIndex()) return *null_pointer;
		//		관련 멤버변수 검사:
		if(!_head) return *null_pointer;
		if(_length <= 0) return *null_pointer;



		//	main:
		Iterator* pointer = _head;

		for(type_index n=0; n < index ;n++)
		{
			pointer = pointer->_next;

			if(!pointer) return *null_pointer; // 인덱스에 도달하기도 전에 끝에 도달했다
		}



		//	post:
		return pointer->getValue();
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, bool pointerUseNewInstance, NEType::Type type>
	type_result NETList<T, pointerUseNewInstance, type>::setElement(type_index index, const T& source)  
	{
		//	pre:
		//		파라메터 검사:
		if(index < 0) return RESULT_TYPE_WARNING;
		if(index > getLengthLastIndex()) return RESULT_TYPE_WARNING;
		//		관련멤버변수 검사:
		if(_length <= 0) return RESULT_TYPE_WARNING;
		if(!_head) return RESULT_TYPE_WARNING;



		//	main:
		Iterator* target = getIterator(index);

		if(!target) return RESULT_TYPE_WARNING;

		target->_value = source;
		
		return RESULT_SUCCESS;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, bool pointerUseNewInstance, NEType::Type type>
	type_result NETList<T, pointerUseNewInstance, type>::push(const ThisClass& source)
	{
		//	pre:
		//		파라메터 검사:
		if(!source._length)	return RESULT_TYPE_INFORMATION | RESULT_ABORT_ACTION;
		if(&source == this) return RESULT_TYPE_WARNING | RESULT_WRONG_PARAMETER | RESULT_ABORT_ACTION;



		//	main:
		for(type_index index=0; index < source._length ;index++) // length는 index보다 1크므로 <= 대신 <를 사용한다
			insert(_length, source.getElement(index));				



		//	post:
		return RESULT_SUCCESS;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, bool pointerUseNewInstance, NEType::Type type>
	type_result NETList<T, pointerUseNewInstance, type>::pushFront(const ThisClass& source)
	{
		//	pre:
		//		파라메터 검사:
		if(!source._length)	return RESULT_TYPE_INFORMATION | RESULT_ABORT_ACTION;
		if(&source == this) return RESULT_TYPE_WARNING | RESULT_WRONG_PARAMETER | RESULT_ABORT_ACTION;


		//	main:
		const ThisClass::Iterator* source_iterator = source.getIterator(0);
		type_index index = 0;
		while(source_iterator)
		{
			insert(index, source_iterator->getValue());

			index++;

			source_iterator = source_iterator->getNext();
		}



		//	post:
		return RESULT_SUCCESS;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	데이터를 임의의 인덱스에 삽입한다.	
	//	동작조건:	중간에 값을 삽입. 길이 == 크기 일경우, 전체 크기가 + 1 증가한다.
	//	메모	:	만약 5에 데이터를 삽입하면, 5에 있던 데이터는 6으로 밀려난다.
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------	
	template <typename T, bool pointerUseNewInstance, NEType::Type type>
	type_index NETList<T, pointerUseNewInstance, type>::insert(type_index index, const T& source) 
	{
		//	pre:
		//		파라메터 검사:
		if(index < 0) return NE_INDEX_ERROR;
		if(index > _length) return NE_INDEX_ERROR;



		//	main:
		//		조건1:	제일 앞에있는 인덱스(= _head )를 선택했다면
		if(index == 0)
		{	//		_head에 새로운 인스턴스 생성:
			Iterator* temp = new Iterator(source, _head);

			_head = temp;
		}
		else
		{	//		새로운 인스턴스 추가:	추가할 위치의 전 Iterator의 next를 이용한다
			//			인덱스 변수 생성:	추가할 위치의 전 Iterator을 가리킬 인덱스
			type_index _index = 0;
			//			위치 검색:
			for(Iterator* iterator=_head; iterator ;iterator=iterator->_next)
			{ 	//			조건1-1:	목표Iterator을 next로 가리키고 있는 유닛을 찾았다면
				if(_index == (index - 1)) 
				{	//			추가:
					Iterator* temp = new Iterator(source, iterator->_next);

					iterator->_next = temp;
					break;
				}

				_index++;
			}
		}



		//	post:
		//		길이 수정:	유닛을 추가했으므로, 길이 정보도 동기화 시킨다
		_length++;
		return index;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	임의의 인덱스에 위치한 데이터를 하나 삭제한다.
	//	동작조건:	지정한 인덱스가 최대 인덱스보다 작고, 0 이상이다.
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, bool pointerUseNewInstance, NEType::Type type>
	type_index NETList<T, pointerUseNewInstance, type>::remove(type_index index) 
	{
		//	pre:
		//		파라메터검사:
		if(index < 0) return NE_INDEX_ERROR;
		if(index >= _length) return NE_INDEX_ERROR;



		//	main:
		//		조건1:	처음 유닛을 삭제하려 한다면
		if(index == 0)
		{	//		_head의 next를 이용:
			Iterator* temp = _head;

			_head = _head->_next;


			delete temp;
		}
		else
		{	//		중간 유닛 삭제:	삭제할 위치의 전 Iterator의 next를 이용한다
			//			인덱스 변수 생성:
			type_index _index = 0;
			//			인덱스 검색:
			for(Iterator* iterator=_head; iterator ;iterator=iterator->_next)
			{	//		조건1-1:	인덱스를 찾았다면 (= 리스트는 한발 뒤에서 조작한다 )
				if(_index == (index - 1))
				{	//		삭제:
					Iterator* temp = iterator->_next;

					iterator->_next = iterator->_next->_next;

					delete temp;
					break;
				}

				_index++;

			}
		}



		//	post:		
		//		길이 수정:	유닛은 이미 삭제되었으므로, 길이정보만 수정한다
		_length--;
		return index;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	주어진 데이터와 일치하는 엘리먼트가 존재하는지 검색후, 인덱스를 전달
	//				한다.
	//	동작조건:	템플릿 인자 T가 operator==가 정의되어 있어야 한다.
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, bool pointerUseNewInstance, NEType::Type type>
	type_index NETList<T, pointerUseNewInstance, type>::find(const T& source) const
	{
		//	pre:
		//		관련 멤버변수 검사:
		if(_length <= 0) return NE_INDEX_ERROR;



		//	main:
		//		검색:		
		type_index index = 0;

		for(Iterator* iterator=_head; iterator ;iterator=iterator->_next)
		{
			if(iterator->getValue() == source) return index; // 찾았다

			index++;
		}



		//	post:
		//		에러반환:	못찾았다
		return NE_INDEX_ERROR; // -1
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, bool pointerUseNewInstance, NEType::Type type>
	NEObject& NETList<T, pointerUseNewInstance, type>::clone() const 
	{			
		return *(new ThisClass(*this));
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, bool pointerUseNewInstance, NEType::Type type>
	type_result NETList<T, pointerUseNewInstance, type>::isValid() const  
	{
		//	pre:
		//		상위클래스 VALID 체크:
		type_result result =SuperClass::isValid();
		if(NEResult::hasError(result) == true) return result;
		//		멤버변수 체크:
		if (_length != _getUnitCount()) return RESULT_TYPE_WARNING | RESULT_WRONG_BOUNDARY | RESULT_INVALID_DATA;



		//	post:
		return true;
	}			



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, bool pointerUseNewInstance, NEType::Type type>
	void  NETList<T, pointerUseNewInstance, type>::release()  
	{			
		_release();

		return SuperClass::release();
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, bool pointerUseNewInstance, NEType::Type type>
	NEBinaryFileSaver  &NETList<T, pointerUseNewInstance, type>::serialize(NEBinaryFileSaver& saver) const 
	{	
		//	pre:
		NETCollector::serialize(saver);

		//	main:
		//		엘리먼트 저장:
		for(const Iterator* iterator = _head; iterator ;iterator=iterator->_next)
			saver << iterator->getValue();



		//	post:
		return saver;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, bool pointerUseNewInstance, NEType::Type type>
	NEBinaryFileLoader& NETList<T, pointerUseNewInstance, type>::serialize(NEBinaryFileLoader& loader)
	{
		//	pre:		
		ThisClass::release();
		NETCollector::serialize(loader);
		type_index count = _length;	
		NETCollector::release();



		//	main:
		//		길이 정보 초기화:		
		//		엘리먼트 로드:		
		for(type_index n=0; n < count ;n++)
		{
			T element = T(); // 그냥 T element()를 한다면 함수의 선언으로 컴파일러가 착각한다.

			loader >> element;
			push(element);
		}



		//	post:
		return loader;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, bool pointerUseNewInstance, NEType::Type type>
	NEType::Type NETList<T, pointerUseNewInstance, type>::getType() const
	{
		return type;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	NETList의 중첩 클래스인, Iterator을 외부에 내보낸다. Iterator에는 다음 데이터를
	//				가리키는 next가 존재한다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, bool pointerUseNewInstance, NEType::Type type>
	typename NETList<T, pointerUseNewInstance, type>::Iterator*
		NETList<T, pointerUseNewInstance, type>::getIterator(type_index index)
	{
		//	pre:
		//		파라메터검사:
		if(index < 0) return NE_NULL;
		if(index > getLengthLastIndex()) return NE_NULL;
		//		관련  멤버변수 검사:
		if(_length <= 0) return NE_NULL;
		if(!_head) return NE_NULL;



		//	main:
		//		검색:
		Iterator* pointer = _head;

		for(type_index n=0; n < index ;n++)
		{
			pointer = pointer->_next;

			if(!pointer) return NE_NULL; // 인덱스에 도달하기도 전에, 끝에 도달했다
		}



		//	post:
		return pointer;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, bool pointerUseNewInstance, NEType::Type type>
	const typename NETList<T, pointerUseNewInstance, type>::Iterator*
		NETList<T, pointerUseNewInstance, type>::getIterator(type_index index) const
	{	
		//	pre:
		//		파라메터 검사:
		if(index < 0) return NE_NULL;
		if(index > getLengthLastIndex()) return NE_NULL;
		//		관련 멤버변수 검사:
		if(_length <= 0) return NE_NULL;
		if(!_head) return NE_NULL;



		//	main:
		Iterator* pointer = _head;

		for(type_index n=0; n < index ;n++)
		{
			pointer = pointer->_next;

			if(!pointer) return NE_NULL; // 인덱스에 도달하기도 전에 끝에 도달했다
		}



		//	post:
		return pointer;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, bool pointerUseNewInstance, NEType::Type type>
	const NETList<T, pointerUseNewInstance, type>&
		NETList<T, pointerUseNewInstance, type>::_assign
		(
		const ThisClass& source
		)
	{	
		//	pre:
		release();
		//	main:
		push(source);
		//	post:
		return *this;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, bool pointerUseNewInstance, NEType::Type type>
	void  NETList<T, pointerUseNewInstance, type>::_release() 
	{	
		//	pre:
		if(!_head) return;



		//	main:
		type_count length = getLength(); // pop을 하면 _length가 하나씩 줄어들므로, for문 조건식에서 오작동을 일으킨다. 그러므로 미리 size를 가져옴

		for(type_index n=0; n < length ;n++)
			pop();
	}		



	//	---------------------------------------------------------------------------------
	//	설명	:	몇 개의 유닛이 존재하는지 셈한다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, bool pointerUseNewInstance, NEType::Type type>
	type_count NETList<T, pointerUseNewInstance, type>::_getUnitCount() const
	{
		//	main:
		type_count count = 0;

		for(Iterator* iterator = _head; iterator ;iterator = iterator->_next)
			count++;				



		//	post:
		return count;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	맨 마지막 바로 앞의 Iterator에 접근한다.
	//	동작조건:
	//	메모	:	LinkedList의 특성상, 바로 앞의 Iterator이 삭제/삽입을 할 수 있기 때문이다.
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, bool pointerUseNewInstance, NEType::Type type>
	typename NETList<T, pointerUseNewInstance, type>::Iterator*
		NETList<T, pointerUseNewInstance, type>::_getBeforeTail()
	{
		//	pre:				
		if(_length <= 0) return NE_NULL;
		if(_length == 1) return NE_NULL;



		//	post:
		return getIterator(getLengthLastIndex() - 1);
	}



	template <typename T, bool pointerUseNewInstance, NEType::Type type>
	type_index NETList<T, pointerUseNewInstance, type>::push(const T& source)
	{
		return insert(getLength(), source);
	}



	template <typename T, bool pointerUseNewInstance, NEType::Type type>
	type_index NETList<T, pointerUseNewInstance, type>::pop()
	{
		return remove(getLengthLastIndex());
	}



	template <typename T, bool pointerUseNewInstance, NEType::Type type>
	type_index NETList<T, pointerUseNewInstance, type>::pushFront(const T& source)
	{
		return insert(0, source);
	}



	template <typename T, bool pointerUseNewInstance, NEType::Type type>
	type_index NETList<T, pointerUseNewInstance, type>::popFront()
	{
		return remove(0);
	}
}

#include "innerclass/Iterator/Iterator.inl"
