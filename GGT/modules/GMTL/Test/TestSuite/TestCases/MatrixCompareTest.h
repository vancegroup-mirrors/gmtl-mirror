/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: MatrixCompareTest.h,v $
 * Date modified: $Date: 2002-03-18 21:56:24 $
 * Version:       $Revision: 1.10 $
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

class MatrixCompareTest : public CppUnit::TestCase
{
public:
   MatrixCompareTest( std::string name = "MatrixCompareTest" )
   : CppUnit::TestCase (name)
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

   void testMatEqualityFloatTest();
   void testMatEqualityDoubleTest();
   void testMatEqualityIntTest();

   void testMatTimingOpEqualityTest();
   void testMatTimingOpNotEqualityTest();
   void testMatTimingIsEqualTest();

   static CppUnit::Test* suite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("MatrixCompareTest");
      test_suite->addTest( new CppUnit::TestCaller<MatrixCompareTest>("testMatTimingOpEqualityTest", &MatrixCompareTest::testMatTimingOpEqualityTest));
      test_suite->addTest( new CppUnit::TestCaller<MatrixCompareTest>("testMatTimingIsEqualTest", &MatrixCompareTest::testMatTimingIsEqualTest));
      test_suite->addTest( new CppUnit::TestCaller<MatrixCompareTest>("testMatTimingOpNotEqualityTest", &MatrixCompareTest::testMatTimingOpNotEqualityTest));
      test_suite->addTest( new CppUnit::TestCaller<MatrixCompareTest>("testMatEqualityFloatTest", &MatrixCompareTest::testMatEqualityFloatTest));
      test_suite->addTest( new CppUnit::TestCaller<MatrixCompareTest>("testMatEqualityDoubleTest", &MatrixCompareTest::testMatEqualityDoubleTest));
      test_suite->addTest( new CppUnit::TestCaller<MatrixCompareTest>("testMatEqualityIntTest", &MatrixCompareTest::testMatEqualityIntTest));
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
