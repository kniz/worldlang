#include "NEString.hpp"
#include "../NEWString/NEWString.hpp"
#include "../NEStringList/NEStringList.hpp"

namespace NE
{
	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEString::NEString()
		: NEArrayTemplate()
	{

	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEString::NEString(LPCSTR source)
		: NECharSet()
	{
		from(source);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEString::NEString(LPCWSTR source)
		: NECharSet()
	{
		from(source);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEString::NEString(const NEString& source)
		: NECharSet(source)
	{

	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEString::NEString(const NECharSet& source)
		: NECharSet(source)
	{

	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-08-09	이태훈	작성
	//	---------------------------------------------------------------------------------
	NE_DLL NEString::NEString(const NEWString& source)
		: NECharSet()
	{
		from(source.toCharPointer());
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-08-09	이태훈	작성
	//	---------------------------------------------------------------------------------
	NE_DLL NEString::NEString(const NEWCharSet& source)
		: NECharSet()
	{
		from(&source[0]);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	//	bool도 이쪽으로 온다
	NE_DLL NEString::NEString(const type_int data)
		: NECharSet()
	{
		from(data);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEString::NEString(const type_double data)
		: NECharSet()
	{
		from(data);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEString::NEString(const type_char data)
		: NEArrayTemplate()
	{
		from(data);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-08-09	이태훈	작성
	//	---------------------------------------------------------------------------------
	NE_DLL NEString::NEString(const type_wchar data)
		: NEArrayTemplate()
	{
		from(data);
	}


	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEString::NEString(const type_bool data)
		: NEArrayTemplate()
	{
		from(data);
	}

	NEString::NEString(const type_uint data)
		: NEArrayTemplate()
	{
		from(data);
	}

	NEString::NEString(const type_uchar data)
		: NEArrayTemplate()
	{
		from(data);
	}

	NEString::NEString(const type_int64 data)
		: NEArrayTemplate()
	{
		from(data);
	}

	NEString::NEString(const type_uint64 data)
		: NEArrayTemplate()
	{
		from(data);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NE_DLL NEString::~NEString()
	{

	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEString NE_DLL NEString::operator+(const NEString& source) const
	{
		//	pre:
		if(source._length <= 0)	return NEString(*this);
		if(_length <= 0) return NEString(source);

		//	main:				
		NEString buffer;			
		buffer.create(_length - 1 + source._length); // -1 하는 이유는 널문자를 빼내기 위해서
		buffer.push(*this);
		buffer.pop(); // 널문자 빼내기
		buffer.push(source);

		// main
		return buffer;
	}	



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	const NEString NE_DLL &NEString::operator+=(const NEString& source)
	{			
		if(source._length <= 0) return *this;
		if(_length <= 0) return operator=(source);

		NEString buffer = *this;			
		create(_length - 1 + source._length); // -1 하는 이유는 널문자를 빼내기 위해서
		push(buffer);
		pop();
		push(source);

		return *this;
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	생성자를 통해서 변수형 -> String으로 변환되게 했으나, 그 역은 위험하다.
	//				잘못했다간 형변환 모호성 오류가 발생할 여지가 크다.
	//				그래서 String -> 다른 변수형은 따로 함수를 제작한다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------

	int NE_DLL NEString::toInt() const 
	{
		if(getLength() <= 0) return 0;
		
		return atoi( &getElement(0) );
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	double NE_DLL NEString::toDouble() const
	{
		if(getLength() <= 0) return 0.0;
		
		return atof( &getElement(0) );
	}



	//	---------------------------------------------------------------------------------
	//	설명	:	0일때 false, 0이외의 값은 모두 true로 처러하는 C++의 특성을 고려해서,
	//				문자열값이 0일 경우만 false를 리턴한다.
	//	동작조건:
	//	메모	:
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	//	
	bool NE_DLL NEString::toBoolean() const
	{
		//	pre:
		if(!_size) return false;



		//	main:
		if( operator==( NEString(_T("true")) ) == true)		return true;
		else if( operator==( NEString(_T("TRUE")) ) == true) return true;



		//	post:
		return false;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	char NE_DLL *NEString::toCharPointer()
	{
		return &getElement(0);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	const char NE_DLL * const NEString::toCharPointer() const
	{
		return &getElement(0);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEType::Type NE_DLL NEString::getType() const
	{
		return NEType::NESTRING;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	type_result NE_DLL NEString::isValid() const 
	{
		// 타입코드 확인:
		if( ! isSubClassOf(NEType::NESTRING)) return RESULT_TYPE_ERROR | RESULT_INVALID_DATA;

		return NEArrayTemplate::isValid();
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEObject NE_DLL &NEString::clone() const
	{
		return *(new NEString(*this));
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	NEString NE_DLL operator+(LPCSTR source1, const NEString& source2) 
	{
		NEString temp(source1);
		temp += source2;

		return NEString(temp);
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-08-09	이태훈	작성
	//	---------------------------------------------------------------------------------
	void NEString::_convertString(LPCWSTR source)
	{
		//	pre:		
		if(!source) return release();


		
		//	main:
		//		길이 계산:
		int size_with_null = WideCharToMultiByte(CP_ACP, 0, source, -1, NULL, NULL, NULL, NULL);
		if(size_with_null <= 0) return release();
		//			버퍼 생성:
		create(size_with_null);
		//		버퍼에 변환된 데이터 삽입:
		WideCharToMultiByte(CP_ACP, 0, source, -1, _data, size_with_null,  NULL, NULL);
		_length = size_with_null;
	}

	bool NE_DLL NEString::operator==(const NEString& source) const
	{
		if(this == &source) return true;
		
		return NECharSet::operator==(source);
	}

	bool NE_DLL NEString::operator!=(const NEString& source) const
	{
		return !(operator==(source));
	}

	type_result NE_DLL NEString::split(const NEString& delimiter, NE_OUT NEStringSet& buffer_from_outside) const
	{
		//	pre:
		if(delimiter.getLength() <= 0 || delimiter == "")
		{
			//KERNAL_ERROR(" : ")
			return RESULT_TYPE_WARNING | RESULT_ABORT_ACTION;
		}
		if( ! &buffer_from_outside) return RESULT_TYPE_ERROR;
		
		
		
		//	main:
		//		초기화:
		//			list				:	몇개의 구분자로 나뉘어질지 모르므로 크기가 고정되지 않는 리스트를 임시 버퍼로 사용한다.
		//			split_start_index	:	원본 문자열에서 파싱이 시작되는 시작 위치
		//			split_end_index		:	파싱이 끝나는 위치. start부터 end까지 된다.(2,2일경우, 1글자가 된다)
		//			delimiter_length	:	구분자의 길이. 널문자 포함이다.
		//			delimiter_last_index:	구분자의 마지막 인덱스.
		NEStringList list;		
		type_index split_start_index = 0;
		type_count	delimiter_length = delimiter.getLength() - 1,	// -1 null문자를 뺀다.
					delimiter_last_index = delimiter_length - 1;	
		//		루핑:
		int n=0;
		while(true)
		{
			//		타겟팅:
			type_index split_end_index = n - 1;
			//		추출:
			NEString& extracted = extract(n, n + delimiter_last_index); // 널문자가 뒤에 붙어서 나온다.
			//		추출한 단어가 구분자일 경우:
			if(extracted == delimiter)
			{	//		구분자 이전까지의 단어를 buffer에 추가:	split_start_index는 아직 추가하지않은 단어의 시작 인덱스. start_index부터 추가해야한다.
				//			추가할 단어가 있다면:
				if(split_start_index <= split_end_index)
					list.push( extract(split_start_index, split_end_index) );
					
				//		검색 위치 조정:
				//			n : 다음에 탐색할 위치
				//			n에 왜 delimiter_last_index를 더하는가:
				//				찾아낸 delimiter의 길이만큼은 탐색하지 않아도 되기 때문이다.
				//				예를들어, helloSANTAworld에서 SANTA가 delimiter일 경우, 결과물은
				//				hello, world가 나와야 한다.
				//				이게 가능한 이유는, 5번 인덱스까지 탐색했을때 SANTA 구분자를 인식하고
				//				바로 w인 10번 인덱스로 점프 했기 때문이다.
				//
				//			split_start_index에 왜 n+1을 할당하는가:
				//				n+1은 현재가 아닌 "다음 탐색 위치"를 의미한다.
				//				n은 현재 탐색위치(즉, n) + delimiter_last_index 이므로 구분자의 마지막
				//				위치를 의미한다. (위의 helloSANTAworld로 보면, 'A'
				//				그래서 +1 을 해서 다음 위치로 파싱 시작 위치로 지정한다.				
				n += delimiter_last_index;
				split_start_index = n+1; 
			}
			//		탐색이 끝났다면:
			//			단어 추가:	맨 끝에는 구분자가 있는것과 마찬가지다.
			if(n >= getLengthLastIndex()-1) // 널문자를 빼기 위해 -1을 한다.
			{
				if(split_start_index <= n)
					//	왜 getLengthLastIndex() - 1을 하는가:
					//		lastIndex가 널문자이기 때문이다.
					list.push( extract(split_start_index, getLengthLastIndex()-1) );
					
				break;
			}
			
			n++;
		}
	
	
	
		//	post:	
		buffer_from_outside.create(list.getLength());
		NEStringList::Iterator* iterator = list.getIterator(0);
		while(iterator)
		{
			buffer_from_outside.push(iterator->getValue());
						
			iterator = iterator->getNext();
		}
		
		return RESULT_SUCCESS;	
	}

	NEString NE_DLL NEString::extract(type_index start_index, type_index end_index) const
	{
		//	pre:
		if(getLengthLastIndex() < 0)			return "";
		if(end_index > getLengthLastIndex())	end_index = getLengthLastIndex();
		if(start_index > end_index)				return "";
		while( end_index >= 0 && ! getElement(end_index))
			end_index--;
		if(end_index < 0 )						return "";
		if( ! &getElement(end_index))			return "";
		
						
		//	main:
		type_count length = end_index - start_index + 1;
		if(length <= 0) return "";

		NEString buffer;
		buffer.create(length + 1);
		
		for(int n=start_index; n <= end_index ;n++) // 조건식이 n <= 임에 주의하라
			buffer.push(getElement(n));
			
					
		//	post:
		if(buffer[buffer.getLengthLastIndex()] != '\0')
			buffer.push('\0');
			
		return buffer;		
	}

	const NEString NE_DLL &NEString::operator=(const NEString& source)
	{
		if(this == &source) return *this;

		NECharSet::operator=(source);

		return *this;
	}

	const NEString& NEString::_assign(LPCSTR source)
	{
		if(toCharPointer() == source) return *this;
		
		type_index length_with_null = strlen(source) + 1;

		create(length_with_null);

		for(type_index n = 0; n < length_with_null ;n++)
			push( *(source + n) );
			
		return *this;
	}

	void NEString::from(const type_int data)
	{
		char buffer[20];
		sprintf_s(buffer, 20, "%d", data);

		from(buffer);
		
	}

	void NEString::from(LPCSTR data)
	{
		_assign(data);
	}

	void NEString::from(LPCWSTR data)
	{
		_convertString(data);
	}

	void NEString::from(const type_double data)
	{
		char buffer[20] = {0, };
		sprintf_s(buffer, 20, "%lf", data);

		from(buffer);
	}

	void NEString::from(const type_bool data)
	{
		if(data)
			from("true");
		else
			from("false");
	}

	void NEString::from(const type_uint data)
	{
		char buffer[20] = {0, };
		sprintf_s(buffer, 20, "%u", data);

		from(buffer);
	}

	void NEString::from(const type_uchar data)
	{
		char buffer[20] = {0, };
		sprintf_s(buffer, 20, "%u", (type_uint) data);

		from(buffer);
	}

	void NEString::from(const type_wchar data)
	{
		//	버퍼 생성:
		wchar_t buffer[2] = {0, };
		buffer[0] = data;
		//	버퍼로 데이터 삽입:
		_convertString(buffer);
	}

	void NEString::from(const type_char data)
	{
		create(2); // null 문자가 뒤에 붙는다

		push(data);
		push(0);	//	널문자. length를 2로 만들어야 하기 때문에 여기서 굳이 push를 하는 것이다.
	}

	void NEString::from(const type_int64 data)
	{
		char buffer[21] = {0, };
		sprintf_s(buffer, 21, "%I64d", data);

		from(buffer);
	}

	void NEString::from(const type_uint64 data)
	{
		char buffer[21] = {0, };
		sprintf_s(buffer, 21, "%I64u", data);

		from(buffer);
	}

	NE::NEIntSet NEString::find(const NEString& sample) const
	{
		//	pre:
		NEIntSet to_return;
		type_count sp_len = sample.getLength() - 1;	//	without null
		if(	sp_len <= 0			||
			getLength() < sp_len) 
			return to_return;
	

		//	main:
		type_index end_index = sp_len-1;
		NEListTemplate<int> bucket;
		for(int n=0; n < getLength() ;n++)
			if(extract(n, n + end_index) == sample)
				bucket.push(n);


		//	post:
		to_return.create(bucket.getLength());
		for(NEListTemplate<int>::Iterator* itr=bucket.getIterator(0); itr ;itr=itr->getNext())
			to_return.push(itr->getValue());

		return to_return;
	}

}