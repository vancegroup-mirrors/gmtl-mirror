/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: IntersectionTest.h,v $
 * Date modified: $Date: 2002-11-26 06:32:26 $
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
#ifndef _GMTL_INTERSECTIONTEST_H_
#define _GMTL_INTERSECTIONTEST_H_
#include <iostream>

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

namespace gmtlTest
{

class IntersectionTest : public CppUnit::TestCase
{
public:
   IntersectionTest( std::string name = "IntersectionTest" )
      : CppUnit::TestCase (name)
   {}

   //---------------------------------------------------------------------------
   // Functionality tests
   //---------------------------------------------------------------------------
   void testIntersectAABoxAABox();
   void testIntersectAABoxPoint();
   void testIntersectAABoxSphere();

   void testIntersectAABoxSweep();
   void testIntersectSphereSweep();

   //---------------------------------------------------------------------------
   // Performance tests
   //---------------------------------------------------------------------------
   void testTimingIntersectAABoxAABox();
   void testTimingIntersectAABoxPoint();

   void testTimingIntersectAABoxSweep();
   void testTimingIntersectSphereSweep();

   static CppUnit::Test* suite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("IntersectionTest");
#define ADD_TEST(x) test_suite->addTest(new CppUnit::TestCaller<IntersectionTest>( "test" #x, &IntersectionTest::test ## x))
      ADD_TEST(IntersectAABoxAABox);
      ADD_TEST(IntersectAABoxPoint);
      ADD_TEST(IntersectAABoxSphere);
      ADD_TEST(IntersectAABoxSweep);
      ADD_TEST(IntersectSphereSweep);
#undef ADD_TEST
      return test_suite;
   }

   static CppUnit::Test* perfSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("IntersectionPerfTest");
#define ADD_TEST(x) test_suite->addTest(new CppUnit::TestCaller<IntersectionTest>( "testTiming" #x, &IntersectionTest::testTiming ## x))
      ADD_TEST(IntersectAABoxAABox);
      ADD_TEST(IntersectAABoxPoint);
      ADD_TEST(IntersectAABoxSweep);
      ADD_TEST(IntersectSphereSweep);
#undef ADD_TEST
      return test_suite;
   }

   static CppUnit::Test* interactiveSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("InteractiveIntersectionTest");
      //test_suite->addTest( new CppUnit::TestCaller<ThreadTest>("interactiveCPUGrind", &ThreadTest::interactiveTestCPUGrind));
      return test_suite;
   }

protected:

};

}

#endif
