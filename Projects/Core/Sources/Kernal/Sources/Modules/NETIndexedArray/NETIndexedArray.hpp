//	---------------------------------------------------------------------------------
//	Ŭ������:	NETIndexedArray
//	����	:	Array�� ���·� �����͸� �����ϴ� Ŭ����.
//	����	:	���Ŭ����.			NETReservedCollector
//	Ư��	:	�迭�� Ư���� �״�� �����Ѵ�. �� ������Ʈ�� �߰�/����/������
//				���ϰ� ū �ݸ�, "�˻�"�� ���ϴ�.//				
//	�˰�����:	���� �����͸� �������� ���, �ش� �����ͷκ��� ���󺹻�������� clone
//				�� ȣ���ؼ� DeepCopy �Ѵ�.
//	�����:	���� ���
//					:	���ø� ���� Type�� ����
//							���� 1.	NEObject�� ����ؾ��Ѵ�. 
//									NEObject::clone()�� ����ϱ� �����̴�.
//							���� 2. 
//				bool pointerUseNewInstance��?
//					:	false�϶� Type�� �������� ���, �����Ͱ� ���ο� �ν��Ͻ��� ����Ű����
//						�����ʰ�, shallowcopy���� ����ϰڴٴ� �ǹ̴�.
//						true�϶��� NEPointerList.hpp�� �����϶�.
//				�⺻������ NETCollector�� �Լ��� ��� ��밡���ϴ�. (���� �� ��)
//				�⺻ �������̽�
//					1. push(Type*)			:	�������� ���·� ������ �����ϴ�.
//					2. pushFront(Type*)	:	�������� ���·� ������ �����ϴ�.
//					3. push(NETList&)	:	����Ʈ ���θ� ��°�� �����Ѵ�.
//					4. pushFront(NETList&)
/*
				����(Outside)�� ����(Inside) Ÿ���� ���� �ٸ� Collector ���� ���:
					1. Ÿ���� �ٸ� ���, NETIndexedArray�� �߻�Ŭ�����μ� ����ȴ�.
					2. ������ �Լ����� �Ļ�Ŭ�������� ä�����Ѵ�.
						1. ���������
						2. virtual release
						3. virtual insert
						3. virtual remove
						4. virtual getElement(index) const
						5. virtual getElement(index)
						6. virtual setElement
						7. virtual clone
						8. virtual find
*/
//	�޸�	:	
//	�����丮:	2013-01-10	������	���� �Ϸ�	
//	---------------------------------------------------------------------------------
#pragma once

//	include:
#include "../NEOccupiedSet/NEOccupiedSet.hpp"
#include "../NETReservedCollector/NETReservedCollector.hpp"
#include "../../Commons/Interfaces/NESpecifiedInsertable/NESpecifiedInsertable.hpp"

namespace NE
{
	template <typename Type, bool pointerUseNewInstance = false, NEType::Type type = NEType::NEINDEXED_ARRAY_TEMPLATE>
	class NETIndexedArray : public NETReservedCollector<Type>, public NESpecifiedInsertable<Type>
	{	
		typedef NETIndexedArray<Type, pointerUseNewInstance, type> ThisClass;

		//	������:
	public:
		NETIndexedArray();
		NETIndexedArray(type_count size);
		NETIndexedArray(const ThisClass& source);

		//	�Ҹ���:
	public:
		virtual ~NETIndexedArray();

		//	������ ��ø:
	public:
		const ThisClass& operator=(const ThisClass& source); 
		ThisClass operator+(const ThisClass& source) const;
		bool operator==(const ThisClass& source) const;
		bool operator!=(const ThisClass& source) const;
		const ThisClass& operator+=(const ThisClass& source);

		//	�������̽�:
		//		������:
	public:
		const NEOccupiedSet& getOccupiedSet() const;

		//		���:
		//			NESpecifiedInsertable:
	public:
		virtual type_index insert(type_index index, const Type& source);
		virtual type_index remove(type_index index);
		//			NETReservedCollector:
	public:
		virtual type_result resize(type_index new_size);
		virtual type_result create(type_count new_size);
		//			NETCollector:
	public:		
		virtual Type& getElement(type_index index);
		virtual const Type& getElement(type_index index) const;
		virtual type_result setElement(type_index index, const Type& source);
		virtual type_index push(const Type& source);
		virtual type_index pop();		
		virtual type_index find(const Type& source) const;
		//			NEObject:
	public:
		virtual NEObject& clone() const;
		virtual type_result isValid() const;
		virtual void release();
		virtual NEBinaryFileLoader& serialize(NEBinaryFileLoader& loader);
		virtual NEBinaryFileSaver& serialize(NEBinaryFileSaver& saver) const;
		virtual NEType::Type getType() const;
		
		//		���� �������̽�:
	public:
		type_index pushFront(const Type& source);
		type_index popFront();
		type_result push(const ThisClass& source);
		type_result pushFront(const ThisClass& source);
		bool isEqualSizeAndElement(const ThisClass& source) const;
		bool isEqualElement(const ThisClass& source) const;

	protected:
		type_index _searchIndex(bool by_decreasing, bool target_is_occupied) const;

		//	�����Լ�:
	private:
		const ThisClass& _assign(const ThisClass& source);
		void _release();

		//	�������:
	protected:
		Type*	_data;
		NEOccupiedSet _occupiedset;
	};
}

#include "NETIndexedArray.inl"
#include "NETPointerIndexedArray.hpp"
#include "NETPointerIndexedArrayUsingPolyMorphism.hpp"