/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: QuatClassTest.h,v $
 * Date modified: $Date: 2002-06-11 21:52:54 $
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
   class QuatClassTest : public CppUnit::TestCase
   {
   public:
      QuatClassTest( std::string name = "QuatClassTest" )
         : CppUnit::TestCase( name )
      {
      }

      virtual ~QuatClassTest()
      {}

      virtual void setUp()
      {
      }

      virtual void tearDown()
      {
      }

      void testQuatClassTestCreation();
      void testQuatTimingDefaultConstructor();
      void testQuatTimingElementConstructor();
      void testQuatTimingCopyConstructor();
      void testQuatTimingGet();
      void testQuatTimingSet();
      void testQuatTimingOpBracket();
      void testQuatTimingGetData();
      void testQuatTimingOpEqual();

      static CppUnit::Test* suite()
      {
         CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("QuatClassTest");
         test_suite->addTest( new CppUnit::TestCaller<QuatClassTest>("testQuatClassTestCreation", &QuatClassTest::testQuatClassTestCreation));
         return test_suite;
      }

      static Test* perfSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("QuatClassTiming");
      test_suite->addTest( new CppUnit::TestCaller<QuatClassTest>("testQuatTimingDefaultConstructor", &QuatClassTest::testQuatTimingDefaultConstructor));
         test_suite->addTest( new CppUnit::TestCaller<QuatClassTest>("testQuatTimingElementConstructor", &QuatClassTest::testQuatTimingElementConstructor));
         test_suite->addTest( new CppUnit::TestCaller<QuatClassTest>("testQuatTimingCopyConstructor", &QuatClassTest::testQuatTimingCopyConstructor));
         test_suite->addTest( new CppUnit::TestCaller<QuatClassTest>("testQuatTimingGet", &QuatClassTest::testQuatTimingGet));
         test_suite->addTest( new CppUnit::TestCaller<QuatClassTest>("testQuatTimingSet", &QuatClassTest::testQuatTimingSet));
         test_suite->addTest( new CppUnit::TestCaller<QuatClassTest>("testQuatTimingOpBracket", &QuatClassTest::testQuatTimingOpBracket));
         test_suite->addTest( new CppUnit::TestCaller<QuatClassTest>("testQuatTimingGetData", &QuatClassTest::testQuatTimingGetData));
         test_suite->addTest( new CppUnit::TestCaller<QuatClassTest>("testQuatTimingOpEqual", &QuatClassTest::testQuatTimingOpEqual));
         return test_suite;
   }
   
      static CppUnit::Test* interactiveSuite()
      {
         CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("InteractiveQuatClassTest");
         //test_suite->addTest( new CppUnit::TestCaller<ThreadTest>("interactiveCPUGrind", &ThreadTest::interactiveTestCPUGrind));
         return test_suite;
      }

   protected:

   };

} // end namespace
