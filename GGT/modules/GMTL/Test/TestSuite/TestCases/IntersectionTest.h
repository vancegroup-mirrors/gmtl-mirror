/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: IntersectionTest.h,v $
 * Date modified: $Date: 2002-05-20 22:39:23 $
 * Version:       $Revision: 1.4 $
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
#ifndef _INTERSECTION_TEST_H_
#define _INTERSECTION_TEST_H_

#include <iostream>

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include <gmtl/Vec3.h>
#include <gmtl/Point3.h>
#include <gmtl/OOBox.h>
#include <gmtl/Intersection.h>
#include <gmtl/gmtlOutput.h>


namespace gmtlTest
{
   using namespace gmtl;

class IntersectionTest : public CppUnit::TestCase
{
public:
   IntersectionTest( std::string name = "IntersectionTest")
   : TestCase (name)
   {;}

   virtual ~IntersectionTest()
   {}

   virtual void setUp()
   {;}

   virtual void tearDown()
   {;}

   void testStaticObbObbIntersection()
   {
      OOBox box0, box1;

      // Axis A0
      box0.axis(0) = Vec3(1,0,0);  box0.axis(1) = Vec3(0,1,0); box0.axis(2) = Vec3(0,0,1);
      box0.center().set(0,0,0);
      box0.halfLen(0) = box0.halfLen(1) = box0.halfLen(2) = 1.0f;
      box1.axis(0) = Vec3(1,0,0);  box1.axis(1) = Vec3(0,1,0); box1.axis(2) = Vec3(0,0,1);
      box1.center().set(3,0,0);
      box1.halfLen(0) = box1.halfLen(1) = box1.halfLen(2) = 1.0f;
      CPPUNIT_ASSERT(TestIntersect(box0,box1) == false);
      CPPUNIT_ASSERT(TestIntersect(1.0f,box0,Vec3(0,0,0),box1,Vec3(0,0,0)) == false);

      // Axis A1
      box1.center().set(0,3,0);
      CPPUNIT_ASSERT(TestIntersect(box0,box1) == false);
      CPPUNIT_ASSERT(TestIntersect(1.0f,box0,Vec3(0,0,0),box1,Vec3(0,0,0)) == false);

      // Axis A2
      box1.center().set(0,0,3);
      CPPUNIT_ASSERT(TestIntersect(box0,box1) == false);
      CPPUNIT_ASSERT(TestIntersect(1.0f,box0,Vec3(0,0,0),box1,Vec3(0,0,0)) == false);

      // Axis B0
      // Axis B1
      // Axis B2


      // --- Intersections --- //
      // intersection on X Axis
      box0.axis(0) = Vec3(1,0,0);  box0.axis(1) = Vec3(0,1,0); box0.axis(2) = Vec3(0,0,1);
      box0.center().set(0,0,0);
      box0.halfLen(0) = box0.halfLen(1) = box0.halfLen(2) = 1.0f;
      box1.axis(0) = Vec3(1,0,0);  box1.axis(1) = Vec3(0,1,0); box1.axis(2) = Vec3(0,0,1);
      box1.center().set(1,0,0);
      box1.halfLen(0) = box1.halfLen(1) = box1.halfLen(2) = 1.0f;
      CPPUNIT_ASSERT(TestIntersect(box0,box1) == true);
      CPPUNIT_ASSERT(TestIntersect(1.0f,box0,Vec3(0,0,0),box1,Vec3(0,0,0)) == true);


      // ---- Other tests --- //
      // From graph test prob
      // ( cntr: [0, -9.31322e-09, 7.45058e-09]
      // ax: [0.816496, 0.408249, -0.408248] xh:0.942809
      // ay: [0.577351, -0.57735, 0.577349] yh:1
      // az: [-1.49011e-08, -0.707106, -0.707107] zh:1
      box0.center().set(0, -9.31322e-09, 7.45058e-09);
      box0.axis(0).set(0.816496, 0.408249, -0.408248);      box0.halfLen(0) = 0.942809;
      box0.axis(1).set(0.577351, -0.57735, 0.577349);       box0.halfLen(1) = 1.0;
      box0.axis(2).set(-1.49011e-08, -0.707106, -0.707107); box0.halfLen(2) = 1.0;

      // ( cntr: [1.87644e-08, 1.39422e-08, 3.96674e-10]
      // ax: [0, -4.65661e-10, -1] xh:0.25
      // ay: [1, 0, 0] yh:2.25
      // az: [0, -1, 4.65661e-10] zh:2.25
      box1.center().set(1.87644e-08, 1.39422e-08, 3.96674e-10);
      box1.axis(0).set(0, -4.65661e-10, -1);    box1.halfLen(0) = 0.25;
      box1.axis(1).set(1, 0, 0);                box1.halfLen(1) = 2.25;
      box1.axis(2).set(0, -1, 4.65661e-10);     box1.halfLen(2) = 2.25;
      CPPUNIT_ASSERT(TestIntersect(box0,box1) == true);

   }

   void testDynamicObbObbIntersection()
   {
      OOBox box0, box1;

      // Axis A0
      box0.axis(0) = Vec3(1,0,0);  box0.axis(1) = Vec3(0,1,0); box0.axis(2) = Vec3(0,0,1);
      box0.center().set(0,0,0);
      box0.halfLen(0) = box0.halfLen(1) = box0.halfLen(2) = 1.0f;
      box1.axis(0) = Vec3(1,0,0);  box1.axis(1) = Vec3(0,1,0); box1.axis(2) = Vec3(0,0,1);
      box1.center().set(3,0,0);
      box1.halfLen(0) = box1.halfLen(1) = box1.halfLen(2) = 1.0f;
      CPPUNIT_ASSERT(TestIntersect(0.5f,box0,Vec3(1,0,0),box1,Vec3(0,0,0)) == false);
      CPPUNIT_ASSERT(TestIntersect(0.5f,box0,Vec3(0,0,0),box1,Vec3(-1,0,0)) == false);
      CPPUNIT_ASSERT(TestIntersect(1.0f,box0,Vec3(1,0,0),box1,Vec3(0,0,0)) == true);
      CPPUNIT_ASSERT(TestIntersect(1.0f,box0,Vec3(0,0,0),box1,Vec3(-1,0,0)) == true);
      CPPUNIT_ASSERT(TestIntersect(2.0f,box0,Vec3(1,0,0),box1,Vec3(0,0,0)) == true);
      CPPUNIT_ASSERT(TestIntersect(2.0f,box0,Vec3(0,0,0),box1,Vec3(-1,0,0)) == true);


      // Axis A1
      box1.center().set(0,3,0);
      CPPUNIT_ASSERT(TestIntersect(0.5f,box0,Vec3(0,1,0),box1,Vec3(0,0,0)) == false);
      CPPUNIT_ASSERT(TestIntersect(0.5f,box0,Vec3(0,0,0),box1,Vec3(0,-1,0)) == false);
      CPPUNIT_ASSERT(TestIntersect(1.0f,box0,Vec3(0,1,0),box1,Vec3(0,0,0)) == true);
      CPPUNIT_ASSERT(TestIntersect(1.0f,box0,Vec3(0,0,0),box1,Vec3(0,-1,0)) == true);
      CPPUNIT_ASSERT(TestIntersect(2.0f,box0,Vec3(0,1,0),box1,Vec3(0,0,0)) == true);
      CPPUNIT_ASSERT(TestIntersect(2.0f,box0,Vec3(0,0,0),box1,Vec3(0,-1,0)) == true);

      // Axis A2
      box1.center().set(0,0,3);
      CPPUNIT_ASSERT(TestIntersect(0.5f,box0,Vec3(0,0,1),box1,Vec3(0,0,0)) == false);
      CPPUNIT_ASSERT(TestIntersect(0.5f,box0,Vec3(0,0,0),box1,Vec3(0,0,-1)) == false);
      CPPUNIT_ASSERT(TestIntersect(1.0f,box0,Vec3(0,0,1),box1,Vec3(0,0,0)) == true);
      CPPUNIT_ASSERT(TestIntersect(1.0f,box0,Vec3(0,0,0),box1,Vec3(0,0,-1)) == true);
      CPPUNIT_ASSERT(TestIntersect(2.0f,box0,Vec3(0,0,1),box1,Vec3(0,0,0)) == true);
      CPPUNIT_ASSERT(TestIntersect(2.0f,box0,Vec3(0,0,0),box1,Vec3(0,0,-1)) == true);

      // Axis B0
      // Axis B1
      // Axis B2


      // --- X crossing --- //
      // intersection on X,Y plane
      box0.axis(0) = Vec3(1,0,0);  box0.axis(1) = Vec3(0,1,0); box0.axis(2) = Vec3(0,0,1);
      box0.center().set(-2,-2,0);
      box0.halfLen(0) = box0.halfLen(1) = box0.halfLen(2) = 0.5f;
      box1.axis(0) = Vec3(1,0,0);  box1.axis(1) = Vec3(0,1,0); box1.axis(2) = Vec3(0,0,1);
      box1.center().set(2,2,0);
      box1.halfLen(0) = box1.halfLen(1) = box1.halfLen(2) = 0.5f;
      Vec3 urVec(1,1,0);      // Vector moving up and right
      CPPUNIT_ASSERT(TestIntersect(0.5f,box0,urVec,box1,-urVec) == false);
      CPPUNIT_ASSERT(TestIntersect(1.0f,box0,urVec,box1,-urVec) == false);
      CPPUNIT_ASSERT(TestIntersect(1.5f,box0,urVec,box1,-urVec) == true);
      CPPUNIT_ASSERT(TestIntersect(2.0f,box0,urVec,box1,-urVec) == true);
      CPPUNIT_ASSERT(TestIntersect(2.5f,box0,urVec,box1,-urVec) == true);
   }


   void testFirstContactObbObbIntersection()
   {
      OOBox box0, box1;

      // Axis A0
      box0.axis(0).set(1,0,0);  box0.axis(1).set(0,1,0); box0.axis(2).set(0,0,1);
      box0.center().set(0,0,0);
      box0.halfLen(0) = box0.halfLen(1) = box0.halfLen(2) = 1.0f;

      box1.axis(0).set(1,0,0);  box1.axis(1).set(0,1,0); box1.axis(2).set(0,0,1);
      box1.center().set(3,0,0);
      box1.halfLen(0) = box1.halfLen(1) = box1.halfLen(2) = 1.0f;

      float contactTime;

      // --- Axis A0 --- //
      // Move towards, but don't hit
      CPPUNIT_ASSERT(TestIntersect(0.5f,box0,Vec3(1,0,0),box1,Vec3(0,0,0),contactTime) == false);
      CPPUNIT_ASSERT(TestIntersect(0.5f,box0,Vec3(0,0,0),box1,Vec3(-1,0,0),contactTime) == false);
      CPPUNIT_ASSERT(TestIntersect(0.25f,box0,Vec3(1,0,0),box1,Vec3(-1,0,0),contactTime) == false);
      // Move towards, and hit at end of time
      CPPUNIT_ASSERT(TestIntersect(1.0f,box0,Vec3(1,0,0),box1,Vec3(0,0,0),contactTime) == true);
      CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0f,contactTime,0.001);
      CPPUNIT_ASSERT(TestIntersect(1.0f,box0,Vec3(0,0,0),box1,Vec3(-1,0,0),contactTime) == true);
      CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0f,contactTime,0.001);
      CPPUNIT_ASSERT(TestIntersect(0.5f,box0,Vec3(1,0,0),box1,Vec3(-1,0,0),contactTime) == true);
      CPPUNIT_ASSERT_DOUBLES_EQUAL(0.5f,contactTime,0.001);
      // Move towards, and hit during
      CPPUNIT_ASSERT(TestIntersect(1.0f,box0,Vec3(2,0,0),box1,Vec3(0,0,0),contactTime) == true);
      CPPUNIT_ASSERT_DOUBLES_EQUAL(0.5f,contactTime,0.001);
      CPPUNIT_ASSERT(TestIntersect(2.0f,box0,Vec3(0,0,0),box1,Vec3(-2,0,0),contactTime) == true);
      CPPUNIT_ASSERT_DOUBLES_EQUAL(0.5f,contactTime,0.001);
      CPPUNIT_ASSERT(TestIntersect(10.0f,box0,Vec3(0.25,0,0),box1,Vec3(-0.5,0,0),contactTime) == true);
      CPPUNIT_ASSERT_DOUBLES_EQUAL(1.333333f,contactTime,0.001);

      /*
      // Axis A1
      box1.center().set(0,3,0);
      CPPUNIT_ASSERT(TestIntersect(0.5f,box0,Vec3(0,1,0),box1,Vec3(0,0,0)) == false);
      CPPUNIT_ASSERT(TestIntersect(0.5f,box0,Vec3(0,0,0),box1,Vec3(0,-1,0)) == false);
      CPPUNIT_ASSERT(TestIntersect(1.0f,box0,Vec3(0,1,0),box1,Vec3(0,0,0)) == true);
      CPPUNIT_ASSERT(TestIntersect(1.0f,box0,Vec3(0,0,0),box1,Vec3(0,-1,0)) == true);
      CPPUNIT_ASSERT(TestIntersect(2.0f,box0,Vec3(0,1,0),box1,Vec3(0,0,0)) == true);
      CPPUNIT_ASSERT(TestIntersect(2.0f,box0,Vec3(0,0,0),box1,Vec3(0,-1,0)) == true);

      // Axis A2
      box1.center().set(0,0,3);
      CPPUNIT_ASSERT(TestIntersect(0.5f,box0,Vec3(0,0,1),box1,Vec3(0,0,0)) == false);
      CPPUNIT_ASSERT(TestIntersect(0.5f,box0,Vec3(0,0,0),box1,Vec3(0,0,-1)) == false);
      CPPUNIT_ASSERT(TestIntersect(1.0f,box0,Vec3(0,0,1),box1,Vec3(0,0,0)) == true);
      CPPUNIT_ASSERT(TestIntersect(1.0f,box0,Vec3(0,0,0),box1,Vec3(0,0,-1)) == true);
      CPPUNIT_ASSERT(TestIntersect(2.0f,box0,Vec3(0,0,1),box1,Vec3(0,0,0)) == true);
      CPPUNIT_ASSERT(TestIntersect(2.0f,box0,Vec3(0,0,0),box1,Vec3(0,0,-1)) == true);

      // Axis B0
      // Axis B1
      // Axis B2


      // --- X crossing --- //
      // intersection on X,Y plane
      box0.axis(0) = Vec3(1,0,0);  box0.axis(1) = Vec3(0,1,0); box0.axis(2) = Vec3(0,0,1);
      box0.center().set(-2,-2,0);
      box0.halfLen(0) = box0.halfLen(1) = box0.halfLen(2) = 0.5f;
      box1.axis(0) = Vec3(1,0,0);  box1.axis(1) = Vec3(0,1,0); box1.axis(2) = Vec3(0,0,1);
      box1.center().set(2,2,0);
      box1.halfLen(0) = box1.halfLen(1) = box1.halfLen(2) = 0.5f;
      Vec3 urVec(1,1,0);      // Vector moving up and right
      CPPUNIT_ASSERT(TestIntersect(0.5f,box0,urVec,box1,-urVec) == false);
      CPPUNIT_ASSERT(TestIntersect(1.0f,box0,urVec,box1,-urVec) == false);
      CPPUNIT_ASSERT(TestIntersect(1.5f,box0,urVec,box1,-urVec) == true);
      CPPUNIT_ASSERT(TestIntersect(2.0f,box0,urVec,box1,-urVec) == true);
      CPPUNIT_ASSERT(TestIntersect(2.5f,box0,urVec,box1,-urVec) == true);
      */
   }


   static Test* suite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("IntersectionTest");
      test_suite->addTest( new CppUnit::TestCaller<IntersectionTest>("testStaticObbObbIntersection", &IntersectionTest::testStaticObbObbIntersection));
      test_suite->addTest( new CppUnit::TestCaller<IntersectionTest>("testDynamicObbObbIntersection", &IntersectionTest::testDynamicObbObbIntersection));
      test_suite->addTest( new CppUnit::TestCaller<IntersectionTest>("testFirstContactObbObbIntersection", &IntersectionTest::testFirstContactObbObbIntersection));

      return test_suite;
   }

   static Test* interactiveSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("IntersectionTestInteractive");
      //test_suite->addTest( new CppUnit::TestCaller<ThreadTest>("interactiveCPUGrind", &ThreadTest::interactiveTestCPUGrind));
      return test_suite;
   }

protected:

};

};

#endif
