/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: QuatOpsTest.h,v $
 * Date modified: $Date: 2002-03-21 16:07:55 $
 * Version:       $Revision: 1.12 $
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
#include <gmtl/gmtlConfig.h>
#include <iostream>

#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include <gmtl/Quat.h>
#include <gmtl/QuatOps.h>
#include <gmtl/Generate.h>

namespace gmtlTest
{

class QuatOpsTest : public CppUnit::TestCase
{
public:
   QuatOpsTest( std::string name = "QuatOpsTest" )
   : CppUnit::TestCase( name )
   {;}

   virtual ~QuatOpsTest()
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
   

   void testQuatTimingNegate();
   void testQuatTimingOperatorMinus();
   void testQuatTimingMult();
   void testQuatTimingOperatorMult();
   void testQuatTimingDiv();
   void testQuatTimingLerp();
   void testQuatTimingVectorMult();
   void testQuatTimingVectorAdd();
   void testQuatTimingVectorSub();
   void testQuatTimingVectorDot();
   void testQuatTimingNorm();
   void testQuatTimingMag();
   void testQuatTimingNormalize();
   void testQuatTimingConj();
   void testQuatTimingInvert();
   
   
   
   void testQuatMult();
   void testQuatDiv();
   void testQuatVectorMult();
   void testQuatVectorAdd();
   void testQuatVectorSub();
   void testQuatVectorDot();
   void testQuatNorm();
   void testQuatMag();
   void testQuatNormalize();
   void testQuatConj();
   void testQuatNegate();
   void testQuatInvert();
   void testQuatSlerp();
   void testQuatLerp();
   

   static CppUnit::Test* suite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite( "QuatOpsTest" );
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>( "testQuatMult", &QuatOpsTest::testQuatMult ));
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>( "testQuatVectorMult", &QuatOpsTest::testQuatVectorMult ));
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>( "testQuatDiv", &QuatOpsTest::testQuatDiv ));
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>( "testQuatVectorAdd", &QuatOpsTest::testQuatVectorAdd ));
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>( "testQuatVectorSub", &QuatOpsTest::testQuatVectorSub ));
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>( "testQuatVectorDot", &QuatOpsTest::testQuatVectorDot ));
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>( "testQuatNorm", &QuatOpsTest::testQuatNorm ));
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>( "testQuatMag", &QuatOpsTest::testQuatMag ));
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>( "testQuatNormalize", &QuatOpsTest::testQuatNormalize ));
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>( "testQuatConj", &QuatOpsTest::testQuatConj ));
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>( "testQuatInvert", &QuatOpsTest::testQuatInvert ));
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>( "testQuatNegate", &QuatOpsTest::testQuatNegate ));
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>( "testQuatSlerp", &QuatOpsTest::testQuatSlerp ));
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>( "testQuatLerp", &QuatOpsTest::testQuatLerp ));
 
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>( "testQuatTimingOperatorMinus", &QuatOpsTest::testQuatTimingOperatorMinus ));
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>( "testQuatTimingNegate", &QuatOpsTest::testQuatTimingNegate ));
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>( "testQuatTimingMult", &QuatOpsTest::testQuatTimingMult ));
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>( "testQuatTimingLerp", &QuatOpsTest::testQuatTimingLerp ));
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>( "testQuatTimingOperatorMult", &QuatOpsTest::testQuatTimingOperatorMult ));
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>( "testQuatTimingVectorMult", &QuatOpsTest::testQuatTimingVectorMult ));
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>( "testQuatTimingDiv", &QuatOpsTest::testQuatTimingDiv ));
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>( "testQuatTimingVectorAdd", &QuatOpsTest::testQuatTimingVectorAdd ));
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>( "testQuatTimingVectorSub", &QuatOpsTest::testQuatTimingVectorSub ));
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>( "testQuatTimingVectorDot", &QuatOpsTest::testQuatTimingVectorDot ));
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>( "testQuatTimingNorm", &QuatOpsTest::testQuatTimingNorm ));
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>( "testQuatTimingMag", &QuatOpsTest::testQuatTimingMag ));
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>( "testQuatTimingNormalize", &QuatOpsTest::testQuatTimingNormalize ));
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>( "testQuatTimingConj", &QuatOpsTest::testQuatTimingConj ));
      test_suite->addTest( new CppUnit::TestCaller<QuatOpsTest>( "testQuatTimingInvert", &QuatOpsTest::testQuatTimingInvert ));

      return test_suite;
   }

   static CppUnit::Test* interactiveSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite( "InteractiveThreadTest" );
      //test_suite->addTest( new CppUnit::TestCaller<ThreadTest>( "interactiveCPUGrind", &ThreadTest::interactiveTestCPUGrind ));
      return test_suite;
   }

protected:

};

};
