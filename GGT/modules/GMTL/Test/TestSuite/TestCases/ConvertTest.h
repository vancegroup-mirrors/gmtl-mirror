/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: ConvertTest.h,v $
 * Date modified: $Date: 2002-06-11 21:52:53 $
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

#include <gmtl/Generate.h>

/// @todo test convert( vec, matrix ), convert( matrix, vec )

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
   {}

   void testConvertVecToPureQuat();

   void testConvertQuatMat_MatQuat();

   static CppUnit::Test* suite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite( "ConvertTest" );
      test_suite->addTest( new CppUnit::TestCaller<ConvertTest>( "testConvertVecToPureQuat", &ConvertTest::testConvertVecToPureQuat ) );
      test_suite->addTest( new CppUnit::TestCaller<ConvertTest>( "testConvertQuatMat_MatQuat", &ConvertTest::testConvertQuatMat_MatQuat ) );
      return test_suite;
   }

   static Test* perfSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("ConvertTiming");
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
