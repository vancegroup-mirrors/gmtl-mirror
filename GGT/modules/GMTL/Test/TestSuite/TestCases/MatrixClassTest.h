/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: MatrixClassTest.h,v $
 * Date modified: $Date: 2002-03-18 21:56:24 $
 * Version:       $Revision: 1.12 $
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
#include <gmtl/gmtlConfig.h>
#include <iostream>

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include <gmtl/Matrix.h>

namespace gmtlTest
{

class MatrixClassTest : public CppUnit::TestCase
{
public:
   MatrixClassTest( std::string name = "MatrixClassTest" )
   : CppUnit::TestCase (name)
   {;}

   virtual ~MatrixClassTest()
   {}

   virtual void setUp()
   {;}

   virtual void tearDown()
   {
   }

   void testTimingDefaultConstructor();
   void testTimingCopyConstructor();

   void testTimingOpEqual();
   void testTimingOpParen();
   void testTimingOpBracket();

   void testTimingSetPtr();
   void testTimingSetTransposePtr();
   void testTimingGetData();
   void testTimingSet();

   // test out operations using identity matrix
   void testMatrixIdentity();

   // make sure set( float* ) works
   template <typename DATA_TYPE>
   class matrixSetPtr
   {
   public:
      static void go()
      {   
         {
            DATA_TYPE mat44[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
            gmtl::Matrix<DATA_TYPE, 4, 4> test_mat;
            test_mat.set( mat44 );

            CPPUNIT_ASSERT( test_mat( 0, 0 ) == 0  );
            CPPUNIT_ASSERT( test_mat( 1, 0 ) == 1  );
            CPPUNIT_ASSERT( test_mat( 2, 0 ) == 2  );
            CPPUNIT_ASSERT( test_mat( 3, 0 ) == 3  );
            CPPUNIT_ASSERT( test_mat( 0, 1 ) == 4  );
            CPPUNIT_ASSERT( test_mat( 1, 1 ) == 5  );
            CPPUNIT_ASSERT( test_mat( 2, 1 ) == 6  );
            CPPUNIT_ASSERT( test_mat( 3, 1 ) == 7  );
            CPPUNIT_ASSERT( test_mat( 0, 2 ) == 8  );
            CPPUNIT_ASSERT( test_mat( 1, 2 ) == 9  );
            CPPUNIT_ASSERT( test_mat( 2, 2 ) == 10 );
            CPPUNIT_ASSERT( test_mat( 3, 2 ) == 11 );
            CPPUNIT_ASSERT( test_mat( 0, 3 ) == 12 );
            CPPUNIT_ASSERT( test_mat( 1, 3 ) == 13 );
            CPPUNIT_ASSERT( test_mat( 2, 3 ) == 14 );
            CPPUNIT_ASSERT( test_mat( 3, 3 ) == 15 );
         }

         {
            DATA_TYPE mat34[] = { 0,1,2,3,4,5,6,7,8,9,10,11 };
            gmtl::Matrix<DATA_TYPE, 3, 4> test_mat;
            test_mat.set( mat34 );

            CPPUNIT_ASSERT( test_mat( 0, 0 ) == 0 );
            CPPUNIT_ASSERT( test_mat( 1, 0 ) == 1 );
            CPPUNIT_ASSERT( test_mat( 2, 0 ) == 2 );
            CPPUNIT_ASSERT( test_mat( 0, 1 ) == 3 );
            CPPUNIT_ASSERT( test_mat( 1, 1 ) == 4 );
            CPPUNIT_ASSERT( test_mat( 2, 1 ) == 5 );
            CPPUNIT_ASSERT( test_mat( 0, 2 ) == 6 );
            CPPUNIT_ASSERT( test_mat( 1, 2 ) == 7 );
            CPPUNIT_ASSERT( test_mat( 2, 2 ) == 8 );
            CPPUNIT_ASSERT( test_mat( 0, 3 ) == 9 );
            CPPUNIT_ASSERT( test_mat( 1, 3 ) == 10 );
            CPPUNIT_ASSERT( test_mat( 2, 3 ) == 11 );
         }

         {
            DATA_TYPE mat33[] = { 0,1,2,3,4,5,6,7,8 };
            gmtl::Matrix<DATA_TYPE, 3, 3> test_mat;
            test_mat.set( mat33 );

            CPPUNIT_ASSERT( test_mat( 0, 0 ) == 0 );
            CPPUNIT_ASSERT( test_mat( 1, 0 ) == 1 );
            CPPUNIT_ASSERT( test_mat( 2, 0 ) == 2 );
            CPPUNIT_ASSERT( test_mat( 0, 1 ) == 3 );
            CPPUNIT_ASSERT( test_mat( 1, 1 ) == 4 );
            CPPUNIT_ASSERT( test_mat( 2, 1 ) == 5 );
            CPPUNIT_ASSERT( test_mat( 0, 2 ) == 6 );
            CPPUNIT_ASSERT( test_mat( 1, 2 ) == 7 );
            CPPUNIT_ASSERT( test_mat( 2, 2 ) == 8 );
         }

         {
            DATA_TYPE mat23[] = { 0,1,2,3,4,5 };
            gmtl::Matrix<DATA_TYPE, 2, 3> test_mat;
            test_mat.set( mat23 );

            CPPUNIT_ASSERT( test_mat( 0, 0 ) == 0 );
            CPPUNIT_ASSERT( test_mat( 1, 0 ) == 1 );
            CPPUNIT_ASSERT( test_mat( 0, 1 ) == 2 );
            CPPUNIT_ASSERT( test_mat( 1, 1 ) == 3 );
            CPPUNIT_ASSERT( test_mat( 0, 2 ) == 4 );
            CPPUNIT_ASSERT( test_mat( 1, 2 ) == 5 );
         }
         {
            DATA_TYPE mat22[] = { 0,1,2,3 };
            gmtl::Matrix<DATA_TYPE, 2, 2> test_mat;
            test_mat.set( mat22 );

            CPPUNIT_ASSERT( test_mat( 0, 0 ) == 0 );
            CPPUNIT_ASSERT( test_mat( 1, 0 ) == 1 );
            CPPUNIT_ASSERT( test_mat( 0, 1 ) == 2 );
            CPPUNIT_ASSERT( test_mat( 1, 1 ) == 3 );
         }
      }
   };


   // make sure set( float* ) works
   void testMatrixSetPtr();

   // make sure setTranspose( float* ) works
   // setTranspose allows you to set up your mat by hand in a static array (float mat[] = {};)
   // in such a way that the formatting in your code looks like the memory layout of the matrix
   // i.e. colums and rows will match. 
   // this setTranspose func doesn't take mat data in memory order, but rather its transpose.
   template <typename DATA_TYPE>
   class matrixSetTransposePtr
   {
   public:
      static void go()
      {   
         {
            DATA_TYPE mat44[] = {  0, 1, 2, 3,
                                   4, 5, 6, 7,
                                   8, 9,10,11,
                                  12,13,14,15  };
            gmtl::Matrix<DATA_TYPE, 4, 4> test_mat;
            test_mat.setTranspose( mat44 );

            CPPUNIT_ASSERT( test_mat( 0, 0 ) == 0  );
            CPPUNIT_ASSERT( test_mat( 0, 1 ) == 1  );
            CPPUNIT_ASSERT( test_mat( 0, 2 ) == 2  );
            CPPUNIT_ASSERT( test_mat( 0, 3 ) == 3  );
            CPPUNIT_ASSERT( test_mat( 1, 0 ) == 4  );
            CPPUNIT_ASSERT( test_mat( 1, 1 ) == 5  );
            CPPUNIT_ASSERT( test_mat( 1, 2 ) == 6  );
            CPPUNIT_ASSERT( test_mat( 1, 3 ) == 7  );
            CPPUNIT_ASSERT( test_mat( 2, 0 ) == 8  );
            CPPUNIT_ASSERT( test_mat( 2, 1 ) == 9  );
            CPPUNIT_ASSERT( test_mat( 2, 2 ) == 10 );
            CPPUNIT_ASSERT( test_mat( 2, 3 ) == 11 );
            CPPUNIT_ASSERT( test_mat( 3, 0 ) == 12 );
            CPPUNIT_ASSERT( test_mat( 3, 1 ) == 13 );
            CPPUNIT_ASSERT( test_mat( 3, 2 ) == 14 );
            CPPUNIT_ASSERT( test_mat( 3, 3 ) == 15 );
         }

         {
            DATA_TYPE mat34[] = { 0, 1,  2,  3,
                                  4, 5,  6,  7,
                                  8, 9, 10, 11  };
            gmtl::Matrix<DATA_TYPE, 3, 4> test_mat;
            test_mat.setTranspose( mat34 );

            CPPUNIT_ASSERT( test_mat( 0, 0 ) == 0  );
            CPPUNIT_ASSERT( test_mat( 0, 1 ) == 1  );
            CPPUNIT_ASSERT( test_mat( 0, 2 ) == 2  );
            CPPUNIT_ASSERT( test_mat( 0, 3 ) == 3  );
            CPPUNIT_ASSERT( test_mat( 1, 0 ) == 4  );
            CPPUNIT_ASSERT( test_mat( 1, 1 ) == 5  );
            CPPUNIT_ASSERT( test_mat( 1, 2 ) == 6  );
            CPPUNIT_ASSERT( test_mat( 1, 3 ) == 7  );
            CPPUNIT_ASSERT( test_mat( 2, 0 ) == 8  );
            CPPUNIT_ASSERT( test_mat( 2, 1 ) == 9  );
            CPPUNIT_ASSERT( test_mat( 2, 2 ) == 10 );
            CPPUNIT_ASSERT( test_mat( 2, 3 ) == 11 );
         }

         {
            DATA_TYPE mat33[] = { 0,1,2,
                                  3,4,5,
                                  6,7,8 };
            gmtl::Matrix<DATA_TYPE, 3, 3> test_mat;
            test_mat.setTranspose( mat33 );

            CPPUNIT_ASSERT( test_mat( 0, 0 ) == 0 );
            CPPUNIT_ASSERT( test_mat( 0, 1 ) == 1 );
            CPPUNIT_ASSERT( test_mat( 0, 2 ) == 2 );
            CPPUNIT_ASSERT( test_mat( 1, 0 ) == 3 );
            CPPUNIT_ASSERT( test_mat( 1, 1 ) == 4 );
            CPPUNIT_ASSERT( test_mat( 1, 2 ) == 5 );
            CPPUNIT_ASSERT( test_mat( 2, 0 ) == 6 );
            CPPUNIT_ASSERT( test_mat( 2, 1 ) == 7 );
            CPPUNIT_ASSERT( test_mat( 2, 2 ) == 8 );
         }

         {
            DATA_TYPE mat23[] = { 0,1,2,
                                  3,4,5 };
            gmtl::Matrix<DATA_TYPE, 2, 3> test_mat;
            test_mat.setTranspose( mat23 );

            CPPUNIT_ASSERT( test_mat( 0, 0 ) == 0 );
            CPPUNIT_ASSERT( test_mat( 0, 1 ) == 1 );
            CPPUNIT_ASSERT( test_mat( 0, 2 ) == 2 );
            CPPUNIT_ASSERT( test_mat( 1, 0 ) == 3 );
            CPPUNIT_ASSERT( test_mat( 1, 1 ) == 4 );
            CPPUNIT_ASSERT( test_mat( 1, 2 ) == 5 );
         }
         {
            DATA_TYPE mat22[] = { 0,1,
                                  2,3 };
            gmtl::Matrix<DATA_TYPE, 2, 2> test_mat;
            test_mat.setTranspose( mat22 );

            CPPUNIT_ASSERT( test_mat( 0, 0 ) == 0 );
            CPPUNIT_ASSERT( test_mat( 0, 1 ) == 1 );
            CPPUNIT_ASSERT( test_mat( 1, 0 ) == 2 );
            CPPUNIT_ASSERT( test_mat( 1, 1 ) == 3 );
         }
      }
   };
   // make sure set( float* ) works
   void testMatrixSetTransposePtr();

   // more general creation tests..
   // tests default constructor, copy constructor, set()
   //       operator() operator[]
   void testMatrix44Creation();
   void testMatrix34Creation();
   void testMatrix33Creation();
   void testMatrix23Creation();
   void testMatrix22Creation();

   static CppUnit::Test* suite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("MatrixClassTest");
      test_suite->addTest( new CppUnit::TestCaller<MatrixClassTest>("testTimingDefaultConstructor", &MatrixClassTest::testTimingDefaultConstructor));
      test_suite->addTest( new CppUnit::TestCaller<MatrixClassTest>("testTimingCopyConstructor", &MatrixClassTest::testTimingCopyConstructor));
      test_suite->addTest( new CppUnit::TestCaller<MatrixClassTest>("testTimingOpEqual", &MatrixClassTest::testTimingOpEqual));
      test_suite->addTest( new CppUnit::TestCaller<MatrixClassTest>("testTimingOpParen", &MatrixClassTest::testTimingOpParen));
      test_suite->addTest( new CppUnit::TestCaller<MatrixClassTest>("testTimingOpBracket", &MatrixClassTest::testTimingOpBracket));
      test_suite->addTest( new CppUnit::TestCaller<MatrixClassTest>("testTimingSetPtr", &MatrixClassTest::testTimingSetPtr));
      test_suite->addTest( new CppUnit::TestCaller<MatrixClassTest>("testTimingSetTransposePtr", &MatrixClassTest::testTimingSetTransposePtr));
      test_suite->addTest( new CppUnit::TestCaller<MatrixClassTest>("testTimingGetData", &MatrixClassTest::testTimingGetData));
      test_suite->addTest( new CppUnit::TestCaller<MatrixClassTest>("testTimingSet", &MatrixClassTest::testTimingSet));
      test_suite->addTest( new CppUnit::TestCaller<MatrixClassTest>("testMatrixIdentity", &MatrixClassTest::testMatrixIdentity));
      test_suite->addTest( new CppUnit::TestCaller<MatrixClassTest>("testMatrixSetPtr", &MatrixClassTest::testMatrixSetPtr));
      test_suite->addTest( new CppUnit::TestCaller<MatrixClassTest>("testMatrixSetTransposePtr", &MatrixClassTest::testMatrixSetTransposePtr));
      test_suite->addTest( new CppUnit::TestCaller<MatrixClassTest>("testMatrix44Creation", &MatrixClassTest::testMatrix44Creation));
      test_suite->addTest( new CppUnit::TestCaller<MatrixClassTest>("testMatrix34Creation", &MatrixClassTest::testMatrix34Creation));
      test_suite->addTest( new CppUnit::TestCaller<MatrixClassTest>("testMatrix33Creation", &MatrixClassTest::testMatrix33Creation));
      test_suite->addTest( new CppUnit::TestCaller<MatrixClassTest>("testMatrix23Creation", &MatrixClassTest::testMatrix23Creation));
      test_suite->addTest( new CppUnit::TestCaller<MatrixClassTest>("testMatrix22Creation", &MatrixClassTest::testMatrix22Creation));
      
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
