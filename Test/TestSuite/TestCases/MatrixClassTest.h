/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: MatrixClassTest.h,v $
 * Date modified: $Date: 2002-05-20 22:39:23 $
 * Version:       $Revision: 1.15 $
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

   // correctness tests

   // test out operations using identity matrix
   void testMatrixIdentity();

   // make sure set( float* ) works
   void testMatrixSetPtr();

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

   // performance tests
   void testTimingDefaultConstructor();
   void testTimingCopyConstructor();

   void testTimingOpEqual();
   void testTimingOpParen();
   void testTimingOpBracket();

   void testTimingSetPtr();
   void testTimingSetTransposePtr();
   void testTimingGetData();
   void testTimingSet();


   static CppUnit::Test* suite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("MatrixClassTest");
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

   static CppUnit::Test* perfSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("MatrixClassPerfTest");

      test_suite->addTest( new CppUnit::TestCaller<MatrixClassTest>("testTimingDefaultConstructor", &MatrixClassTest::testTimingDefaultConstructor));
      test_suite->addTest( new CppUnit::TestCaller<MatrixClassTest>("testTimingCopyConstructor", &MatrixClassTest::testTimingCopyConstructor));
      test_suite->addTest( new CppUnit::TestCaller<MatrixClassTest>("testTimingOpEqual", &MatrixClassTest::testTimingOpEqual));
      test_suite->addTest( new CppUnit::TestCaller<MatrixClassTest>("testTimingOpParen", &MatrixClassTest::testTimingOpParen));
      test_suite->addTest( new CppUnit::TestCaller<MatrixClassTest>("testTimingOpBracket", &MatrixClassTest::testTimingOpBracket));
      test_suite->addTest( new CppUnit::TestCaller<MatrixClassTest>("testTimingSetPtr", &MatrixClassTest::testTimingSetPtr));
      test_suite->addTest( new CppUnit::TestCaller<MatrixClassTest>("testTimingSetTransposePtr", &MatrixClassTest::testTimingSetTransposePtr));
      test_suite->addTest( new CppUnit::TestCaller<MatrixClassTest>("testTimingGetData", &MatrixClassTest::testTimingGetData));
      test_suite->addTest( new CppUnit::TestCaller<MatrixClassTest>("testTimingSet", &MatrixClassTest::testTimingSet));

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
