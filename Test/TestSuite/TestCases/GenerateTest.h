/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: GenerateTest.h,v $
 * Date modified: $Date: 2002-03-19 23:06:49 $
 * Version:       $Revision: 1.13 $
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
#include <gmtl/gmtlConfig.h>
#include <iostream>

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include <gmtl/Vec.h>
#include <gmtl/VecOps.h>
#include <gmtl/Quat.h>
#include <gmtl/QuatOps.h>
#include <gmtl/Generate.h>


/// @todo test/timing on makeRot( quat ) (euler version)

namespace gmtlTest
{

class GenerateTest : public CppUnit::TestCase
{
public:
   GenerateTest( std::string name = "GenerateTest" )
   : CppUnit::TestCase (name)
   {;}

   virtual ~GenerateTest()
   {}

   virtual void setUp()
   {;}

   virtual void tearDown()
   {
   }

   void output( gmtl::Quat<float> q )
   {
      std::cout<<q[0]<<" "<<q[1]<<" "<<q[2]<<" "<<q[3]<<std::endl;
   }

   //-- vec tests --//
   void testMakeVecFromQuat();
   void testMakeNormalVecFromVec();

   //-- quat tests --//
   void testQuatMakePure();
   void testQuatMakeConj();
   void testQuatMakeInvert();
   void testQuatMakeRot();
   void testQuatGetRot();
   void testQuatMakeGetMakeRot();

   //-- timing tests --//
   void testGenTimingMakeNormalVec1();
   void testGenTimingMakeNormalVec2();
   void testGenTimingMakeNormalVec3();
   void testGenTimingMakeNormalVec4();

   void testGenTimingMakeInvert1();
   void testGenTimingMakeInvert2();

   void testGenTimingMakeConj();
   void testGenTimingMakePure();
   void testGenTimingMakeVec();
   void testGenTimingMakeNormalQuat();
   void testGenTimingMakeRot();

   /** @todo implement quat makeRot Euler */
   static CppUnit::Test* suite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite( "GenerateTest" );
      test_suite->addTest( new CppUnit::TestCaller<GenerateTest>( "testMakeVecFromQuat", &GenerateTest::testMakeVecFromQuat ) );
      test_suite->addTest( new CppUnit::TestCaller<GenerateTest>( "testMakeNormalVecFromVec", &GenerateTest::testMakeNormalVecFromVec ) );
      test_suite->addTest( new CppUnit::TestCaller<GenerateTest>( "testQuatMakePure", &GenerateTest::testQuatMakePure ) );
      test_suite->addTest( new CppUnit::TestCaller<GenerateTest>( "testQuatMakeConj", &GenerateTest::testQuatMakeConj ) );
      test_suite->addTest( new CppUnit::TestCaller<GenerateTest>( "testQuatMakeInvert", &GenerateTest::testQuatMakeInvert ) );
      test_suite->addTest( new CppUnit::TestCaller<GenerateTest>( "testQuatMakeRot", &GenerateTest::testQuatMakeRot ) );
      test_suite->addTest( new CppUnit::TestCaller<GenerateTest>( "testQuatGetRot", &GenerateTest::testQuatGetRot ) );
      test_suite->addTest( new CppUnit::TestCaller<GenerateTest>( "testQuatMakeGetMakeRot", &GenerateTest::testQuatMakeGetMakeRot ) );
      
      test_suite->addTest( new CppUnit::TestCaller<GenerateTest>( "testGenTimingMakeNormalVec1", &GenerateTest::testGenTimingMakeNormalVec1 ) );
      test_suite->addTest( new CppUnit::TestCaller<GenerateTest>( "testGenTimingMakeNormalVec2", &GenerateTest::testGenTimingMakeNormalVec2 ) );
      test_suite->addTest( new CppUnit::TestCaller<GenerateTest>( "testGenTimingMakeNormalVec3", &GenerateTest::testGenTimingMakeNormalVec3 ) );
      test_suite->addTest( new CppUnit::TestCaller<GenerateTest>( "testGenTimingMakeNormalVec4", &GenerateTest::testGenTimingMakeNormalVec4 ) );
      test_suite->addTest( new CppUnit::TestCaller<GenerateTest>( "testGenTimingMakeInvert1", &GenerateTest::testGenTimingMakeInvert1 ) );
      test_suite->addTest( new CppUnit::TestCaller<GenerateTest>( "testGenTimingMakeInvert2", &GenerateTest::testGenTimingMakeInvert2 ) );
      test_suite->addTest( new CppUnit::TestCaller<GenerateTest>( "testGenTimingMakeConj", &GenerateTest::testGenTimingMakeConj ) );
      test_suite->addTest( new CppUnit::TestCaller<GenerateTest>( "testGenTimingMakePure", &GenerateTest::testGenTimingMakePure ) );
      test_suite->addTest( new CppUnit::TestCaller<GenerateTest>( "testGenTimingMakeVec", &GenerateTest::testGenTimingMakeVec ) );
      test_suite->addTest( new CppUnit::TestCaller<GenerateTest>( "testGenTimingMakeNormalQuat", &GenerateTest::testGenTimingMakeNormalQuat ) );
      test_suite->addTest( new CppUnit::TestCaller<GenerateTest>( "testGenTimingMakeRot", &GenerateTest::testGenTimingMakeRot ) );

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
