#include "../../NETList.hpp"

namespace NE
{
	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T>
	NETList<T*, false>::Iterator::Iterator(const T* source, typename NETList<T*, false>::Iterator* next)
		: _next(next)
	{
		T* const_casted_source = const_cast<T*>(source);
		_value = const_casted_source;
	}

	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T>
	NETList<T*, false>::Iterator::~Iterator()
	{

	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T>
	typename T& NETList<T*, false>::Iterator::getValue()
	{
		return *_value;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T>
	typename const T& NETList<T*, false>::Iterator::getValue() const
	{
		return *_value;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T>
	void NETList<T*, false>::Iterator::setValue(T* source)
	{
		_value = source;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T>
	typename const NETList<T*, false>::Iterator* NETList<T*, false>::Iterator::getNext() const
	{
		return _next;
	}

	template <typename T>
	typename NETList<T*, false>::Iterator* NETList<T*, false>::Iterator::getNext()
	{
		return _next;
	}
}