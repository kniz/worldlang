#include "Chunks.hpp"
#include "../interface/Instance.hpp"

namespace wrd { namespace memlite {

	WRD_DEF_THIS(Chunks, Allocator)

	This::Chunks(wcnt blkbyte) : Super(blkbyte), _s(0) {}
	This::~Chunks() { _rel(); }

	Chunk& This::operator[](widx n) { return get(n); }
	Chunk& This::operator[](const Instance& inst) { return get(inst); }
	const Chunk& This::operator[](widx n) const { return get(n); }
	const Chunk& This::operator[](const Instance& inst) const { return get(inst); }

	Chunk& This::get(widx n) { return *(Chunk*)_get(n); }
	Chunk& This::get(const Instance& it) { return *(Chunk*)_get(it.getId().s.chkN); }
	const Chunk& This::get(const Instance& it) const { return ((Chunks*)this)->get(it); }
	const Chunk& This::get(widx n) const { return ((Chunks*)this)->get(n); }

	wbool This::rel() { return _rel(); }
	wcnt This::getLen() const { return _chunks.size(); }
	wcnt This::getSize() const { return getLen(); }

	void* This::new1() {
		widx n = _findCapable();
		void* ret = _chunks[n]->new1();
		Instance::_vault.set(ret, n);
		return ret;
	}

	wbool This::del(void* pt, wcnt sz) {
		//	in fact, cast wasn't be deallocated yet:
		//		if we guarrantee that destructor didn't change its _id value,
		//		_id will keep its value till now.
		widx chkN = ((Instance*) pt)->_id.s.chkN;
		return _chunks[chkN]->del(pt, sz);
	}

	widx This::_findCapable() {
		wcnt sz = _chunks.size();
		widx end = _s;

		do {
			const Chunk& e = get(_s);
			if(!nul(e) && e.isCapable())
				return _s;
			_s++;
			if(_s >= sz) _s = 0;
		} while(_s != end);

		resize(getLen() + 1);
		return _s;
	}

	wbool This::has(const Instance& it) const { return _chunks[it.getId().s.chkN]->has(it); }

	wbool This::resize(wcnt new1) {
		_s = _chunks.size();
		if(_s > new1) _s = new1-1;
		if(_s < 0) _s = 0;

		while(_chunks.size() < new1)
			_chunks.push_back(new Chunk(getBlkSize()));
		return true;
	}

	wbool This::_rel() {
		for(Chunk* e : _chunks)
			e->rel();
		_chunks.clear();
		_s = 0;
		return true;
	}

	void* This::_get(widx n) {
		if (0 > n || n >= _chunks.size())
			return WRD_NULL;

		return _chunks[n];
	}
}}