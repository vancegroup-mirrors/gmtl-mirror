/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: ConvertTest.h,v $
 * Date modified: $Date: 2002-03-10 20:19:53 $
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
* modify it under th MathPrimitives  [PrimName]Ops.h  Vec & Point [100%] -ab
Quat [] -km Transforquations XformInterface? Xform.h   Collision detection CollisionInterface? Intersection.h   Bounding volumes BoundingInterface? Containment.h   Math factories MathFactories Builder.h  e terms of the GNU Lesser General Public
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

#include <gmtl/gmtlConfig.h>
#include <gmtl/Convert.h>

namespace gmtlTest
{

class ConvertTest : public CppUnit::TestCase
{
public:
   ConvertTest( std::string name = "ConvertTest" )
   : CppUnit::TestCase (name)
   {;}

   virtual ~ConvertTest()
   {}

   virtual void setUp()
   {;}

   virtual void tearDown()
   {
   }

   void testConvertVecToPureQuat()
   {
      const float eps = 0.0001f;
      gmtl::Vec<float, 3> vec( 1,2,3 );
      gmtl::Quat<float> quat( 4,5,6 ), bok, expected( 1, 2, 3, 0 );
      bok = gmtl::convert( quat, vec );
      CPPUNIT_ASSERT( gmtl::isEqual( expected, quat, eps ) );
      CPPUNIT_ASSERT( gmtl::isEqual( expected, bok, eps ) );
   }

   static CppUnit::Test* suite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite( "ConvertTest" );
      test_suite->addTest( new CppUnit::TestCaller<ConvertTest>( "testConvertVecToPureQuat", &ConvertTest::testConvertVecToPureQuat ) );
      return test_suite;
   }

   static CppUnit::Test* interactiveSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite( "InteractiveThreadTest" );
      //test_suite->addTest( new CppUnit::TestCaller<ThreadTest>( "interactiveCPUGrind", &ThreadTest::interactiveTestCPUGrind));
      return test_suite;
   }

protected:

};

};
