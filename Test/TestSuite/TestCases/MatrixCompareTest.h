/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: MatrixCompareTest.h,v $
 * Date modified: $Date: 2002-02-12 22:29:59 $
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
#include <gmtl/gmtlConfig.h>
#include <iostream>

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include <gmtl/Matrix.h>
#include <gmtl/Compare.h>

namespace gmtlTest
{

class MatrixCompareTest : public CppUnit::TestCase
{
public:
   MatrixCompareTest( std::string name = "MatrixCompareTest" )
   : TestCase (name)
   {;}

   virtual ~MatrixCompareTest()
   {}

   virtual void setUp()
   {;}

   virtual void tearDown()
   {
   }

   template<typename T, int ROWS, int COLS>
   class testEqual
   {
   public:
      static void go()
      {
         assert( ROWS <= 5 &&  COLS <= 5 );
         gmtl::Matrix<T, ROWS, COLS> mat1, mat2;
         T array[] = { (T)0.78, (T) 1.4,   (T) 2.9,  (T)3.45,
                       (T)4.21, (T)57.9,  (T) 65.9,  (T)74.6,
                       (T)89.2, (T)99.2,  (T) 10.9,  (T)11.9,
                       (T)12.5, (T)13.9,  (T)14.78,  (T)15.6,
                       (T)4.21, (T)57.9,  (T) 65.9,  (T)74.6,
                       (T)89.2, (T)99.2,  (T) 10.9,  (T)11.9, 
                       (T)89.2, (T)99.2,  (T) 10.9,  (T)11.9 };
         mat1.set( array );
         mat1 = mat2;
         CPPUNIT_ASSERT( mat1 == mat2 );
         CPPUNIT_ASSERT( mat2 == mat1 );

         // Test that != works on all elements
         for (int i = 0; i < ROWS; ++i)
         {
            for (int j = 0; j < COLS; ++j)
            {
               mat2( i, j ) = (T)1221.0f;
               CPPUNIT_ASSERT(  (mat1 != mat2) );
               CPPUNIT_ASSERT( !(mat1 == mat2) );
               mat2( i, j ) = mat1( i, j ); // put it back
            }
         }

         // Test for epsilon equals working
         CPPUNIT_ASSERT( gmtl::isEqual( mat1, mat2 ) );
         CPPUNIT_ASSERT( gmtl::isEqual( mat1, mat2, (T)0.0f ) );
         CPPUNIT_ASSERT( gmtl::isEqual( mat2, mat1, (T)0.0f ) );
         CPPUNIT_ASSERT( gmtl::isEqual( mat2, mat1, (T)100000.0f ) );
         T eps = (T)10.0;
         for (int i = 0; i < ROWS; ++i)
         {
            for (int j = 0; j < COLS; ++j)
            {
               mat2( i, j ) = mat1( i, j ) - (eps / (T)2.0);
               CPPUNIT_ASSERT(  gmtl::isEqual( mat1, mat2, eps ) );
               CPPUNIT_ASSERT( !gmtl::isEqual( mat1, mat2, (T)(eps / 3.0) ) );
               mat2( i, j ) = mat1( i, j ); // put it back
            }
         }
      }
   };
   
   void testMatEqualFloatTest()
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
   
   void testMatEqualDoubleTest()
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
   
   void testMatEqualIntTest()
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
   

   
   static Test* suite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("MatrixCompareTest");
      test_suite->addTest( new CppUnit::TestCaller<MatrixCompareTest>("testMatEqualFloatTest", &MatrixCompareTest::testMatEqualFloatTest));
      test_suite->addTest( new CppUnit::TestCaller<MatrixCompareTest>("testMatEqualDoubleTest", &MatrixCompareTest::testMatEqualDoubleTest));
      test_suite->addTest( new CppUnit::TestCaller<MatrixCompareTest>("testMatEqualIntTest", &MatrixCompareTest::testMatEqualIntTest));
      return test_suite;
   }

   static Test* interactiveSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("InteractiveThreadTest");
      //test_suite->addTest( new CppUnit::TestCaller<ThreadTest>("interactiveCPUGrind", &ThreadTest::interactiveTestCPUGrind));
      return test_suite;
   }

protected:

};

};
