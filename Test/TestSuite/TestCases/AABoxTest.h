/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: AABoxTest.h,v $
 * Date modified: $Date: 2002-06-05 02:43:13 $
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
#ifndef _GMTL_AABOXTEST_H_
#define _GMTL_AABOXTEST_H_
#include <iostream>

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

namespace gmtlTest
{

class AABoxTest : public CppUnit::TestCase
{
public:
   AABoxTest( std::string name = "AABoxTest" )
      : CppUnit::TestCase (name)
   {}

   //---------------------------------------------------------------------------
   // Functionality tests
   //---------------------------------------------------------------------------
   void testCreation();
   void testCopyConstruct();
   void testConstructors();

   // -- Test accessors --//
   void testGetMin();
   void testGetMax();
   void testIsEmpty();

   // -- Test setters --//
   void testSetMin();
   void testSetMax();
   void testSetEmpty();

   //---------------------------------------------------------------------------
   // Performance tests
   //---------------------------------------------------------------------------
   void testTimingCreation();
   void testTimingCopyConstruct();
   void testTimingConstructors();

   // -- Test accessors --//
   void testTimingGetMin();
   void testTimingGetMax();
   void testTimingIsEmpty();

   // -- Test setters --//
   void testTimingSetMin();
   void testTimingSetMax();
   void testTimingSetEmpty();


   static CppUnit::Test* suite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("AABoxTest");
#define ADD_TEST(x) test_suite->addTest(new CppUnit::TestCaller<AABoxTest>( "test" #x, &AABoxTest::test ## x))
      ADD_TEST(Creation);
      ADD_TEST(CopyConstruct);
      ADD_TEST(Constructors);
      ADD_TEST(GetMin);
      ADD_TEST(GetMax);
      ADD_TEST(SetMin);
      ADD_TEST(SetMax);
      ADD_TEST(IsEmpty);
      ADD_TEST(SetEmpty);
#undef ADD_TEST
      return test_suite;
   }

   static CppUnit::Test* perfSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("AABoxPerfTest");
#define ADD_TEST(x) test_suite->addTest(new CppUnit::TestCaller<AABoxTest>( "testTiming" #x, &AABoxTest::testTiming ## x))
      ADD_TEST(Creation);
      ADD_TEST(CopyConstruct);
      ADD_TEST(Constructors);
      ADD_TEST(GetMin);
      ADD_TEST(GetMax);
      ADD_TEST(SetMin);
      ADD_TEST(SetMax);
      ADD_TEST(IsEmpty);
      ADD_TEST(SetEmpty);
#undef ADD_TEST
      return test_suite;
   }

   static CppUnit::Test* interactiveSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("InteractiveSphereTest");
      //test_suite->addTest( new CppUnit::TestCaller<ThreadTest>("interactiveCPUGrind", &ThreadTest::interactiveTestCPUGrind));
      return test_suite;
   }

protected:

};

}

#endif
