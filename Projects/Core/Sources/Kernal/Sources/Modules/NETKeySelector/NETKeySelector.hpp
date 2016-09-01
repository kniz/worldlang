#include "NETKeySelector.inl"

namespace NE
{	
	//	---------------------------------------------------------------------------------
	//	설명	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-08-04	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename NodeSelector>
	NETKeySelector<NodeSelector, type>::NETKeySelector(const NETString& keyname)
		: NodeSelector(keyname)
	{
		_release();
	}



	template <typename NodeSelector>
	NETKeySelector<NodeSelector, type>::NETKeySelector(/*NEType::Type manager_type, */const NETString& keyname)
		: NodeSelector(/*manager_type, */keyname)
	{
		_release();
	}



	//	---------------------------------------------------------------------------------
	//	설명	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-08-04	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename NodeSelector>
	NETKeySelector<NodeSelector, type>::NETKeySelector(const NETKeySelector& source)
		: NodeSelector(source)
	{
		_assign(source);
	}



	//	---------------------------------------------------------------------------------
	//	설명	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-08-04	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename NodeSelector>
	NETKeySelector<NodeSelector, type>::~NETKeySelector()
	{

	}



	//	---------------------------------------------------------------------------------
	//	설명	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-08-12	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename NodeSelector>
	const NETKeySelector<NodeSelector, type> &NETKeySelector<NodeSelector, type>::operator=(const NETKeySelector& source)
	{	
		if(this == &source) return *this;

		NodeSelector::operator=(source);

		return _assign(source);
	}


	template <typename NodeSelector>
	const NETKeySelector<NodeSelector, type> &NE::NETKeySelector<NodeSelector, type>::operator=( const NEKey& source )
	{
		assign(source);

		return *this;
	}


	//	---------------------------------------------------------------------------------
	//	설명	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-08-12	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename NodeSelector>
	type_bool NETKeySelector<NodeSelector, type>::operator==(const NETKeySelector& source) const
	{	
		if(this == &source) return true;
		if(NodeSelector::operator!=(source)) return false;
		if(_key_index != source._key_index) return false;
		if(_use_auto_binding != source._use_auto_binding) return false;
		if(_is_key_returned_once != source._is_key_returned_once) return false;
		if(_keyname != source._keyname) return false;

		return true;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-08-12	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename NodeSelector>
	type_bool NETKeySelector<NodeSelector, type>::operator!=(const NETKeySelector& source) const
	{	
		return !(operator==(source));
	}



	template <typename NodeSelector>
	type_index NETKeySelector<NodeSelector, type>::getKeyIndex() const
	{
		return _key_index;
	}


	template <typename NodeSelector>
	void NETKeySelector<NodeSelector, type>::setKeyName(const NETString& new_name)
	{
		initializeReferingPoint();
		_keyname = new_name;
	}


	template <typename NodeSelector>
	NEKey& NETKeySelector<NodeSelector, type>::getKey()
	{
		//	pre:
		//		널 레퍼런스:
		NEKey* null_pointer = NE_NULL;
		//		PeekingLock:
		if(_binder.isBinded())
			return _getKeyByBinder();


		//	main:		
		NENode* peeked = &peekNode();
		if(	! peeked		||
			_key_index < 0	)
			peeked = &getNode();

		//		탐색 시작:
		while(peeked)
		{
			NEKeyCodeSet& ks = peeked->getKeySet();
			for(_key_index++; _key_index < ks.getLength() ;_key_index++)
				if(ks[_key_index].getName() == _keyname)
				{
					_is_key_returned_once = true;
					if(_use_auto_binding && ! _binder.isBinded())
						bind();

					return ks[_key_index];
				}

				peeked = &getNode();
				_key_index = NE_INDEX_ERROR;
		}


		//	post:
		//		if you found:
		_is_key_returned_once = false;
		return *null_pointer;		
	}



	template <typename NodeSelector>
	NEKey& NETKeySelector<NodeSelector, type>::peekKey()
	{
		//	pre:
		if(_binder.isBinded())
			return _binder.getBinded();
		//		널 레퍼런스:
		NEKey* null_pointer = NE_NULL;
		//		타겟팅:
		NENode& node = peekNode();
		if( ! &node) return *null_pointer;
		if(_key_index > node.getKeySet().getLengthLastIndex()) return *null_pointer;

		return node.getKeySet()[_key_index];
	}



	template <typename NodeSelector>
	const NEKey& NETKeySelector<NodeSelector, type>::peekKey() const
	{
		//	pre:
		if(_binder.isBinded())
			return _binder.getBinded();
		//		널 레퍼런스:
		NEKey* null_pointer = NE_NULL;
		//		타겟팅:
		const NENode& node = peekNode();
		if( ! &node) return *null_pointer;
		if(_key_index > node.getKeySet().getLengthLastIndex()) return *null_pointer;

		return node.getKeySet()[_key_index];
	}


	template <typename NodeSelector>
	type_bool NE::NETKeySelector<NodeSelector, type>::_operateToReferencingKeys(UnaryOperation method, const NEKey& source) const
	{
		This copied = *this;	//	이렇게 안하면 연산 후에 참조ptr가 옮겨지게 된다.

		//	main:
		type_bool result = RESULT_SUCCESS;		
		while(NEKey* e = &copied.getKey())
			if( ! e->isSubClassOf(getClass()))
				if( ! (e->*method)(source))
					return false;

		return true;
	}

	template <typename NodeSelector>
	type_result NE::NETKeySelector<NodeSelector, type>::_operateToReferencingKeys(BinaryOperation method, NEKey& result, const NEKey& operand2) const
	{		
		This copied = *this;	//	이렇게 안하면 연산 후에 참조ptr가 옮겨지게 된다.
		NEKey* e = &copied.getKey();
		if( ! e) return RESULT_SUCCESS | RESULT_ABORT_ACTION;

		//	pre:
		//		단일 연산:
		if(	this != &result				&&
			! e->isSubClassOf(*this)	)
			return (e->*method)(result, operand2);


		//	main:
		//		자기자신이면 블록연산:
		type_result res = RESULT_SUCCESS;
		do
		if( ! e->isSubClassOf(NETClass<This>()))
			res |= (e->*method)(result, operand2);
		while(e = &copied.getKey());

		return res;
	}

	template <typename NodeSelector>
	NEKey& NE::NETKeySelector<NodeSelector, type>::_findKeyByName(NEKeyCodeSet& keyset)
	{	
		//	pre:
		if(_key_index > NE_INDEX_ERROR) return keyset[_key_index];


		//	main:
		for(; _key_index < keyset.getLength() ;_key_index++)
			if(keyset[_key_index].getName() == _keyname)				
				return keyset[_key_index];

		NEKey* nullpoint = 0;
		return *nullpoint;
	}


	template <typename NodeSelector>
	type_result NETKeySelector<NodeSelector, type>::assign(const NEKey& source)
	{
		if( ! &source) return RESULT_TYPE_ERROR;
		if(this == &source) return RESULT_SUCCESS;		
		if(source.isSubClassOf(getClass()))
		{
			*this = static_cast<const This&>(source);

			return RESULT_SUCCESS;
		}
		else if (source.isSubClassOf(NENodeSelector::getClassStatically()))
		{
			const NENodeSelector& casted = static_cast<const NENodeSelector&>(source);

			NENodeSelector::operator=(casted);

			return RESULT_SUCCESS;
		}


		//	main:
		NEKeySelector copied(*this);
		//	왜 NEKeySelector를 복사하는가:
		//		키를 getKey()로 탐색하는 도중에 assign이 호출되는 시나리오가 있을 수 있다.
		//		이 경우, this->getKey()를 해서 assign을 완료하고 원래 caller로 돌아가게 되면,
		//		call을 한 시점과 탐색포인터가 어긋나게 되므로 예상과 다른 결과가 나올 수 있다.
		while(NEKey* itr = &copied.getKey())
			if( ! itr->isSubClassOf(getClass()))	//	무한 루프 이슈 방지
				*itr = source;

		return RESULT_SUCCESS;
	}

	template <typename NodeSelector>
	type_result NETKeySelector<NodeSelector, type>::add(NEKey& result, const NEKey& source) const
	{
		if( ! &source)					return RESULT_TYPE_ERROR;
		if(source.isSubClassOf(*this))	return RESULT_SUCCESS | RESULT_ABORT_ACTION;

		return _operateToReferencingKeys(&NEKey::add, result, source);
	}


	template <typename NodeSelector>
	type_result NETKeySelector<NodeSelector, type>::multiply(NEKey& result, const NEKey& source) const
	{
		if( ! &source)								return RESULT_TYPE_ERROR;
		if(source.isSubClassOf(NETClass<This>()))	return RESULT_SUCCESS | RESULT_ABORT_ACTION;

		return _operateToReferencingKeys(&NEKey::multiply, result, source);
	}

	template <typename NodeSelector>
	type_bool NETKeySelector<NodeSelector, type>::isEqualTo(const NEKey& source) const
	{
		if(source.isSubClassOf(getClass()))
		{
			const This& casted = static_cast<const This&>(source);

			return *this == casted;
		}

		return _operateToReferencingKeys(&NEKey::isEqualTo, source);
	}

	template <typename NodeSelector>
	type_bool NETKeySelector<NodeSelector, type>::isLower(const NEKey& source) const
	{
		if(source.isSubClassOf(*this))	return false;

		return _operateToReferencingKeys(&NEKey::isLower, source);
	}


	template <typename NodeSelector>
	void NETKeySelector<NodeSelector, type>::releaseValue()
	{
		NodeSelector::releaseValue();

		_release();
	}

	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-08-04	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename NodeSelector>
	void NETKeySelector<NodeSelector, type>::release()
	{
		NodeSelector::release();

		_release();
	}


	template <typename NodeSelector>
	NEBinaryFileSaver& NETKeySelector<NodeSelector, type>::serialize(NEBinaryFileSaver& saver) const
	{
		NodeSelector::serialize(saver);

		return saver << _key_index << _binder << _use_auto_binding << _is_key_returned_once << _keyname;
	}



	template <typename NodeSelector>
	NEBinaryFileLoader& NETKeySelector<NodeSelector, type>::serialize(NEBinaryFileLoader& loader)
	{
		NodeSelector::serialize(loader);

		return loader >> _key_index >> _binder >> _use_auto_binding >> _is_key_returned_once >> _keyname;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-08-04	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename NodeSelector>
	type_result NETKeySelector<NodeSelector, type>::isValid() const
	{
		//	pre:
		//		상위 클래스 메소드:
		type_result result = NodeSelector::isValid();
		if(NEResult::hasError(result) == true) return result;
		//		멤버변수의 최소 검사:
		if(_keyname.getLength() <= 0) return RESULT_TYPE_ERROR | RESULT_INVALID_DATA | RESULT_WRONG_BOUNDARY;


		//	post:
		return RESULT_SUCCESS;
	}

	template <typename NodeSelector>
	const NETKeySelector<NodeSelector, type>& NETKeySelector<NodeSelector, type>::_assign(const NETKeySelector<NodeSelector, type>& source)
	{
		if(this == &source) *this;

		_key_index = source._key_index;
		_keyname = source._keyname;
		_binder = source._binder;
		_use_auto_binding = source._use_auto_binding;
		_is_key_returned_once = source._is_key_returned_once;

		return *this;
	}

	template <typename NodeSelector>
	void NETKeySelector<NodeSelector, type>::_release()
	{		
		_key_index = NE_DEFAULT;
		_keyname.release();
		_use_auto_binding = _is_key_returned_once = false;
		_binder.release();
	}


	template <typename NodeSelector>
	type_result NETKeySelector<NodeSelector, type>::unbind()
	{
		Super::unbind();

		return _binder.unbind();
	}

	template <typename NodeSelector>
	type_bool NETKeySelector<NodeSelector, type>::isBinded() const
	{
		return Super::isBinded() || _binder.isBinded();
	}

	template <typename NodeSelector>
	type_result NETKeySelector<NodeSelector, type>::bind()
	{
		Super::bind();

		//	pre:
		//		타겟팅:
		NEEnlistableManager& manager = getManager();
		if( ! &manager)
		{
			KERNAL_ERROR(" : ");
			return RESULT_TYPE_ERROR;
		}	
		NENode& node = peekNode();
		if( ! &node ) return RESULT_TYPE_ERROR;


		//	main:
		NEKeyCodeSet& ks = node.getKeySet();
		if(	_key_index > ks.getLengthLastIndex()	||
			_key_index < 0							)
			return RESULT_TYPE_ERROR;
		//		Binder 정의:
		//			Real Index:		
		_binder._real_index = ks.getInnerElement(_key_index);
		//			Id:
		NEKey& key = manager._getKeySet().getElement(_binder._real_index);
		if( ! &key)
		{
			_binder.release();
			return RESULT_TYPE_ERROR;
		}
		_binder._comparing_id = key.getId();


		//	post:
		_is_key_returned_once = false;
		_binder._manager_type = getManagerType();
		return RESULT_SUCCESS;
	}

	template <typename NodeSelector>
	NEKeyBinder& NETKeySelector<NodeSelector, type>::getBinder()
	{
		return _binder;
	}

	template <typename NodeSelector>
	const NEKeyBinder& NETKeySelector<NodeSelector, type>::getBinder() const
	{
		return _binder;
	}

	template <typename NodeSelector>
	type_bool NETKeySelector<NodeSelector, type>::isUsingAutoBinding() const
	{
		return _use_auto_binding;
	}

	template <typename NodeSelector>
	type_bool& NETKeySelector<NodeSelector, type>::isUsingAutoBinding()
	{
		return _use_auto_binding;
	}

	template <typename NodeSelector>
	NEKey& NETKeySelector<NodeSelector, type>::_getKeyByBinder()
	{
		NEKey* nullpoint = 0;		
		NEKey& to_return = _is_key_returned_once ? *nullpoint : _binder.getBinded();
		_is_key_returned_once = !_is_key_returned_once;
		return to_return;
	}
}