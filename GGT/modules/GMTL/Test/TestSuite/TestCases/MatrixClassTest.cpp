/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: MatrixClassTest.cpp,v $
 * Date modified: $Date: 2002-03-18 23:40:46 $
 * Version:       $Revision: 1.2 $
 * -----------------------------------------------------------------
 *
 *********************************************************** ggt-head end */
/*************************************************************** ggt-cpr beg
*
* GGT: The Generic Graphics Toolkit
* Copyright (C) 2001, 2002 Allen Bierbaum
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
#include "MatrixClassTest.h"
#include <cppunit/extensions/MetricRegistry.h>

namespace gmtlTest {
   void MatrixClassTest::testTimingDefaultConstructor()
   {
      // Test overhead of creation
      const long iters(25000);
      float use_value(0);
      CPPUNIT_METRIC_START_TIMING();

      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::Matrix<float, 1, 1> test_mat11;
         test_mat11[0] = 1.0f;
         gmtl::Matrix<float, 2, 2> test_mat22;
         test_mat22[0] = 1.0f;
         gmtl::Matrix<float, 3, 3> test_mat33;
         test_mat33[4] = 2.0f;
         gmtl::Matrix<float, 3, 4> test_mat34;
         test_mat34[5] = 2.0f;
         gmtl::Matrix<float, 4, 4> test_mat44;
         test_mat44[15] = 3.0f;
         gmtl::Matrix<double, 10, 1> test_mat101;
         test_mat101[9] = 1.0;

         use_value = use_value + test_mat11[0] + test_mat22[0] + test_mat33[4] +
                     test_mat34[5] + test_mat44[15] + test_mat101[9];
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixTest/ConstructorOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT( use_value > 0.0f );
   }

   void MatrixClassTest::testTimingCopyConstructor()
   {
      gmtl::Matrix<float, 1, 1> src_mat11;
      src_mat11[0] = 1.0f;
      gmtl::Matrix<float, 2, 2> src_mat22;
      src_mat22[0] = 1.0f;
      gmtl::Matrix<float, 3, 3> src_mat33;
      src_mat33[4] = 2.0f;
      gmtl::Matrix<float, 3, 4> src_mat34;
      src_mat34[5] = 2.0f;
      gmtl::Matrix<float, 4, 4> src_mat44;
      src_mat44[15] = 3.0f;
      gmtl::Matrix<double, 10, 1> src_mat101;
      src_mat101[9] = 1.0f;

      // Test overhead of creation
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();

      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::Matrix<float, 1, 1> test_mat11( src_mat11 );
         gmtl::Matrix<float, 2, 2> test_mat22( src_mat22 );
         gmtl::Matrix<float, 3, 3> test_mat33( src_mat33 );
         gmtl::Matrix<float, 3, 4> test_mat34( src_mat34 );
         gmtl::Matrix<float, 4, 4> test_mat44( src_mat44 );
         gmtl::Matrix<double, 10, 1> test_mat101( src_mat101 );

         test_mat11[0] = 1.0f;
         test_mat22[0] = 1.0f;
         test_mat33[4] = 2.0f;
         test_mat34[5] = 2.0f;
         test_mat44[15] = 3.0f;
         test_mat101[9] = 1.0f;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixTest/CopyConstructorOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void MatrixClassTest::testTimingOpEqual()
   {
      gmtl::Matrix<float, 1, 1> src_mat11;
      src_mat11[0] = 1.0f;
      gmtl::Matrix<float, 2, 2> src_mat22;
      src_mat22[0] = 1.0f;
      gmtl::Matrix<float, 3, 3> src_mat33;
      src_mat33[4] = 2.0f;
      gmtl::Matrix<float, 3, 4> src_mat34;
      src_mat34[5] = 2.0f;
      gmtl::Matrix<double, 4, 4> src_mat44;
      src_mat44[15] = 3.0;
      gmtl::Matrix<float, 10, 1> src_mat101;
      src_mat101[9] = 1.0f;

      // Test overhead of creation
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();

      gmtl::Matrix<float, 1, 1> test_mat11;
      gmtl::Matrix<float, 2, 2> test_mat22;
      gmtl::Matrix<float, 3, 3> test_mat33;
      gmtl::Matrix<float, 3, 4> test_mat34;
      gmtl::Matrix<double, 4, 4> test_mat44;
      gmtl::Matrix<float, 10, 1> test_mat101;

      for (long iter = 0; iter < iters; ++iter)
      {
         test_mat11 = src_mat11;
         test_mat22 = src_mat22;
         test_mat33 = src_mat33;
         test_mat34 = src_mat34;
         test_mat44 = src_mat44;
         test_mat101 = src_mat101;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixTest/OpEqualOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void MatrixClassTest::testTimingOpParen()
   {
      // Test overhead of creation
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();

      gmtl::Matrix<float, 1, 1> test_mat11;
      gmtl::Matrix<float, 2, 2> test_mat22;
      gmtl::Matrix<float, 3, 3> test_mat33;
      gmtl::Matrix<float, 3, 4> test_mat34;
      gmtl::Matrix<double, 4, 4> test_mat44;
      gmtl::Matrix<float, 10, 1> test_mat101;

      for (long iter = 0; iter < iters; ++iter)
      {
         test_mat11( 0,0 ) = 0.0f;
         test_mat22( 1,1 ) = 0.0f;
         test_mat33( 1,1 ) = 0.0f;
         test_mat34( 1,2 ) = 0.0f;
         test_mat44( 3,3 ) = 0.0f;
         test_mat101( 9,0 ) = 0.0f;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixTest/OpParenOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void MatrixClassTest::testTimingOpBracket()
   {
      // Test overhead of creation
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();

      gmtl::Matrix<float, 1, 1> test_mat11;
      gmtl::Matrix<float, 2, 2> test_mat22;
      gmtl::Matrix<float, 3, 3> test_mat33;
      gmtl::Matrix<float, 3, 4> test_mat34;
      gmtl::Matrix<double, 4, 4> test_mat44;
      gmtl::Matrix<float, 10, 1> test_mat101;

      for (long iter = 0; iter < iters; ++iter)
      {
         test_mat11[0] = 0.0f;
         test_mat22[3] = 0.0f;
         test_mat33[8] = 0.0f;
         test_mat34[11] = 0.0f;
         test_mat44[15] = 0.0f;
         test_mat101[9] = 0.0f;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixTest/OpBracketOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void MatrixClassTest::testTimingSetPtr()
   {
      // Test overhead of creation
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();

      gmtl::Matrix<float, 2, 2> test_mat22;
      gmtl::Matrix<float, 3, 3> test_mat33;
      gmtl::Matrix<float, 3, 4> test_mat34;
      gmtl::Matrix<double, 4, 4> test_mat44;

      for (long iter = 0; iter < iters; ++iter)
      {
         test_mat22.set( gmtl::MAT_IDENTITY22F.getData() );
         test_mat33.set( gmtl::MAT_IDENTITY33F.getData() );
         test_mat34.set( gmtl::MAT_IDENTITY34F.getData() );
         test_mat44.set( gmtl::MAT_IDENTITY44D.getData() );
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixTest/SetPtrOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void MatrixClassTest::testTimingSetTransposePtr()
   {
      gmtl::Matrix<float, 2, 2> test_mat22;
      gmtl::Matrix<float, 3, 3> test_mat33;
      gmtl::Matrix<float, 3, 4> test_mat34;
      gmtl::Matrix<double, 4, 4> test_mat44;

      // Test overhead of creation
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();

      for (long iter = 0; iter < iters; ++iter)
      {
         test_mat22.setTranspose( gmtl::MAT_IDENTITY22F.getData() );
         test_mat33.setTranspose( gmtl::MAT_IDENTITY33F.getData() );
         test_mat34.setTranspose( gmtl::MAT_IDENTITY34F.getData() );
         test_mat44.setTranspose( gmtl::MAT_IDENTITY44D.getData() );
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixTest/SetTransposePtrOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void MatrixClassTest::testTimingGetData()
   {
      // Test overhead of creation
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();

      gmtl::Matrix<float, 2, 2> test_mat22;
      gmtl::Matrix<float, 3, 3> test_mat33;
      gmtl::Matrix<float, 3, 4> test_mat34;
      gmtl::Matrix<double, 4, 4> test_mat44;
      float bok = 0.0f;
      double bokk = 0.0;
      for (long iter = 0; iter < iters; ++iter)
      {
         const float* temp1 = test_mat22.getData();
         bok += temp1[0];
         const float* temp2 = test_mat33.getData();
         bok += temp2[3];
         const float* temp3 = test_mat34.getData();
         bok += temp3[11];
         const double* temp4 = test_mat44.getData();
         bokk += temp4[15];
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixTest/GetDataOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void MatrixClassTest::testTimingSet()
   {
      // Test overhead of creation
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();

      gmtl::Matrix<float, 2, 2> test_mat22;
      gmtl::Matrix<float, 3, 3> test_mat33;
      gmtl::Matrix<float, 3, 4> test_mat34;
      gmtl::Matrix<double, 4, 4> test_mat44;

      for (long iter = 0; iter < iters; ++iter)
      {
         test_mat22.set( 1,2,3,4 );
         test_mat33.set( 2,3,4,5,6,7,7,10,1451235 );
         test_mat34.set( 2,3,4,5,6,7,7,10,1451235,1,2,3 );
         test_mat44.set( 2,3,4,5,6,7,7,10,1451235,1,2,3,1,2,3,4 );
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixTest/SetOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void MatrixClassTest::testMatrixIdentity()
   {
      // make sure identity constants are set up correctly.
      {
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY44F( 0, 0  ) == 1.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY44F( 1, 1  ) == 1.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY44F( 2, 2  ) == 1.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY44F( 3, 3  ) == 1.0f );

         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY44F( 1, 0  ) == 0.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY44F( 2, 0  ) == 0.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY44F( 3, 0  ) == 0.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY44F( 0, 1  ) == 0.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY44F( 2, 1  ) == 0.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY44F( 3, 1  ) == 0.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY44F( 0, 2  ) == 0.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY44F( 1, 2  ) == 0.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY44F( 3, 2  ) == 0.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY44F( 0, 3  ) == 0.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY44F( 1, 3  ) == 0.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY44F( 2, 3  ) == 0.0f );
      }

      {
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY34F( 0, 0 ) == 1.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY34F( 1, 1 ) == 1.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY34F( 2, 2 ) == 1.0f );

         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY34F( 1, 0 ) == 0.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY34F( 2, 0 ) == 0.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY34F( 0, 1 ) == 0.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY34F( 2, 1 ) == 0.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY34F( 0, 2 ) == 0.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY34F( 1, 2 ) == 0.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY34F( 0, 3 ) == 0.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY34F( 1, 3 ) == 0.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY34F( 2, 3 ) == 0.0f );
      }

      {
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY33F( 0, 0 ) == 1.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY33F( 1, 1 ) == 1.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY33F( 2, 2 ) == 1.0f );

         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY33F( 1, 0 ) == 0.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY33F( 2, 0 ) == 0.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY33F( 0, 1 ) == 0.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY33F( 2, 1 ) == 0.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY33F( 0, 2 ) == 0.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY33F( 1, 2 ) == 0.0f );
      }

      {
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY23F( 0, 0 ) == 1.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY23F( 1, 1 ) == 1.0f );

         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY23F( 1, 0 ) == 0.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY23F( 0, 1 ) == 0.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY23F( 0, 2 ) == 0.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY23F( 1, 2 ) == 0.0f );
      }

      {
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY22F( 0, 0 ) == 1.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY22F( 1, 1 ) == 1.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY22F( 1, 0 ) == 0.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY22F( 0, 1 ) == 0.0f );
      }

      // make sure default constructor inits to ident
      {
         gmtl::Matrix44f test_mat;
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 2, 2 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 3, 3 ) == 1.0f );

         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 3, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 3, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 2 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 1, 2 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 3, 2 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 3 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 1, 3 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 3 ) == 0.0f );
      }

      {
         gmtl::Matrix34f test_mat;
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 2, 2 ) == 1.0f );

         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 2 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 1, 2 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 3 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 1, 3 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 3 ) == 0.0f );
      }

      {
         gmtl::Matrix33f test_mat;
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 2, 2 ) == 1.0f );

         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 2 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 1, 2 ) == 0.0f );
      }

      {
         gmtl::Matrix23f test_mat;
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 1.0f );

         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 2 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 1, 2 ) == 0.0f );
      }
      {
         gmtl::Matrix22f test_mat;
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 0.0f );
      }

      // make sure copy constructor works.
      {
         gmtl::Matrix44f test_mat( gmtl::MAT_IDENTITY44F );
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 2, 2 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 3, 3 ) == 1.0f );

         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 3, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 3, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 2 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 1, 2 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 3, 2 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 3 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 1, 3 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 3 ) == 0.0f );
      }

      {
         gmtl::Matrix34f test_mat( gmtl::MAT_IDENTITY34F );
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 2, 2 ) == 1.0f );

         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 2 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 1, 2 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 3 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 1, 3 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 3 ) == 0.0f );
      }

      {
         gmtl::Matrix33f test_mat( gmtl::MAT_IDENTITY33F );
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 2, 2 ) == 1.0f );

         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 2 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 1, 2 ) == 0.0f );
      }

      // make sure operator= works:
      {
         gmtl::Matrix44f test_mat;
         test_mat = gmtl::MAT_IDENTITY44F;
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 2, 2 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 3, 3 ) == 1.0f );

         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 3, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 3, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 2 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 1, 2 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 3, 2 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 3 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 1, 3 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 3 ) == 0.0f );
      }

      {
         gmtl::Matrix34f test_mat;
         test_mat = gmtl::MAT_IDENTITY34F;
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 2, 2 ) == 1.0f );

         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 2 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 1, 2 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 3 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 1, 3 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 3 ) == 0.0f );
      }

      {
         gmtl::Matrix33f test_mat( gmtl::MAT_IDENTITY33F );
         test_mat = gmtl::MAT_IDENTITY33F;
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 2, 2 ) == 1.0f );

         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 2 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 1, 2 ) == 0.0f );
      }

      {
         gmtl::Matrix23f test_mat( gmtl::MAT_IDENTITY23F );
         test_mat = gmtl::MAT_IDENTITY23F;
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 1.0f );

         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 2 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 1, 2 ) == 0.0f );
      }
      {
         gmtl::Matrix22f test_mat( gmtl::MAT_IDENTITY22F );
         test_mat = gmtl::MAT_IDENTITY22F;
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 1.0f );

         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 0.0f );
      }
   }

   void MatrixClassTest::testMatrixSetPtr()
   {
      matrixSetPtr<float>::go();
      matrixSetPtr<double>::go();
      matrixSetPtr<int>::go();
      matrixSetPtr<long>::go();
      matrixSetPtr<char>::go();
      matrixSetPtr<short>::go();
   }

   void MatrixClassTest::testMatrixSetTransposePtr()
   {
      matrixSetTransposePtr<float>::go();
      matrixSetTransposePtr<double>::go();
      matrixSetTransposePtr<int>::go();
      matrixSetTransposePtr<long>::go();
      matrixSetTransposePtr<char>::go();
      matrixSetTransposePtr<short>::go();
   }

   void MatrixClassTest::testMatrix44Creation()
   {
      // make sure setter and getters work (float* setter tested in a different test)
      gmtl::Matrix44f src_mat;
      src_mat.set( 0.0f,  1.0f,  2.0f,  3.0f, 
                   4.0f,  5.0f,  6.0f,  7.0f, 
                   8.0f,  9.0f,  10.0f, 11.0f, 
                   12.0f, 13.0f, 14.0f, 15.0f);

      // test that operator[] is sane
      {
         CPPUNIT_ASSERT( src_mat[0]   == 0 );
         CPPUNIT_ASSERT( src_mat[1]   == 4 );
         CPPUNIT_ASSERT( src_mat[2]   == 8 );
         CPPUNIT_ASSERT( src_mat[3]   == 12 );
         CPPUNIT_ASSERT( src_mat[4]   == 1 );
         CPPUNIT_ASSERT( src_mat[5]   == 5 );
         CPPUNIT_ASSERT( src_mat[6]   == 9 );
         CPPUNIT_ASSERT( src_mat[7]   == 13 );
         CPPUNIT_ASSERT( src_mat[8]   == 2 );
         CPPUNIT_ASSERT( src_mat[9]   == 6 );
         CPPUNIT_ASSERT( src_mat[10]  == 10 );
         CPPUNIT_ASSERT( src_mat[11]  == 14 );
         CPPUNIT_ASSERT( src_mat[12]  == 3 );
         CPPUNIT_ASSERT( src_mat[13]  == 7 );
         CPPUNIT_ASSERT( src_mat[14]  == 11 );
         CPPUNIT_ASSERT( src_mat[15]  == 15 );
      }
      // test that operator() is sane (points to what we expect)
      {
         CPPUNIT_ASSERT( src_mat( 0, 0 ) == 0 );
         CPPUNIT_ASSERT( src_mat( 1, 0 ) == 4 );
         CPPUNIT_ASSERT( src_mat( 2, 0 ) == 8 );
         CPPUNIT_ASSERT( src_mat( 3, 0 ) == 12 );
         CPPUNIT_ASSERT( src_mat( 0, 1 ) == 1 );
         CPPUNIT_ASSERT( src_mat( 1, 1 ) == 5 );
         CPPUNIT_ASSERT( src_mat( 2, 1 ) == 9 );
         CPPUNIT_ASSERT( src_mat( 3, 1 ) == 13 );
         CPPUNIT_ASSERT( src_mat( 0, 2 ) == 2 );
         CPPUNIT_ASSERT( src_mat( 1, 2 ) == 6 );
         CPPUNIT_ASSERT( src_mat( 2, 2 ) == 10 );
         CPPUNIT_ASSERT( src_mat( 3, 2 ) == 14 );
         CPPUNIT_ASSERT( src_mat( 0, 3 ) == 3 );
         CPPUNIT_ASSERT( src_mat( 1, 3 ) == 7 );
         CPPUNIT_ASSERT( src_mat( 2, 3 ) == 11 );
         CPPUNIT_ASSERT( src_mat( 3, 3 ) == 15 );
      }

      // test that operator() and operator[] are equivelent
      {
         gmtl::Matrix44f src_mat( gmtl::MAT_IDENTITY44F );
         CPPUNIT_ASSERT( src_mat( 0, 0 ) == src_mat[0] );
         CPPUNIT_ASSERT( src_mat( 1, 0 ) == src_mat[1] );
         CPPUNIT_ASSERT( src_mat( 2, 0 ) == src_mat[2] );
         CPPUNIT_ASSERT( src_mat( 3, 0 ) == src_mat[3] );
         CPPUNIT_ASSERT( src_mat( 0, 1 ) == src_mat[4] );
         CPPUNIT_ASSERT( src_mat( 1, 1 ) == src_mat[5] );
         CPPUNIT_ASSERT( src_mat( 2, 1 ) == src_mat[6] );
         CPPUNIT_ASSERT( src_mat( 3, 1 ) == src_mat[7] );
         CPPUNIT_ASSERT( src_mat( 0, 2 ) == src_mat[8] );
         CPPUNIT_ASSERT( src_mat( 1, 2 ) == src_mat[9] );
         CPPUNIT_ASSERT( src_mat( 2, 2 ) == src_mat[10] );
         CPPUNIT_ASSERT( src_mat( 3, 2 ) == src_mat[11] );
         CPPUNIT_ASSERT( src_mat( 0, 3 ) == src_mat[12] );
         CPPUNIT_ASSERT( src_mat( 1, 3 ) == src_mat[13] );
         CPPUNIT_ASSERT( src_mat( 2, 3 ) == src_mat[14] );
         CPPUNIT_ASSERT( src_mat( 3, 3 ) == src_mat[15] );
      }
      // make sure copy constructor works.
      {
         gmtl::Matrix44f test_mat( src_mat );
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 0 );
         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 4 );
         CPPUNIT_ASSERT( test_mat( 2, 0 ) == 8 );
         CPPUNIT_ASSERT( test_mat( 3, 0 ) == 12 );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 1 );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 5 );
         CPPUNIT_ASSERT( test_mat( 2, 1 ) == 9 );
         CPPUNIT_ASSERT( test_mat( 3, 1 ) == 13 );
         CPPUNIT_ASSERT( test_mat( 0, 2 ) == 2 );
         CPPUNIT_ASSERT( test_mat( 1, 2 ) == 6 );
         CPPUNIT_ASSERT( test_mat( 2, 2 ) == 10 );
         CPPUNIT_ASSERT( test_mat( 3, 2 ) == 14 );
         CPPUNIT_ASSERT( test_mat( 0, 3 ) == 3 );
         CPPUNIT_ASSERT( test_mat( 1, 3 ) == 7 );
         CPPUNIT_ASSERT( test_mat( 2, 3 ) == 11 );
         CPPUNIT_ASSERT( test_mat( 3, 3 ) == 15 );
      }
      // make sure operator= works
      {
         gmtl::Matrix44f test_mat;
         // it is identity matrix now...
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 2, 2 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 3, 3 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 3, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 3, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 2 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 1, 2 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 3, 2 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 3 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 1, 3 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 3 ) == 0.0f );
         test_mat = src_mat;
         // it should have changed...
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 0 );
         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 4 );
         CPPUNIT_ASSERT( test_mat( 2, 0 ) == 8 );
         CPPUNIT_ASSERT( test_mat( 3, 0 ) == 12 );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 1 );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 5 );
         CPPUNIT_ASSERT( test_mat( 2, 1 ) == 9 );
         CPPUNIT_ASSERT( test_mat( 3, 1 ) == 13 );
         CPPUNIT_ASSERT( test_mat( 0, 2 ) == 2 );
         CPPUNIT_ASSERT( test_mat( 1, 2 ) == 6 );
         CPPUNIT_ASSERT( test_mat( 2, 2 ) == 10 );
         CPPUNIT_ASSERT( test_mat( 3, 2 ) == 14 );
         CPPUNIT_ASSERT( test_mat( 0, 3 ) == 3 );
         CPPUNIT_ASSERT( test_mat( 1, 3 ) == 7 );
         CPPUNIT_ASSERT( test_mat( 2, 3 ) == 11 );
         CPPUNIT_ASSERT( test_mat( 3, 3 ) == 15 );
      }
   }

   void MatrixClassTest::testMatrix34Creation()
   {
      // make sure setter and getters work (float* setter tested in a different test)
      gmtl::Matrix34f src_mat;
      src_mat.set( 0, 1, 2, 3, 
                   4, 5, 6, 7, 
                   8, 9, 10, 11);

      // test that operator[] is sane
      {
         CPPUNIT_ASSERT( src_mat[0]  == 0 );
         CPPUNIT_ASSERT( src_mat[1]  == 4 );
         CPPUNIT_ASSERT( src_mat[2]  == 8 );
         CPPUNIT_ASSERT( src_mat[3]  == 1 );
         CPPUNIT_ASSERT( src_mat[4]  == 5 );
         CPPUNIT_ASSERT( src_mat[5]  == 9 );
         CPPUNIT_ASSERT( src_mat[6]  == 2 );
         CPPUNIT_ASSERT( src_mat[7]  == 6 );
         CPPUNIT_ASSERT( src_mat[8]  == 10 );
         CPPUNIT_ASSERT( src_mat[9]  == 3 );
         CPPUNIT_ASSERT( src_mat[10] == 7 );
         CPPUNIT_ASSERT( src_mat[11] == 11 );
      }
      // test that operator() is sane (points to what we expect)
      {
         CPPUNIT_ASSERT( src_mat( 0, 0 ) == 0 );
         CPPUNIT_ASSERT( src_mat( 1, 0 ) == 4 );
         CPPUNIT_ASSERT( src_mat( 2, 0 ) == 8 );
         CPPUNIT_ASSERT( src_mat( 0, 1 ) == 1 );
         CPPUNIT_ASSERT( src_mat( 1, 1 ) == 5 );
         CPPUNIT_ASSERT( src_mat( 2, 1 ) == 9 );
         CPPUNIT_ASSERT( src_mat( 0, 2 ) == 2 );
         CPPUNIT_ASSERT( src_mat( 1, 2 ) == 6 );
         CPPUNIT_ASSERT( src_mat( 2, 2 ) == 10 );
         CPPUNIT_ASSERT( src_mat( 0, 3 ) == 3 );
         CPPUNIT_ASSERT( src_mat( 1, 3 ) == 7 );
         CPPUNIT_ASSERT( src_mat( 2, 3 ) == 11 );
      }

      // test that operator() and operator[] are equivelent
      {
         gmtl::Matrix34f src_mat( gmtl::MAT_IDENTITY34F );
         CPPUNIT_ASSERT( src_mat( 0, 0 ) == src_mat[0] );
         CPPUNIT_ASSERT( src_mat( 1, 0 ) == src_mat[1] );
         CPPUNIT_ASSERT( src_mat( 2, 0 ) == src_mat[2] );
         CPPUNIT_ASSERT( src_mat( 0, 1 ) == src_mat[3] );
         CPPUNIT_ASSERT( src_mat( 1, 1 ) == src_mat[4] );
         CPPUNIT_ASSERT( src_mat( 2, 1 ) == src_mat[5] );
         CPPUNIT_ASSERT( src_mat( 0, 2 ) == src_mat[6] );
         CPPUNIT_ASSERT( src_mat( 1, 2 ) == src_mat[7] );
         CPPUNIT_ASSERT( src_mat( 2, 2 ) == src_mat[8] );
         CPPUNIT_ASSERT( src_mat( 0, 3 ) == src_mat[9] );
         CPPUNIT_ASSERT( src_mat( 1, 3 ) == src_mat[10] );
         CPPUNIT_ASSERT( src_mat( 2, 3 ) == src_mat[11] );
      }
      // make sure copy constructor works.
      {
         gmtl::Matrix34f test_mat( src_mat );
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 0 );
         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 4 );
         CPPUNIT_ASSERT( test_mat( 2, 0 ) == 8 );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 1 );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 5 );
         CPPUNIT_ASSERT( test_mat( 2, 1 ) == 9 );
         CPPUNIT_ASSERT( test_mat( 0, 2 ) == 2 );
         CPPUNIT_ASSERT( test_mat( 1, 2 ) == 6 );
         CPPUNIT_ASSERT( test_mat( 2, 2 ) == 10 );
         CPPUNIT_ASSERT( test_mat( 0, 3 ) == 3 );
         CPPUNIT_ASSERT( test_mat( 1, 3 ) == 7 );
         CPPUNIT_ASSERT( test_mat( 2, 3 ) == 11 );
      }
      // make sure operator= works
      {
         gmtl::Matrix34f test_mat;
         // it is identity matrix now...
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 2, 2 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 2 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 1, 2 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 3 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 1, 3 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 3 ) == 0.0f );
         test_mat = src_mat;
         // it should have changed...
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 0 );
         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 4 );
         CPPUNIT_ASSERT( test_mat( 2, 0 ) == 8 );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 1 );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 5 );
         CPPUNIT_ASSERT( test_mat( 2, 1 ) == 9 );
         CPPUNIT_ASSERT( test_mat( 0, 2 ) == 2 );
         CPPUNIT_ASSERT( test_mat( 1, 2 ) == 6 );
         CPPUNIT_ASSERT( test_mat( 2, 2 ) == 10 );
         CPPUNIT_ASSERT( test_mat( 0, 3 ) == 3 );
         CPPUNIT_ASSERT( test_mat( 1, 3 ) == 7 );
         CPPUNIT_ASSERT( test_mat( 2, 3 ) == 11 );
      }
   }

   void MatrixClassTest::testMatrix33Creation()
   {
      // make sure setter and getters work (float* setter tested in a different test)
      gmtl::Matrix33f src_mat;
      src_mat.set( 0, 1, 2, 
                   3, 4, 5, 
                   6, 7, 8);

      // test that operator[] is sane
      {
         CPPUNIT_ASSERT( src_mat[0] == 0 );
         CPPUNIT_ASSERT( src_mat[1] == 3 );
         CPPUNIT_ASSERT( src_mat[2] == 6 );
         CPPUNIT_ASSERT( src_mat[3] == 1 );
         CPPUNIT_ASSERT( src_mat[4] == 4 );
         CPPUNIT_ASSERT( src_mat[5] == 7 );
         CPPUNIT_ASSERT( src_mat[6] == 2 );
         CPPUNIT_ASSERT( src_mat[7] == 5 );
         CPPUNIT_ASSERT( src_mat[8] == 8 );
      }

      // test that operator() is sane (points to what we expect)
      {
         CPPUNIT_ASSERT( src_mat( 0, 0 ) == 0 );
         CPPUNIT_ASSERT( src_mat( 1, 0 ) == 3 );
         CPPUNIT_ASSERT( src_mat( 2, 0 ) == 6 );
         CPPUNIT_ASSERT( src_mat( 0, 1 ) == 1 );
         CPPUNIT_ASSERT( src_mat( 1, 1 ) == 4 );
         CPPUNIT_ASSERT( src_mat( 2, 1 ) == 7 );
         CPPUNIT_ASSERT( src_mat( 0, 2 ) == 2 );
         CPPUNIT_ASSERT( src_mat( 1, 2 ) == 5 );
         CPPUNIT_ASSERT( src_mat( 2, 2 ) == 8 );
      }

      // test that operator() and operator[] are equivelent
      {
         CPPUNIT_ASSERT( src_mat( 0, 0 ) == src_mat[0] );
         CPPUNIT_ASSERT( src_mat( 1, 0 ) == src_mat[1] );
         CPPUNIT_ASSERT( src_mat( 2, 0 ) == src_mat[2] );
         CPPUNIT_ASSERT( src_mat( 0, 1 ) == src_mat[3] );
         CPPUNIT_ASSERT( src_mat( 1, 1 ) == src_mat[4] );
         CPPUNIT_ASSERT( src_mat( 2, 1 ) == src_mat[5] );
         CPPUNIT_ASSERT( src_mat( 0, 2 ) == src_mat[6] );
         CPPUNIT_ASSERT( src_mat( 1, 2 ) == src_mat[7] );
         CPPUNIT_ASSERT( src_mat( 2, 2 ) == src_mat[8] );
      }
      // make sure copy constructor works.
      {
         gmtl::Matrix33f test_mat( src_mat );
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 0 );
         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 3 );
         CPPUNIT_ASSERT( test_mat( 2, 0 ) == 6 );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 1 );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 4 );
         CPPUNIT_ASSERT( test_mat( 2, 1 ) == 7 );
         CPPUNIT_ASSERT( test_mat( 0, 2 ) == 2 );
         CPPUNIT_ASSERT( test_mat( 1, 2 ) == 5 );
         CPPUNIT_ASSERT( test_mat( 2, 2 ) == 8 );
      }
      // make sure operator= works
      {
         gmtl::Matrix33f test_mat;
         // it is identity matrix now...
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 2, 2 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 2 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 1, 2 ) == 0.0f );
         test_mat = src_mat;
         // it should have changed...
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 0 );
         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 3 );
         CPPUNIT_ASSERT( test_mat( 2, 0 ) == 6 );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 1 );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 4 );
         CPPUNIT_ASSERT( test_mat( 2, 1 ) == 7 );
         CPPUNIT_ASSERT( test_mat( 0, 2 ) == 2 );
         CPPUNIT_ASSERT( test_mat( 1, 2 ) == 5 );
         CPPUNIT_ASSERT( test_mat( 2, 2 ) == 8 );
      }
   }

   void MatrixClassTest::testMatrix23Creation()
   {
      // make sure setter and getters work (float* setter tested in a different test)
      gmtl::Matrix23f src_mat;
      src_mat.set( 0, 1, 2,   
                   3, 4, 5 );

      // test that operator[] is sane
      {
         CPPUNIT_ASSERT( src_mat[0] == 0 );
         CPPUNIT_ASSERT( src_mat[1] == 3 );
         CPPUNIT_ASSERT( src_mat[2] == 1 );
         CPPUNIT_ASSERT( src_mat[3] == 4 );
         CPPUNIT_ASSERT( src_mat[4] == 2 );
         CPPUNIT_ASSERT( src_mat[5] == 5 );
      }

      // test that operator() is sane (points to what we expect)
      {
         CPPUNIT_ASSERT( src_mat( 0, 0 ) == 0 );
         CPPUNIT_ASSERT( src_mat( 1, 0 ) == 3 );
         CPPUNIT_ASSERT( src_mat( 0, 1 ) == 1 );
         CPPUNIT_ASSERT( src_mat( 1, 1 ) == 4 );
         CPPUNIT_ASSERT( src_mat( 0, 2 ) == 2 );
         CPPUNIT_ASSERT( src_mat( 1, 2 ) == 5 );
      }

      // test that operator() and operator[] are equivelent
      {
         CPPUNIT_ASSERT( src_mat( 0, 0 ) == src_mat[0] );
         CPPUNIT_ASSERT( src_mat( 1, 0 ) == src_mat[1] );
         CPPUNIT_ASSERT( src_mat( 0, 1 ) == src_mat[2] );
         CPPUNIT_ASSERT( src_mat( 1, 1 ) == src_mat[3] );
         CPPUNIT_ASSERT( src_mat( 0, 2 ) == src_mat[4] );
         CPPUNIT_ASSERT( src_mat( 1, 2 ) == src_mat[5] );
      }
      // make sure copy constructor works.
      {
         gmtl::Matrix23f test_mat( src_mat );
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 0 );
         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 3 );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 1 );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 4 );
         CPPUNIT_ASSERT( test_mat( 0, 2 ) == 2 );
         CPPUNIT_ASSERT( test_mat( 1, 2 ) == 5 );
      }
      // make sure operator= works
      {
         gmtl::Matrix23f test_mat;
         // it is identity matrix now...
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 0, 2 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 1, 2 ) == 0.0f );
         test_mat = src_mat;
         // it should have changed...
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 0 );
         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 3 );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 1 );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 4 );
         CPPUNIT_ASSERT( test_mat( 0, 2 ) == 2 );
         CPPUNIT_ASSERT( test_mat( 1, 2 ) == 5 );
      }
   }

   void MatrixClassTest::testMatrix22Creation()
   {
      // make sure setter and getters work (float* setter tested in a different test)
      gmtl::Matrix22f src_mat;
      src_mat.set( 0, 1,  
                   2, 3 );

      // test that operator[] is sane
      {
         CPPUNIT_ASSERT( src_mat[0] == 0 );
         CPPUNIT_ASSERT( src_mat[1] == 2 );
         CPPUNIT_ASSERT( src_mat[2] == 1 );
         CPPUNIT_ASSERT( src_mat[3] == 3 );
      }

      // test that operator() is sane (points to what we expect)
      {
         CPPUNIT_ASSERT( src_mat( 0, 0 ) == 0 );
         CPPUNIT_ASSERT( src_mat( 1, 0 ) == 2 );
         CPPUNIT_ASSERT( src_mat( 0, 1 ) == 1 );
         CPPUNIT_ASSERT( src_mat( 1, 1 ) == 3 );
      }

      // test that operator() and operator[] are equivelent
      {
         CPPUNIT_ASSERT( src_mat( 0, 0 ) == src_mat[0] );
         CPPUNIT_ASSERT( src_mat( 1, 0 ) == src_mat[1] );
         CPPUNIT_ASSERT( src_mat( 0, 1 ) == src_mat[2] );
         CPPUNIT_ASSERT( src_mat( 1, 1 ) == src_mat[3] );
      }
      // make sure copy constructor works.
      {
         gmtl::Matrix22f test_mat( src_mat );
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 0 );
         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 2 );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 1 );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 3 );
      }
      // make sure operator= works
      {
         gmtl::Matrix22f test_mat;
         // it is identity matrix now...
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 1.0f );
         test_mat = src_mat;
         // it should have changed...
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 0 );
         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 2 );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 1 );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 3 );
      }
   }






}
