/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: AxisAngleClassTest.h,v $
 * Date modified: $Date: 2002-06-10 20:16:39 $
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
   class AxisAngleClassTest : public CppUnit::TestCase
   {
   public:
      AxisAngleClassTest( std::string name = "AxisAngleClassTest" )
         : CppUnit::TestCase( name )
      {
      }

      virtual ~AxisAngleClassTest()
      {}

      virtual void setUp()
      {
      }

      virtual void tearDown()
      {
      }

      void testAxisAngleClassTestCreation();
      void testAxisAngleTimingDefaultConstructor();
      void testAxisAngleTimingElementConstructor();
      void testAxisAngleTimingCopyConstructor();
      void testAxisAngleTimingSet();
      void testAxisAngleTimingOpBracket();
      void testAxisAngleTimingGetData();
      void testAxisAngleTimingOpEqual();

      static CppUnit::Test* suite()
      {
         CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("AxisAngleClassTest");
         
         // perf_suite
         test_suite->addTest( new CppUnit::TestCaller<AxisAngleClassTest>("testAxisAngleTimingDefaultConstructor", &AxisAngleClassTest::testAxisAngleTimingDefaultConstructor));
         test_suite->addTest( new CppUnit::TestCaller<AxisAngleClassTest>("testAxisAngleTimingElementConstructor", &AxisAngleClassTest::testAxisAngleTimingElementConstructor));
         test_suite->addTest( new CppUnit::TestCaller<AxisAngleClassTest>("testAxisAngleTimingCopyConstructor", &AxisAngleClassTest::testAxisAngleTimingCopyConstructor));
         test_suite->addTest( new CppUnit::TestCaller<AxisAngleClassTest>("testAxisAngleTimingSet", &AxisAngleClassTest::testAxisAngleTimingSet));
         test_suite->addTest( new CppUnit::TestCaller<AxisAngleClassTest>("testAxisAngleTimingOpBracket", &AxisAngleClassTest::testAxisAngleTimingOpBracket));
         test_suite->addTest( new CppUnit::TestCaller<AxisAngleClassTest>("testAxisAngleTimingGetData", &AxisAngleClassTest::testAxisAngleTimingGetData));
         test_suite->addTest( new CppUnit::TestCaller<AxisAngleClassTest>("testAxisAngleTimingOpEqual", &AxisAngleClassTest::testAxisAngleTimingOpEqual));
         
         // gmtl_suite
         test_suite->addTest( new CppUnit::TestCaller<AxisAngleClassTest>("testAxisAngleClassTestCreation", &AxisAngleClassTest::testAxisAngleClassTestCreation));
         return test_suite;
      }

      static CppUnit::Test* interactiveSuite()
      {
         CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("InteractiveAxisAngleClassTest");
         //test_suite->addTest( new CppUnit::TestCaller<ThreadTest>("interactiveCPUGrind", &ThreadTest::interactiveTestCPUGrind));
         return test_suite;
      }

   protected:

   };

} // end namespace
