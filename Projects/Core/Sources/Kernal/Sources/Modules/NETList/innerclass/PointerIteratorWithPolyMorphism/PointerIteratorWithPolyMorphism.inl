#include "../../NETList.hpp"

namespace NE
{
	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, NEType::Type type>
	NETList<T*, true, type>::Iterator::Iterator(const T* source, typename NETList<T*, true, type>::Iterator* next)
		: _next(next)
	{
		_value = static_cast<T*>( &(source->clone()) );
	}

	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, NEType::Type type>
	NETList<T*, true, type>::Iterator::~Iterator()
	{
		if(_value)
			delete _value;
		_value = NE_NULL;
	}

	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, NEType::Type type>
	typename const NETList<T*, true, type>::Iterator& NETList<T*, true, type>::Iterator::operator=(typename const NETList<T*, true, type>::Iterator& source)
	{
		_next = source._next;
		return operator=(source._value);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, NEType::Type type>
	typename const NETList<T*, true, type>::Iterator& NETList<T*, true, type>::Iterator::operator=(const T* source)
	{
		if(_value) 
		{
			delete _value;
			_value = NE_NULL;
		}

		_value = static_cast<T*>( &(source->clone()) );

		return *this;
	}

	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, NEType::Type type>
	typename T& NETList<T*, true, type>::Iterator::getValue()
	{
		return *_value;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, NEType::Type type>
	typename const T& NETList<T*, true, type>::Iterator::getValue() const
	{
		return *_value;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, NEType::Type type>
	void NETList<T*, true, type>::Iterator::setValue(const T* const source)
	{
		if(_next)
		{
			delete _next;
			_next = NE_NULL;
		}
		
		_value = static_cast<T*>( &(source->clone()) );
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, NEType::Type type>
	typename const NETList<T*, true, type>::Iterator* NETList<T*, true, type>::Iterator::getNext() const
	{
		return _next;
	}
	
	template <typename T, NEType::Type type>
	typename NETList<T*, true, type>::Iterator* NETList<T*, true, type>::Iterator::getNext()
	{
		return _next;
	}
}
