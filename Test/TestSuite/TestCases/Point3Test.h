/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Point3Test.h,v $
 * Date modified: $Date: 2002-01-26 23:47:52 $
 * Version:       $Revision: 1.2 $
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

#include <gmtl/Point3.h>

namespace gmtlTest
{

class Point3Test : public CppUnit::TestCase
{
public:
   Point3Test( std::string name = "Point3Test")
   : TestCase (name)
   {;}

   virtual ~Point3Test()
   {}

   virtual void setUp()
   {;}

   virtual void tearDown()
   {;}

   void testPoint3Creation()
   {
      gmtl::Point3  test_point;
      test_point.set(1,2,3);

      gmtl::Point3 new_point(test_point);    // Test copy constructor
      gmtl::Point3 another_pt;
      another_pt = test_point;               // Test it again
      another_pt = new_point;

      gmtl::Vec3 vec_pt(3,4,5);
      gmtl::Point3 p1(vec_pt);
      gmtl::Point3 p2;
      p2 = vec_pt;
      p1 = p2;
      CPPUNIT_ASSERT(p1 == vec_pt);           // Should be able to construct one

   }



   static Test* suite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("Point3Test");
      test_suite->addTest( new CppUnit::TestCaller<Point3Test>("testPoint3Creation", &Point3Test::testPoint3Creation));
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
