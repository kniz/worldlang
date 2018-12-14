#pragma once

#define WRD_INITIATE_CLASS(klass) Initiator<klass> __##klass;
#define WRD_TESTCASE(name, method)	\
	namespace wrd	\
	{	\
		namespace ut	\
		{	\
			class name : public TestCase	\
			{	WRD_INHERIT(name, TestCase)	\
			public:	\
				virtual WRD_LAZY_METHOD(std::string, getName, const, #name)	\
			protected:	\
				virtual std::string _onTest()	\
				{	\
					WRD_UNWRAP method	\
				}	\
			};	\
			Initiator<name> __##name; \
		}	\
	}