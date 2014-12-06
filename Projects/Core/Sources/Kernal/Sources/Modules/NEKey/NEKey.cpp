#pragma once

#include "NEKey.hpp"

namespace NE
{
	NEKey::NEKey(const NETString& new_keyname)
		: _name(new_keyname), _owner(0x00)
	{

	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEKey::NEKey(const NEKey& source)
		: NEUnit(source), _owner(0x00)
	{
		_name = source._name;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEKey::~NEKey() 
	{
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	const NEKey NE_DLL &NEKey::operator=(const NEKey& source)
	{
		assign(source);

		return *this;
	}



	const NEKey NE_DLL &NEKey::operator+=(const NEKey& source)
	{
		add(*this, source);

		return *this;
	}



	const NEKey& NEKey::operator*=(const NEKey& source)
	{
		multiply(*this, source);

		return *this;
	}



	const NEKey& NEKey::operator/=(const NEKey& source)
	{
		multiply(*this, source);

		return *this;
	}


	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	bool NE_DLL NEKey::operator==(const NEKey& source) const
	{
		return isEqualTo(source);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	bool NE_DLL NEKey::operator!=(const NEKey& source) const
	{
		return !(operator==(source));
	}

	bool NE_DLL NEKey::operator<(const NEKey& source) const
	{
		return isLower(source);
	}

	bool NE_DLL NEKey::operator<=(const NEKey& source) const
	{
		return isEqualTo(source) || isLower(source);
	}

	bool NE_DLL NEKey::operator>(const NEKey& source) const
	{
		return ( ! isLower(source)) && ( ! isEqualTo(source));
	}

	bool NE_DLL NEKey::operator>=(const NEKey& source) const
	{
		return ( ! isLower(source));
	}

	bool NE_DLL NEKey::isLower(const NEKey& source) const
	{
		return false;
	}

	NETString& NEKey::getName()
	{
		return _name;
	}

	const NETString& NEKey::getName() const
	{
		return _name;
	}

	type_result NEKey::assign(const NEKey& source)
	{
		//_name = source._name;	정책상 키의 이름은 assign 되어서는 안된다.

		return RESULT_SUCCESS;
	}

	type_result NEKey::add(NEKey& result, const NEKey& operand2) const
	{
		return RESULT_SUCCESS | RESULT_ABORT_ACTION;
	}
	type_result NEKey::multiply(NEKey& result, const NEKey& operand2) const
	{
		return RESULT_SUCCESS | RESULT_ABORT_ACTION;
	}
	type_result NEKey::makeReciprocal()
	{
		return RESULT_SUCCESS | RESULT_ABORT_ACTION;
	}
	type_result NEKey::negate()
	{
		return RESULT_SUCCESS | RESULT_ABORT_ACTION;
	}

	bool NEKey::isEqualTo(const NEKey& source) const
	{
		return true;//_name == source._name;	값만을 비교한다.
	}

	void NEKey::release()
	{
		_name.release();
	}

	NEBinaryFileSaver& NEKey::serialize(NEBinaryFileSaver& saver) const
	{
		return saver << _name;
	}

	NEBinaryFileLoader& NEKey::serialize(NEBinaryFileLoader& loader)
	{
		return loader >> _name;
	}

	type_result NEKey::isValid() const
	{
		return _name.isValid();
	}

	NEKeyCodeSet& NEKey::getOwner()
	{
		return *_owner;
	}

	const NEKeyCodeSet& NEKey::getOwner() const
	{
		return *_owner;
	}
}

