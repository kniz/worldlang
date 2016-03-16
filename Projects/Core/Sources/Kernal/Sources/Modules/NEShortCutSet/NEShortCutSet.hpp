//	---------------------------------------------------------------------------------
//	클래스명:	NEShortCutSet
//	설명	:	복수의 NEShortCut를 관리하고, 셀렉터들에게 friend선언을 하도록 만들어진
//				클래스.
//	관계	:	기반클래스.	NETArray<NEShortCut>
//	특성	:	
//	알고리즘:	
//	사용방법:	NETArray를 참고하라.
//	메모	:	
//	히스토리:	2011-07-12	이태훈	개발 완료	
//	---------------------------------------------------------------------------------
#pragma once

#include "../../Commons/Interfaces/NEEnlistable/NEEnlistable.hpp"
#include "../NEShortCut/NEShortCut.hpp"

namespace NE
{
	template 
	class NE_DLL NETArray<NEShortCut, false, NEShortCut>;

	class NE_DLL NEShortCutSet : public NETArray<NEShortCut, false, NEShortCut>, public NEEnlistable
	{
	public:
		typedef NETArray<NEShortCut, false, NEShortCut> SuperClass;
		typedef NEShortCutSet ThisClass;
		
		friend class NEEnlistableManager;

	public:
		NEShortCutSet();
		NEShortCutSet(const NECodeType& type);
		NEShortCutSet(const ThisClass& source);

	public:
		virtual ~NEShortCutSet();

	public:
		ThisClass& operator=(const ThisClass& source);
		bool operator==(const ThisClass& source) const;
		bool operator!=(const ThisClass& source) const;

	public:
		const NECodeType& getCodeType() const;

	public:
		virtual NEObject& clone() const;
		virtual void release();
		virtual NEType::Type getType() const;
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);

	public:
		virtual type_result _enlist(NENode& node, type_index real_index);
		virtual type_result _unlist(NENode& node, type_index real_index);

	private:
		type_result _enlist(NENode& node, const NECode& code, type_index real_index);
		type_result _unlist(NENode& node, const NECode& code, type_index real_index);

	private:
		NECodeType _type;
	};
}