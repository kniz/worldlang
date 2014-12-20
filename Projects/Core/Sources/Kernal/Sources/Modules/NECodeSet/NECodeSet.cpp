#include "NECodeSet.hpp"
#include "../Kernal/Kernal.hpp"

namespace NE
{
	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NECodeSet::NECodeSet()
		: SuperClass()
	{

	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NECodeSet::NECodeSet(type_count size)
		: SuperClass(size)
	{

	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NECodeSet::NECodeSet(const NECodeSet& source)
		: SuperClass(source)
	{
		_assign(source);
	}



	NE_DLL NECodeSet::NECodeSet(NECodeType::CodeType initial_type, bool is_fixed)
		: SuperClass(), _type(initial_type, is_fixed)
	{

	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NECodeSet::~NECodeSet()
	{

	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NECodeSet NE_DLL &NECodeSet::operator+=(const NECodeSet& source)
	{
		if( ! getCodeType().isAcceptableType(source.getCodeType())) return *this;

		SuperClass::operator+=(source);

		return *this;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NECodeSet NE_DLL NECodeSet::operator+(const NECodeSet& source) const
	{
		NECodeSet buffer(getSize() + source.getSize());

		buffer.push(*this);
		buffer.push(source);

		return buffer;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEType::Type NE_DLL NECodeSet::getType() const
	{
		return NEType::NECODE_SET;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-19	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	//	save는 기존의 NEPointerArray로도 가능하다
	NEBinaryFileSaver NE_DLL &NECodeSet::serialize(NEBinaryFileSaver& saver) const
	{	
		SuperClass::serialize(saver);

		return saver << _type;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-19	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEBinaryFileLoader NE_DLL &NECodeSet::serialize(NEBinaryFileLoader& loader)
	{	
		SuperClass::serialize(loader);		

		return loader >> _type;
	}

	NEObject NE_DLL &NECodeSet::clone() const
	{
		return *(new ThisClass(*this));
	}

	type_result NECodeSet::setElement(type_index index, const NECode& source)
	{
		if(_isElementDuplicated(source)) return RESULT_TYPE_WARNING | RESULT_ABORT_ACTION;

		return SuperClass::setElement(index, source);		
	}

	bool NECodeSet::_isElementDuplicated(const NECode& new_one) const
	{
		if(getCodeType().isTypeFixed())
		{
			for(int n = 0; n < getLength(); n++)
				if(getElement(n).getCode() == new_one.getCode())
					return true;
		}
		else
			return find(new_one) > NE_INDEX_ERROR;

		return true;
	}

	type_index NECodeSet::insert(type_index index, const NECode& source)
	{		
		if( ! getCodeType().isAcceptableType(source)) return NE_INDEX_ERROR;
		NECodeType new_type(_type);
		new_type = source;
		NECode to_insert(source.getCode(), new_type.getCodeType(), new_type.isTypeFixed());

		if( _isElementDuplicated(to_insert)) return RESULT_TYPE_WARNING | RESULT_ABORT_ACTION;

		return SuperClass::insert(index, source);
	}

	const NECodeType& NECodeSet::getCodeType() const
	{
		return _type;
	}

	void NECodeSet::release()
	{
		_type.release();

		return SuperClass::release();
	}

	NECodeSet& NECodeSet::operator=(const NECodeSet& source)
	{
		if(this == &source) return *this;

		return _assign(source);
	}

	NECode& NECodeSet::getElement(type_index index)
	{
		return SuperClass::getElement(index);
	}

	NECodeSet& NECodeSet::_assign(const ThisClass& source)
	{
		_type = source._type;

		return *this;
	}
}