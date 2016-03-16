#include "../../NETList.hpp"

namespace NE
{
	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T>
	NETList<T*, true>::Iterator::Iterator(const T* source, typename NETList<T*, true>::Iterator* next)
		: _next(next)
	{
		_value = static_cast<T*>( &(source->clone()) );
	}

	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T>
	NETList<T*, true>::Iterator::~Iterator()
	{
		if(_value)
			delete _value;
		_value = NE_NULL;
	}

	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T>
	typename const NETList<T*, true>::Iterator& NETList<T*, true>::Iterator::operator=(typename const NETList<T*, true>::Iterator& source)
	{
		_next = source._next;
		return operator=(source._value);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T>
	typename const NETList<T*, true>::Iterator& NETList<T*, true>::Iterator::operator=(const T* source)
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
	template <typename T>
	typename T& NETList<T*, true>::Iterator::getValue()
	{
		return *_value;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T>
	typename const T& NETList<T*, true>::Iterator::getValue() const
	{
		return *_value;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T>
	void NETList<T*, true>::Iterator::setValue(const T* const source)
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
	template <typename T>
	typename const NETList<T*, true>::Iterator* NETList<T*, true>::Iterator::getNext() const
	{
		return _next;
	}

	template <typename T>
	typename NETList<T*, true>::Iterator* NETList<T*, true>::Iterator::getNext()
	{
		return _next;
	}
}
