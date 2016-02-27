namespace NE
{
	template <typename T, NEType::Type type>
	NETKey<T, type>::NETKey(const T& source, const NETString& keyname)
		: SuperClass(keyname), _value(source)
	{

	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, NEType::Type type>
	NETKey<T, type>::NETKey(const NETKey<T, type>& source)		
		: SuperClass(source)
	{
		_value = source._value;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, NEType::Type type>
	NETKey<T, type>::NETKey(const NEKey& source)
		: SuperClass(source.getName())
	{

	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, NEType::Type type>
	NETKey<T, type>::~NETKey() 
	{
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, NEType::Type type>
	const NETKey<T, type>  & NETKey<T, type>::operator=(const NETKey<T, type>& source)
	{
		if(this == &source) return *this;

		SuperClass::operator=(source);
		_value = source._value;
		return *this;
	}


	template <typename T, NEType::Type type>
	T& NETKey<T, type>::getValue()
	{
		return _value;
	}

	template <typename T, NEType::Type type>
	const T& NETKey<T, type>::getValue() const
	{
		return _value;	
	}


	template <typename T, NEType::Type type>
	void NETKey<T, type>::releaseValue()
	{
		_value = T();
	}

	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, NEType::Type type>
	void  NETKey<T, type>::release() 
	{
		SuperClass::release();

		releaseValue();
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, NEType::Type type>
	NEBinaryFileSaver& NETKey<T, type>::serialize(NEBinaryFileSaver& saver) const  
	{
		SuperClass::serialize(saver);

		return saver << _value;
	}



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, NEType::Type type>
	NEBinaryFileLoader& NETKey<T, type>::serialize(NEBinaryFileLoader& loader)
	{
		SuperClass::serialize(loader);

		return loader >> _value;
	}	



	//	---------------------------------------------------------------------------------
	//	히스토리:	2011-07-07	이태훈	개발 완료
	//	---------------------------------------------------------------------------------
	template <typename T, NEType::Type type>
	NEType::Type NETKey<T, type>::getType() const
	{
		return type;
	}



	template <typename T, NEType::Type type>
	NEObject& NE::NETKey<T, type>::clone() const
	{
		return *(new ThisClass(*this));
	}
}