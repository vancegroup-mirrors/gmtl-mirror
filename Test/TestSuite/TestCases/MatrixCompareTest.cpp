/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: MatrixCompareTest.cpp,v $
 * Date modified: $Date: 2002-03-18 21:57:53 $
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
* modify it under th MathPrimitives  [PrimName]Ops.h  Vec & Point [100%] -ab
Matrix [] -km Transformations XformInterface? Xform.h   Collision detection CollisionInterface? Intersection.h   Bounding volumes BoundingInterface? Containment.h   Math factories MathFactories Builder.h  e terms of the GNU Lesser General Public
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
#include "MatrixCompareTest.h"
#include <cppunit/extensions/MetricRegistry.h>

namespace gmtlTest {
   void MatrixCompareTest::testMatEqualityFloatTest()
   {
      testEqual<float, 5, 5>::go();
      testEqual<float, 5, 4>::go();
      testEqual<float, 4, 5>::go();
      testEqual<float, 4, 4>::go();
      testEqual<float, 4, 3>::go();
      testEqual<float, 3, 4>::go();
      testEqual<float, 4, 3>::go();
      testEqual<float, 3, 3>::go();
      testEqual<float, 3, 2>::go();
      testEqual<float, 2, 3>::go();
      testEqual<float, 2, 2>::go();
      testEqual<float, 2, 1>::go();
      testEqual<float, 1, 2>::go();
      testEqual<float, 1, 1>::go();
   }

   void MatrixCompareTest::testMatEqualityDoubleTest()
   {
      testEqual<double, 5, 5>::go();
      testEqual<double, 5, 4>::go();
      testEqual<double, 4, 5>::go();
      testEqual<double, 4, 4>::go();
      testEqual<double, 4, 3>::go();
      testEqual<double, 3, 4>::go();
      testEqual<double, 4, 3>::go();
      testEqual<double, 3, 3>::go();
      testEqual<double, 3, 2>::go();
      testEqual<double, 2, 3>::go();
      testEqual<double, 2, 2>::go();
      testEqual<double, 2, 1>::go();
      testEqual<double, 1, 2>::go();
      testEqual<double, 1, 1>::go();
   }

   void MatrixCompareTest::testMatEqualityIntTest()
   {
      testEqual<int, 5, 5>::go();
      testEqual<int, 5, 4>::go();
      testEqual<int, 4, 5>::go();
      testEqual<int, 4, 4>::go();
      testEqual<int, 4, 3>::go();
      testEqual<int, 3, 4>::go();
      testEqual<int, 4, 3>::go();
      testEqual<int, 3, 3>::go();
      testEqual<int, 3, 2>::go();
      testEqual<int, 2, 3>::go();
      testEqual<int, 2, 2>::go();
      testEqual<int, 2, 1>::go();
      testEqual<int, 1, 2>::go();
      testEqual<int, 1, 1>::go();
   }

   void MatrixCompareTest::testMatTimingOpEqualityTest()
   {
      // Test overhead of creation
      const long iters(25000);

      gmtl::Matrix<float, 1, 1> src_mat11;
      gmtl::Matrix<float, 2, 2> src_mat22;
      gmtl::Matrix<float, 3, 3> src_mat33;
      gmtl::Matrix<float, 3, 4> src_mat34;
      gmtl::Matrix<float, 4, 4> src_mat44;
      gmtl::Matrix<double, 10, 1> src_mat101;

      // half will be equal
      src_mat11[0] = 1.0f;
      src_mat22[0] = 1.0f;
      src_mat33[4] = 2.0f;

      gmtl::Matrix<float, 1, 1> test_mat11( src_mat11 );
      gmtl::Matrix<float, 2, 2> test_mat22( src_mat22 );
      gmtl::Matrix<float, 3, 3> test_mat33( src_mat33 );
      gmtl::Matrix<float, 3, 4> test_mat34( src_mat34 );
      gmtl::Matrix<float, 4, 4> test_mat44( src_mat44 );
      gmtl::Matrix<double, 10, 1> test_mat101( src_mat101 );

      // half will be not equal
      src_mat34[5] = 2.0f;
      src_mat44[15] = 3.0f;
      src_mat101[9] = 1.0f;

      unsigned true_count(0);

      CPPUNIT_METRIC_START_TIMING();
      for( long iter=0;iter<iters; ++iter)
      {
         if (src_mat11 == test_mat11)
            ++true_count;
         if (src_mat22 == test_mat22)
            ++true_count;
         if (src_mat33 == test_mat33)
            ++true_count;
         if (src_mat34 == test_mat34)
            ++true_count;
         if (src_mat44 == test_mat44)
            ++true_count;
         if (src_mat101 == test_mat101)
            ++true_count;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixCompareTest/OpEqualityTest", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      // make sure compiler uses true_count
      CPPUNIT_ASSERT( true_count > 0 );
   }

   void MatrixCompareTest::testMatTimingOpNotEqualityTest()
   {
      // Test overhead of creation
      const long iters(25000);

      gmtl::Matrix<float, 1, 1> src_mat11;
      gmtl::Matrix<float, 2, 2> src_mat22;
      gmtl::Matrix<float, 3, 3> src_mat33;
      gmtl::Matrix<float, 3, 4> src_mat34;
      gmtl::Matrix<float, 4, 4> src_mat44;
      gmtl::Matrix<double, 10, 1> src_mat101;

      // half will be equal
      src_mat11[0] = 1.0f;
      src_mat22[0] = 1.0f;
      src_mat33[4] = 2.0f;

      gmtl::Matrix<float, 1, 1> test_mat11( src_mat11 );
      gmtl::Matrix<float, 2, 2> test_mat22( src_mat22 );
      gmtl::Matrix<float, 3, 3> test_mat33( src_mat33 );
      gmtl::Matrix<float, 3, 4> test_mat34( src_mat34 );
      gmtl::Matrix<float, 4, 4> test_mat44( src_mat44 );
      gmtl::Matrix<double, 10, 1> test_mat101( src_mat101 );

      // half will be not equal
      src_mat34[5] = 2.0f;
      src_mat44[15] = 3.0f;
      src_mat101[9] = 1.0f;

      unsigned true_count(0);

      CPPUNIT_METRIC_START_TIMING();
      for( long iter=0;iter<iters; ++iter)
      {
         if (src_mat11 != test_mat11)
            ++true_count;
         if (src_mat22 != test_mat22)
            ++true_count;
         if (src_mat33 != test_mat33)
            ++true_count;
         if (src_mat34 != test_mat34)
            ++true_count;
         if (src_mat44 != test_mat44)
            ++true_count;
         if (src_mat101 != test_mat101)
            ++true_count;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixCompareTest/OpNotEqualityTest", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      // make sure compiler uses true_count
      CPPUNIT_ASSERT( true_count > 0 );
   }

   void MatrixCompareTest::testMatTimingIsEqualTest()
   {
      // Test overhead of creation
      const long iters(25000);

      gmtl::Matrix<float, 1, 1> src_mat11;
      gmtl::Matrix<float, 2, 2> src_mat22;
      gmtl::Matrix<float, 3, 3> src_mat33;
      gmtl::Matrix<float, 3, 4> src_mat34;
      gmtl::Matrix<float, 4, 4> src_mat44;
      gmtl::Matrix<double, 10, 1> src_mat101;

      // half will be equal
      src_mat11[0] = 1.0f;
      src_mat22[0] = 1.0f;
      src_mat33[4] = 2.0f;

      gmtl::Matrix<float, 1, 1> test_mat11( src_mat11 );
      gmtl::Matrix<float, 2, 2> test_mat22( src_mat22 );
      gmtl::Matrix<float, 3, 3> test_mat33( src_mat33 );
      gmtl::Matrix<float, 3, 4> test_mat34( src_mat34 );
      gmtl::Matrix<float, 4, 4> test_mat44( src_mat44 );
      gmtl::Matrix<double, 10, 1> test_mat101( src_mat101 );

      // half will be not equal
      src_mat34[5] = 2.0f;
      src_mat44[15] = 3.0f;
      src_mat101[9] = 1.0f;

      unsigned true_count(0);

      CPPUNIT_METRIC_START_TIMING();
      for( long iter=0;iter<iters; ++iter)
      {
         if (gmtl::isEqual( src_mat11,  test_mat11, 0.0f ))
            ++true_count;
         if (gmtl::isEqual( src_mat22,  test_mat22, 0.2f ))
            ++true_count;
         if (gmtl::isEqual( src_mat33,  test_mat33, 0.3f ))
            ++true_count;
         if (gmtl::isEqual( src_mat34,  test_mat34, 0.6f ))
            ++true_count;
         if (gmtl::isEqual( src_mat44,  test_mat44, 0.8f ))
            ++true_count;
         if (gmtl::isEqual( src_mat101, test_mat101, 111.1 ))
            ++true_count;
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixCompareTest/IsEqualTest", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      // make sure compiler uses true_count
      CPPUNIT_ASSERT( true_count > 0 );
   }
}
