/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: VecTest.h,v $
 * Date modified: $Date: 2003-02-06 01:39:50 $
 * Version:       $Revision: 1.28 $
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
#ifndef _GMTL_VEC_TEST_H_
#define _GMTL_VEC_TEST_H_

#include <cppunit/extensions/HelperMacros.h>

namespace gmtlTest
{
   /**
    * Functionality tests
    */
   class VecTest : public CppUnit::TestFixture
   {
      CPPUNIT_TEST_SUITE(VecTest);

      CPPUNIT_TEST(testCreation);
      CPPUNIT_TEST(testCopyConstruct);
      CPPUNIT_TEST(testConstructors);
      CPPUNIT_TEST(testSet);
      CPPUNIT_TEST(testSetPtr);
      CPPUNIT_TEST(testGetData);
      CPPUNIT_TEST(testEqualityCompare);
      CPPUNIT_TEST(testIsEqual);
      CPPUNIT_TEST(testOpNegate);
      CPPUNIT_TEST(testOpPlusEq);
      CPPUNIT_TEST(testOpPlus);
      CPPUNIT_TEST(testOpMinusEq);
      CPPUNIT_TEST(testOpMinus);
      CPPUNIT_TEST(testOpMultScalarEq);
      CPPUNIT_TEST(testOpMultScalar);
      CPPUNIT_TEST(testOpScalarVecMult);
      CPPUNIT_TEST(testOpDivScalarEq);
      CPPUNIT_TEST(testOpDivScalar);
      CPPUNIT_TEST(testGroupedOpsPerformance);
      CPPUNIT_TEST(testDot);
      CPPUNIT_TEST(testLength);
      CPPUNIT_TEST(testNormalize);
      CPPUNIT_TEST(testIsNormalized);
      CPPUNIT_TEST(testIsNormalizedEps);
      CPPUNIT_TEST(testCross);
      CPPUNIT_TEST(testReflect);
      CPPUNIT_TEST(testVecTimingLerp);
      CPPUNIT_TEST(testLerp);

      CPPUNIT_TEST_SUITE_END();

   public:
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
      void testReflect();

      void testVecTimingLerp();
      void testLerp();
   };
}

#endif
