/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: MatrixCompareTest.h,v $
 * Date modified: $Date: 2002-03-21 21:51:28 $
 * Version:       $Revision: 1.11 $
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
