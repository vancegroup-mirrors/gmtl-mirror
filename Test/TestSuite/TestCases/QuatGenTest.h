/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: QuatGenTest.h,v $
 * Date modified: $Date: 2002-07-02 02:07:02 $
 * Version:       $Revision: 1.5 $
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

#include <gmtl/Vec.h>
#include <gmtl/VecOps.h>
#include <gmtl/Quat.h>
#include <gmtl/QuatOps.h>
#include <gmtl/Generate.h>


/// @todo test/timing on makeRot( quat ) (euler version)

namespace gmtlTest
{

class QuatGenTest : public CppUnit::TestCase
{
public:
   QuatGenTest( std::string name = "QuatGenTest" )
   : CppUnit::TestCase (name)
   {;}

   virtual ~QuatGenTest()
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

   //-- quat tests --//
   void testQuatMakePure();
   void testQuatMakeConj();
   void testQuatMakeInvert();
   void testQuatMakeRot();
   void testQuatGetRot();
   void testQuatMakeGetMakeRot();

   //-- timing tests --//
   void testGenTimingMakeInvert1();
   void testGenTimingMakeInvert2();
   void testGenTimingMakeConj();
   void testGenTimingMakePure();
   void testGenTimingMakeNormalQuat();
   void testGenTimingMakeRot();
   void testGenTimingSetRot();

   /** @todo implement quat makeRot Euler */
   static CppUnit::Test* suite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite( "QuatGenTest" );
      test_suite->addTest( new CppUnit::TestCaller<QuatGenTest>( "testQuatMakePure", &QuatGenTest::testQuatMakePure ) );
      test_suite->addTest( new CppUnit::TestCaller<QuatGenTest>( "testQuatMakeConj", &QuatGenTest::testQuatMakeConj ) );
      test_suite->addTest( new CppUnit::TestCaller<QuatGenTest>( "testQuatMakeInvert", &QuatGenTest::testQuatMakeInvert ) );
      test_suite->addTest( new CppUnit::TestCaller<QuatGenTest>( "testQuatMakeRot", &QuatGenTest::testQuatMakeRot ) );
      test_suite->addTest( new CppUnit::TestCaller<QuatGenTest>( "testQuatGetRot", &QuatGenTest::testQuatGetRot ) );
      test_suite->addTest( new CppUnit::TestCaller<QuatGenTest>( "testQuatMakeGetMakeRot", &QuatGenTest::testQuatMakeGetMakeRot ) );
      
      return test_suite;
   }

   static CppUnit::Test* perfSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("QuatGenTiming");
      test_suite->addTest( new CppUnit::TestCaller<QuatGenTest>( "testGenTimingMakeInvert1", &QuatGenTest::testGenTimingMakeInvert1 ) );
      test_suite->addTest( new CppUnit::TestCaller<QuatGenTest>( "testGenTimingMakeInvert2", &QuatGenTest::testGenTimingMakeInvert2 ) );
      test_suite->addTest( new CppUnit::TestCaller<QuatGenTest>( "testGenTimingMakeConj", &QuatGenTest::testGenTimingMakeConj ) );
      test_suite->addTest( new CppUnit::TestCaller<QuatGenTest>( "testGenTimingMakePure", &QuatGenTest::testGenTimingMakePure ) );
      test_suite->addTest( new CppUnit::TestCaller<QuatGenTest>( "testGenTimingMakeNormalQuat", &QuatGenTest::testGenTimingMakeNormalQuat ) );
      test_suite->addTest( new CppUnit::TestCaller<QuatGenTest>( "testGenTimingMakeRot", &QuatGenTest::testGenTimingMakeRot ) );
      test_suite->addTest( new CppUnit::TestCaller<QuatGenTest>( "testGenTimingSetRot", &QuatGenTest::testGenTimingSetRot ) );
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
