/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: EulerAngleClassTest.cpp,v $
 * Date modified: $Date: 2002-06-06 19:30:25 $
 * Version:       $Revision: 1.1 $
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
#include "EulerAngleClassTest.h"
#include <cppunit/extensions/MetricRegistry.h>
#include <gmtl/EulerAngle.h>

namespace gmtlTest
{
   void EulerAngleClassTest::testEulerAngleClassTestCreation()
   {
      // test that it initializes to the identity
      gmtl::EulerAngle3f q;
      CPPUNIT_ASSERT( q[0] == 0.0f );
      CPPUNIT_ASSERT( q[1] == 0.0f );
      CPPUNIT_ASSERT( q[2] == 0.0f );
      CPPUNIT_ASSERT( q.getOrder() == gmtl::XYZ );

      // try out set...
      q.set( 1.0f, 2.0f, 3.0f, gmtl::ZYX );
      CPPUNIT_ASSERT( q[0] == 1.0f );
      CPPUNIT_ASSERT( q[1] == 2.0f );
      CPPUNIT_ASSERT( q[2] == 3.0f );
      CPPUNIT_ASSERT( q.getOrder() == gmtl::ZYX );

      // try out setting with brackets
      q[0] = 5.0f;
      q[1] = 6.0f;
      q[2] = 7.0f;
      q.setOrder( gmtl::XYZ );
      CPPUNIT_ASSERT( q[0] == 5.0f );
      CPPUNIT_ASSERT( q[1] == 6.0f );
      CPPUNIT_ASSERT( q[2] == 7.0f );
      CPPUNIT_ASSERT( q.getOrder() == gmtl::XYZ );
     
      // try out element constructor
      gmtl::EulerAngle3f q2( 10.0f, 11.0f, 12.0f, gmtl::ZYX );
      CPPUNIT_ASSERT( q2[0] == 10.0f );
      CPPUNIT_ASSERT( q2[1] == 11.0f );
      CPPUNIT_ASSERT( q2[2] == 12.0f );
      CPPUNIT_ASSERT( q2.getOrder() == gmtl::ZYX );

      // try out copy constructor
      gmtl::EulerAngle3f q3( q );
      CPPUNIT_ASSERT( q3[0] == 5.0f );
      CPPUNIT_ASSERT( q3[1] == 6.0f );
      CPPUNIT_ASSERT( q3[2] == 7.0f );
      CPPUNIT_ASSERT( q3.getOrder() == gmtl::XYZ );

      // try out operator=() function
      gmtl::EulerAngle3f q4;
      CPPUNIT_ASSERT( q4[0] == 0.0f );
      CPPUNIT_ASSERT( q4[1] == 0.0f );
      CPPUNIT_ASSERT( q4[2] == 0.0f );
      CPPUNIT_ASSERT( q4.getOrder() == gmtl::XYZ );
      q4 = q2;
      CPPUNIT_ASSERT( q4[0] == 10.0f );
      CPPUNIT_ASSERT( q4[1] == 11.0f );
      CPPUNIT_ASSERT( q4[2] == 12.0f );
      CPPUNIT_ASSERT( q4.getOrder() == gmtl::ZYX );

      // check out the const identities...
      gmtl::EulerAngle3f q9( gmtl::EULERANGLE_IDENTITY3F );
      CPPUNIT_ASSERT( q9[0] == 0.0f );
      CPPUNIT_ASSERT( q9[1] == 0.0f );
      CPPUNIT_ASSERT( q9[2] == 0.0f );
      CPPUNIT_ASSERT( q9.getOrder() == gmtl::XYZ );
   }

   void EulerAngleClassTest::testEulerAngleTimingDefaultConstructor()
   {
      const long iters( 400000 );
      float use_value(1);

      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         // performance of def constructor
         gmtl::EulerAngle3f q;
         use_value += q.mData[0];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("EulerAngleTest/DefaultConstructor", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT( use_value != 0 );
   }

   void EulerAngleClassTest::testEulerAngleTimingElementConstructor()
   {
      const long iters( 400000 );
      float use_value(1);

      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         // performance of element constructor
         gmtl::EulerAngle3f q2( 10.0f, 11.0f, 12.0f, gmtl::XYZ );
         use_value += q2.mData[0];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("EulerAngleTest/ElementConstructor", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT( use_value != 0 );
   }

   void EulerAngleClassTest::testEulerAngleTimingCopyConstructor()
   {
      const long iters( 400000 );
      float use_value(1);
      gmtl::EulerAngle3f q( 67.0f, 68.0f, 69.0f, gmtl::XYZ );

      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         // performance of copy constructor
         gmtl::EulerAngle3f q3( q );
         use_value += q3.mData[0];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("EulerAngleTest/CopyConstructor", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT( use_value != 0 );
   }

   void EulerAngleClassTest::testEulerAngleTimingSet()
   {
      const long iters( 400000 );
      float use_value(0);
      CPPUNIT_METRIC_START_TIMING();
      gmtl::EulerAngle3f q;
      for (long iter = 0; iter < iters; ++iter)
      {
         // performance of set...
         q.set( 1, 2, 3, gmtl::XYZ );
         use_value += q[0];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("EulerAngleTest/set()", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT( use_value >= 0.0f );
   }

   void EulerAngleClassTest::testEulerAngleTimingOpBracket()
   {
      const long iters( 400000 );
      float use_value(0);
      CPPUNIT_METRIC_START_TIMING();
      gmtl::EulerAngle3f q;
      float x = 102.0f, y = 103.0f, z = 101.0f;
      gmtl::RotationOrder w = gmtl::XYZ;
      for (long iter = 0; iter < iters; ++iter)
      {
         // performance of brackets
         q[0] = x;
         q[1] = y;
         q[2] = z;
         q.setOrder( w );
         use_value = use_value + x + y + z + w;
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("EulerAngleTest/operator[]()", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT( use_value > 0.0f );
   }

   void EulerAngleClassTest::testEulerAngleTimingGetData()
   {
      const long iters( 400000 );
      float use_value(0);
      CPPUNIT_METRIC_START_TIMING();
      gmtl::EulerAngle3f q( 1, 2, 3, gmtl::XYZ );
      for (long iter = 0; iter < iters; ++iter)
      {
         // performance of getData...
         const float* d = q.getData();
         use_value += d[1];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("EulerAngleTest/getData()", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT( use_value > 0.0f );
   }

   void EulerAngleClassTest::testEulerAngleTimingOpEqual()
   {
      const long iters( 400000 );
      gmtl::EulerAngle3f q4, q2( 0.0f, 2.0f, 1.0f, gmtl::XYZ );
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         // performance of operator=() function
         q4 = q2;
         q2[0] += q4[2];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("EulerAngleTest/operator=()", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT( q4[0] != 3498.0f );
   }
}
