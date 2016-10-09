#pragma once

#include "../NETCollector/NETCollector.hpp"
#include "NETReservedCollector.inl"

namespace NE
{
#define _NAME	NETReservedCollector<T>

	NE_DEFINE_INTERFACE_ONLY(_NAME, template <typename T>)

	template<typename T>
	_NAME::NETReservedCollector()
		: Super()
	{
		_release();
	}

	template<typename T>
	_NAME::NETReservedCollector(type_index size)
		: Super()
	{
		_release();
		_size = size;
	}

	template<typename T>
	_NAME::~NETReservedCollector() 
	{
		_release();
	}		

	template<typename T>
	_NAME::NETReservedCollector(const This& source)
		: Super(source)
	{
		_assign(source);
	}

	template<typename T>
	const _NAME  &_NAME::operator=(const This& source) 
	{	
		Super::operator=(source);

		return _assign(source);
	}
	
	template<typename T>
	type_bool _NAME::operator==(const _NAME& source) const 
	{
		if(this == &source) return true;
		if(Super::operator!=(source)) return false;
		if(_size != source._size) return false;

		return true;
	}

	template<typename T>
	type_bool _NAME::operator!=(const _NAME& source) const
	{
		return !(operator==(source));
	}

	template<typename T>	
	type_index	 _NAME::getSize() const 
	{
		return _size;
	}	

	template<typename T>	
	type_index	 _NAME::getSizeLastIndex() const 
	{
		return _size-1;
	}

	template<typename T>	
	void  _NAME::release()   
	{
		Super::release();

		return _release();
	}

	template<typename T>	
	type_result  _NAME::isValid() const 
	{		
		type_result result = Super::isValid();
		if(NEResult::hasError(result)) return result;
		if(_size < 0) return RESULT_TYPE_ERROR | RESULT_WRONG_BOUNDARY;
		if(_size < getLength()) return RESULT_TYPE_ERROR | RESULT_WRONG_BOUNDARY;

		return RESULT_SUCCESS;
	}

	template<typename T>
	NEBinaryFileSaver &_NAME::serialize(NEBinaryFileSaver& saver) const
	{
		NETCollector<T>::serialize(saver);

		return saver << _size;
	}

	template<typename T>
	NEBinaryFileLoader &_NAME::serialize(NEBinaryFileLoader& loader)
	{
		NETCollector<T>::serialize(loader);

		return loader >> _size;
	}

	template <typename T>
	type_bool _NAME::isEqualElement(const This& rhs) const
	{
		type_bool to_return = false;
		if(getLength() != rhs.getLength()) return to_return;

		NETCIterator<T>& rhs_e = *rhs.getFirstIterator();
		each( [&rhs_e] (T& e) {			
			if(e == *rhs_e) {
				to_return = true;
				return RESULT_ABORT_ACTION;
			}			
			++rhs_e;
		});

		return to_return;
	}

	template<typename T>
	const _NAME& _NAME::_assign(const This& source)
	{			
		if(this == &source) return *this;

		_size = source._size;

		return *this; 
	}

	template<typename T>
	void _NAME::_release()
	{
		_size = 0;
	}
}