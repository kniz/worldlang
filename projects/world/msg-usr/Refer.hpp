#pragma once

#include "../base/Node.hpp"
#include "../bind/TBindable.inl"

namespace wrd
{
    class Refer : public TBindable<Node>
	{	WRD_CLASS_DECL(Refer, TBindable<Node>)
	public:
		//TODO: uncomment this. Refer(const Class& cls = Node::getStaticClass(), wbool want_const = false);
		Refer(const Class& cls = Node::getClassStatic(), wbool is_const = false);
		Refer(Node& it, wbool is_const = false);
		Refer(const Node& it, wbool is_const = true);
		Refer(const This& it, wbool is_const = true);
		Refer(This& it, wbool is_const = false);
		template <typename V> Refer(const TBindable<V>& rhs) : Super() { bind(rhs.get()); }
		template <typename V> Refer(TBindable<V>& rhs) : Super() { bind(rhs.get()); }

	public:
		wbool operator==(const This& rhs);
		wbool operator!=(const This& rhs);
		using Super::operator=;
		template <typename V> This& operator=(const TBindable<V>& rhs) {
			this->bind(rhs);
			return *this;
		}
		template <typename V> This& operator=(TBindable<V>& rhs) {
			this->bind(rhs);
			return *this;
		}
		This& operator=(const Instance& it);

	public:	//	Node:
		virtual Refer use(Msg& msg) const; 
		virtual Refer use(Msg& msg); 
		virtual const Origin& getOrigin() const; 
		virtual wbool isConst() const; 
		virtual const Container& getNodes() const;

	public:	//	TBindable:
		using Super::bind;
		virtual Res& bind(const Instance& it);
		Res& bind(Instance& it);
		virtual wbool isBind() const;
		virtual Res& unbind();

	public:	//	Thing:
		virtual Refer to(const Class& cls);
		virtual Res& assign(const Thing& it);

	protected: //Gettable:
		virtual Instance& _get();
		//	TODO: const cast.
		//		Refer는 알다시피 World의 const를 구현하는 핵심 클래스다.
		//		Node& n = Refer(const T&..);
		//		n.to<T>(); // REJECT. return Refer(Null)
		//		T& cast = n.down<T>(); // REJECT. cast.isNull() == true.
		//		const T& cast = n.down<const T>(); // OK.
		//		Refer& cast1 = n.to<const T>(); // OK. cast1->isNull() != true
		//	위의 코드가 가능하도록 해야 한다.
		virtual Thing& _down(const Class& cls);

	private:
		wbool _is_const;
		Strong _bean;
		const Class& _cls;
	};
}