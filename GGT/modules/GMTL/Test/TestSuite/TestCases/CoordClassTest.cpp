
/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: CoordClassTest.cpp,v $
 * Date modified: $Date: 2002-03-20 22:54:48 $
 * Version:       $Revision: 1.2 $
 * -----------------------------------------------------------------
 *
 *********************************************************** ggt-head end */
/*************************************************************** ggt-cpr beg
*
* GGT: The Generic Graphics Toolkit
* Copyright (C) 2001,2002 Allen Bierbaum
*
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this library; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*
 ************************************************************ ggt-cpr end */
#include "CoordClassTest.h"
#include <cppunit/extensions/MetricRegistry.h>
#include <gmtl/Coord.h>
#include <gmtl/CoordOps.h>

namespace gmtlTest
{
   void CoordClassTest::testCoordClassTestCreation()
   {
      // test that it initializes to the multiplication identity
      gmtl::Coord<float, 3, 3> q;
      CPPUNIT_ASSERT( q.pos()[0] == 0.0f );
      CPPUNIT_ASSERT( q.pos()[1] == 0.0f );
      CPPUNIT_ASSERT( q.pos()[2] == 0.0f );
      CPPUNIT_ASSERT( q.rot()[0] == 0.0f );
      CPPUNIT_ASSERT( q.rot()[1] == 0.0f );
      CPPUNIT_ASSERT( q.rot()[2] == 0.0f );

      // try out element constructor
      gmtl::Vec3f p( 1, 2, 3 );
      gmtl::Vec3f r( 4, 5, 6 );
      gmtl::Coord<float, 3, 3> q2( p, r );
      CPPUNIT_ASSERT( q2.pos()[0] == 1.0f );
      CPPUNIT_ASSERT( q2.pos()[1] == 2.0f );
      CPPUNIT_ASSERT( q2.pos()[2] == 3.0f );
      CPPUNIT_ASSERT( q2.rot()[0] == 4.0f );
      CPPUNIT_ASSERT( q2.rot()[1] == 5.0f );
      CPPUNIT_ASSERT( q2.rot()[2] == 6.0f );

      // try out copy constructor
      gmtl::Coord<float, 3, 3> q3( q2 );
      CPPUNIT_ASSERT( q3.pos()[0] == 1.0f );
      CPPUNIT_ASSERT( q3.pos()[1] == 2.0f );
      CPPUNIT_ASSERT( q3.pos()[2] == 3.0f );
      CPPUNIT_ASSERT( q3.rot()[0] == 4.0f );
      CPPUNIT_ASSERT( q3.rot()[1] == 5.0f );
      CPPUNIT_ASSERT( q3.rot()[2] == 6.0f );

      // try out operator=() function
      gmtl::Coord<float, 3, 3> q4;
      CPPUNIT_ASSERT( q4.pos()[0] == 0.0f );
      CPPUNIT_ASSERT( q4.pos()[1] == 0.0f );
      CPPUNIT_ASSERT( q4.pos()[2] == 0.0f );
      CPPUNIT_ASSERT( q4.rot()[0] == 0.0f );
      CPPUNIT_ASSERT( q4.rot()[1] == 0.0f );
      CPPUNIT_ASSERT( q4.rot()[2] == 0.0f );
      q4 = q3;
      CPPUNIT_ASSERT( q4.pos()[0] == 1.0f );
      CPPUNIT_ASSERT( q4.pos()[1] == 2.0f );
      CPPUNIT_ASSERT( q4.pos()[2] == 3.0f );
      CPPUNIT_ASSERT( q4.rot()[0] == 4.0f );
      CPPUNIT_ASSERT( q4.rot()[1] == 5.0f );
      CPPUNIT_ASSERT( q4.rot()[2] == 6.0f );
   }

   void CoordClassTest::testCoordTimingDefaultConstructor()
   {
      const long iters( 400000 );
      float use_value(1);

      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         // performance of def constructor
         gmtl::Coord<float, 3, 3> q;
         use_value += q.mPos[0];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("CoordTest/DefaultConstructor", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT( use_value != 0 );
   }

   void CoordClassTest::testCoordTimingElementConstructor()
   {
      const long iters( 400000 );
      float use_value(1);

      gmtl::Vec3f p( 1, 2, 3 );
      gmtl::Vec3f r( 4, 5, 6 );
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         // performance of element constructor
         gmtl::Coord<float, 3, 3> q2( p, r );
         use_value += q2.mPos[0];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("CoordTest/ElementConstructor", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT( use_value != 0 );
   }

   void CoordClassTest::testCoordTimingCopyConstructor()
   {
      const long iters( 400000 );
      float use_value(1);
      gmtl::Coord<float, 3, 3> q;

      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         // performance of copy constructor
         gmtl::Coord<float, 3, 3> q3( q );
         use_value += q3.mPos[0];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("CoordTest/CopyConstructor", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT( use_value != 0 );
   }


   void CoordClassTest::testCoordTimingGet()
   {
      const long iters( 400000 );
      float use_value(0);
      CPPUNIT_METRIC_START_TIMING();
      gmtl::Coord<float, 3, 3> q;
      for (long iter = 0; iter < iters; ++iter)
      {
         // performance of get...
         use_value += use_value + q.pos()[0];
         use_value += use_value + q.rot()[0];
         q.rot()[0] -= use_value;
         q.pos()[0] -= use_value;
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("CoordTest/get()", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT( use_value != 8324908723.0f );
   }

   void CoordClassTest::testCoordTimingOpEqual()
   {
      const long iters( 400000 );
      gmtl::Coord<float, 3, 3> q4, q2;
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         // performance of operator=() function
         q4 = q2;
         q2.pos()[2] += q4.pos()[1];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("CoordTest/operator=()", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( q4.pos()[0] != 3498.0f );
   }
}
