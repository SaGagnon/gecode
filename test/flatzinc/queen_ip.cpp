/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*- */
/*
 *  Main authors:
 *     Guido Tack <tack@gecode.org>
 *
 *  Copyright:
 *     Guido Tack, 2014
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

#include "test/flatzinc.hh"

namespace Test { namespace FlatZinc {

  namespace {
    /// Helper class to create and register tests
    class Create {
    public:

      /// Perform creation and registration
      Create(void) {
        (void) new FlatZincTest("queens::ip",
"predicate bool_lin_ge(array [int] of int: a, array [int] of var bool: x, var int: c);\n\
predicate bool_lin_gt(array [int] of int: a, array [int] of var bool: x, var int: c);\n\
predicate bool_lin_lt(array [int] of int: a, array [int] of var bool: x, var int: c);\n\
predicate bool_lin_ne(array [int] of int: a, array [int] of var bool: x, var int: c);\n\
array [1..64] of var 0..1: q :: output_array([0..7, 0..7]);\n\
constraint int_lin_eq([1, 1, 1, 1, 1, 1, 1, 1], [q[1], q[2], q[3], q[4], q[5], q[6], q[7], q[8]], 1);\n\
constraint int_lin_eq([1, 1, 1, 1, 1, 1, 1, 1], [q[1], q[9], q[17], q[25], q[33], q[41], q[49], q[57]], 1);\n\
constraint int_lin_eq([1, 1, 1, 1, 1, 1, 1, 1], [q[2], q[10], q[18], q[26], q[34], q[42], q[50], q[58]], 1);\n\
constraint int_lin_eq([1, 1, 1, 1, 1, 1, 1, 1], [q[3], q[11], q[19], q[27], q[35], q[43], q[51], q[59]], 1);\n\
constraint int_lin_eq([1, 1, 1, 1, 1, 1, 1, 1], [q[4], q[12], q[20], q[28], q[36], q[44], q[52], q[60]], 1);\n\
constraint int_lin_eq([1, 1, 1, 1, 1, 1, 1, 1], [q[5], q[13], q[21], q[29], q[37], q[45], q[53], q[61]], 1);\n\
constraint int_lin_eq([1, 1, 1, 1, 1, 1, 1, 1], [q[6], q[14], q[22], q[30], q[38], q[46], q[54], q[62]], 1);\n\
constraint int_lin_eq([1, 1, 1, 1, 1, 1, 1, 1], [q[7], q[15], q[23], q[31], q[39], q[47], q[55], q[63]], 1);\n\
constraint int_lin_eq([1, 1, 1, 1, 1, 1, 1, 1], [q[8], q[16], q[24], q[32], q[40], q[48], q[56], q[64]], 1);\n\
constraint int_lin_eq([1, 1, 1, 1, 1, 1, 1, 1], [q[9], q[10], q[11], q[12], q[13], q[14], q[15], q[16]], 1);\n\
constraint int_lin_eq([1, 1, 1, 1, 1, 1, 1, 1], [q[17], q[18], q[19], q[20], q[21], q[22], q[23], q[24]], 1);\n\
constraint int_lin_eq([1, 1, 1, 1, 1, 1, 1, 1], [q[25], q[26], q[27], q[28], q[29], q[30], q[31], q[32]], 1);\n\
constraint int_lin_eq([1, 1, 1, 1, 1, 1, 1, 1], [q[33], q[34], q[35], q[36], q[37], q[38], q[39], q[40]], 1);\n\
constraint int_lin_eq([1, 1, 1, 1, 1, 1, 1, 1], [q[41], q[42], q[43], q[44], q[45], q[46], q[47], q[48]], 1);\n\
constraint int_lin_eq([1, 1, 1, 1, 1, 1, 1, 1], [q[49], q[50], q[51], q[52], q[53], q[54], q[55], q[56]], 1);\n\
constraint int_lin_eq([1, 1, 1, 1, 1, 1, 1, 1], [q[57], q[58], q[59], q[60], q[61], q[62], q[63], q[64]], 1);\n\
constraint int_lin_le([1, 1], [q[2], q[9]], 1);\n\
constraint int_lin_le([1, 1], [q[7], q[16]], 1);\n\
constraint int_lin_le([1, 1], [q[49], q[58]], 1);\n\
constraint int_lin_le([1, 1], [q[56], q[63]], 1);\n\
constraint int_lin_le([1, 1, 1], [q[3], q[10], q[17]], 1);\n\
constraint int_lin_le([1, 1, 1], [q[6], q[15], q[24]], 1);\n\
constraint int_lin_le([1, 1, 1], [q[41], q[50], q[59]], 1);\n\
constraint int_lin_le([1, 1, 1], [q[48], q[55], q[62]], 1);\n\
constraint int_lin_le([1, 1, 1, 1], [q[4], q[11], q[18], q[25]], 1);\n\
constraint int_lin_le([1, 1, 1, 1], [q[5], q[14], q[23], q[32]], 1);\n\
constraint int_lin_le([1, 1, 1, 1], [q[33], q[42], q[51], q[60]], 1);\n\
constraint int_lin_le([1, 1, 1, 1], [q[40], q[47], q[54], q[61]], 1);\n\
constraint int_lin_le([1, 1, 1, 1, 1], [q[4], q[13], q[22], q[31], q[40]], 1);\n\
constraint int_lin_le([1, 1, 1, 1, 1], [q[5], q[12], q[19], q[26], q[33]], 1);\n\
constraint int_lin_le([1, 1, 1, 1, 1], [q[25], q[34], q[43], q[52], q[61]], 1);\n\
constraint int_lin_le([1, 1, 1, 1, 1], [q[32], q[39], q[46], q[53], q[60]], 1);\n\
constraint int_lin_le([1, 1, 1, 1, 1, 1], [q[3], q[12], q[21], q[30], q[39], q[48]], 1);\n\
constraint int_lin_le([1, 1, 1, 1, 1, 1], [q[6], q[13], q[20], q[27], q[34], q[41]], 1);\n\
constraint int_lin_le([1, 1, 1, 1, 1, 1], [q[17], q[26], q[35], q[44], q[53], q[62]], 1);\n\
constraint int_lin_le([1, 1, 1, 1, 1, 1], [q[24], q[31], q[38], q[45], q[52], q[59]], 1);\n\
constraint int_lin_le([1, 1, 1, 1, 1, 1, 1], [q[2], q[11], q[20], q[29], q[38], q[47], q[56]], 1);\n\
constraint int_lin_le([1, 1, 1, 1, 1, 1, 1], [q[7], q[14], q[21], q[28], q[35], q[42], q[49]], 1);\n\
constraint int_lin_le([1, 1, 1, 1, 1, 1, 1], [q[9], q[18], q[27], q[36], q[45], q[54], q[63]], 1);\n\
constraint int_lin_le([1, 1, 1, 1, 1, 1, 1], [q[16], q[23], q[30], q[37], q[44], q[51], q[58]], 1);\n\
constraint int_lin_le([1, 1, 1, 1, 1, 1, 1, 1], [q[1], q[10], q[19], q[28], q[37], q[46], q[55], q[64]], 1);\n\
constraint int_lin_le([1, 1, 1, 1, 1, 1, 1, 1], [q[8], q[15], q[22], q[29], q[36], q[43], q[50], q[57]], 1);\n\
solve  :: int_search(q, first_fail, indomain_min, complete) satisfy;\n\
", "q = array2d(0..7, 0..7, [0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0]);\n\
----------\n\
");
      }
    };

    Create c;
  }

}}

// STATISTICS: test-flatzinc
