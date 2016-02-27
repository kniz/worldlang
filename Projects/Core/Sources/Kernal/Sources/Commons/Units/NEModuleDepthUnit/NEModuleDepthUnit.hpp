//	---------------------------------------------------------------------------------
//	클래스명:	
//	설명	:	주어진 모듈셋을 몇번 인덱스까지 탐색했는지에 대한 정보를 관리한다.
//	관계	:	기반클래스.	NEObject
//	특성	:	중첩클래스
//	알고리즘:	모듈셋포인터와 인덱스를 사용해서, 모듈셋포인터가 가리키는 모듈셋의
//				몇번째 인덱스까지 검색했다는 것을 기록한다.
//	사용방법:	1.	getModule()				:	모듈을 가져온다.
//				3.	isThereAnyModule()		:	현재 인덱스가 주어진 모듈셋의 마지막
//												모듈인가?
//	메모	:	
//	히스토리:	2011-07-07	이태훈	개발 완료	
//				2011-09-28	이태훈	common 객체로 카테고리 변경
//	---------------------------------------------------------------------------------
#pragma once

#include "../../../Modules/NEObject/NEObject.hpp"

namespace NE
{
	class NEModule;
	class NEModuleCodeSet;

	class NE_DLL NEModuleDepthUnit : public NEObject
	{
		enum
		{
			FROM_MODULE_CODE_SET_OF_NODE = -2
		};
		//	friend 선언:
		template <typename NodeSelector, NEType::Type type> friend class NETModuleSelector;
		//	생성자:
	public:
		NEModuleDepthUnit();
		NEModuleDepthUnit(type_index new_key_index);
		NEModuleDepthUnit(const NEModuleDepthUnit& source);

		//	소멸자:
	public:
		virtual ~NEModuleDepthUnit();

		//	연산자 중첩:
	public:
		bool operator==(const NEModuleDepthUnit& source) const;
		bool operator!=(const NEModuleDepthUnit& source) const;
		const NEModuleDepthUnit& operator=(const NEModuleDepthUnit& source);


		//		상속:
		//			NEObject:
	public:
		virtual void release();
		virtual type_result isValid() const;
		virtual NEObject& clone() const;
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
		virtual NEType::Type getType() const;

		//	내부함수:
	private:
		const NEModuleDepthUnit& _assign(const NEModuleDepthUnit& source);

		//	멤버변수:
	public:
		//	접근시 바로쓰면 안되고, 가공이 필요하기때문에 private로 접근한다.
		type_index key_index_to_be_moduleset; // 모듈셋은 노드의 모듈셋과 BLOCK, IF모듈의 모듈셋의 주소가 들어가게 된다
		type_index module_index; // 들어있는 모듈셋의 인덱스 값.
	};
}
