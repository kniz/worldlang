//	--------------------------------------------------------------------------------
//	클래스명:	NEShortCut
//	설명	:	NEShortCut 기능을 위해서 Node의 주소를 NETList의 형태로 관리하는 클래스.
//	관계	:	기반클래스.	NETList<T*, false>
//	특성	:	NEShortCut 기능이란?
//					:	노드는 코드라고 하는 카테고리를 여러개 지니고 있다.
//						셀렉터는 이 코드를 통해서 노드를 검색하게 되는데, 단순히 배열로
//						노드셋을 구성하면 코드 탐색을 하는 수 밖에 없다. 
//						그러나, 만약 코드별로 노드를 모아두고 관리한다면 탐색에 들어가는
//						시간이 매우 줄어들 것이다.
//						숏컷은 그 아이디어에서 착안한 것으로, 인스턴스를 코드별로 관리하는
//						게 아니라 노드의 주소를 관리한다.
//	알고리즘:	
//	사용방법:	
//	메모	:	
//	히스토리:	2011-07-07	이태훈	개발 완료	
//	---------------------------------------------------------------------------------
#pragma once 

#include "../NETList/NETList.hpp"
#include "../NENode/NENode.hpp"
#include "../NETShallower/NETShallower.hpp"

namespace NE
{
	template
	class NE_DLL NETShallower<NETArray<NENode>>;
	typedef NETShallower<NETArray<NENode>> NEShortCut;
}