/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Vec3Test.h,v $
 * Date modified: $Date: 2002-01-31 00:56:20 $
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
#include <gfxConfig.h>
#include <iostream>

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include <gmtl/Vec3.h>
#include <gmtl/matVecFuncs.h>

namespace gmtlTest
{

class Vec3Test : public CppUnit::TestCase
{
public:
   Vec3Test( std::string name = "Vec3Test" )
   : TestCase (name)
   {;}

   virtual ~Vec3Test()
   {}

   virtual void setUp()
   {;}

   virtual void tearDown()
   {
   }

   void testVec3Creation()
   {
      gmtl::Vec3  float_vec3;
      float_vec3.set(1,2,3);
   }

   void testVec3Equal()
   {
      gmtl::Vec3 v1(1.0,2.0,3.0);
      gmtl::Vec3 v2(1.00001, 2.00002, 3.00003);
      gmtl::Vec3 v3(1.1, 2.2, 3.3);

      CPPUNIT_ASSERT(v1 != v2);
      CPPUNIT_ASSERT(v1.equal(v2));
      CPPUNIT_ASSERT(!v1.equal(v3,0.001));
   }

   void testVec3Cross()
   {
      gmtl::Vec3 v1(gmtl::XUnitVec3);
      gmtl::Vec3 v2(gmtl::YUnitVec3);
      gmtl::Vec3 v3(gmtl::ZUnitVec3);
      gmtl::Vec3 cross;

      // Base Vectors
      cross = v1.cross(v2);
      CPPUNIT_ASSERT(cross.equal(v3));
      cross = v2.cross(v1);
      CPPUNIT_ASSERT(cross.equal(v3 * -1.0f));

      v1.set(13.45, -7.8, 0.056);
      v2.set(0.777, 5.333,12.21);
      v3.set(-95.537, -164.181, 77.789);

      cross = v1.cross(v2);
      CPPUNIT_ASSERT(cross.equal(v3,0.01));
      cross = v2.cross(v1);
      CPPUNIT_ASSERT(cross.equal(v3 * -1.0f,0.01));
   }


   void testVec3Dot()
   {
      gmtl::Vec3 v1(gmtl::XUnitVec3);
      gmtl::Vec3 v2(gmtl::YUnitVec3);
      gmtl::Vec3 v3(gmtl::ZUnitVec3);
      float dot, ans;

      // Base Vectors
      CPPUNIT_ASSERT(v1.dot(v2) == 0.0f);
      CPPUNIT_ASSERT(v1.dot(v3) == 0.0f);
      CPPUNIT_ASSERT(v2.dot(v3) == 0.0f);

      // Other Vectors
      v1.set(13.45, -7.8, 0.056);
      v2.set(0.777, 5.333,12.21);
      v3.set(3.4, -1.6, 0.23);

      ans = -30.463;
      dot = v1.dot(v2);
      CPPUNIT_ASSERT(GMTL_NEAR(dot,ans,0.01));
      dot = v2.dot(v1);
      CPPUNIT_ASSERT(GMTL_NEAR(dot,ans,0.01));
      ans = -3.0827;
      dot = v2.dot(v3);
      CPPUNIT_ASSERT(GMTL_NEAR(dot,ans,0.01));
      dot = v3.dot(v2);
      CPPUNIT_ASSERT(GMTL_NEAR(dot,ans,0.01));
   }


   static Test* suite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("Vec3Test");
      test_suite->addTest( new CppUnit::TestCaller<Vec3Test>("testVec3Create", &Vec3Test::testVec3Creation));
      test_suite->addTest( new CppUnit::TestCaller<Vec3Test>("testVec3Equal", &Vec3Test::testVec3Equal));
      test_suite->addTest( new CppUnit::TestCaller<Vec3Test>("testVec3Dot", &Vec3Test::testVec3Dot));
      test_suite->addTest( new CppUnit::TestCaller<Vec3Test>("testVec3Cross", &Vec3Test::testVec3Cross));
      return test_suite;
   }

   static Test* interactiveSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("InteractiveThreadTest");
      //test_suite->addTest( new CppUnit::TestCaller<ThreadTest>("interactiveCPUGrind", &ThreadTest::interactiveTestCPUGrind));
      return test_suite;
   }

protected:

};

};
