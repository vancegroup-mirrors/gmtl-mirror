/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: MatrixOpsTest.h,v $
 * Date modified: $Date: 2002-02-22 19:45:18 $
 * Version:       $Revision: 1.8 $
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
#include <gmtl/gmtlConfig.h>
#include <iostream>

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include <gmtl/Matrix.h>
#include <gmtl/MatrixOps.h>

namespace gmtlTest
{

class MatrixOpsTest : public CppUnit::TestCase
{
public:
   MatrixOpsTest( std::string name = "MatrixOpsTest" )
   : CppUnit::TestCase (name)
   {;}

   virtual ~MatrixOpsTest()
   {}

   virtual void setUp()
   {
   }

   virtual void tearDown()
   {
   }

    void testMatrixTimeTranspose()
   {
      gmtl::Matrix<float, 4, 4> test_mat1;
      test_mat1.set( 0,  1,  2,  3, 
                     4,  5,  6,  7,
                     8,  9, 10, 11,
                    12, 13, 14, 15 );
      gmtl::Matrix<double, 3, 3> test_mat2;
      test_mat2.set( 0,  1,  2, 
                    4,  5,  6, 
                    8,  9,  10 );
         
      const long iters(400000);
      CPPUNIT_METRIC_START_TIMING();

      bool result = false;
      for( long iter=0;iter<iters; ++iter)
      {
         gmtl::transpose( test_mat1 );
         gmtl::transpose( test_mat2 );
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixOpsTest/TransposeTest", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }   

   void testMatrixTimeMult44()
   {
      gmtl::Matrix<float, 4, 4> test_mat1, test_mat2, res_mat;
      test_mat1.set( 0,  1,  2,  3, 
                     4,  5,  6,  7,
                     8,  9, 10, 11,
                    12, 13, 14, 15 );
      test_mat2 = test_mat1;
      
      const long iters(400000);
      CPPUNIT_METRIC_START_TIMING();

      bool result = false;
      for( long iter=0;iter<iters; ++iter)
      {
         gmtl::mult( res_mat, test_mat1, test_mat2 );
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixOpsTest/Mult44", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      
      
      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         res_mat = test_mat1 * test_mat2;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixOpsTest/Mult44operatorStar", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }   
   

   void testMatrixTimeAdd44()
   {
      gmtl::Matrix<float, 4, 4> test_mat1, test_mat2, res_mat;
      test_mat1.set( 0,  1,  2,  3, 
                     4,  5,  6,  7,
                     8,  9, 10, 11,
                    12, 13, 14, 15 );
      test_mat2 = test_mat1;
      
      const long iters(400000);
      CPPUNIT_METRIC_START_TIMING();

      bool result = false;
      for( long iter=0;iter<iters; ++iter)
      {
         gmtl::add( res_mat, test_mat1, test_mat2 );
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixOpsTest/Add44", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }
   

   void testMatrixTimeSub44()
   {
      gmtl::Matrix<float, 4, 4> test_mat1, test_mat2, res_mat;
      test_mat1.set( 0,  1,  2,  3, 
                     4,  5,  6,  7,
                     8,  9, 10, 11,
                    12, 13, 14, 15 );
      test_mat2 = test_mat1;
      
      const long iters(400000);
      CPPUNIT_METRIC_START_TIMING();

      bool result = false;
      for( long iter=0;iter<iters; ++iter)
      {
         gmtl::sub( res_mat, test_mat1, test_mat2 );
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("MatrixOpsTest/Sub44", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }   
   
   
   
   ///////////////////////////////////////////////////
   // op tests:
   
   
   
   template<typename T, int SIZE, bool TEST>
   class transposeTest
   {
   public:
      static void go()
      {
         gmtl::Matrix<T, SIZE, SIZE> test_mat, res_mat;
         test_mat( SIZE - 1, 0 ) = 9;
         res_mat( 0, SIZE - 1 ) = 9;
         test_mat( 1, 0 ) = 2;
         res_mat( 0, 1 ) = 2;
         gmtl::transpose( res_mat );
         if (TEST == true)
         { CPPUNIT_ASSERT( res_mat == test_mat ); }
         gmtl::transpose( res_mat );
         
         // test the other transpose op
         gmtl::transpose( res_mat, res_mat );
         if (TEST == true)
         { CPPUNIT_ASSERT( res_mat == test_mat ); }
      }      
   };   
   
   void testMatrixTranspose()
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

  
   template <typename DATA_TYPE>
   class matrixAddSub
   {
   public:
      static void go()
      {
         {
            gmtl::Matrix<DATA_TYPE, 2, 2> test_mat1, test_mat2, res_mat, ans_mat;
            test_mat1.set( 0,  1,  
                           4,  5 );
            test_mat2 = test_mat1;
            ans_mat.set( 0,  2, 
                         8, 10  );
            gmtl::add( res_mat, test_mat1, test_mat2 );    // rm = m1 + m2
            CPPUNIT_ASSERT(res_mat == ans_mat);


            gmtl::Matrix<DATA_TYPE, 2, 2> diff_mat;
            gmtl::sub( diff_mat, res_mat, test_mat1 );    // rm = m1 - m2
            CPPUNIT_ASSERT(diff_mat != res_mat);
            CPPUNIT_ASSERT(diff_mat == test_mat2);
         }
         {
            gmtl::Matrix<DATA_TYPE, 3, 3> test_mat1, test_mat2, res_mat, ans_mat;
            test_mat1.set( 0,  1,  2, 
                           4,  5,  6, 
                           8,  9, 10 );
            test_mat2 = test_mat1;
            ans_mat.set( 0,  2,  4, 
                         8, 10, 12, 
                        16, 18, 20 );
            gmtl::add( res_mat, test_mat1, test_mat2 );    // rm = m1 + m2
            CPPUNIT_ASSERT(res_mat == ans_mat);


            gmtl::Matrix<DATA_TYPE, 3, 3> diff_mat;
            gmtl::sub( diff_mat, res_mat, test_mat1 );    // rm = m1 - m2
            CPPUNIT_ASSERT(diff_mat != res_mat);
            CPPUNIT_ASSERT(diff_mat == test_mat2);
         }
         {
            gmtl::Matrix<DATA_TYPE, 3, 4> test_mat1, test_mat2, res_mat, ans_mat;
            test_mat1.set( 0,  1,  2,  3,
                           4,  5,  6,  7,
                           8,  9, 10, 11 );
            test_mat2 = test_mat1;
            ans_mat.set( 0,  2,  4,  6,
                         8, 10, 12, 14,
                        16, 18, 20, 22 );
            gmtl::add( res_mat, test_mat1, test_mat2 );    // rm = m1 + m2
            CPPUNIT_ASSERT(res_mat == ans_mat);


            gmtl::Matrix<DATA_TYPE, 3, 4> diff_mat;
            gmtl::sub( diff_mat, res_mat, test_mat1 );    // rm = m1 - m2
            CPPUNIT_ASSERT(diff_mat != res_mat);
            CPPUNIT_ASSERT(diff_mat == test_mat2);
         }
         {
            gmtl::Matrix<DATA_TYPE, 4, 3> test_mat1, test_mat2, res_mat, ans_mat;
            DATA_TYPE v1[] = { 0,  1,  2,  
                               4,  5,  6, 
                               8,  9, 10, 
                              12, 13, 14 };
            test_mat1.setTranspose( v1 );
            test_mat2 = test_mat1;
            DATA_TYPE v2[] = { 0,  2,  4,
                               8, 10, 12,
                              16, 18, 20,
                              24, 26, 28 };
            ans_mat.setTranspose( v2 );
            gmtl::add( res_mat, test_mat1, test_mat2 );    // rm = m1 + m2
            CPPUNIT_ASSERT(res_mat == ans_mat);


            gmtl::Matrix<DATA_TYPE, 4, 3> diff_mat;
            gmtl::sub( diff_mat, res_mat, test_mat1 );    // rm = m1 - m2
            CPPUNIT_ASSERT(diff_mat != res_mat);
            CPPUNIT_ASSERT(diff_mat == test_mat2);
         }
         {
            gmtl::Matrix<DATA_TYPE, 4, 4> test_mat1, test_mat2, res_mat, ans_mat;
            test_mat1.set( 0,  1,  2,  3, 
                           4,  5,  6,  7,
                           8,  9, 10, 11,
                          12, 13, 14, 15 );
            test_mat2 = test_mat1;
            ans_mat.set( 0,  2,  4,  6,
                         8, 10, 12, 14,
                        16, 18, 20, 22,
                        24, 26, 28, 30 );
            gmtl::add( res_mat, test_mat1, test_mat2 );    // rm = m1 + m2
            CPPUNIT_ASSERT(res_mat == ans_mat);


            gmtl::Matrix<DATA_TYPE, 4, 4> diff_mat;
            gmtl::sub( diff_mat, res_mat, test_mat1 );    // rm = m1 - m2
            CPPUNIT_ASSERT(diff_mat != res_mat);
            CPPUNIT_ASSERT(diff_mat == test_mat2);
         }
      }
   };

   void testMatrixAddSub()
   {
      matrixAddSub<float>::go();
      matrixAddSub<double>::go();
      matrixAddSub<int>::go();
      matrixAddSub<short>::go();
      matrixAddSub<char>::go();
   }

   
   template <typename T>
   class matrixMult33
   {
   public:
      static void go()
      {
         gmtl::Matrix<T, 3, 3> mat1, mat2, mat3, res_mat;

         T eps = (T)0.001;

         mat1.set((T) 1.1000, (T)2.2000,  (T) 3.3000, 
                  (T) 5.5000, (T)6.6000,  (T) 7.7000, 
                  (T) 9.9000, (T)10.1000, (T)11.1100 );
         mat2.set((T) 43,  (T) -8,  (T) -4, 
                  (T) 23,  (T) 22,  (T) 72, 
                  (T)-34,  (T)-23,  (T) 99 );

         // make sure mat3 = mat1 * mat2 yields the correct result
         gmtl::mult( mat3, mat1, mat2 );
         res_mat.set( (T)-14.300,   (T) -36.300,   (T) 480.700,
                      (T)126.500,   (T) -75.900,   (T)1215.500,
                      (T)280.260,   (T)-112.530,   (T)1787.490 );
         CPPUNIT_ASSERT( gmtl::isEqual( res_mat, mat3, eps ) );

         // test post and pre mult operators...
         {
            gmtl::Matrix<T, 3, 3> m1( mat1 );
            const gmtl::Matrix<T, 3, 3> m2( mat2 );
            gmtl::postMult( m1, m2 );
            CPPUNIT_ASSERT( gmtl::isEqual( res_mat, m1, eps ) );
         }
         {
            gmtl::Matrix<T, 3, 3> m1( mat1 );
            const gmtl::Matrix<T, 3, 3> m2( mat2 );
            m1 *= m2;
            CPPUNIT_ASSERT( gmtl::isEqual( res_mat, m1, eps ) );
         }
         {
            const gmtl::Matrix<T, 3, 3> m1( mat1 );
            gmtl::Matrix<T, 3, 3> m2( mat2 );
            gmtl::preMult( m2, m1 );
            CPPUNIT_ASSERT( gmtl::isEqual( res_mat, m2, eps ) );
         }
         {
            gmtl::Matrix<T, 3, 3> result;
            result = mat1 * mat2;
            CPPUNIT_ASSERT( gmtl::isEqual( res_mat, result, eps ) );
         }
         
         // make sure mult is not commutitive
         gmtl::mult( mat3, mat2, mat1 );
         CPPUNIT_ASSERT( !gmtl::isEqual( res_mat, mat3, eps ) );

         // make sure mat3 = mat2 * mat1 yields the correct result
         res_mat.set((T)-36.3000,    (T)  1.4000,   (T)  35.8600,
                     (T)859.1000,    (T)923.0000,   (T)1045.2200,
                     (T)816.2000,    (T)773.3000,   (T) 810.5900 );
         CPPUNIT_ASSERT( gmtl::isEqual( res_mat, mat3, eps ) );
         
         // test post and pre mult operators...
         {
            const gmtl::Matrix<T, 3, 3> m1( mat1 );
            gmtl::Matrix<T, 3, 3> m2( mat2 );
            gmtl::postMult( m2, m1 );
            CPPUNIT_ASSERT( gmtl::isEqual( res_mat, m2, eps ) );
         }
         {
            const gmtl::Matrix<T, 3, 3> m1( mat1 );
            gmtl::Matrix<T, 3, 3> m2( mat2 );
            m2 *=m1;
            CPPUNIT_ASSERT( gmtl::isEqual( res_mat, m2, eps ) );
         }
         {
            gmtl::Matrix<T, 3, 3> m1( mat1 );
            const gmtl::Matrix<T, 3, 3> m2( mat2 );
            gmtl::preMult( m1, m2 );
            CPPUNIT_ASSERT( gmtl::isEqual( res_mat, m1, eps ) );
         }
         {
            gmtl::Matrix<T, 3, 3> result;
            result = mat2 * mat1;
            CPPUNIT_ASSERT( gmtl::isEqual( res_mat, result, eps ) );
         }
      }
   };
   
   template <typename T>
   class matrixMultUnlike
   {
   public:
      static void go()
      {
         gmtl::Matrix<T, 3, 4> lhs34;
         gmtl::Matrix<T, 4, 3> rhs43;
         gmtl::Matrix<T, 4, 4> res44, expected_answer44;
         gmtl::Matrix<T, 3, 3> res33, expected_answer33;

         
         T eps = (T)0.01;

         T v1[] = { 1.1000, 2.2000, 3.3000, 4.4000, 
                    5.5000, 6.6000, 7.7000, 8.8000,   
                    9.9000, 10.1000, 11.1100, 12.1200 };
         lhs34.setTranspose( v1 );
         T v2[] = { 13.100, 14.200, 15.300, 
                    16.400, 17.500, 18.600,  
                    19.700, 20.800, 21.900, 
                    22.100, 23.110, 24.120  };
         rhs43.setTranspose( v2 );

         // make sure mat3 = mat2 * mat1 yields the correct result
         T v3[] = {  243.98, 277.07, 322.55, 368.04,  
                     298.43, 339.44, 395.52, 451.59, 
                     352.88, 401.81, 468.48, 535.15,   
                     390.20, 444.76, 518.85, 592.94  };
         expected_answer44.setTranspose( v3 );
         gmtl::mult( res44, rhs43, lhs34 );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_answer44, res44, eps ) );
         {
            gmtl::Matrix<T, 4, 4> result;
            result = rhs43 * lhs34;
            CPPUNIT_ASSERT( gmtl::isEqual( expected_answer44, result, eps ) );
         }
         
         // make sure mat3 = mat1 * mat2 yields the correct result
         T v4[] = {  212.74,  224.44,  236.15,  
                     526.46,  557.13,  587.80,  
                     782.05,  828.51,  874.97   };
         expected_answer33.setTranspose( v4 );
         gmtl::mult( res33, lhs34, rhs43 );
         CPPUNIT_ASSERT( gmtl::isEqual( res33, expected_answer33, eps ) );
         {
            gmtl::Matrix<T, 3, 3> result;
            result = lhs34 * rhs43;
            CPPUNIT_ASSERT( gmtl::isEqual( expected_answer33, result, eps ) );
         }
         
         
         gmtl::Matrix<T, 5, 3> lhs53;
         gmtl::Matrix<T, 5, 4> res54, expected_answer54;
         T v5[] = { 13.100, 14.200, 15.300,  
                    16.400, 17.500, 18.600, 
                    19.700, 20.800, 21.900,  
                    22.100, 23.110, 24.120,  
                    25.000, 26.000, 27.000  };
         lhs53.setTranspose( v5 );
         gmtl::mult( res54, lhs53, lhs34 );
         T v6[] = { 243.98, 277.07, 322.55, 368.04, 298.43,  
                    339.44, 395.52, 451.59, 352.88, 401.81,  
                    468.48, 535.15, 390.20, 444.76, 518.85,  
                    592.94, 437.80, 499.30, 582.67, 666.04  };
         expected_answer54.setTranspose( v6 );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_answer54, res54, eps ) );
         {
            gmtl::Matrix<T, 5, 4> result;
            result = lhs53 * lhs34;
            CPPUNIT_ASSERT( gmtl::isEqual( expected_answer54, result, eps ) );
         }
      }
   };
   
   template <typename T>
   class matrixMult44
   {
   public:
      static void go()
      {
         gmtl::Matrix<T, 4, 4> mat1, mat2, mat3, res_mat;

         T eps = (T)0.001;

         mat1.set((T) 1.1000, (T)2.2000,  (T) 3.3000, (T) 4.4000,
                  (T) 5.5000, (T)6.6000,  (T) 7.7000, (T) 8.8000,
                  (T) 9.9000, (T)10.1000, (T)11.1100, (T)12.1200,
                  (T)13.1300, (T)14.1400, (T)15.1500, (T)16.1600 );
         mat2.set((T) 43,  (T) -8,  (T) -4, (T)   7,
                  (T) 23,  (T) 22,  (T) 72, (T)  69,
                  (T)-34,  (T)-23,  (T) 99, (T) -48,
                  (T) 12,  (T) 16,  (T) 21, (T)  18);

         // make sure mat3 = mat1 * mat2 yields the correct result
         gmtl::mult( mat3, mat1, mat2 );
         res_mat.set((T) 38.500,   (T) 34.100,  (T) 573.100,   (T) 80.300,
                     (T)232.100,   (T) 64.900,  (T)1400.300,   (T)282.700,
                     (T)425.700,   (T) 81.390,  (T)2042.010,   (T)451.080,
                     (T)568.630,   (T)116.150,  (T)2804.770,   (T)631.250 );
         CPPUNIT_ASSERT( gmtl::isEqual( res_mat, mat3, eps ) );

         // test post and pre mult operators...
         {
            gmtl::Matrix<T, 4, 4> m1( mat1 );
            const gmtl::Matrix<T, 4, 4> m2( mat2 );
            gmtl::postMult( m1, m2 );
            CPPUNIT_ASSERT( gmtl::isEqual( res_mat, m1, eps ) );
         }
         {
            gmtl::Matrix<T, 4, 4> m1( mat1 );
            const gmtl::Matrix<T, 4, 4> m2( mat2 );
            m1 *= m2;
            CPPUNIT_ASSERT( gmtl::isEqual( res_mat, m1, eps ) );
         }
         {
            const gmtl::Matrix<T, 4, 4> m1( mat1 );
            gmtl::Matrix<T, 4, 4> m2( mat2 );
            gmtl::preMult( m2, m1 );
            CPPUNIT_ASSERT( gmtl::isEqual( res_mat, m2, eps ) );
         }
         {
            gmtl::Matrix<T, 4, 4> result;
            result = mat1 * mat2;
            CPPUNIT_ASSERT( gmtl::isEqual( res_mat, result, eps ) );
         }
         
         // make sure mult is not commutitive
         gmtl::mult( mat3, mat2, mat1 );
         CPPUNIT_ASSERT( !gmtl::isEqual( res_mat, mat3, eps ) );

         // make sure mat3 = mat2 * mat1 yields the correct result
         res_mat.set(  55.610,   100.380,   141.910,   183.440,
                     1765.070,  1898.660,  2090.570,  2282.480,
                      185.960,    94.580,    83.390,    72.200,
                      545.440,   598.620,   668.810,   739.000 );
         CPPUNIT_ASSERT( gmtl::isEqual( res_mat, mat3, eps ) );
         
         // test post and pre mult operators...
         {
            const gmtl::Matrix<T, 4, 4> m1( mat1 );
            gmtl::Matrix<T, 4, 4> m2( mat2 );
            gmtl::postMult( m2, m1 );
            CPPUNIT_ASSERT( gmtl::isEqual( res_mat, m2, eps ) );
         }
         {
            const gmtl::Matrix<T, 4, 4> m1( mat1 );
            gmtl::Matrix<T, 4, 4> m2( mat2 );
            m2 *= m1;
            CPPUNIT_ASSERT( gmtl::isEqual( res_mat, m2, eps ) );
         }
         {
            gmtl::Matrix<T, 4, 4> m1( mat1 );
            const gmtl::Matrix<T, 4, 4> m2( mat2 );
            gmtl::preMult( m1, m2 );
            CPPUNIT_ASSERT( gmtl::isEqual( res_mat, m1, eps ) );
         }
         {
            gmtl::Matrix<T, 4, 4> result;
            result = mat2 * mat1;
            CPPUNIT_ASSERT( gmtl::isEqual( res_mat, result, eps ) );
         }
      }
   };

   void testMatrixMult()
   {
      matrixMult33<float>::go();
      matrixMult33<double>::go();
      matrixMult44<float>::go();
      matrixMult44<double>::go();
      matrixMultUnlike<float>::go();
      matrixMultUnlike<double>::go();
   }
   
   template <typename T>
   class matrixScalarMult
   {
   public:
      static void go()
      {
         gmtl::Matrix<T, 4, 4> mat1, res_mat, expected_result;

         T eps = (T)0.001;

         mat1.set((T) 1.1000, (T)2.2000,  (T) 3.3000, (T) 4.4000,
                  (T) 5.5000, (T)6.6000,  (T) 7.7000, (T) 8.8000,
                  (T) 9.9000, (T)10.1000, (T)11.1100, (T)12.1200,
                  (T)13.1300, (T)14.1400, (T)15.1500, (T)16.1600 );
         expected_result.set(  3.3000,   6.6000,   9.9000,  13.2000,
                              16.5000,  19.8000,  23.1000,  26.4000,
                              29.7000,  30.3000,  33.3300,  36.3600,
                              39.3900,  42.4200,  45.4500,  48.4800  );

         // result = mat * scalar
         gmtl::mult( res_mat, mat1, (T)3 );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result, res_mat, eps ) );

         // result *= scalar
         res_mat = mat1;
         gmtl::mult( res_mat, (T)3 );
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result, res_mat, eps ) );

         // result *= scalar
         res_mat = mat1;
         res_mat *= (T)3;
         CPPUNIT_ASSERT( gmtl::isEqual( expected_result, res_mat, eps ) );
      }
   };
      
   void testMatrixScalarMult()
   {
      matrixScalarMult<float>::go();
      matrixScalarMult<double>::go();
   }
   
   template <typename DATA_TYPE>
   class matInvertFull
   {
   public:
      static void go()
      {
         gmtl::Matrix<DATA_TYPE, 4, 4> mat1, expected_value, result, identity;
         DATA_TYPE eps = 0.001;
         mat1.set( 0.78,  1.4,   2.9, 3.45,
                   4.21, 57.9,  65.9, 74.6,
                   89.2, 99.2,  10.9, 11.9,
                   12.5, 13.9, 14.78, 15.6  );
         expected_value.set( 0.3071733,  -0.0239700,   0.0034853,   0.0440345,
                            -0.2891106,   0.0216826,   0.0079218,  -0.0457924,
                            -3.0532152,   0.0305681,  -0.0547335,   0.5708037,
                             2.9041982,  -0.0290744,   0.0420053,  -0.4711792 );

         // Make sure our pre-computed answer is right
         gmtl::mult( result, mat1, expected_value );
         CPPUNIT_ASSERT( gmtl::isEqual( result, identity, eps ) );

         // Test inversion
         result = gmtl::Matrix<DATA_TYPE, 4, 4>();
         gmtl::invert( result, mat1 );
         CPPUNIT_ASSERT( gmtl::isEqual( result, expected_value, eps ) );
         
         // Test inversion in place
         result = gmtl::Matrix<DATA_TYPE, 4, 4>();
         gmtl::invert( mat1 );
         CPPUNIT_ASSERT( gmtl::isEqual( mat1, expected_value, eps ) );
      }
   };
   
   void testMatInvert()
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
      
   /*
   void testGetSetAxes()
   {
      gmtl::Matrix mat1, mat2;
      gmtl::Vec3 xAxis1,yAxis1,zAxis1;
      gmtl::Vec3 xAxis2,yAxis2,zAxis2;

      // Simple rotation around X axis
      mat1.makeRot(90,gmtl::XUnitVec3);
      mat1.getAxes(xAxis1,yAxis1,zAxis1);
      mat2.makeAxes(xAxis1,yAxis1,zAxis1);
      mat2.getAxes(xAxis2,yAxis2,zAxis2);

      CPPUNIT_ASSERT(xAxis1.equal(xAxis2,0.01));
      CPPUNIT_ASSERT(yAxis1.equal(yAxis2,0.01));
      CPPUNIT_ASSERT(zAxis1.equal(zAxis2,0.01));

      // More complex Euler rotation
      mat1.makeXYZEuler(45.0f, -35.0f, 13.0f);
      mat1.getAxes(xAxis1,yAxis1,zAxis1);
      mat2.makeAxes(xAxis1,yAxis1,zAxis1);
      mat2.getAxes(xAxis2,yAxis2,zAxis2);

      CPPUNIT_ASSERT(xAxis1.equal(xAxis2,0.01));
      CPPUNIT_ASSERT(yAxis1.equal(yAxis2,0.01));
      CPPUNIT_ASSERT(zAxis1.equal(zAxis2,0.01));

      // Use orthonormal axis
      xAxis1.set(7, 11, 21);     xAxis1.normalize();
      yAxis1.set(12, 21, 75);    yAxis1.normalize();
      zAxis1 = xAxis1.cross(yAxis1);   zAxis1.normalize();

      mat2.makeAxes(xAxis1,yAxis1,zAxis1);
      mat2.getAxes(xAxis2,yAxis2,zAxis2);

      CPPUNIT_ASSERT(xAxis1.equal(xAxis2,0.01));
      CPPUNIT_ASSERT(yAxis1.equal(yAxis2,0.01));
      CPPUNIT_ASSERT(zAxis1.equal(zAxis2,0.01));
   }
   */


   static CppUnit::Test* suite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("MatrixOpsTest");
      test_suite->addTest( new CppUnit::TestCaller<MatrixOpsTest>( "testMatrixTranspose", &MatrixOpsTest::testMatrixTranspose ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixOpsTest>( "testMatrixMult", &MatrixOpsTest::testMatrixMult ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixOpsTest>( "testMatrixScalarMult", &MatrixOpsTest::testMatrixScalarMult ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixOpsTest>( "testMatrixAddSub", &MatrixOpsTest::testMatrixAddSub ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixOpsTest>( "testMatInvert", &MatrixOpsTest::testMatInvert ) );
      //test_suite->addTest( new CppUnit::TestCaller<MatrixOpsTest>("testGetSetAxes", &MatrixOpsTest::testGetSetAxes));
      
      test_suite->addTest( new CppUnit::TestCaller<MatrixOpsTest>( "testMatrixTimeTranspose", &MatrixOpsTest::testMatrixTimeTranspose ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixOpsTest>( "testMatrixTimeMult44", &MatrixOpsTest::testMatrixTimeMult44 ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixOpsTest>( "testMatrixTimeAdd44", &MatrixOpsTest::testMatrixTimeAdd44 ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixOpsTest>( "testMatrixTimeSub44", &MatrixOpsTest::testMatrixTimeSub44 ) );
      return test_suite;
   }

   static CppUnit::Test* interactiveSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("InteractiveThreadTest");
      //test_suite->addTest( new CppUnit::TestCaller<ThreadTest>("interactiveCPUGrind", &ThreadTest::interactiveTestCPUGrind));
      return test_suite;
   }

protected:

};

};
