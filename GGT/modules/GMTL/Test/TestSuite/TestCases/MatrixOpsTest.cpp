/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: MatrixOpsTest.cpp,v $
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
#include "MatrixOpsTest.h"
#include <cppunit/extensions/MetricRegistry.h>

namespace gmtlTest
{
   void MatrixOpsTest::testMatrixIdentity()
   {
      {
         gmtl::Matrix44f test_mat, ident_mat;
         test_mat.set( 0, 1, 2, 3,
                       0, 1, 2, 3,
                       0, 1, 2, 3,
                       0, 1, 2, 3);
         CPPUNIT_ASSERT(test_mat != ident_mat);
         gmtl::identity(test_mat);
         CPPUNIT_ASSERT(test_mat == ident_mat);
      }
   }

   void MatrixOpsTest::testMatrixTimeIdentity44f()
   {
      gmtl::Matrix44f test_mat;
      float bogus_value(0.0f);

      const long iters(50000);
      CPPUNIT_METRIC_START_TIMING();
      for( long iter=0;iter<iters; ++iter)
      {
         test_mat.set( 0, iter+1, iter+2, iter+3,
                       0, 1, 2, 3,
                       0, 1, 2, 3,
                       0, 1, 2, 3);
         gmtl::identity( test_mat );
         bogus_value += test_mat(1,1); // Should add 1 everytime
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixOpsTest/identity(mat44f)", iters, 0.095f, 0.125f);   // warn at 9.5%, error at 12.5%

      // force intelligent compilers to do all the iterations (ie. to not optimize them out),
      // by using the variables computed...
      CPPUNIT_ASSERT_DOUBLES_EQUAL( bogus_value, iters, 0.5f);
   }

   void MatrixOpsTest::testMatrixSetTrans()
   {
      float eps = 0.01f;

      // 3D trans
      {
         gmtl::Matrix34f mat34, expected_result34;
         gmtl::makeRot(expected_result34, 0.5f, 1.0f, -1.0f, gmtl::XYZ);
         expected_result34(0,3) = 21;
         expected_result34(1,3) = 22;
         expected_result34(2,3) = 23;

         gmtl::makeRot(mat34, 0.5f, 1.0f, -1.0f, gmtl::XYZ);
         gmtl::setTrans( mat34, gmtl::Vec3f( 21, 22, 23 ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result34, mat34, eps ) );
      }
      // 3D rot/trans set by homogeneous vector
      {
         gmtl::Matrix34f mat34, expected_result34;
         gmtl::makeRot(expected_result34, 0.5f, 1.0f, -1.0f, gmtl::XYZ);
         expected_result34(0,3) = 42;
         expected_result34(1,3) = 44;
         expected_result34(2,3) = 46;

         gmtl::makeRot(mat34, 0.5f, 1.0f, -1.0f, gmtl::XYZ);
         gmtl::setTrans( mat34, gmtl::Vec4f( 21, 22, 23, 0.5f ) );

         CPPUNIT_ASSERT( gmtl::isEqual( expected_result34, mat34, eps ) );
      }
      // 3D trans
      {
         gmtl::Matrix44f mat44, expected_result44;
         gmtl::makeRot(expected_result44, 0.5f, 1.0f, -1.0f, gmtl::XYZ);
         expected_result44(0,3) = 21;
         expected_result44(1,3) = 22;
         expected_result44(2,3) = 23;

         gmtl::makeRot( mat44, 0.5f, 1.0f, -1.0f, gmtl::XYZ);
         gmtl::setTrans( mat44, gmtl::Vec3f( 21.0f, 22.0f, 23.0f ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result44, mat44, eps ) );
      }
      // 3D rot/trans/skew set by homogeneous vector...
      {
         gmtl::Matrix44f mat44, expected_result44;

         gmtl::makeRot(expected_result44, 0.5f, 1.0f, -1.0f, gmtl::XYZ);
         expected_result44(0,3) = 42;
         expected_result44(1,3) = 44;
         expected_result44(2,3) = 46;

         gmtl::makeRot( mat44, 0.5f, 1.0f, -1.0f, gmtl::XYZ);
         gmtl::setTrans( mat44, gmtl::Vec4f( 21, 22, 23, 0.5f ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result44, mat44, eps ) );
      }
   }

   void MatrixOpsTest::testTimingMakeTrans()
   {
      gmtl::Matrix33f mat33;
      gmtl::Matrix34f mat34;
      gmtl::Matrix44f mat44;
      float a = 1.0f;

      const long iters(100000);

      // 2D translation
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::setTrans( mat33, gmtl::Vec2f( a, 2 ) );
         a += mat33[3];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixOpsTest/setTrans(mat33f,vec2f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat33[3] != 1234.0456f && a != 987654.321f  );


      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::setTrans( mat33, gmtl::Vec3f( 1, a, 1.0f ) ); // homogeneous
         a += mat33[3];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixOpsTest/setTrans(mat33f,vec3f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat33[3] != 1234.0456f && a != 987654.321f  );


      // 3D translation
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::setTrans( mat34, gmtl::Vec3f( a, 32, 121 ) );
         a += mat34[3];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixOpsTest/setTrans(mat34f,vec3f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat34[3] != 1234.0456f && a != 987654.321f  );


      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::setTrans( mat44, gmtl::Vec3f( 30, a, 121 ) );
         a += mat44[3];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixOpsTest/setTrans(mat44f,vec3f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat44[3] != 1234.0456f && a != 987654.321f  );


      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         gmtl::setTrans( mat44, gmtl::Vec4f( 30, 32, a, 1.0f ) ); // homogeneous
         a += mat44[3];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixOpsTest/setTrans(mat44f,vec4f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      CPPUNIT_ASSERT( mat44[3] != 1234.0456f && a != 987654.321f  );
   }

   void MatrixOpsTest::testMatrixTimeTranspose44f()
   {
      gmtl::Matrix<float, 4, 4> test_mat1;
      test_mat1.set( 0,  1,  2,  3,
                     4,  5,  6,  7,
                     8,  9, 10, 11,
                    12, 13, 14, 15 );

      const long iters(50000);
      CPPUNIT_METRIC_START_TIMING();
      for( long iter=0;iter<iters; ++iter)
      {
         gmtl::transpose( test_mat1 );
         test_mat1[2] += test_mat1[3];
         test_mat1[3] -= test_mat1[1];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixOpsTest/transpose(mat44f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // force intelligent compilers to do all the iterations (ie. to not optimize them out),
      // by using the variables computed...
      CPPUNIT_ASSERT( test_mat1[2] != test_mat1[0] );
   }


   void MatrixOpsTest::testMatrixTimeTranspose33d()
   {
      gmtl::Matrix<double, 3, 3> test_mat2;
      test_mat2.set( 0,  1,  2,
                    4,  5,  6,
                    8,  9,  10 );

      const long iters(50000);
      CPPUNIT_METRIC_START_TIMING();
      for( long iter=0;iter<iters; ++iter)
      {
         gmtl::transpose( test_mat2 );
         test_mat2[2] += test_mat2[3];
         test_mat2[3] -= test_mat2[1];
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixOpsTest/transpose(mat33d)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // force intelligent compilers to do all the iterations (ie. to not optimize them out),
      // by using the variables computed...
      CPPUNIT_ASSERT( test_mat2[2] != test_mat2[0] );
   }

   void MatrixOpsTest::testMatrixTimeMult44_mult()
   {
      gmtl::Matrix<float, 4, 4> test_mat1, test_mat2, res_mat;
      test_mat1.set( 0,  1,  2,  3,
                     4,  5,  6,  7,
                     8,  9, 10, 11,
                    12, 13, 14, 15 );
      res_mat = test_mat2 = test_mat1;

      const long iters(50000);
      CPPUNIT_METRIC_START_TIMING();
      for( long iter=0;iter<iters; ++iter)
      {
         gmtl::mult( res_mat, res_mat, test_mat1 );
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixOpsTest/mult(res,mat44f,mat44f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // force intelligent compilers to do all the iterations (ie. to not optimize them out),
      // by using the variables computed...
      CPPUNIT_ASSERT( test_mat1[2] != test_mat2[0] );
      CPPUNIT_ASSERT( res_mat[2] != 1000.0f );
   }

   void MatrixOpsTest::testMatrixTimeMult44_operatorStar()
   {
      gmtl::Matrix<float, 4, 4> test_mat1, test_mat2, res_mat;
      test_mat1.set( 0,  1,  2,  3,
                     4,  5,  6,  7,
                     8,  9, 10, 11,
                    12, 13, 14, 15 );
      res_mat = test_mat2 = test_mat1;

      const long iters(50000);
      CPPUNIT_METRIC_START_TIMING();
      for( long iter=0;iter<iters; ++iter)
      {
         res_mat = test_mat1 * res_mat;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixOpsTest/operator*(mat44f,mat44f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // force intelligent compilers to do all the iterations (ie. to not optimize them out),
      // by using the variables computed...
      CPPUNIT_ASSERT( test_mat1[2] != test_mat2[0] );
      CPPUNIT_ASSERT( res_mat[2] != 1000.0f );
   }

   void MatrixOpsTest::testMatrixTimeMult44f_operatorStarStar()
   {
      gmtl::Matrix<float, 4, 4> test_mat1, test_mat2, res_mat;
      test_mat1.set( 0,  1,  2,  3,
                     4,  5,  6,  7,
                     8,  9, 10, 11,
                    12, 13, 14, 15 );
      res_mat = test_mat2 = test_mat1;

      const long iters(5000);
      CPPUNIT_METRIC_START_TIMING();
      for( long iter=0;iter<iters; ++iter)
      {
         res_mat = test_mat1 * res_mat * test_mat2;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixOpsTest/mat44f*mat44f*mat44f", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // force intelligent compilers to do all the iterations (ie. to not optimize them out),
      // by using the variables computed...
      CPPUNIT_ASSERT( test_mat1[2] != test_mat2[0] );
      CPPUNIT_ASSERT( res_mat[2] != 1000.0f );
   }

   void MatrixOpsTest::testMatrixTimeMult44d_operatorStarStar()
   {
      gmtl::Matrix<double, 4, 4> test_mat1, test_mat2, res_mat;
      test_mat1.set( 0,  1,  2,  3,
                     4,  5,  6,  7,
                     8,  9, 10, 11,
                    12, 13, 14, 15 );
      res_mat = test_mat2 = test_mat1;

      const long iters(5000);
      CPPUNIT_METRIC_START_TIMING();
      for( long iter=0;iter<iters; ++iter)
      {
         res_mat = test_mat1 * res_mat * test_mat2;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixOpsTest/mat44d*mat44d*mat44d", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // force intelligent compilers to do all the iterations (ie. to not optimize them out),
      // by using the variables computed...
      CPPUNIT_ASSERT( test_mat1[2] != test_mat2[0] );
      CPPUNIT_ASSERT( res_mat[2] != 1000.0f );
   }

   void MatrixOpsTest::testMatrixTimeMult33f_operatorStarStar()
   {
      gmtl::Matrix<float, 3, 3> test_mat1, test_mat2, res_mat;
      test_mat1.set( 0,  1,  2,
                     4,  5,  6,
                     8,  9, 10 );
      res_mat = test_mat2 = test_mat1;

      const long iters(50000);
      CPPUNIT_METRIC_START_TIMING();
      for( long iter=0;iter<iters; ++iter)
      {
         res_mat = test_mat1 * res_mat * test_mat2;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixOpsTest/mat33f*mat33f*mat33f", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // force intelligent compilers to do all the iterations (ie. to not optimize them out),
      // by using the variables computed...
      CPPUNIT_ASSERT( test_mat1[2] != test_mat2[0] );
      CPPUNIT_ASSERT( res_mat[2] != 1000.0f );
   }

   void MatrixOpsTest::testMatrixTimeMult33d_operatorStarStar()
   {
      gmtl::Matrix<double, 3, 3> test_mat1, test_mat2, res_mat;
      test_mat1.set( 0,  1,  2,
                     4,  5,  6,
                     8,  9, 10 );
      res_mat = test_mat2 = test_mat1;

      const long iters(50000);
      CPPUNIT_METRIC_START_TIMING();
      for( long iter=0;iter<iters; ++iter)
      {
         res_mat = test_mat1 * res_mat * test_mat2;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixOpsTest/mat33d*mat33d*mat33d", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // force intelligent compilers to do all the iterations (ie. to not optimize them out),
      // by using the variables computed...
      CPPUNIT_ASSERT( test_mat1[2] != test_mat2[0] );
      CPPUNIT_ASSERT( res_mat[2] != 1000.0f );
   }


   void MatrixOpsTest::testMatrixTimeAdd44()
   {
      gmtl::Matrix<float, 4, 4> test_mat1, test_mat2, res_mat;
      test_mat1.set( 0,  1,  2,  3,
                     4,  5,  6,  7,
                     8,  9, 10, 11,
                    12, 13, 14, 15 );
      res_mat = test_mat2 = test_mat1;

      const long iters(50000);
      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         gmtl::add( res_mat, res_mat, test_mat2 );
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixOpsTest/add(res,mat44f,mat44f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // force intelligent compilers to do all the iterations (ie. to not optimize them out),
      // by using the variables computed...
      CPPUNIT_ASSERT( res_mat[2] != 1000.0f );
   }


   void MatrixOpsTest::testMatrixTimeSub44()
   {
      gmtl::Matrix<float, 4, 4> test_mat1, test_mat2, res_mat;
      test_mat1.set( 0,  1,  2,  3,
                     4,  5,  6,  7,
                     8,  9, 10, 11,
                    12, 13, 14, 15 );
      res_mat = test_mat2 = test_mat1;

      const long iters(50000);
      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         gmtl::sub( res_mat, test_mat1, res_mat );
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixOpsTest/sub(res,mat44f,mat44f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // force intelligent compilers to do all the iterations (ie. to not optimize them out),
      // by using the variables computed...
      CPPUNIT_ASSERT( res_mat[2] != 1000.0f );
   }

   void MatrixOpsTest::testMatrixTranspose()
   {
      // this can use transposeTest::go() if we
      // can figure out how to generically pass in init values.
      {
         gmtl::Matrix<float, 2, 2> test_mat, res_mat;
         test_mat.set( 0,  1,
                       4,  5 );
         res_mat.set( 0,   4,
                      1,   5 );
         gmtl::transpose( res_mat );
         CPPUNIT_ASSERT( res_mat == test_mat );
         gmtl::transpose( res_mat );

         // test the other transpose op
         gmtl::transpose( res_mat, res_mat );
         CPPUNIT_ASSERT( res_mat == test_mat );
      }

      {
         gmtl::Matrix<float, 3, 3> test_mat, res_mat;
         test_mat.set( 0,  1,  2,
                       4,  5,  6,
                       8,  9,  10 );
         res_mat.set( 0,   4,   8,
                      1,   5,   9,
                      2,   6,  10 );
         gmtl::transpose( res_mat );
         CPPUNIT_ASSERT( res_mat == test_mat );
         gmtl::transpose( res_mat );

         // test the other transpose op
         gmtl::transpose( res_mat, res_mat );
         CPPUNIT_ASSERT( res_mat == test_mat );
      }
      {
         gmtl::Matrix<float, 4, 4> test_mat, res_mat;
         test_mat.set( 0,  1,  2,  3,
                       4,  5,  6,  7,
                       8,  9,  10, 11,
                       12, 13, 14, 15 );
         res_mat.set( 0,   4,   8,  12,
                      1,   5,   9,  13,
                      2,   6,  10,  14,
                      3,   7,  11,  15 );
         gmtl::transpose( res_mat );
         CPPUNIT_ASSERT( res_mat == test_mat );
         gmtl::transpose( res_mat );

         // test the other transpose op
         gmtl::transpose( res_mat, res_mat );
         CPPUNIT_ASSERT( res_mat == test_mat );
      }

      transposeTest<float, 2, true>::go();
      transposeTest<float, 3, true>::go();
      transposeTest<float, 4, true>::go();
      transposeTest<float, 5, true>::go();
      transposeTest<float, 6, true>::go();
      transposeTest<float, 7, true>::go();
      transposeTest<float, 8, true>::go();
      transposeTest<float, 9, true>::go();
      transposeTest<float, 10, true>::go();
      transposeTest<double, 2, true>::go();
      transposeTest<double, 3, true>::go();
      transposeTest<double, 4, true>::go();
      transposeTest<double, 5, true>::go();
      transposeTest<double, 6, true>::go();
      transposeTest<double, 7, true>::go();
      transposeTest<double, 8, true>::go();
      transposeTest<double, 9, true>::go();
      transposeTest<double, 10, true>::go();

      // test the case where we convert between different degrees (3x4 to 4x3)
      {
         gmtl::Matrix<float, 4, 3> source_mat;
         gmtl::Matrix<float, 3, 4> result_mat, expected_answer;
         float v1[] = { 0,  4,  8,
                        1,  5,  9,
                        2,  6,  10,
                        3,  7,  11 };
         source_mat.setTranspose( v1 );
         float v2[] = { 0,  1,  2, 3,
                        4,  5,  6, 7,
                        8,  9,  10, 11 };
         expected_answer.setTranspose( v2 );
         gmtl::transpose( result_mat, source_mat );
         CPPUNIT_ASSERT( result_mat == expected_answer );
      }
      {
         gmtl::Matrix<float, 3, 4> source_mat;
         gmtl::Matrix<float, 4, 3> result_mat, expected_answer;
         float v1[] = { 0,  1,  2, 3,
                        4,  5,  6, 7,
                        8,  9,  10, 11 };
         source_mat.setTranspose( v1 );
         float v2[] = { 0,  4,  8,
                        1,  5,  9,
                        2,  6,  10,
                        3,  7,  11 };
         expected_answer.setTranspose( v2 );
         gmtl::transpose( result_mat, source_mat );
         CPPUNIT_ASSERT( result_mat == expected_answer );
      }
   }

   void MatrixOpsTest::testMatrixAddSub()
   {
      matrixAddSub<float>::go();
      matrixAddSub<double>::go();
      matrixAddSub<int>::go();
      matrixAddSub<short>::go();
      matrixAddSub<char>::go();
   }

   void MatrixOpsTest::testMatrixMult()
   {
      matrixMult33<float>::go();
      matrixMult33<double>::go();
      matrixMult44<float>::go();
      matrixMult44<double>::go();
      matrixMultUnlike<float>::go();
      matrixMultUnlike<double>::go();
   }

   void MatrixOpsTest::testMatrixScalarMult()
   {
      matrixScalarMult<float>::go();
      matrixScalarMult<double>::go();
   }

   void MatrixOpsTest::testMatInvert()
   {
      matInvertFull<float>::go();
      matInvertFull<double>::go();

      /*
      // Test rotation inversions
      gmtl::Matrix<DATA_TYPE, 4, 4> rot_mat1, rot_mat1_inv; // rot_mat2, rot_mat2_inv;
      rot_mat1.makeXYZEuler( 30.0f, 45.0f, 60.0f );
      rot_mat1_inv.invert(rot_mat1);
      result = rot_mat1*rot_mat1_inv;
      CPPUNIT_ASSERT(result.equal(identity));

      // Test translation matrix inversion
      gmtl::Matrix<DATA_TYPE, 4, 4> trans_mat1, trans_mat1_inv;
      trans_mat1.makeTrans(21.0f, -23.45f, 0.045f);
      trans_mat1_inv.invert(trans_mat1);
      result = trans_mat1*trans_mat1_inv;
      CPPUNIT_ASSERT(result.equal(identity));
      */
   }
}
