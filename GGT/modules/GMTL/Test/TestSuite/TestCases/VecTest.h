/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: VecTest.h,v $
 * Date modified: $Date: 2002-05-20 22:39:23 $
 * Version:       $Revision: 1.24 $
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

#include <gmtl/Vec.h>
#include <gmtl/VecOps.h>

namespace gmtlTest
{

class VecTest : public CppUnit::TestCase
{
public:
   VecTest( std::string name = "VecTest" )
   : CppUnit::TestCase (name)
   {;}

   virtual ~VecTest()
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
   void testOpNegate();
   void testOpPlusEq();
   void testOpPlus();
   void testOpMinusEq();
   void testOpMinus();
   void testOpMultScalarEq();
   void testOpMultScalar();
   void testOpScalarVecMult();
   void testOpDivScalarEq();
   void testOpDivScalar();
   void testGroupedOpsPerformance();

   // ---- Vec specific functions --- //
   void testDot();
   void testLength();
   void testNormalize();
   void testIsNormalized();
   void testIsNormalizedEps();
   void testCross();

   void testVecTimingLerp();
   void testLerp();
   

   static CppUnit::Test* suite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("VecTest");
      test_suite->addTest( new CppUnit::TestCaller<VecTest>("testLerp", &VecTest::testLerp));
      test_suite->addTest( new CppUnit::TestCaller<VecTest>("testVecTimingLerp", &VecTest::testVecTimingLerp));
      
      test_suite->addTest( new CppUnit::TestCaller<VecTest>("testCreation", &VecTest::testCreation));
      test_suite->addTest( new CppUnit::TestCaller<VecTest>("testCopyConstruct", &VecTest::testCopyConstruct));
      test_suite->addTest( new CppUnit::TestCaller<VecTest>("testConstructors", &VecTest::testConstructors));
      test_suite->addTest( new CppUnit::TestCaller<VecTest>("testSet", &VecTest::testSet));
      test_suite->addTest( new CppUnit::TestCaller<VecTest>("testSetPtr", &VecTest::testSetPtr));
      test_suite->addTest( new CppUnit::TestCaller<VecTest>("testGetData", &VecTest::testGetData));
      test_suite->addTest( new CppUnit::TestCaller<VecTest>("testEqualityCompare", &VecTest::testEqualityCompare));
      test_suite->addTest( new CppUnit::TestCaller<VecTest>("testIsEqual", &VecTest::testIsEqual));

      test_suite->addTest( new CppUnit::TestCaller<VecTest>("testOpPlusEq", &VecTest::testOpPlusEq));
      test_suite->addTest( new CppUnit::TestCaller<VecTest>("testOpPlus", &VecTest::testOpPlus));
      test_suite->addTest( new CppUnit::TestCaller<VecTest>("testOpMinusEq", &VecTest::testOpMinusEq));
      test_suite->addTest( new CppUnit::TestCaller<VecTest>("testOpMinus", &VecTest::testOpMinus));
      test_suite->addTest( new CppUnit::TestCaller<VecTest>("testOpMultScalarEq", &VecTest::testOpMultScalarEq));
      test_suite->addTest( new CppUnit::TestCaller<VecTest>("testOpMultScalar", &VecTest::testOpMultScalar));
      test_suite->addTest( new CppUnit::TestCaller<VecTest>("testOpScalarVecMult", &VecTest::testOpScalarVecMult));
      test_suite->addTest( new CppUnit::TestCaller<VecTest>("testOpDivScalarEq", &VecTest::testOpDivScalarEq));
      test_suite->addTest( new CppUnit::TestCaller<VecTest>("testOpDivScalar", &VecTest::testOpDivScalar));

      test_suite->addTest( new CppUnit::TestCaller<VecTest>("testGroupedOpsPerformance", &VecTest::testGroupedOpsPerformance));

      test_suite->addTest( new CppUnit::TestCaller<VecTest>("testDot", &VecTest::testDot));
      test_suite->addTest( new CppUnit::TestCaller<VecTest>("testLength", &VecTest::testLength));
      test_suite->addTest( new CppUnit::TestCaller<VecTest>("testNormalize", &VecTest::testNormalize));
      test_suite->addTest( new CppUnit::TestCaller<VecTest>("testIsNormalized", &VecTest::testIsNormalized));
      test_suite->addTest( new CppUnit::TestCaller<VecTest>("testIsNormalizedEps", &VecTest::testIsNormalizedEps));
      test_suite->addTest( new CppUnit::TestCaller<VecTest>("testCross", &VecTest::testCross));


      return test_suite;
   }

   static CppUnit::Test* interactiveSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("InteractiveVecTest");
      //test_suite->addTest( new CppUnit::TestCaller<ThreadTest>("interactiveCPUGrind", &ThreadTest::interactiveTestCPUGrind));
      return test_suite;
   }

protected:

};

};
