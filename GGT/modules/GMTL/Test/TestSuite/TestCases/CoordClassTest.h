/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: CoordClassTest.h,v $
 * Date modified: $Date: 2002-05-20 22:39:23 $
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
   class CoordClassTest : public CppUnit::TestCase
   {
   public:
      CoordClassTest( std::string name = "CoordClassTest" )
         : CppUnit::TestCase( name )
      {
      }

      virtual ~CoordClassTest()
      {}

      virtual void setUp()
      {
      }

      virtual void tearDown()
      {
      }

      // Correctness tests
      void testCoordClassTestCreation();

      // Performance tests
      void testCoordTimingDefaultConstructor();
      void testCoordTimingElementConstructor();
      void testCoordTimingCopyConstructor();
      void testCoordTimingGet();
      void testCoordTimingOpEqual();

      static CppUnit::Test* suite()
      {
         CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("CoordClassTest");
         test_suite->addTest( new CppUnit::TestCaller<CoordClassTest>("testCoordClassTestCreation", &CoordClassTest::testCoordClassTestCreation));
         return test_suite;
      }

      static CppUnit::Test* perfSuite()
      {
         CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("CoordClassPerfTest");

         test_suite->addTest( new CppUnit::TestCaller<CoordClassTest>("testCoordTimingDefaultConstructor", &CoordClassTest::testCoordTimingDefaultConstructor));
         test_suite->addTest( new CppUnit::TestCaller<CoordClassTest>("testCoordTimingElementConstructor", &CoordClassTest::testCoordTimingElementConstructor));
         test_suite->addTest( new CppUnit::TestCaller<CoordClassTest>("testCoordTimingCopyConstructor", &CoordClassTest::testCoordTimingCopyConstructor));
         test_suite->addTest( new CppUnit::TestCaller<CoordClassTest>("testCoordTimingGet", &CoordClassTest::testCoordTimingGet));
         test_suite->addTest( new CppUnit::TestCaller<CoordClassTest>("testCoordTimingOpEqual", &CoordClassTest::testCoordTimingOpEqual));

         return test_suite;
      }

      static CppUnit::Test* interactiveSuite()
      {
         CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("InteractiveCoordClassTest");
         //test_suite->addTest( new CppUnit::TestCaller<ThreadTest>("interactiveCPUGrind", &ThreadTest::interactiveTestCPUGrind));
         return test_suite;
      }

   protected:

   };

} // end namespace
