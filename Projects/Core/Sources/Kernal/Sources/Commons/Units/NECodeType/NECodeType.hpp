//	isFixedType:
//		FixedType은 이 인스턴스는 반드시 이 CodeType이 유지가 되어야 한다는 걸
//		의미한다.
//		Script Type이라고 하더라도, Fixed 선언이 되어있지 않으면 Target의 Type
//		으로 처리될 가능성이 존재한다.
//		하지만, 양쪽 모두 Fixed이며, 서로 다른 타입일 경우에는 연산이 성립되지
//		않는다.
//		Fixed는 Unique 속성으로써 다른 인스턴스에 할당하거나 할당될 수 없다.
//
//	FixedType간 연산 성립 테이블:
//		This = Source의 연산의 경우,
//		+===================================================+
//		|	This \ Source	|	Flexible	|	Fixed		|
//		|====================================================
//		|	Flexible		|	Source's	|	Source's	|
//		|---------------------------------------------------|
//		|	Fixed			|	Mine		|	Mine		|
//		|====================================================
//		*1)	단, Type이 같다면 성립한다.
//
//	operator+, +=, -=, -, *, *=, /=의 연산은 적용이 되면 안된다:
//
#pragma once

#include "../../../Modules/NEObject/NEObject.hpp"

namespace NE
{
	class NE_DLL NECodeType : public NEObject
	{
	public:
		typedef NEObject SuperClass;
		typedef NECodeType ThisClass;

	public:
		enum CodeType
		{
			CODETYPE_START = -1,
			UNDEFINED = 0,
			SCRIPT,
			NAME,
			GROUP,
			PRIORITY,
			RECENT,
			ME,
			ALL,
			CODETYPE_END
		};

	public:
		NECodeType()
			: SuperClass(), _is_type_fixed(false)
		{
			ThisClass::release();
		}
		NECodeType(CodeType new_codetype)
			: SuperClass(), _codetype(new_codetype), _is_type_fixed(true)
		{

		}
		NECodeType(CodeType new_codetype, bool is_type_fixed)
			: SuperClass(), _codetype(new_codetype), _is_type_fixed(is_type_fixed)
		{

		}
		NECodeType(const ThisClass& rhs)
			: SuperClass(rhs), _is_type_fixed(rhs._is_type_fixed)
		{
			_assign(rhs);
		}

	public:
		ThisClass& operator=(const ThisClass& source)
		{
			if (this == &source) return *this;

			return _assign(source);
		}
		bool operator==(const ThisClass& source) const
		{
			return	_codetype == source._codetype			&&
				_is_type_fixed == source._is_type_fixed	;
		}

	public:
		CodeType getCodeType() const {
			return _codetype;
		}
		type_result setCodeType(CodeType new_one) {
			if (isTypeFixed())
				return RESULT_SUCCESS | RESULT_ABORT_ACTION;

			_codetype = new_one;
			return RESULT_SUCCESS;
		}
		bool isTypeFixed() const {
			return _is_type_fixed;
		}
		bool isAcceptableType(const NECodeType& source) const
		{
			return  ! isTypeFixed()			||
				! source.isTypeFixed()	||
				operator==(source)		;
		}

	public:
		virtual void release() {
			//	_is_type_fixed = false	는 UNIQUE 속성이므로 변경할 수 없다
			if(!_is_type_fixed)
				_codetype = UNDEFINED;
		}
		virtual type_result isValid() const
		{
			if(	_codetype <= CODETYPE_START ||
				_codetype >= CODETYPE_END	)
				return RESULT_TYPE_WARNING;

			return RESULT_SUCCESS;
		}
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const
		{
			return saver << static_cast<type_int>(_codetype) << _is_type_fixed;
		}
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader)
		{
			type_int buffer = 0;
			loader >> buffer;
			_codetype = CodeType(buffer);

			return loader >> _is_type_fixed;
		}
		virtual NEObject& clone() const
		{
			return *(new ThisClass(*this));
		}
		virtual NEType::Type getType() const
		{
			return NEType::NECODE_TYPE;
		}

	private:
		ThisClass& _assign(const ThisClass& source)
		{
			setCodeType(source._codetype);

			return *this;
		}

	public:
		CodeType _codetype;
		bool _is_type_fixed;
	};
}
