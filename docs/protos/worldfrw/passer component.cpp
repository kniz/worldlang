class Executable {
	virtual Result& execute() const = 0;
};

class Object : public Node {
	virtual Refer call(const Msg& msg) {
		Object& old = msg.getThis();
		msg._setThis(*this);

		...

		msg._setThis(old);
	}
	virtual Refer call(const Msg& msg) const {
	}
};

class Refer : public Node {
	This();
	This(const Class& cls, wbool is_const = false)
	: Super(), _cls(cls), _is_const(is_const) {}
	This(const Class& cls, Object& it);
	This(Object& it)
	: Super(), _cls(it.getClass() {
		bind(it);	
	}
	This(const Class& cls, const Object& it);
	This(const Object& it);
	This(const Class& cls, const This& it);
	This(const This& it);

	operator==() const;
	operator!=() const;
	operator=(const This& it);
	operator=(Object& it);
	operator=(const Object& it);
	Object& operator->();
	const Object& operator->() const;
	Object& operator*();
	const Object& operator*() const;

	virtual CStrong call(const Msg& msg) const { return _bean.call(msg); }
	virtual Strong call(const Msg& msg) { return _bean.call(msg); }

	Result& bind(Object& it) {
		const Class& cls = it.getClass();
		WRD_IS_NULL(cls)
		if( ! cls.isSub(_cls))
			return TypeInvalid.warn("...");

		unbind();
		WRD_IS_ERR(_bean.bind(it))
		_is_const = false;
		return Success;
	}
	Result& bind(const Object& it) const {
		This& unconst = const_cast<This&>(*this);
		Result& res = unconst.bind(const_cast<Object&>(it));
		WRD_IS_ERR(res)

		_is_const = true;
		return res;
	}
	Result& unbind() {
		Result& res = _bean.unbind();
		WRD_IS_ERR(res)

		_is_const = false;
		return Success;
	}
	Node& get() {
		WRD_IS_THIS(Object)
		WRD_IF(_is_const, InvalidCall, Nuller<Object>::ref)

		return _bean.get();
	}
	const Node& get() const {
		WRD_IS_THIS(Object)
		return _bean.get();
	}

	wbool isConst() const { return _is_const; }
	wbool _is_const;
	TStrong<Node> _bean;
	const Class& _cls;
};

class Method : public Object, public Executable {
	BlockStmt _blkstmt;
	virtual Result& execute() const {
		Method& old = msg.getMe();
		msg._setMe(*this);

		...

		msg._setMe(old);
	}
};

class BlockStmt : public Stmt {
	typedef vector<Stmt> Stmts;
	Stmts _stmts; // Expr은 invisible하게 한다는 뜻이다.
	Stmts& getStmts();
	const Stmts& getStmts() const;
	virtual Result& execute() const {
		for(auto s in _stmts)
			s.execute();
		return Success;
	}
};

class Stmt : public Instance, public Executable {};

//	Expression은 invisible 하다.
class Expr : public Stmt {
	Msg _msg;
	const Msg& getMsg() const;
	Msg& getMsg();

	TStrong _caller; // expression or object 가 여기에 들어간다.
	Node& getCaller();
	const Node& getCaller() const;

	virtual Result& execute() const; // const 상태에서도 excute가 가능하게 해야한다.
	// Expression은 반환형이 될 수 없다는 것이다.
	// visible할 필요가 없으므로 Refer로 하지 않는다.
	mutable TStrong _returned; 
	Node& getReturned() const;

	virtual Refer to(const Class& cls) const {
		if(cls.isSub(Node::getStaticClass())) 
		{
			execute();
			return Refer(cls, _returned);
		}

		return Super::to(cls);
	}
};