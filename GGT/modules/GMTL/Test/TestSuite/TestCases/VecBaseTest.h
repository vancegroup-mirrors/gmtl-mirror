/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: VecBaseTest.h,v $
 * Date modified: $Date: 2002-05-20 22:39:23 $
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
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

namespace gmtlTest
{

class VecBaseTest : public CppUnit::TestCase
{
public:
   VecBaseTest( std::string name = "VecBaseTest" )
   : CppUnit::TestCase (name)
   {;}

   virtual ~VecBaseTest()
   {}

   virtual void setUp()
   {;}

   virtual void tearDown()
   {
   }

   // correctness tests
   void testVecBaseCreation();
   void testCopyConstruct();
   void testConstructors();

   void testSet();
   void testSetPtr();
   void testGetData();

   // performance tests
   void testTimingVecBaseCreation();
   void testTimingCopyConstruct();
   void testTimingConstructors();

   void testTimingSet();
   void testTimingSetPtr();
   void testTimingGetData();

   static CppUnit::Test* suite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("VecBaseTest");
      test_suite->addTest( new CppUnit::TestCaller<VecBaseTest>("testVecBaseCreation", &VecBaseTest::testVecBaseCreation));
      test_suite->addTest( new CppUnit::TestCaller<VecBaseTest>("testCopyConstruct", &VecBaseTest::testCopyConstruct));
      test_suite->addTest( new CppUnit::TestCaller<VecBaseTest>("testConstructors", &VecBaseTest::testConstructors));
      test_suite->addTest( new CppUnit::TestCaller<VecBaseTest>("testSet", &VecBaseTest::testSet));
      test_suite->addTest( new CppUnit::TestCaller<VecBaseTest>("testSetPtr", &VecBaseTest::testSetPtr));
      test_suite->addTest( new CppUnit::TestCaller<VecBaseTest>("testGetData", &VecBaseTest::testGetData));

      return test_suite;
   }

   static CppUnit::Test* perfSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("VecBasePerfTest");

      test_suite->addTest( new CppUnit::TestCaller<VecBaseTest>("testTimingVecBaseCreation", &VecBaseTest::testTimingVecBaseCreation));
      test_suite->addTest( new CppUnit::TestCaller<VecBaseTest>("testTimingCopyConstruct", &VecBaseTest::testTimingCopyConstruct));
      test_suite->addTest( new CppUnit::TestCaller<VecBaseTest>("testTimingConstructors", &VecBaseTest::testTimingConstructors));
      test_suite->addTest( new CppUnit::TestCaller<VecBaseTest>("testTimingSet", &VecBaseTest::testTimingSet));
      test_suite->addTest( new CppUnit::TestCaller<VecBaseTest>("testTimingSetPtr", &VecBaseTest::testTimingSetPtr));

      return test_suite;
   }

   static CppUnit::Test* interactiveSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("InteractiveVecBaseTest");
      //test_suite->addTest( new CppUnit::TestCaller<ThreadTest>("interactiveCPUGrind", &ThreadTest::interactiveTestCPUGrind));
      return test_suite;
   }

protected:

};

};
