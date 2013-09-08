/*****************************************************************************

  The following code is derived, directly or indirectly, from the SystemC
  source code Copyright (c) 1996-2014 by all Contributors.
  All Rights reserved.

  The contents of this file are subject to the restrictions and limitations
  set forth in the SystemC Open Source License (the "License");
  You may not use this file except in compliance with such restrictions and
  limitations. You may obtain instructions on how to receive a copy of the
  License at http://www.accellera.org/. Software distributed by Contributors
  under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
  ANY KIND, either express or implied. See the License for the specific
  language governing rights and limitations under the License.

 *****************************************************************************/

/*****************************************************************************

  arith06.cpp -- 

  Original Author: Martin Janssen, Synopsys, Inc., 2002-02-15

 *****************************************************************************/

/*****************************************************************************

  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
  changes you are making here.

      Name, Affiliation, Date:
  Description of Modification:

 *****************************************************************************/

#include <stdlib.h>
#include "systemc.h"
#include "isaac.h"

QTIsaac<8> rng;		// Platform independent random number generator.

int
sc_main( int argc, char* argv[] )
{
    signed int vali[5] = { 0, 1, -1, 7, -8 };
    signed int valj[5] = { 0, 1, -1, 7, -8 };

    for (int i = 3; i < 32; ++i) {
        for (int j = 3; j < 32; ++j) {
            cout << "i = " << i << ", j = " << j << endl;

            sc_signed x(i);
            sc_signed y(j);
            sc_signed z(64);

            vali[3] = (1 << (i - 1)) - 1;
            vali[4] = - (1 << (i - 1));

            valj[3] = (1 << (j - 1)) - 1;
            valj[4] = - (1 << (j - 1));

            for (int ii = 0; ii < 100; ++ii) {
                for (int jj = 0; jj < 100; ++jj) {
                    signed int qi = (ii < 5) ? vali[ii] : (rng.rand() & ((1 << i) - 1));
                    signed int qj = (jj < 5) ? valj[jj] : (rng.rand() & ((1 << j) - 1));

                    if (qi & (1 << (i - 1))) {
                        qi = (qi << (32 - i)) >> (32 - i);
                    }
                    if (qj & (1 << (j - 1))) {
                        qj = (qj << (32 - j)) >> (32 - j);
                    }

                    x = qi;
                    sc_assert( x == qi );
                    y = qj;
                    sc_assert( y == qj );
                    sc_assert((x == qj) == (qi == qj));
                    sc_assert((x == qj) == (qj == x));
                    sc_assert((x != qj) == (qi != qj));
                    sc_assert((x != qj) == (qj != x));
                    sc_assert((x < qj) == (qi < qj));
                    sc_assert((x < qj) == (qj > x));
                    sc_assert((x <= qj) == (qi <= qj));
                    sc_assert((x <= qj) == (qj >= x));
                    sc_assert((x > qj) == (qi > qj));
                    sc_assert((x > qj) == (qj < x));
                    sc_assert((x >= qj) == (qi >= qj));
                    sc_assert((x >= qj) == (qj <= x));
                    z = x + qj;
                    sc_assert( static_cast<sc_bigint<32> >( z.range(31,0) ) ==
			    (qi + qj) );
                    z = qi + y;
                    sc_assert( static_cast<sc_bigint<32> >( z.range(31,0) ) ==
			    (qi + qj) );
                    z = x - qj;
                    sc_assert( static_cast<sc_bigint<32> >( z.range(31,0) ) ==
			    (qi - qj) );
                    z = qi - y;
                    sc_assert( static_cast<sc_bigint<32> >( z.range(31,0) ) ==
			    (qi - qj) );
                    z = x * qj;
                    sc_assert( static_cast<sc_bigint<32> >( z.range(31,0) ) ==
			    (qi * qj) );
                    z = qi * y;
                    sc_assert( static_cast<sc_bigint<32> >( z.range(31,0) ) ==
			    (qi * qj) );
                    if (qj != 0) {
                        z = x / qj;
                        sc_assert( static_cast<sc_bigint<32> >( z.range(31,0) ) ==
				(qi / qj) );
                        z = qi / y;
                        sc_assert( static_cast<sc_bigint<32> >( z.range(31,0) ) ==
				(qi / qj) );
                        z = x % qj;
                        sc_assert( static_cast<sc_bigint<32> >( z.range(31,0) ) ==
				(qi % qj) );
                        z = qi % y;
                        sc_assert( static_cast<sc_bigint<32> >( z.range(31,0) ) ==
				(qi % qj) );
                    }
                    z = x & qj;
                    sc_assert( static_cast<sc_bigint<32> >( z.range(31,0) ) ==
			    (qi & qj) );
                    z = qi & y;
                    sc_assert( static_cast<sc_bigint<32> >( z.range(31,0) ) ==
			    (qi & qj) );
                    z = x | qj;
                    sc_assert( static_cast<sc_bigint<32> >( z.range(31,0) ) ==
			    (qi | qj) );
                    z = qi | y;
                    sc_assert( static_cast<sc_bigint<32> >( z.range(31,0) ) ==
			    (qi | qj) );
                    z = x ^ qj;
                    sc_assert( static_cast<sc_bigint<32> >( z.range(31,0) ) ==
			    (qi ^ qj) );
                    z = qi ^ y;
                    sc_assert( static_cast<sc_bigint<32> >( z.range(31,0) ) ==
			    (qi ^ qj) );
                }
            }
        }
    }
    return 0;
}
