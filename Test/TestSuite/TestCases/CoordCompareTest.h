/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: CoordCompareTest.h,v $
 * Date modified: $Date: 2002-03-20 21:43:36 $
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
#include <gmtl/gmtlConfig.h>
#include <iostream>

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include <gmtl/Coord.h>
#include <gmtl/CoordOps.h>

namespace gmtlTest
{

class CoordCompareTest : public CppUnit::TestCase
{
public:
   CoordCompareTest( std::string name = "CoordCompareTest" )
      : CppUnit::TestCase (name)
   {;}

   virtual ~CoordCompareTest()
   {}

   virtual void setUp()
   {;}

   virtual void tearDown()
   {
   }

   void testCoordEqualityFloatTest();
   void testCoordEqualityDoubleTest();
   void testCoordTimingOpEqualityTest();
   void testCoordTimingOpNotEqualityTest();
   void testCoordTimingIsEqualTest();


   static CppUnit::Test* suite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("CoordCompareTest");
      test_suite->addTest( new CppUnit::TestCaller<CoordCompareTest>("testCoordTimingOpEqualityTest", &CoordCompareTest::testCoordTimingOpEqualityTest));
      test_suite->addTest( new CppUnit::TestCaller<CoordCompareTest>("testCoordTimingIsEqualTest", &CoordCompareTest::testCoordTimingIsEqualTest));
      test_suite->addTest( new CppUnit::TestCaller<CoordCompareTest>("testCoordTimingOpNotEqualityTest", &CoordCompareTest::testCoordTimingOpNotEqualityTest));
      test_suite->addTest( new CppUnit::TestCaller<CoordCompareTest>("testCoordEqualityFloatTest", &CoordCompareTest::testCoordEqualityFloatTest));
      test_suite->addTest( new CppUnit::TestCaller<CoordCompareTest>("testCoordEqualityDoubleTest", &CoordCompareTest::testCoordEqualityDoubleTest));
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
