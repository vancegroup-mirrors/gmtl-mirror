
/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: EulerAngleCompareTest.cpp,v $
 * Date modified: $Date: 2002-06-12 19:38:53 $
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
#include "EulerAngleCompareTest.h"
#include <cppunit/extensions/MetricRegistry.h>
#include "gmtl/EulerAngleOps.h"

namespace gmtlTest
{
   void EulerAngleCompareTest::testEulerAngleEqualityFloatTest()
   {
      testEqual<float>::go();
      testEqual<float>::go();
      testEqual<float>::go();
      testEqual<float>::go();
      testEqual<float>::go();
      testEqual<float>::go();
      testEqual<float>::go();
      testEqual<float>::go();
      testEqual<float>::go();
      testEqual<float>::go();
      testEqual<float>::go();
      testEqual<float>::go();
      testEqual<float>::go();
      testEqual<float>::go();
   }

   void EulerAngleCompareTest::testEulerAngleEqualityDoubleTest()
   {
      testEqual<double>::go();
      testEqual<double>::go();
      testEqual<double>::go();
      testEqual<double>::go();
      testEqual<double>::go();
      testEqual<double>::go();
      testEqual<double>::go();
      testEqual<double>::go();
      testEqual<double>::go();
      testEqual<double>::go();
      testEqual<double>::go();
      testEqual<double>::go();
      testEqual<double>::go();
      testEqual<double>::go();
   }

   void EulerAngleCompareTest::testEulerAngleTimingOpEqualityTest()
   {
      // Test overhead of creation
      const long iters(400000);

      gmtl::EulerAngleXYZf src_quat11;
      gmtl::EulerAngleXYZf src_quat22;
      gmtl::EulerAngleXYZf src_quat33;
      gmtl::EulerAngleXYZf src_quat34;
      gmtl::EulerAngleXYZf src_quat44;
      gmtl::EulerAngleXYZd src_quat101;

      // half of them will be equal
      src_quat11[0] = 1.0f;
      src_quat22[2] = 1.0f;
      src_quat33[1] = 2.0f;

      gmtl::EulerAngleXYZf test_quat11( src_quat11 );
      gmtl::EulerAngleXYZf test_quat22( src_quat22 );
      gmtl::EulerAngleXYZf test_quat33( src_quat33 );
      gmtl::EulerAngleXYZf test_quat34( src_quat34 );
      gmtl::EulerAngleXYZf test_quat44( src_quat44 );
      gmtl::EulerAngleXYZd test_quat101( src_quat101 );

      // half will be not equal
      src_quat34[0] = 2.0f;
      src_quat44[1] = 3.0f;
      src_quat101[2] = 1.0;

      unsigned true_count(0);

      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         if (src_quat11 == test_quat11)
            ++true_count;
         if (src_quat22 == test_quat22)
            ++true_count;
         if (src_quat33 == test_quat33)
            ++true_count;
         if (src_quat34 == test_quat34)
            ++true_count;
         if (src_quat44 == test_quat44)
            ++true_count;
         if (src_quat101 == test_quat101)
            ++true_count;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("EulerAngleCompareTest/operator==", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // Make sure the compiler doesn't optimize out true_count
      CPPUNIT_ASSERT( true_count > 0 );
   }

   void EulerAngleCompareTest::testEulerAngleTimingOpNotEqualityTest()
   {
      // Test overhead of creation
      const long iters(400000);

      gmtl::EulerAngleXYZf src_quat11;
      gmtl::EulerAngleXYZf src_quat22;
      gmtl::EulerAngleXYZf src_quat33;
      gmtl::EulerAngleXYZf src_quat34;
      gmtl::EulerAngleXYZf src_quat44;
      gmtl::EulerAngleXYZd src_quat101;

      // half will be equal
      src_quat11[0] = 1.0f;
      src_quat22[2] = 1.0f;
      src_quat33[1] = 2.0f;

      gmtl::EulerAngleXYZf test_quat11( src_quat11 );
      gmtl::EulerAngleXYZf test_quat22( src_quat22 );
      gmtl::EulerAngleXYZf test_quat33( src_quat33 );
      gmtl::EulerAngleXYZf test_quat34( src_quat34 );
      gmtl::EulerAngleXYZf test_quat44( src_quat44 );
      gmtl::EulerAngleXYZd test_quat101( src_quat101 );

      // half will be not equal
      src_quat34[0] = 2.0f;
      src_quat44[1] = 3.0f;
      src_quat101[2] = 1.0f;

      unsigned true_count(0);

      CPPUNIT_METRIC_START_TIMING();
      for( long iter=0;iter<iters; ++iter)
      {
         if (src_quat11 != test_quat11)
            ++true_count;
         if (src_quat22 != test_quat22)
            ++true_count;
         if (src_quat33 != test_quat33)
            ++true_count;
         if (src_quat34 != test_quat34)
            ++true_count;
         if (src_quat44 != test_quat44)
            ++true_count;
         if (src_quat101 != test_quat101)
            ++true_count;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("EulerAngleCompareTest/operator!=", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // Make sure the compiler doesn't optimize out true_count
      CPPUNIT_ASSERT( true_count > 0 );
   }

   void EulerAngleCompareTest::testEulerAngleTimingIsEqualTest()
   {
      // Test overhead of creation
      const long iters(400000);

      gmtl::EulerAngleXYZf src_quat11;
      gmtl::EulerAngleXYZf src_quat22;
      gmtl::EulerAngleXYZf src_quat33;
      gmtl::EulerAngleXYZf src_quat34;
      gmtl::EulerAngleXYZf src_quat44;
      gmtl::EulerAngleXYZd src_quat101;

      // half will be equal
      src_quat11[0] = 1.0f;
      src_quat22[1] = 1.0f;
      src_quat33[2] = 2.0f;

      gmtl::EulerAngleXYZf test_quat11( src_quat11 );
      gmtl::EulerAngleXYZf test_quat22( src_quat22 );
      gmtl::EulerAngleXYZf test_quat33( src_quat33 );
      gmtl::EulerAngleXYZf test_quat34( src_quat34 );
      gmtl::EulerAngleXYZf test_quat44( src_quat44 );
      gmtl::EulerAngleXYZd test_quat101( src_quat101 );

      // half will be not equal
      src_quat34[0] = 23.0f;
      src_quat44[2] = 234.0f;
      src_quat101[1] = 1234.0f;

      unsigned true_count(0);

      CPPUNIT_METRIC_START_TIMING();
      for( long iter=0;iter<iters; ++iter)
      {
         if (gmtl::isEqual( src_quat11,  test_quat11, 0.0f ))
            ++true_count;
         if (gmtl::isEqual( src_quat22,  test_quat22, 0.2f ))
            ++true_count;
         if (gmtl::isEqual( src_quat33,  test_quat33, 0.3f ))
            ++true_count;
         if (gmtl::isEqual( src_quat34,  test_quat34, 0.6f ))
            ++true_count;
         if (gmtl::isEqual( src_quat44,  test_quat44, 0.8f ))
            ++true_count;
         if (gmtl::isEqual( src_quat101, test_quat101, 111.1 ))
            ++true_count;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("EulerAngleCompareTest/isEqual(...)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // Make sure the compiler doesn't optimize out true_count
      CPPUNIT_ASSERT( true_count > 0 );
   }
}
