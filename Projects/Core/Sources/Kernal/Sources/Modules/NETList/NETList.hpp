#pragma once

#include "../NETClass/NETClass.hpp"
#include "../NETCollector/NETCollector.hpp"
#include "NETList.inl"
#include "innerclass/Iterator/Iterator.hpp"
#include "innerclass/PointerIterator/PointerIterator.hpp"
#include "NETListWithBinder.hpp"
#include "innerclass/PointerIteratorWithPolyMorphism/PointerIteratorWithPolyMorphism.hpp"

namespace NE
{
#define _LISTNAME	NETList<T, ptrAsHeap>
#define _TEMPLATE	template <typename T, type_bool pointerUseNewInstance>
#define _NAME		_LISTNAME##::Node

	NE_DEFINE_CLASS_ONLY_2(NE_MACRO_FUNNEL(_NAME), NE_MACRO_FUNNEL(_TEMPLATE))

	_TEMPLATE
	type_bool _NAME::operator==(const This& rhs) const
	{
		return	_value == rhs._value	&&
				_next == rhs._next		&&
				_back == rhs._back		;
	}

	_TEMPLATE
	type_bool _NAME::operator!=(const This& rhs) const
	{
		return ! operator==(rhs);
	}

	_TEMPLATE
	type_result _NAME::isValid() const
	{
		if(	! _value.isBinded()					&&
			_back.isBinded() && _next.isBinded())
			return RESULT_TYPE_WARNING;

		return RESULT_SUCCESS;
	}

	_TEMPLATE
	void _NAME::release()
	{
		Super::release();

		_value.release();
		_next.release();
		_back.release();
	}

	_TEMPLATE
	NEBinaryFileSaver& _NAME::serialize(NEBinaryFileSaver& saver) const
	{
		return saver << _value << _next << _back;
	}

	_TEMPLATE
	NEBinaryFileLoader& _NAME::serialize(NEBinaryFileLoader& loader)
	{
		return loader >> _value >> _next >> _back;
	}

	_TEMPLATE
	NETBinder<T>& _NAME::getValueBinder()
	{
		return _value;
	}

	_TEMPLATE
	const NETBinder<T>& _NAME::getValueBinder() const
	{
		return _value;
	}

	_TEMPLATE
	NETBinder<Node>& _NAME::getNextBinder()
	{
		return _next;
	}

	_TEMPLATE
	const NETBinder<Node>& _NAME::getNextBinder() const
	{
		return _next;
	}

	_TEMPLATE
	NETBinder<Node>& _NAME::getBackBinder()
	{
		return _back;
	}

	_TEMPLATE
	const NETBinder<Node>& _NAME::getBackBinder() const
	{
		return _back;
	}

#undef _NAME	
#define _NAME	_LISTNAME##::Iterator

	NE_DEFINE_CLASS_ONLY_2(NE_MACRO_FUNNEL(_NAME), NE_MACRO_FUNNEL(_TEMPLATE))

	_TEMPLATE
	_NAME::Iterator(_This& owner, Node& new_node)
		: Super(), _owner(owner), _node(new_node)
	{

	}			

	_TEMPLATE
	type_bool _NAME::operator==(const This& rhs) const
	{
		//	When these binders are designating same object each other,
		//	we'll return true.
		return	_owner.get() == rhs._owner.get()	&&
				_node.get() == rhs._node.get()	;
	}

	_TEMPLATE
	const T& _NAME::get() const
	{
		const T* nullpointer = NE_NULL;
		if( ! _node.isBinded())
			return *nullpointer;

		return *_node->getValueBinder();
	}

	_TEMPLATE
	T& _NAME::get()
	{
		T* nullpointer = NE_NULL;
		if( ! _node)
			return nullpointer;

		return *_node->getValueBinder();
	}
	
	_TEMPLATE
	type_bool _NAME::isEnd() const
	{
		if( ! _node.isBinded())
			//	Oops. Now, we got trouble.
			return false;

		return ! _node->getNextBinder().isBinded();
	}
	
	_TEMPLATE
	type_result _NAME::next(type_index step_for_next)
	{
		for(int n=0; n < step_for_next ;n++)
		{
			if(isEnd())
				return RESULT_TYPE_WARNING;

			_node.bind(*_node->getNextBinder());
		}
		return RESULT_SUCCESS;
	}

	_TEMPLATE
	type_result _NAME::back(type_index step_for_back)
	{
		for(int n=0; n < step_for_back ;n++)
		{
			if(isEnd())
				return RESULT_TYPE_WARNING;

			_node.bind(*_node->getBackBinder());
		}
		return RESULT_SUCCESS;
	}
	
	_TEMPLATE
	type_index _NAME::getLength() const
	{
		return _owner.isBinded() ? _owner->getLength() : 0;
	}
	
	_TEMPLATE
	void _NAME::release()
	{
		_owner.release();
		_node.release();
	}

	_TEMPLATE
	NEBinaryFileSaver& _NAME::serialize(NEBinaryFileSaver& saver) const
	{
		return saver << _owner << _node;
	}
	
	_TEMPLATE
	NEBinaryFileLoader& _NAME::serialize(NEBinaryFileLoader& loader)
	{
		return loader >> _owner >> _node;
	}
	
	_TEMPLATE
	type_result _NAME::isValid() const
	{
		if( ! _owner.isBinded()) return RESULT_TYPE_ERROR;
		if( ! _node.isBinded()) return RESULT_TYPE_ERROR;
		if(	NEResult::hasError(_owner.isValid())	|| 
			NEResult::hasError(_node.isValid())	)
			return RESULT_TYPE_WARNING;		
		if(_node->getNextBinder().isBinded() && ! _node->getValueBinder().isBinded())
			return RESULT_TYPE_ERROR;

		return RESULT_SUCCESS;
	}

	_TEMPLATE
	const _LISTNAME& _NAME::getOwner() const
	{
		return _owner;
	}

	_TEMPLATE
	const _LISTNAME::Node& _NAME::getNode() const
	{
		return _node;
	}

#undef _NAME	
#define _NAME	NETList<T, ptrAsHeap>::CIterator

	NE_DEFINE_CLASS_ONLY_2(NE_MACRO_FUNNEL(_NAME), NE_MACRO_FUNNEL(_TEMPLATE))

	_TEMPLATE
	_NAME::CIterator(const _This& owner, Node& new_node)
		: Super(), _owner(owner), _node(new_node)
	{

	}			

	_TEMPLATE
	type_bool _NAME::operator==(const This& rhs) const
	{
		//	When these binders are designating same object each other,
		//	we'll return true.
		return	_owner.get() == rhs._owner.get()	&&
				_node.get() == rhs._node.get()	;
	}

	_TEMPLATE
	const T& _NAME::get() const
	{
		const T* nullpointer = NE_NULL;
		if( ! _node.isBinded())
			return *nullpointer;

		return *_node->getValueBinder();
	}

	_TEMPLATE
	type_bool _NAME::isEnd() const
	{
		if( ! _node.isBinded())
			//	Oops. we got trouble.
			return false;

		return ! _node->getNextBinder().isBinded();
	}

	_TEMPLATE
	type_result _NAME::next(type_index step_for_next)
	{
		for(int n=0; n < step_for_next ;n++)
		{
			if(isEnd())
				return RESULT_TYPE_WARNING;

			_node.bind(*_node->getNextBinder());
		}
		return RESULT_SUCCESS;
	}

	_TEMPLATE
	type_result _NAME::back(type_index step_for_back)
	{
		for(int n=0; n < step_for_back ;n++)
		{
			if(isEnd())
				return RESULT_TYPE_WARNING;

			_node.bind(*_node->getBackBinder());
		}
		return RESULT_SUCCESS;
	}

	_TEMPLATE
	type_index _NAME::getLength() const
	{
		return _owner.isBinded() ? _owner->getLength() : 0;
	}

	_TEMPLATE
	void _NAME::release()
	{
		_owner.release();
		_node.release();
	}

	_TEMPLATE
	NEBinaryFileSaver& _NAME::serialize(NEBinaryFileSaver& saver) const
	{
		return saver << _owner << _node;
	}

	_TEMPLATE
	NEBinaryFileLoader& _NAME::serialize(NEBinaryFileLoader& loader)
	{
		return loader >> _owner >> _node;
	}

	_TEMPLATE
	type_result _NAME::isValid() const
	{
		if( ! _owner.isBinded()) return RESULT_TYPE_ERROR;
		if( ! _node.isBinded()) return RESULT_TYPE_ERROR;
		if(	NEResult::hasError(_owner.isValid())	|| 
			NEResult::hasError(_node.isValid())	)
			return RESULT_TYPE_WARNING;		
		if(_node->getNextBinder().isBinded() && ! _node->getValueBinder().isBinded())
			return RESULT_TYPE_ERROR;

		return RESULT_SUCCESS;
	}

	_TEMPLATE
	_LISTNAME& _NAME::getOwner()
	{
		return _owner;
	}

	_TEMPLATE
	const _LISTNAME& _NAME::getOwner() const
	{
		return _owner;
	}

	_TEMPLATE
	_LISTNAME::Node& _NAME::getNode()
	{
		return _node;
	}

	_TEMPLATE
	const _LISTNAME::Node& _NAME::getNode() const
	{
		return _node;
	}

#undef _NAME

	NE_DEFINE_CLASS_ONLY_2(NE_MACRO_FUNNEL(_LISTNAME), NE_MACRO_FUNNEL(_TEMPLATE))

	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	_LISTNAME::NETList()
		:Super()
	{
		_release();
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	_LISTNAME::NETList(const This& source)
		:Super()
	{
		_assign(source);
	}	



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	_LISTNAME::~NETList()
	{
		_release();
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	const _LISTNAME& _LISTNAME::operator=(const This& source) 
	{
		if(this == &rhs) return *this;

		//	Don't need to call Super. length will be synchronized automatically.

		return _assign(source);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	_LISTNAME _LISTNAME::operator+(const This& source) const
	{
		//	pre:
		//		파라메터 검사:
		if(source._length <= 0)	return This(*this);



		//	main:
		//		복사:
		//			임시 버퍼 생성:
		This buffer(*this);
		//			버퍼에 데이터 축적:		
		buffer.push(source);



		// post:
		return buffer;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	type_bool  _LISTNAME::operator==(const This& source) const
	{
		//	pre:
		if(this == &source) return true;
		if(NETCollector<T>::operator==(source) == false) return false;


		//	main:
		NETIterator<T>	my_e = getIterator(),
						their_e = getIterator();
		for(; ! my_e.isEnd() ;my_e++, their_e++)
			if(	their_e.isEnd()	||
				*my_e != *their_e	)	
				return false;

		
		//	post:
		return true;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	type_bool  _LISTNAME::operator!=(const This& source) const
	{
		return !(operator==(source));
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//				2011-11-20	이태훈	버그 수정	source가 *this일 때 발생하게될 오류 대처 추가
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	const _LISTNAME& _LISTNAME::operator+=(const This& source)
	{
		if(source._length == NE_NULL) return *this;

		push(source);

		return *this;	
	}


	_TEMPLATE
	NETBinder<NETIterator<T>> _LISTNAME::getIterator(type_index index)
	{
		Iterator iterator(this, _head);
		iterator.next(index);

		//TODO:
		return NETBinder<NETIterator<T>>(iterator.clone());	//	new heap alloc at inside.
	}

	_TEMPLATE
	NETBinder<NETCIterator<T>> _LISTNAME::getIterator(type_index index) const
	{
		CIterator iterator(this, _head);
		iterator.next(index);

		//TODO:
		return NETBinder<NETCIterator<T>>(iterator.clone());	//	new heap alloc at inside.
	}

	//	---------------------------------------------------------------------------------
	//	설명	:	데이터를 임의의 인덱스에 삽입한다.	
	//	동작조건:	중간에 값을 삽입. 길이 == 크기 일경우, 전체 크기가 + 1 증가한다.
	//	메모	:	만약 5에 데이터를 삽입하면, 5에 있던 데이터는 6으로 밀려난다.
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------	
	_TEMPLATE
	type_index _LISTNAME::insert(const NETCIterator<T>& where, const T& source) 
	{
		//	pre:
		//		파라메터 검사:
		CIterator& wh = cast<CIterator>(where);
		if( ! &wh || ! &source)	return NE_INDEX_ERROR;
		if( &wh.getOwner() != this) return NE_INDEX_ERROR;
		//		Iterator valid check:
		if(NEResult::hasError(wh.isValid()))
			return NE_INDEX_ERROR;
		

		//	main:
		//		targetting:
		Node& next = wh.getNode(),
			& previous = *next.getBackBinder();
		//		create new one:
		Node node = *(new Node());
		node.getValueBinder().bind(source.clone());
		node.getBackBinder().bind(previous);
		node.getNextBinder().bind(next);
		//		rebinding:
		NETBinder<Node>& previous_binder = &previous ? 
			previous.getNextBinder() : _head;
		previous_binder.getNextBinder().bind(node);
		next.getBackBinder().bind(node);


		//	post:
		//		길이 수정:	유닛을 추가했으므로, 길이 정보도 동기화 시킨다
		_length++;
		return ??;
	}

	_TEMPLATE
	type_index _LISTNAME::insert(const NETCIterator<T>& where, const NETCIterator<T>& from, const NETCIterator<T>& end)
	{
		NETBinder<NETCIterator<T>> fr(from.clone());
		for(; fr != end	; fr++)
			//	We can keep preserving variable "where":
			//		Let us assume that there are 3 nodes. Like below,
			//
			//			[A]	<->	[B]	<->	[C]
			//					 ^
			//					 |
			//					where
			//
			//		And Iterator "where" is binding Node "B".
			//		in this situation, if user wants to insert continous 2 new const T&
			//		into Iterator "where", This gonna happen.
			//
			//	Step #1 - First T&ㅡF1ㅡwill be inserted to "where".
			//
			//			[A]	<->	[F1]	<->	[B]	<->	[C]
			//								 ^
			//								 |
			//								where
			//	
			//	Step #2 - And when Second T& goes,
			//
			//			[A]	<->	[F1]	<->	[F2]	<->	[B]	<->	[C]
			//											 ^
			//											 |
			//											where
			//
			//		As you can see, Iterator "where" is still binding "B" even if 
			//		composing of list of Nodes was changed to above.
			//		So there is no need to compensate iterator along with inserted
			//		newly T&s.
			//		
			//	Ok. got it. But, How can this be possible?:
			//		Because that's what Binder does.
			//		Remember each relationship of Nodes are constructed with
			//		Binder. And Binder can catch the instance of target itself 
			//		which located to HEAP managed by InstanceManager.
			insert(where, *fr);

		return ??;		
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	임의의 인덱스에 위치한 데이터를 하나 삭제한다.
	//	동작조건:	지정한 인덱스가 최대 인덱스보다 작고, 0 이상이다.
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	type_index _LISTNAME::remove(const NETCIterator<T>& from, const NETCIterator<T>& end)
	{
		//	pre:
		//		파라메터 검사:
		CIterator&	fr = cast<CIterator>(from),
				 &	ed = cast<CIterator>(end);
		if( ! &fr || ! &ed)	return NE_INDEX_ERROR;
		if( &fr.getOwner() != this	||
			&ed.getOwner() != this	) 
			return NE_INDEX_ERROR;
		//		Iterator valid check:
		if(	NEResult::hasError(fr.isValid())	||
			NEResult::hasError(ed.isValid())	)
			return NE_INDEX_ERROR;


		for(NETBinder<CIterator> e(fr.clone())	;
			e != end							;)
		{
			Node& node = *e.getNode();
			if( ! &node)
				break;
			//	advancing:
			//		Why do we advance e at here?:
			//			Because e has a WeakBinder of Node which was released by
			//			next sequence.
			e++;
			//	targetting:
			Node& previous = *node.getBackBinder(),
				& next = *node.getNextBinder();
			//	rebinding:
			NETBinder<Node>& previous_binder = &previous ? 
				previous.getBackBinder() : _head;
			previous_binder.bind(next);
			next.getBackBinder().bind(previous);
			//	Node will have been already released automatically:
			//		Now, there is no String Binder to make "node" instance keep alive. 
			//		Of course, by releasing variable "node", its "Value" T might had
			//		been gotten same destiny.
			
			_length--;
		}

		//	post:		
		return ??;
	}

	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	type_result _LISTNAME::isValid() const  
	{
		//	pre:
		//		상위클래스 VALID 체크:
		type_result result =Super::isValid();
		if(NEResult::hasError(result) == true) return result;
		//		멤버변수 체크:
		int count = 0;		
		result = each([] (T&) -> type_result {
			count++;
			if(NEResult::hasError(e.getNode().isValid()))
				return RESULT_TYPE_ERROR;

			return RESULT_SUCCESS;
		});
		if(NEResult::hasError(result)) return result;
		if(count != getLength()) return false;

		return true;
	}


	_TEMPLATE
	void  _LISTNAME::release()  
	{			
		_release();

		return Super::release();
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	NEBinaryFileSaver  &_LISTNAME::serialize(NEBinaryFileSaver& saver) const 
	{	
		//	pre:
		NETCollector::serialize(saver);

		//	main:
		//		엘리먼트 저장:
		for(NETCIterator<T>& e = *getStartIterator(); e != *getEndIterator() ;e++)
			saver << *e;


		//	post:
		return saver;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	NEBinaryFileLoader& _LISTNAME::serialize(NEBinaryFileLoader& loader)
	{
		//	pre:		
		release();
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



	_TEMPLATE
	NETBinder<NETIterator<T>> _LISTNAME::getIterator(type_index index)
	{
		//	pre:
		//		파라메터검사:
		if(	index < 0					||
			index > getLengthLastIndex()) return NE_NULL;
		

		//	main:
		//		검색:
		Iterator e(*this, *_head);
		for(type_index n=0; n < index ;n++)
		{
			if(e.isEnd())
				break;
			e++;
		}


		//	post:
		return NETBinder<NETIterator<T>(e.clone());
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	NETBinder<NETCIterator<T>> _LISTNAME::getIterator(type_index index) const
	{	
		//	pre:
		//		파라메터검사:
		if(	index < 0					||
			index > getLengthLastIndex()) return NE_NULL;


		//	main:
		//		검색:
		CIterator e(*this, *_head);
		for(type_index n=0; n < index ;n++)
		{
			if(e.isEnd())
				break;
			e++;
		}


		//	post:
		return NETBinder<NETCIterator<T>(e.clone());
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	_TEMPLATE
	const _LISTNAME& _LISTNAME::_assign(const This& source)
	{	
		//	pre:
		release();
		//	main:
		push(source);
		//	post:
		return *this;
	}

	_TEMPLATE
	void  _LISTNAME::_release() 
	{	
		//	main:
		type_count length = getLength(); // pop을 하면 _length가 하나씩 줄어들므로, for문 조건식에서 오작동을 일으킨다. 그러므로 미리 size를 가져옴

		for(type_index n=0; n < length ;n++)
			pop();


		//	post:
		//		create empty Node at last position. if there isn't.
		//
		//		Why do we create this?:
		//			this's the end iterator.
		//			when we insert some element, At the last position is always 
		//			for this end iterator. 
		//			So usually, when we pop all elements, _head binder actually 
		//			will be pointing this end iterator in order for user to notify
		//			that this NETList reached to end.
		if( ! _head.isBinded())
			_head.bind(Node().clone());
	}		

#undef _LISTNAME
#undef _TEMPLATE
}