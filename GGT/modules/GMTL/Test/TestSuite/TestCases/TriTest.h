/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: TriTest.h,v $
 * Date modified: $Date: 2002-05-20 22:39:23 $
 * Version:       $Revision: 1.10 $
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

class TriTest : public CppUnit::TestCase
{
public:
   TriTest( std::string name = "TriTest")
   : CppUnit::TestCase (name)
   {}

   virtual ~TriTest()
   {}

   virtual void setUp()
   {}

   virtual void tearDown()
   {}

   void testCreation();
   void testCopyConstruct();
   void testConstructors();

   //---------------------------------------------------------------------------
   // Begin testing accessors
   //---------------------------------------------------------------------------
   void testVertexAccessor();
   void testEdges();

   //---------------------------------------------------------------------------
   // Begin testing comparators
   //---------------------------------------------------------------------------
   void testEqualOps();
   void testIsEqual();
   void testCenter();
   void testNormal();


   static CppUnit::Test* suite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("TriTest");
      test_suite->addTest( new CppUnit::TestCaller<TriTest>("testCreation", &TriTest::testCreation));
      test_suite->addTest( new CppUnit::TestCaller<TriTest>("testCopyConstruct", &TriTest::testCopyConstruct));
      test_suite->addTest( new CppUnit::TestCaller<TriTest>("testConstructors", &TriTest::testConstructors));
      test_suite->addTest( new CppUnit::TestCaller<TriTest>("testVertexAccessor", &TriTest::testVertexAccessor));
      test_suite->addTest( new CppUnit::TestCaller<TriTest>("testEdges", &TriTest::testEdges));
      test_suite->addTest( new CppUnit::TestCaller<TriTest>("testEqualOps", &TriTest::testEqualOps));
      test_suite->addTest( new CppUnit::TestCaller<TriTest>("testIsEqual", &TriTest::testIsEqual));
      test_suite->addTest( new CppUnit::TestCaller<TriTest>("testCenter", &TriTest::testCenter));
      test_suite->addTest( new CppUnit::TestCaller<TriTest>("testNormal", &TriTest::testNormal));
      return test_suite;
   }

   static CppUnit::Test* interactiveSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("InteractiveTriTest");
      //test_suite->addTest( new CppUnit::TestCaller<ThreadTest>("interactiveCPUGrind", &ThreadTest::interactiveTestCPUGrind));
      return test_suite;
   }
};

} // namespace gmtlTest
