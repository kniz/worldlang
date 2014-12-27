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



	NE_DLL NECodeSet::NECodeSet(const NECode& single_code)
		: SuperClass(1), _type(single_code)
	{
		push(single_code);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NECodeSet::NECodeSet(const NECodeSet& source)
		: SuperClass(source)
	{
		_assign(source);
	}



	NECodeSet::NECodeSet(const NECodeType::CodeType& initial_type)
		: SuperClass(), _type(initial_type)
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
		if(find(source) != NE_INDEX_ERROR) return RESULT_TYPE_WARNING | RESULT_ABORT_ACTION;

		return SuperClass::setElement(index, source);		
	}

	type_index NECodeSet::insert(type_index index, const NECode& source)
	{		
		if( ! getCodeType().isAcceptableType(source)) return NE_INDEX_ERROR;
		NECodeType new_type(_type);
		new_type = source;
		NECode to_insert(source.getCode(), new_type.getCodeType(), new_type.isTypeFixed());

		if(find(to_insert) != NE_INDEX_ERROR) return RESULT_TYPE_WARNING | RESULT_ABORT_ACTION;

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

		SuperClass::operator=(source);

		removeDuplicated();

		return _assign(source);
	}

	NECodeSet& NECodeSet::_assign(const ThisClass& source)
	{
		_type = source._type;

		return *this;
	}

	type_count NECodeSet::removeDuplicated()
	{
		type_count count_for_removed = 0;

		for(int trg_n=0; trg_n < getLength() ;trg_n++)
		{
			const NECode& trg = getElement(trg_n);

			for(int src_n=trg_n+1; src_n < getLength();)
			{
				if(getElement(src_n) == trg)
				{
					remove(src_n);
					count_for_removed++;
				}
				else
					src_n++;
			}
		}

		return count_for_removed;
	}
}