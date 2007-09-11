/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*- */
/*
 *  Main authors:
 *     Guido Tack <tack@gecode.org>
 *     Christian Schulte <schulte@gecode.org>
 *
 *  Contributing authors:
 *     Gabor Szokoli <szokoli@gecode.org>
 *
 *  Copyright:
 *     Guido Tack, 2004
 *     Christian Schulte, 2004
 *     Gabor Szokoli, 2004
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

#ifndef __GECODE_SET_HH__
#define __GECODE_SET_HH__

namespace Gecode { namespace Set {
  /** 
   * \namespace Gecode::Set
   * \brief Finite integer sets
   * 
   * The Gecode::Set namespace contains all functionality required
   * to program propagators and branchings for finite integer sets.
   * In addition, all propagators and branchings for finite integer
   * sets provided by %Gecode are contained as nested namespaces.
   *
   */
}}

#include "gecode/limits.hh"

#include "gecode/kernel.hh"
#include "gecode/int.hh"
#include "gecode/iter.hh"

/*
 * Support for DLLs under Windows
 *
 */

#if !defined(GECODE_STATIC_LIBS) && \
    (defined(__CYGWIN__) || defined(__MINGW32__) || defined(_MSC_VER))

#ifdef GECODE_BUILD_SET
#define GECODE_SET_EXPORT __declspec( dllexport )
#else
#define GECODE_SET_EXPORT __declspec( dllimport )
#endif

#else

#ifdef GCC_HASCLASSVISIBILITY

#define GECODE_SET_EXPORT __attribute__ ((visibility("default")))

#else

#define GECODE_SET_EXPORT

#endif
#endif

#include "gecode/set/exception.icc"
#include "gecode/set/var.icc"
#include "gecode/set/view.icc"
#include "gecode/set/propagator.icc"
#include "gecode/set/array.icc"

namespace Gecode {

  /**
   * \brief Common relation types for sets
   * \ingroup TaskIntSet
   */
  enum SetRelType {
    SRT_EQ,   ///< Equality (\f$=\f$)
    SRT_NQ,   ///< Disequality (\f$\neq\f$)
    SRT_SUB,  ///< Subset (\f$\subseteq\f$)
    SRT_SUP,  ///< Superset (\f$\supseteq\f$)
    SRT_DISJ, ///< Disjoint (\f$\parallel\f$)
    SRT_CMPL  ///< Complement
  };

  /**
   * \brief Common operations for sets
   * \ingroup TaskIntSet
   */
  enum SetOpType {
    SOT_UNION,  ///< Union
    SOT_DUNION, ///< Disjoint union
    SOT_INTER,  ///< %Intersection
    SOT_MINUS   ///< Difference
  };

  /**
   * \defgroup TaskIntSetDom Domain constraints
   * \ingroup TaskIntSet
   *
   */

  //@{

  /// Propagates \f$ x \sim_r \{i\}\f$
  GECODE_SET_EXPORT void
  dom(Space* home, SetVar x, SetRelType r, int i);

  /// Propagates \f$ x \sim_r \{i,\dots,j\}\f$
  GECODE_SET_EXPORT void
  dom(Space* home, SetVar x, SetRelType r, int i, int j);

  /// Propagates \f$ x \sim_r s\f$
  GECODE_SET_EXPORT void
  dom(Space* home, SetVar x, SetRelType r, const IntSet& s);

  /// Post propagator for \f$ (x \sim_r \{i\}) \Leftrightarrow b \f$
  GECODE_SET_EXPORT void
  dom(Space* home, SetVar x, SetRelType r, int i, BoolVar b);

  /// Post propagator for \f$ (x \sim_r \{i,\dots,j\}) \Leftrightarrow b \f$
  GECODE_SET_EXPORT void
  dom(Space* home, SetVar x, SetRelType r, int i, int j, BoolVar b);

  /// Post propagator for \f$ (x \sim_r s) \Leftrightarrow b \f$
  GECODE_SET_EXPORT void
  dom(Space* home, SetVar x, SetRelType r, const IntSet& s, BoolVar b);

  /// Propagates \f$ i \leq |s| \leq j \f$
  GECODE_SET_EXPORT void
  cardinality(Space* home, SetVar x, unsigned int i, unsigned int j);

  //@}


  /**
   * \defgroup TaskIntSetRel Relation constraints
   * \ingroup TaskIntSet
   *
   */

  //@{

  /// Post propagator for \f$ x \sim_r y\f$
  GECODE_SET_EXPORT void
  rel(Space* home, SetVar x, SetRelType r, SetVar y);

  /// Post propagator for \f$ (x \sim_r y) \Leftrightarrow b \f$
  GECODE_SET_EXPORT void
  rel(Space* home, SetVar x, SetRelType r, SetVar y, BoolVar b);

  /// Post propagator for \f$ (x \sim_r s) \Leftrightarrow b \f$
  GECODE_SET_EXPORT void
  rel(Space* home, SetVar x, SetRelType r, const IntSet& s, BoolVar b);  

  /// Post propagator for \f$ s \sim_r \{x\}\f$
  GECODE_SET_EXPORT void
  rel(Space* home, SetVar s, SetRelType r, IntVar x);

  /// Post propagator for \f$ \{x\} \sim_r s\f$
  GECODE_SET_EXPORT void
  rel(Space* home, IntVar x, SetRelType r, SetVar s);

  /// Post propagator for \f$ (s \sim_r \{x\}) \Leftrightarrow b \f$
  GECODE_SET_EXPORT void
  rel(Space* home, SetVar s, SetRelType r, IntVar x, BoolVar b);

  /// Post propagator for \f$ (\{x\} \sim_r s) \Leftrightarrow b \f$
  GECODE_SET_EXPORT void
  rel(Space* home, IntVar x, SetRelType r, SetVar s, BoolVar b);

  /// Post propagator for \f$\forall i\in s:\ i \sim_r x\f$
  GECODE_SET_EXPORT void
  rel(Space* home, SetVar s, IntRelType r, IntVar x);

  /// Post propagator for \f$\forall i\in s:\ x \sim_r i\f$
  GECODE_SET_EXPORT void
  rel(Space* home, IntVar x, IntRelType r, SetVar s);

  //@}

  /**
   * \defgroup TaskIntSetRelOp Set operation/relation constraints
   * \ingroup TaskIntSet
   *
   */

  //@{

  /// Post propagator for \f$ (x \diamond_{\mathit{op}} y) \sim_r z \f$
  GECODE_SET_EXPORT void
  rel(Space* home, SetVar x, SetOpType op, SetVar y, SetRelType r, SetVar z);

  /// Post propagator for \f$ y = \diamond_{\mathit{op}} x\f$
  GECODE_SET_EXPORT void
  rel(Space* home, SetOpType op, const SetVarArgs& x, SetVar y);

  /// Post propagator for \f$ y = \diamond_{\mathit{op}} x \diamond_{\mathit{op}} z\f$
  GECODE_SET_EXPORT void
  rel(Space* home, SetOpType op, const SetVarArgs& x, const IntSet& z, SetVar y);

  /// Post propagator for \f$ y = \diamond_{\mathit{op}} x \diamond_{\mathit{op}} z\f$
  GECODE_SET_EXPORT void
  rel(Space* home, SetOpType op, const IntVarArgs& x, const IntSet& z, SetVar y);

  /// Post propagator for \f$ y = \diamond_{\mathit{op}} x\f$
  GECODE_SET_EXPORT void
  rel(Space* home, SetOpType op, const IntVarArgs& x, SetVar y);

  /// Post propagator for \f$ (x \diamond_{\mathit{op}} y) \sim_r z \f$
  GECODE_SET_EXPORT void
  rel(Space* home, const IntSet& x, SetOpType op, SetVar y,
      SetRelType r, SetVar z);

  /// Post propagator for \f$ (x \diamond_{\mathit{op}} y) \sim_r z \f$
  GECODE_SET_EXPORT void
  rel(Space* home, SetVar x, SetOpType op, const IntSet& y,
      SetRelType r, SetVar z);

  /// Post propagator for \f$ (x \diamond_{\mathit{op}} y) \sim_r z \f$
  GECODE_SET_EXPORT void
  rel(Space* home, SetVar x, SetOpType op, SetVar y,
      SetRelType r, const IntSet& z);

  /// Post propagator for \f$ (x \diamond_{\mathit{op}} y) \sim_r z \f$
  GECODE_SET_EXPORT void
  rel(Space* home, const IntSet& x, SetOpType op, SetVar y, SetRelType r,
      const IntSet& z);

  /// Post propagator for \f$ (x \diamond_{\mathit{op}} y) \sim_r z \f$
  GECODE_SET_EXPORT void
  rel(Space* home, SetVar x, SetOpType op, const IntSet& y, SetRelType r,
      const IntSet& z);

  //@}


  /**
   * \defgroup TaskIntSetConvex Convexity constraints
   * \ingroup TaskIntSet
   *
   */
  //@{

  /// Post propagator that propagates that \a x is convex 
  GECODE_SET_EXPORT void
  convex(Space* home, SetVar x);

  /// Post propagator that propagates that \a y is the convex hull of \a x
  GECODE_SET_EXPORT void
  convexHull(Space* home, SetVar x, SetVar y);

  //@}

  /**
   * \defgroup TaskIntSetSequence Sequence constraints
   * \ingroup TaskIntSet
   *
   */
  //@{

  /// Post propagator for \f$\forall 0\leq i< |x|-1 : \max(x_i)<\min(x_{i+1})\f$
  GECODE_SET_EXPORT void
  sequence(Space* home, const SetVarArgs& x);

  /// Post propagator for \f$\forall 0\leq i< |x|-1 : \max(x_i)<\min(x_{i+1})\f$ and \f$ x = \bigcup_{i\in\{0,\dots,n-1\}} y_i \f$ 
  GECODE_SET_EXPORT void
  sequentialUnion(Space* home, const SetVarArgs& y, SetVar x);

  //@}

  /**
   * \defgroup TaskIntSetDistinct Distinctness constraints
   * \ingroup TaskIntSet
   *
   */
  //@{


  /// Post propagator for \f$\forall 0\leq i\leq |x| : |x_i|=c\f$ and \f$\forall 0\leq i<j\leq |x| : |x_i\cap x_j|\leq 1\f$
  GECODE_SET_EXPORT void
  atmostOne(Space* home, const SetVarArgs& x, unsigned int c);

  /// Post propagator for \f$\forall 0\leq i\leq |x| : |x_i|=c\f$ and \f$\forall 0\leq i<j\leq |x| : x_i\neq x_j\f$
  GECODE_SET_EXPORT void
  distinct(Space* home, const SetVarArgs& x, unsigned int c);

  //@}

  /**
   * \defgroup TaskIntSetConnect Connection constraints to finite domain variables
   * \ingroup TaskIntSet
   *
   */

  //@{

  /// Post propagator that propagates that \a x is the minimal element of \a s 
  GECODE_SET_EXPORT void
  min(Space* home, SetVar s, IntVar x);
  
  /// Post propagator that propagates that \a x is the maximal element of \a s 
  GECODE_SET_EXPORT void
  max(Space* home, SetVar s, IntVar x);
  
  /// Post propagator that propagates that \a s contains the \f$x_i\f$, which are sorted in non-descending order 
  GECODE_SET_EXPORT void
  match(Space* home, SetVar s, const IntVarArgs& x);
  
  /// Post propagator for \f$x_i=j \Leftrightarrow i\in y_j\f$
  GECODE_SET_EXPORT void
  channel(Space* home, const IntVarArgs& x,const SetVarArgs& y);

  /// Post propagator for \f$x_i=1 \Leftrightarrow i\in y\f$
  GECODE_SET_EXPORT void
  channel(Space* home, const BoolVarArgs& x, SetVar y);
  
  /// Post propagator for \f$ |s|=x \f$ 
  GECODE_SET_EXPORT void
  cardinality(Space* home, SetVar s, IntVar x);


  /**
   * \brief Post propagator for \f$y = \mathrm{weight}(x)\f$
   *
   * The weights are given as pairs of elements and their weight:
   * \f$\mathrm{weight}(\mathrm{elements}_i) = \mathrm{weights}_i\f$
   *
   * The upper bound of \a x is constrained to contain only elements from
   * \a elements. The weight of a set is the sum of the weights of its
   * elements.
   */
  GECODE_SET_EXPORT void
  weights(Space* home, const IntArgs& elements, const IntArgs& weights,
          SetVar x, IntVar y);

  //@}

  /**
   * \defgroup TaskIntSetSelection Selection constraints
   * \ingroup TaskIntSet
   *
   * A selection constraint selects zero, one or more elements out of a 
   * sequence. We write \f$ \langle x_0,\dots, x_{n-1} \rangle \f$ for the
   * sequence, and \f$ [y] \f$ for the selector variable.
   *
   * Set selection constraints are closely related to the ::element constraint
   * on finite domain variables.
   */

  //@{

  /**
   * \brief Post propagator for \f$ z=\bigcup\langle x_0,\dots,x_{n-1}\rangle[y+\mathit{offset}] \f$
   *
   * If \a y is the empty set, \a z will also be constrained to be empty
   * (as an empty union is empty).
   * The indices for \a s start at 0, unless an \a offset is specified.
   */
  GECODE_SET_EXPORT void
  selectUnion(Space* home, const SetVarArgs& x, SetVar y, SetVar z, int offset=0);

  /**
   * \brief Post propagator for \f$ z=\bigcup\langle s_0,\dots,s_{n-1}\rangle[y+\mathit{offset}] \f$
   *
   * If \a y is the empty set, \a z will also be constrained to be empty
   * (as an empty union is empty).
   * The indices for \a s start at 0, unless an \a offset is specified.
   */
  GECODE_SET_EXPORT void
  selectUnion(Space* home, const IntSetArgs& s, SetVar y, SetVar z, int offset=0);

  /** 
   * \brief Post propagator for \f$ z=\bigcap\langle x_0,\dots,x_{n-1}\rangle[y+\mathit{offset}] \f$ using \f$ \mathcal{U} \f$ as universe
   *
   * If \a y is empty, \a z will be constrained to be the universe
   * \f$ \mathcal{U} \f$ (as an empty intersection is the universe).
   * The indices for \a s start at 0, unless an \a offset is specified.
   */
  GECODE_SET_EXPORT void
  selectInter(Space* home, const SetVarArgs& x, SetVar y, SetVar z, int offset=0);

  /** 
   * \brief Post propagator for \f$ z=\bigcap\langle x_0,\dots,x_{n-1}\rangle[y+\mathit{offset}] \f$ using \a u as universe
   *
   * If \a y is empty, \a z will be constrained to be the given universe
   * \a u (as an empty intersection is the universe).
   * The indices for \a s start at 0, unless an \a offset is specified.
   */
  GECODE_SET_EXPORT void
  selectInterIn(Space* home, const SetVarArgs& x, SetVar y, SetVar z,
                const IntSet& u, int offset=0);

  /// Post propagator for \f$ \parallel\langle x_0,\dots,x_{n-1}\rangle[y] \f$ 
  GECODE_SET_EXPORT void
  selectDisjoint(Space* home, const SetVarArgs& x, SetVar y);

  /**
   * \brief Post propagator for \f$ z=\langle x_0,\dots,x_{n-1}\rangle[y+\mathit{offset}] \f$ 
   *
   * The indices for \a s start at 0, unless an \a offset is specified.
   */
  GECODE_SET_EXPORT void
  selectSet(Space* home, const SetVarArgs& x, IntVar y, SetVar z, int offset=0);

  /**
   * \brief Post propagator for \f$ z=\langle s_0,\dots,s_{n-1}\rangle[y+\mathit{offset}] \f$ 
   *
   * The indices for \a s start at 0, unless an \a offset is specified.
   */
  GECODE_SET_EXPORT void
  selectSet(Space* home, const IntSetArgs& s, IntVar y, SetVar z, int offset=0);

  //@}

  /**
   * \defgroup TaskIntSetBranch Branching
   * \ingroup TaskIntSet
   */

  //@{
  
  /// Which variable to select for branching
  enum SetVarBranch {
    SET_VAR_NONE,               ///< First unassigned
    SET_VAR_MIN_CARD,           ///< With smallest unknown set
    SET_VAR_MAX_CARD,           ///< With largest unknown set
    SET_VAR_MIN_UNKNOWN_ELEM,   ///< With smallest unknown element
    SET_VAR_MAX_UNKNOWN_ELEM,   ///< With largest unknown element
  };
  
  /// Which values to select first for branching
  enum SetValBranch {
    SET_VAL_MIN,                ///< Select smallest value in unknown set
    SET_VAL_MAX,                ///< Select largest value in unknown set
  };

  /// Branch over \a x with variable selection \a vars and value selection \a vals
  GECODE_SET_EXPORT void
  branch(Space* home, const SetVarArgs& x, 
         SetVarBranch vars, SetValBranch vals);
  //@}

}

#endif

// STATISTICS: set-post
