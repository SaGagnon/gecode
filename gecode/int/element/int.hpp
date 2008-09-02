/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*- */
/*
 *  Main authors:
 *     Christian Schulte <schulte@gecode.org>
 *
 *  Copyright:
 *     Christian Schulte, 2004
 *
 *  Last modified:
 *     $Date$ by $Author$
 *     $Revision$
 *
 *  This file is part of Gecode, the generic constraint
 *  development environment:
 *     http://www.gecode.org
 *
 *  Permission is hereby granted, free of charge, to any person obtaining
 *  a copy of this software and associated documentation files (the
 *  "Software"), to deal in the Software without restriction, including
 *  without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to
 *  permit persons to whom the Software is furnished to do so, subject to
 *  the following conditions:
 *
 *  The above copyright notice and this permission notice shall be
 *  included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 *  LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 *  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 *  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

namespace Gecode { namespace Int { namespace Element {


  // Index value pairs
  template <class V0, class V1, class Idx, class Val>
  forceinline void
  Int<V0,V1,Idx,Val>::IdxVal::mark(void) {
    idx = -1;
  }
  template <class V0, class V1, class Idx, class Val>
  forceinline bool
  Int<V0,V1,Idx,Val>::IdxVal::marked(void) const {
    return idx<0;
  }

  // Index iterator
  template <class V0, class V1, class Idx, class Val>
  forceinline
  Int<V0,V1,Idx,Val>::IterIdx::IterIdx(IdxVal* iv0) 
    : iv(iv0) {
    Idx p=0;
    i = iv[p].idx_next;
    while ((i != 0) && iv[i].marked())
      i=iv[i].idx_next;
    iv[p].idx_next=i;
  }
  template <class V0, class V1, class Idx, class Val>
  forceinline bool
  Int<V0,V1,Idx,Val>::IterIdx::operator()(void) const {
    return i != 0;
  }
  template <class V0, class V1, class Idx, class Val>
  forceinline void
  Int<V0,V1,Idx,Val>::IterIdx::operator++(void) {
    int p=i;
    i = iv[p].idx_next;
    while ((i != 0) && iv[i].marked())
      i=iv[i].idx_next;
    iv[p].idx_next=i;
  }
  template <class V0, class V1, class Idx, class Val>
  forceinline Idx
  Int<V0,V1,Idx,Val>::IterIdx::val(void) const {
    assert(!iv[i].marked());
    return iv[i].idx;
  }



  template <class V0, class V1, class Idx, class Val>
  forceinline
  Int<V0,V1,Idx,Val>::IterVal::IterVal(IdxVal* iv0)
    : iv(iv0), i(iv[0].val_next) {}
  template <class V0, class V1, class Idx, class Val>
  forceinline bool
  Int<V0,V1,Idx,Val>::IterVal::operator()(void) const {
    return i != 0;
  }
  template <class V0, class V1, class Idx, class Val>
  forceinline void
  Int<V0,V1,Idx,Val>::IterVal::operator++(void) {
    i=iv[i].val_next;
  }
  template <class V0, class V1, class Idx, class Val>
  forceinline Val
  Int<V0,V1,Idx,Val>::IterVal::val(void) const {
    assert(!iv[i].marked());
    return iv[i].val;
  }



  // Sort function
  template <class V0, class V1, class Idx, class Val>
  forceinline
  Int<V0,V1,Idx,Val>::ByVal::ByVal(const IdxVal* iv0) 
    : iv(iv0) {}
  template <class V0, class V1, class Idx, class Val>
  forceinline bool
  Int<V0,V1,Idx,Val>::ByVal::operator()(Idx& i, Idx& j) {
    return iv[i].val < iv[j].val;
  }


  /*
   * Element propagator proper
   *
   */
  template <class V0, class V1, class Idx, class Val>
  forceinline
  Int<V0,V1,Idx,Val>::Int(Space& home, IntSharedArray& c0, V0 y0, V1 y1)
    : Propagator(home), x0(y0), x1(y1), c(c0), iv(NULL) {
    home.notice(*this,AP_DISPOSE);
    x0.subscribe(home,*this,PC_INT_DOM);
    x1.subscribe(home,*this,PC_INT_DOM);
  }

  template <class V0, class V1, class Idx, class Val>
  forceinline size_t
  Int<V0,V1,Idx,Val>::dispose(Space& home) {
    home.ignore(*this,AP_DISPOSE);
    if (!home.failed()) {
      x0.cancel(home,*this,PC_INT_DOM);
      x1.cancel(home,*this,PC_INT_DOM);
    }
    c.~IntSharedArray();
    (void) Propagator::dispose(home);
    return sizeof(*this);
  }

  template <class V0, class V1, class Idx, class Val>
  ExecStatus
  Int<V0,V1,Idx,Val>::post(Space& home, IntSharedArray& c, V0 x0, V1 x1) {
    GECODE_ME_CHECK(x0.gq(home,0));
    GECODE_ME_CHECK(x0.le(home,c.size()));
    if (x0.assigned()) {
      GECODE_ME_CHECK(x1.eq(home,c[x0.val()]));
    } else {
      (void) new (home) Int<V0,V1,Idx,Val>(home,c,x0,x1);
    }
    return ES_OK;
  }

  template <class V0, class V1, class Idx, class Val>
  forceinline
  Int<V0,V1,Idx,Val>::Int(Space& home, bool share, Int& p)
    : Propagator(home,share,p), iv(NULL) {
    c.update(home,share,p.c);
    x0.update(home,share,p.x0);
    x1.update(home,share,p.x1);
  }

  template <class V0, class V1, class Idx, class Val>
  Actor*
  Int<V0,V1,Idx,Val>::copy(Space& home, bool share) {
    return new (home) Int<V0,V1,Idx,Val>(home,share,*this);
  }

  template <class V0, class V1, class Idx, class Val>
  PropCost
  Int<V0,V1,Idx,Val>::cost(const Space&, const ModEventDelta&) const {
    return PC_BINARY_HI;
  }

  template <class V0, class V1, class Idx, class Val>
  inline Support::Symbol
  Int<V0,V1,Idx,Val>::ati(void) {
    return Reflection::mangle<V0,V1,Idx,Val>("Gecode::Int::Element::Int");
  }

  template <class V0, class V1, class Idx, class Val>
  Reflection::ActorSpec
  Int<V0,V1,Idx,Val>::spec(const Space& home, Reflection::VarMap& m) const {
    Reflection::ActorSpec s(ati());
    return s << x0.spec(home, m)
             << x1.spec(home, m)
             << Reflection::Arg::newIntArray(c);
  }

  template <class V0, class V1, class Idx, class Val>
  void
  Int<V0,V1,Idx,Val>::post(Space& home, Reflection::VarMap& vars,
                         const Reflection::ActorSpec& spec) {
    spec.checkArity(3);
    V0 x0(home, vars, spec[0]);
    V1 x1(home, vars, spec[1]);
    Reflection::IntArrayArg* a = spec[2]->toIntArray();
    IntSharedArray is(a->size());
    for (int i=a->size(); i--; ) {
      is[i] = (*a)[i];
    }
    (void) new (home) Int<V0,V1,Idx,Val>(home, is, x0, x1);
  }

  template <class V0, class V1, class Idx, class Val>
  ExecStatus
  Int<V0,V1,Idx,Val>::propagate(Space& home, const ModEventDelta&) {
    bool assigned = x0.assigned() && x1.assigned();
    if (iv == NULL) {
      // Initialize data structure
      iv = home.alloc<IdxVal>(x0.size() + 1);

      // The first element in iv[0] is used as sentinel
      // Enter information sorted by idx
      IdxVal* by_idx = &iv[1];
      {
        Idx i = 0;
        ViewValues<V0> v(x0);
        while (v()) {
          by_idx[i].idx = v.val();
          by_idx[i].val = c[v.val()];
          ++i; ++v;
        }
      }
      Idx size = x0.size();
      // Create val links sorted by val
      Region r(home);
      Idx* by_val = r.alloc<Idx>(size);
      for (Idx i = size; i--; )
        by_val[i] = i+1;
      ByVal lt(iv);
      Support::quicksort<Idx>(by_val,size,lt);
      // Create val links
      for (Idx i = size-1; i--; ) {
        by_idx[i].idx_next = i+2;
        iv[by_val[i]].val_next = by_val[i+1];
      }
      by_idx[size-1].idx_next = 0;
      iv[by_val[size-1]].val_next = 0;
      // Set up sentinel element: iv[0]
      iv[0].idx_next = 1;
      iv[0].val_next = by_val[0];
    } else {
      // Prune index
      Idx p = 0;
      Idx i = iv[p].idx_next;
      ViewRanges<V0> v(x0);
      while (v() && (i != 0)) {
        assert(!iv[i].marked());
        if (iv[i].idx < v.min()) {
          iv[i].mark(); i=iv[i].idx_next; iv[p].idx_next=i;
        } else if (iv[i].idx > v.max()) {
          ++v;
        } else {
          p=i; i=iv[i].idx_next;
        }
      }
      iv[p].idx_next = 0;
      while (i != 0) { iv[i].mark(); i=iv[i].idx_next; }
    }

    // Prune values
    {
      Idx p = 0;
      Idx i = iv[p].val_next;
      ViewRanges<V1> v(x1);
      while (v() && (i != 0)) {
        if (iv[i].marked()) {
          i=iv[i].val_next; iv[p].val_next=i;
        } else if (iv[i].val < v.min()) {
          iv[i].mark(); i=iv[i].val_next; iv[p].val_next=i;
        } else if (iv[i].val > v.max()) {
          ++v;
        } else {
          p=i; i=iv[i].val_next;
        }
      }
      iv[p].val_next = 0;
      while (i != 0) { iv[i].mark(); i=iv[i].val_next; }
    }

    // Peform tell
    {
      IterIdx i(iv);
      GECODE_ME_CHECK(x0.narrow_v(home,i,false));
      IterVal v(iv);
      if (shared(x0,x1)) {
        GECODE_ME_CHECK(x1.inter_v(home,v,false));
        return assigned ? ES_SUBSUMED(*this,home) : ES_NOFIX;
      } else {
        GECODE_ME_CHECK(x1.narrow_v(home,v,false));
        return (x0.assigned() || x1.assigned()) ? 
          ES_SUBSUMED(*this,home) : ES_FIX;
      }
    }
  }

  template <class V0, class V1>
  forceinline ExecStatus
  post_int(Space& home, IntSharedArray& c, V0 x0, V1 x1) {
    int min = INT_MAX;
    int max = INT_MIN;
    for (int i=c.size(); i--; ) {
      min = std::min(c[i],min);
      max = std::max(c[i],max);
    }
    switch (std::max(Support::s_type(min),Support::s_type(max))) {
    case Support::IT_CHAR:
      switch (Support::s_type(c.size()+2)) {
      case Support::IT_CHAR:
        return Int<V0,V1,signed char,signed char>::post(home,c,x0,x1);
      case Support::IT_SHRT:
        return Int<V0,V1,signed char,signed short int>::post(home,c,x0,x1);
      case Support::IT_INT:
        return Int<V0,V1,signed char,signed int>::post(home,c,x0,x1);
      default: GECODE_NEVER;
      }
      break;
    case Support::IT_SHRT:
      switch (Support::s_type(c.size()+1)) {
      case Support::IT_CHAR:
        return Int<V0,V1,signed short int,signed char>::post(home,c,x0,x1);
      case Support::IT_SHRT:
        return Int<V0,V1,signed short int,signed short int>::post(home,c,x0,x1);
      case Support::IT_INT:
        return Int<V0,V1,signed short int,signed int>::post(home,c,x0,x1);
      default: GECODE_NEVER;
      }
      break;
    case Support::IT_INT:
      switch (Support::s_type(c.size()+1)) {
      case Support::IT_CHAR:
        return Int<V0,V1,signed int,signed char>::post(home,c,x0,x1);
      case Support::IT_SHRT:
        return Int<V0,V1,signed int,signed short int>::post(home,c,x0,x1);
      case Support::IT_INT:
        return Int<V0,V1,signed int,signed int>::post(home,c,x0,x1);
      default: GECODE_NEVER;
      }
      break;
    default: GECODE_NEVER;
    }
    return ES_OK;
  }

}}}


// STATISTICS: int-prop
