/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: AABoxContainTest.h,v $
 * Date modified: $Date: 2002-11-26 07:41:17 $
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
#ifndef _GMTL_AABOXCONTAINTEST_H_
#define _GMTL_AABOXCONTAINTEST_H_
#include <iostream>

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

namespace gmtlTest
{

class AABoxContainTest : public CppUnit::TestCase
{
public:
   AABoxContainTest( std::string name = "AABoxContainTest" )
      : CppUnit::TestCase (name)
   {}

   //---------------------------------------------------------------------------
   // Functionality tests
   //---------------------------------------------------------------------------
   void testIsInVolumePt();
   void testIsInVolumeAABox();
   void testExtendVolumePt();
   void testExtendVolumeAABox();
   void testMakeVolumeSphere();

   //---------------------------------------------------------------------------
   // Performance tests
   //---------------------------------------------------------------------------
   void testTimingIsInVolumePt();
   void testTimingIsInVolumeAABox();
   void testTimingExtendVolumePt();
   void testTimingExtendVolumeAABox();

   static CppUnit::Test* suite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("AABoxContainTest");
#define ADD_TEST(x) test_suite->addTest(new CppUnit::TestCaller<AABoxContainTest>( "test" #x, &AABoxContainTest::test ## x))
      ADD_TEST(IsInVolumePt);
      ADD_TEST(IsInVolumeAABox);
      ADD_TEST(ExtendVolumePt);
      ADD_TEST(ExtendVolumeAABox);
      ADD_TEST(MakeVolumeSphere);
#undef ADD_TEST
      return test_suite;
   }

   static CppUnit::Test* perfSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("AABoxContainPerfTest");
#define ADD_TEST(x) test_suite->addTest(new CppUnit::TestCaller<AABoxContainTest>( "testTiming" #x, &AABoxContainTest::testTiming ## x))
      ADD_TEST(IsInVolumePt);
      ADD_TEST(IsInVolumeAABox);
      ADD_TEST(ExtendVolumePt);
      ADD_TEST(ExtendVolumeAABox);
#undef ADD_TEST
      return test_suite;
   }

   static CppUnit::Test* interactiveSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("InteractiveAABoxTest");
      //test_suite->addTest( new CppUnit::TestCaller<ThreadTest>("interactiveCPUGrind", &ThreadTest::interactiveTestCPUGrind));
      return test_suite;
   }

protected:

};

}

#endif
