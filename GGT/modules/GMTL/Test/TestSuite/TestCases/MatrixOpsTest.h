/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: MatrixOpsTest.h,v $
 * Date modified: $Date: 2002-03-21 22:06:21 $
 * Version:       $Revision: 1.20 $
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
Matrix [] -km Transformations XformInterface? Xform.h   Collision detection CollisionInterface? Intersection.h   Bounding volumes BoundingInterface? Containment.h   Math factories MathFactories Builder.h  e terms of the GNU Lesser General Public
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

#include <gmtl/Math.h>
#include <gmtl/Matrix.h>
#include <gmtl/MatrixOps.h>
#include <gmtl/Generate.h>

namespace gmtlTest
{

class MatrixOpsTest : public CppUnit::TestCase
{
public:
   MatrixOpsTest( std::string name = "MatrixOpsTest" )
   : CppUnit::TestCase (name)
   {;}

   virtual ~MatrixOpsTest()
   {}

   virtual void setUp()
   {
   }

   virtual void tearDown()
   {
   }

   // correctness tests
   void testMatrixIdentity();
   void testMatrixTimeIdentity44f();
   void testMatrixSetTrans();
   void testMatrixTranspose();
   void testMatrixAddSub();
   void testMatrixMult();
   void testMatrixScalarMult();
   void testMatInvert();

   // performance tests
   void testTimingMakeTrans();
   void testMatrixTimeTranspose44f();
   void testMatrixTimeTranspose33d();
   void testMatrixTimeMult44_mult();
   void testMatrixTimeMult44_operatorStar();
   void testMatrixTimeMult44f_operatorStarStar();
   void testMatrixTimeMult44d_operatorStarStar();
   void testMatrixTimeMult33f_operatorStarStar();
   void testMatrixTimeMult33d_operatorStarStar();
   void testMatrixTimeAdd44();
   void testMatrixTimeSub44();

   static CppUnit::Test* suite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite( "MatrixOpsTest" );

      test_suite->addTest( new CppUnit::TestCaller<MatrixOpsTest>( "testMatrixIdentity", &MatrixOpsTest::testMatrixIdentity ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixOpsTest>( "testMatrixSetTrans", &MatrixOpsTest::testMatrixSetTrans ) );

      test_suite->addTest( new CppUnit::TestCaller<MatrixOpsTest>( "testMatrixTranspose", &MatrixOpsTest::testMatrixTranspose ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixOpsTest>( "testMatrixMult", &MatrixOpsTest::testMatrixMult ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixOpsTest>( "testMatrixScalarMult", &MatrixOpsTest::testMatrixScalarMult ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixOpsTest>( "testMatrixAddSub", &MatrixOpsTest::testMatrixAddSub ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixOpsTest>( "testMatInvert", &MatrixOpsTest::testMatInvert ) );
      //test_suite->addTest( new CppUnit::TestCaller<MatrixOpsTest>( "testGetSetAxes", &MatrixOpsTest::testGetSetAxes ) );

      return test_suite;
   }

   static CppUnit::Test* perfSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite( "MatrixOpsPerfTest" );

      test_suite->addTest( new CppUnit::TestCaller<MatrixOpsTest>( "testMatrixTimeIdentity44f", &MatrixOpsTest::testMatrixTimeIdentity44f ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixOpsTest>( "testTimingMakeTrans", &MatrixOpsTest::testTimingMakeTrans ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixOpsTest>( "testMatrixTimeTranspose44f", &MatrixOpsTest::testMatrixTimeTranspose44f ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixOpsTest>( "testMatrixTimeTranspose33d", &MatrixOpsTest::testMatrixTimeTranspose33d ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixOpsTest>( "testMatrixTimeMult44_mult", &MatrixOpsTest::testMatrixTimeMult44_mult ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixOpsTest>( "testMatrixTimeMult44_operatorStar", &MatrixOpsTest::testMatrixTimeMult44_operatorStar ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixOpsTest>( "testMatrixTimeMult44f_operatorStarStar", &MatrixOpsTest::testMatrixTimeMult44f_operatorStarStar ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixOpsTest>( "testMatrixTimeMult44d_operatorStarStar", &MatrixOpsTest::testMatrixTimeMult44d_operatorStarStar ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixOpsTest>( "testMatrixTimeMult33f_operatorStarStar", &MatrixOpsTest::testMatrixTimeMult33f_operatorStarStar ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixOpsTest>( "testMatrixTimeMult33d_operatorStarStar", &MatrixOpsTest::testMatrixTimeMult33d_operatorStarStar ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixOpsTest>( "testMatrixTimeAdd44", &MatrixOpsTest::testMatrixTimeAdd44 ) );
      test_suite->addTest( new CppUnit::TestCaller<MatrixOpsTest>( "testMatrixTimeSub44", &MatrixOpsTest::testMatrixTimeSub44 ) );

      return test_suite;
   }

   static CppUnit::Test* interactiveSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("InteractiveThreadTest");
      //test_suite->addTest( new CppUnit::TestCaller<ThreadTest>("interactiveCPUGrind", &ThreadTest::interactiveTestCPUGrind));
      return test_suite;
   }

protected:

};

};
