/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: PointTest.h,v $
 * Date modified: $Date: 2002-06-11 21:52:54 $
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
#include <iostream>

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

namespace gmtlTest
{

class PointTest : public CppUnit::TestCase
{
public:
   PointTest( std::string name = "PointTest" )
   : CppUnit::TestCase (name)
   {;}

   virtual ~PointTest()
   {}

   virtual void setUp()
   {;}

   virtual void tearDown()
   {
   }

   void testCreation();
   void testCopyConstruct();
   void testConstructors();

   void testSet();
   void testSetPtr();
   void testGetData();

   // -- Test comparison -- //
   void testEqualityCompare();
   void testIsEqual();

   // ---------------------------------- //
   // ---------- Math ops -------------- //
   // ---------------------------------- //
   void testOpPlusEq();
   void testOpPlus();
   void testOpMinusEq();
   void testOpMinus();
   void testOpMultScalarEq();
   void testOpMultScalar();
   void testOpDivScalarEq();
   void testOpDivScalar();

   static CppUnit::Test* suite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("PointTest");
      test_suite->addTest( new CppUnit::TestCaller<PointTest>("testCreation", &PointTest::testCreation));
      test_suite->addTest( new CppUnit::TestCaller<PointTest>("testCopyConstruct", &PointTest::testCopyConstruct));
      test_suite->addTest( new CppUnit::TestCaller<PointTest>("testConstructors", &PointTest::testConstructors));
      test_suite->addTest( new CppUnit::TestCaller<PointTest>("testSet", &PointTest::testSet));
      test_suite->addTest( new CppUnit::TestCaller<PointTest>("testSetPtr", &PointTest::testSetPtr));
      test_suite->addTest( new CppUnit::TestCaller<PointTest>("testGetData", &PointTest::testGetData));
      test_suite->addTest( new CppUnit::TestCaller<PointTest>("testEqualityCompare", &PointTest::testEqualityCompare));
      test_suite->addTest( new CppUnit::TestCaller<PointTest>("testIsEqual", &PointTest::testIsEqual));

      test_suite->addTest( new CppUnit::TestCaller<PointTest>("testOpPlusEq", &PointTest::testOpPlusEq));
      test_suite->addTest( new CppUnit::TestCaller<PointTest>("testOpPlus", &PointTest::testOpPlus));
      test_suite->addTest( new CppUnit::TestCaller<PointTest>("testOpMinusEq", &PointTest::testOpMinusEq));
      test_suite->addTest( new CppUnit::TestCaller<PointTest>("testOpMinus", &PointTest::testOpMinus));
      test_suite->addTest( new CppUnit::TestCaller<PointTest>("testOpMultScalarEq", &PointTest::testOpMultScalarEq)); 
      test_suite->addTest( new CppUnit::TestCaller<PointTest>("testOpMultScalar", &PointTest::testOpMultScalar)); 
      test_suite->addTest( new CppUnit::TestCaller<PointTest>("testOpDivScalarEq", &PointTest::testOpDivScalarEq)); 
      test_suite->addTest( new CppUnit::TestCaller<PointTest>("testOpDivScalar", &PointTest::testOpDivScalar)); 


      return test_suite;
   }

   static Test* perfSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("PointTiming");
      return test_suite;
   }
   
   static CppUnit::Test* interactiveSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("InteractivePointTest");
      //test_suite->addTest( new CppUnit::TestCaller<ThreadTest>("interactiveCPUGrind", &ThreadTest::interactiveTestCPUGrind));
      return test_suite;
   }

protected:

};

};
