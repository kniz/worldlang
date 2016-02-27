//	---------------------------------------------------------------------------------
//	클래스명:	NENodeList
//	설명	:	복수의 NENode를 Create, Push가 가능하도록 숏컷을 유지하는 클래스.
//	관계	:	기반클래스.	NETList<NENode>
//	특성	:	push, pop에서 자동으로 NodeManager의 숏컷셋을 유지한다.
//	알고리즘:	
//	사용방법:	NETList를 참고하라.
//	메모	:	
//	히스토리:	2011-07-21	이태훈	개발 완료	
//	---------------------------------------------------------------------------------
#pragma once

#include "../NETList/NETList.hpp"
#include "../NENode/NENode.hpp"

namespace NE
{
	template
	class NE_DLL NETList<NENode, false, NEType::NENODE_LIST>;
	typedef NETList<NENode, false, NEType::NENODE_LIST> NENodeList;
}
