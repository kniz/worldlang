//	---------------------------------------------------------------------------------
//	Name			:	ClassMacro.hpp
//	Comments		:	
//	Relationships	:	
//	Usage			:	
//	Memo			:	
//	Author			:	2016-02-13	kniz
//	---------------------------------------------------------------------------------
#ifdef NE_NATIVE_DEFINE_TEMPLATE_PARAMETERS
#	undef NE_NATIVE_DEFINE_TEMPLATE_PARAMETERS
#endif

#pragma once

#include "../../Includes/Includes.hpp"

//	template class forward declaration:
//		This macro can be included far earlier than derived class of NETClassBase below.
//		See include section of the NETClassBase.hpp file.
namespace NE
{
	class NE_DLL NEClassBase;

	template <typename T>
	class NETInterface;

	template <typename T>
	class NETConcreteClass;

	template <typename T>
	class NETUnknownMetaClass;
}

//	Class Macros:
//		we're providing fully functioned macro only. please don't use macros which have NATIVE 
//		word on its name. that's internal.
//		when you need partial part of these, please code it explicitly for readibility of other 
//		users.
//		we're afraid that too many macros that user should have to remember exist on codes.
//
//		Essentials:
//			Super, MetaClass typedefs are essentials that each classes should contain them in 
//			order to support RTTI. 
//			by defining these, users can template metaclass with NETClass without consideration 
//			that it's a ADT or concrete class.
#define NE_NATIVE_DECLARE_INLINEY(NAME, SUPER, METACLASS)	\
	public:													\
	typedef NAME			This;						\
	typedef SUPER			Super;						\
	typedef METACLASS<NAME>	MetaClass;					\
	\
	public:													\
	virtual const NEClassBase& getClass() const			\
{													\
	return getClassStatically();					\
}													\
	\
	public:													\
	static const NEClassBase& getClassStatically()		\
{													\
	static NETClass<NAME> inner;					\
	\
	return inner;									\
}													\
	private:

#define NE_NATIVE_DECLARE_ONLY(NAME, SUPER, METACLASS)	\
	public:												\
	typedef NAME			This;					\
	typedef SUPER			Super;					\
	typedef METACLASS<NAME>	MetaClass;				\
	\
	public:												\
	virtual const NEClassBase& getClass() const;	\
	\
	public:												\
	static const NEClassBase& getClassStatically();	\
	private:


#define NE_NATIVE_DEFINE_ONLY_1(NAME)					\
	NE_NATIVE_DEFINE_ONLY_2(NAME, NE_VOID)

#define NE_NATIVE_DEFINE_ONLY_2(NAME, TYPE_PARAMETERS)	\
	TYPE_PARAMETERS										\
	const NEClassBase& NAME::getClass() const			\
	{													\
		return getClassStatically();					\
	}													\
														\
	TYPE_PARAMETERS										\
	const NEClassBase& NAME::getClassStatically()		\
	{													\
	static NETClass<This> inner;						\
														\
	return inner;										\
	}

#define NE_NATIVE_DEFINE_ONLY(...)	\
	NE_MACRO_OVERLOADER(NE_NATIVE_DEFINE_ONLY, __VA_ARGS__)



#define NE_DECLARE_INTERFACE(NAME, SUPER)						\
	NE_NATIVE_DECLARE_INLINEY(NAME, SUPER, NETInterface)



#define NE_DECLARE_INTERFACE_ONLY(NAME, SUPER)					\
	NE_NATIVE_DECLARE_ONLY(NAME, SUPER, NETInterface)



#define NE_DECLARE_CLASS(NAME, SUPER)							\
	NE_NATIVE_DECLARE_INLINEY(NAME, SUPER, NETConcreteClass)	\
																\
	public:														\
		virtual NEObject& clone() const							\
		{														\
			return *(new This(*this));							\
		}														\
	private:

#define NE_DECLARE_CLASS_ONLY(NAME, SUPER)						\
	NE_NATIVE_DECLARE_ONLY(NAME, SUPER, NETConcreteClass)		\
																\
	public:														\
		virtual NEObject& clone() const;						\
	private:


//	NE_DEFINE_INTERFACE_ONLY:
//		This macro will expands methods needed for Class which was classified as NETInterrface.
//		In usual, user may use this macro only with 1 argument, Name. 
//		But in fact, This consumes two macro arguments. Name and TypeParameter.
//
//		What is TypeParameter:
//			if you're going to define your "Class" which is a class template,
//			TypeParameter will be needed for you.
//			just pass the statement of defining template parameters as TypeParameter.
//
//		Usage:
//			if your class is "template <typename T> MyList",
//
//				NE_DEFINE_INTERFACE_ONLY(MyList<T>, template <typename T>)
//			
//			will expands codes like below.
//
//				template <typename T>
//				const NEClassBase& MyList<T>::getClass() const
//				{
//					return getClassStatically();
//				}		
//				template <typename T>
//				const NEClassBase& MyList<T>::getClassStatically()
//				{
//					static NETClass<MyList<T>> inner;
//					
//					return inner;
//				}
//
//		Known Issue:
//			This macro works charmly. But hidden issue will arise if you
//			're trying to use a class template which declare more than 2
//			type parameters.
//			Let me show the example.
//
//				NE_DEFINE_INTERFACE_ONLY(MyMap<T, U>, template <typename T, typename U>)
//
//			that codes will expand like below not as you think.
//
//				NE_NATIVE_DEFINE_ONLY_4(MyMap<T, U>, template <typename T, typename U>)
//
//			And obviously, compile fails of course.
//
//
//		Hmm... So, Why does this happen?:
//			The reason is very simple, but hard to solve.
//			It's all matters of ',' . A comma. 
//			As stated the C++ standard docs, the comma between parathesises are not 
//			parsed as delimeter. By using this, if you wrap your Macro arguments to
//			paranthesises, it might solve the problem. But actually not.
//			Because TypeParameters can't accept the paranthesises syntaxically.
//
//				(template <typename T, typename U>)
//				void (MyMap<T, U>)::this_fails_compiling();
//				
//			So, we need to let macro notify that we're passing 2 arguments not 4.
//			If codes are compiled with gcc, known tricks such #define COMMA or #define 
//			SINGLIZER(...) 	__VA_ARGS__ can solve this. But not MSVC.
//			Because MSVC's expanding macro works a little bit weirdly compared to GCC.
//			Whatever you do, when preprocessor meets NE_MACRO_ARGCOUNT, it determind 
//			you passed 4 arguments, not 2.
//
//		Solution:
//			1)	by specifying NATIVE_DEFINE_ONLY macro, avoid NE_MACRO_ARGCOUNT.
//			2)	use NE_MACRO_FUNNEL to send 4 arguments into 2.
//			
//			You must use NE_NATIVE_DEFINE_ONLY. because if expanding goes again after you
//			send arguments with NE_MACRO_FUNNEL, FUNNEL macro doesn't work anymore.
//			NE_MACRO_FUNNEL only works at which it's stated.
//			
//			NE_NATIVE_DEFINE_ONLY_2(	// <--- this's a kind of hint that we'll going to
//				send 2 arguments.
//				NE_MACRO_FUNNEL(MyMap<T, U>)
//				NE_MACRO_FUNNEL(template <typename T, typename U)	//	<-- this 2 arguments
//															 will be turned to single one.
//			)
#define NE_DEFINE_INTERFACE_ONLY_1(NAME)					\
	NE_DEFINE_INTERFACE_ONLY_2(NAME, NE_VOID)

#define NE_DEFINE_INTERFACE_ONLY_2(NAME, TYPE_PARAMETERS)	\
	NE_NATIVE_DEFINE_ONLY(NAME, TYPE_PARAMETERS)

#define NE_DEFINE_INTERFACE_ONLY(...)						\
	NE_MACRO_OVERLOADER(NE_DEFINE_INTERFACE_ONLY, __VA_ARGS__)



#define NE_DEFINE_CLASS_ONLY_2(NAME, TYPE_PARAMETERS)		\
	NE_NATIVE_DEFINE_ONLY(NAME, TYPE_PARAMETERS)			\
	\
	TYPE_PARAMETERS											\
	NEObject& NAME::clone() const							\
{														\
	return *(new This(*this));							\
}
#define NE_DEFINE_CLASS_ONLY_1(NAME)						\
	NE_DEFINE_CLASS_ONLY_2(NAME, NE_VOID)
#define NE_DEFINE_CLASS_ONLY(...)							\
	NE_MACRO_OVERLOADER(NE_DEFINE_CLASS_ONLY, __VA_ARGS__)