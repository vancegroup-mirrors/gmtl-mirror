/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: EulerAngleClassTest.h,v $
 * Date modified: $Date: 2002-07-02 02:07:01 $
 * Version:       $Revision: 1.3 $
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
#include <iostream>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

namespace gmtlTest
{
   class EulerAngleClassTest : public CppUnit::TestCase
   {
   public:
      EulerAngleClassTest( std::string name = "EulerAngleClassTest" )
         : CppUnit::TestCase( name )
      {
      }

      virtual ~EulerAngleClassTest()
      {}

      virtual void setUp()
      {
      }

      virtual void tearDown()
      {
      }

      void testEulerAngleClassTestCreation();
      void testEulerAngleTimingDefaultConstructor();
      void testEulerAngleTimingElementConstructor();
      void testEulerAngleTimingCopyConstructor();
      void testEulerAngleTimingSet();
      void testEulerAngleTimingOpBracket();
      void testEulerAngleTimingGetData();
      void testEulerAngleTimingOpEqual();

      static CppUnit::Test* suite()
      {
         CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("EulerAngleClassTest");
         test_suite->addTest( new CppUnit::TestCaller<EulerAngleClassTest>("testEulerAngleClassTestCreation", &EulerAngleClassTest::testEulerAngleClassTestCreation));
         return test_suite;
      }

      static CppUnit::Test* perfSuite()
      {
         CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("EulerTiming");
         test_suite->addTest( new CppUnit::TestCaller<EulerAngleClassTest>("testEulerAngleTimingDefaultConstructor", &EulerAngleClassTest::testEulerAngleTimingDefaultConstructor));
         test_suite->addTest( new CppUnit::TestCaller<EulerAngleClassTest>("testEulerAngleTimingElementConstructor", &EulerAngleClassTest::testEulerAngleTimingElementConstructor));
         test_suite->addTest( new CppUnit::TestCaller<EulerAngleClassTest>("testEulerAngleTimingCopyConstructor", &EulerAngleClassTest::testEulerAngleTimingCopyConstructor));
         test_suite->addTest( new CppUnit::TestCaller<EulerAngleClassTest>("testEulerAngleTimingSet", &EulerAngleClassTest::testEulerAngleTimingSet));
         test_suite->addTest( new CppUnit::TestCaller<EulerAngleClassTest>("testEulerAngleTimingOpBracket", &EulerAngleClassTest::testEulerAngleTimingOpBracket));
         test_suite->addTest( new CppUnit::TestCaller<EulerAngleClassTest>("testEulerAngleTimingGetData", &EulerAngleClassTest::testEulerAngleTimingGetData));
         test_suite->addTest( new CppUnit::TestCaller<EulerAngleClassTest>("testEulerAngleTimingOpEqual", &EulerAngleClassTest::testEulerAngleTimingOpEqual));
         
         return test_suite;
      }

      static CppUnit::Test* interactiveSuite()
      {
         CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("InteractiveEulerAngleClassTest");
         //test_suite->addTest( new CppUnit::TestCaller<ThreadTest>("interactiveCPUGrind", &ThreadTest::interactiveTestCPUGrind));
         return test_suite;
      }

   protected:

   };

} // end namespace
