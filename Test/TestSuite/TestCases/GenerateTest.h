/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: GenerateTest.h,v $
 * Date modified: $Date: 2002-02-22 20:12:58 $
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
   
   void testMakeVecFromQuat()
   {
      gmtl::Quat<float> quat( 0.0f,21.0f,31.0f,1234.0f );
      gmtl::Vec<float, 3> vec( gmtl::makeVec( quat ) );
      CPPUNIT_ASSERT( vec[0] == 0.0f );
      CPPUNIT_ASSERT( vec[1] == 21.0f );
      CPPUNIT_ASSERT( vec[2] == 31.0f );
   }
   
   //-- quat tests --//

   void testQuatMakePure()
   {
      gmtl::Vec<float, 3> vec( 121, 232, 343 );
      gmtl::Quat<float> quat( gmtl::makePure( vec ) );
      CPPUNIT_ASSERT( quat[gmtl::Xelt] == 121 );
      CPPUNIT_ASSERT( quat[gmtl::Yelt] == 232 );
      CPPUNIT_ASSERT( quat[gmtl::Zelt] == 343 );
   }
   
   void testQuatMakeConj()
   {
      gmtl::Quat<float> quat( 0.0f,21.0f,31.0f,1234.0f );
      gmtl::Quat<float> quat2 = gmtl::makeConj( quat );
      
      // make sure the func didn't munge the data...
      CPPUNIT_ASSERT( quat[gmtl::Xelt] == 0.0f );
      CPPUNIT_ASSERT( quat[gmtl::Yelt] == 21.0f );
      CPPUNIT_ASSERT( quat[gmtl::Zelt] == 31.0f );
      CPPUNIT_ASSERT( quat[gmtl::Welt] == 1234.0f );
      
      // make sure invert worked.
      CPPUNIT_ASSERT( quat2[gmtl::Xelt] == -0.0f );
      CPPUNIT_ASSERT( quat2[gmtl::Yelt] == -21.0f );
      CPPUNIT_ASSERT( quat2[gmtl::Zelt] == -31.0f );
      CPPUNIT_ASSERT( quat2[gmtl::Welt] == 1234.0f );
   }
   
   void testQuatMakeInvert()
   {
      // test out mult( result, quat, quat )
      const float eps = 0.0001f;
      gmtl::Quat<float> q( 0.2, 0.33, 0.44, 0.101 ), expected_result( -0.567053, -0.935637, -1.24752, 0.286362 );
      gmtl::Quat<float> q4( gmtl::makeInvert( q ) );
      CPPUNIT_ASSERT( gmtl::isEqual( expected_result, q4, eps ) );
   }
   
   void testQuatMakeRot()
   {
      const float eps = 0.0001f;
      gmtl::Quat<float> q1, q2;
      gmtl::makeRot( q1, gmtl::Math::deg2Rad( 90.0f ), 1.0f, 0.0f, 0.0f );
      gmtl::makeRot( q2, gmtl::Math::deg2Rad( 32.0f ), 0.0f, 1.0f, 0.0f );
      gmtl::Quat<float> expected_result1( 0.707107, 0, 0, 0.707107 );
      gmtl::Quat<float> expected_result2( 0, 0.275637, 0, 0.961262 );

      CPPUNIT_ASSERT( gmtl::isEqual( expected_result1, q1, eps ) );
      CPPUNIT_ASSERT( gmtl::isEqual( expected_result2, q2, eps ) );
      CPPUNIT_ASSERT( gmtl::isNormalized( q1, eps ) );
      CPPUNIT_ASSERT( gmtl::isNormalized( q2, eps ) );
      
      // values from VR Juggler math lib...
      std::vector< gmtl::Quat<float> > quats;
      quats.push_back( gmtl::Quat<float>( 0, 0, 0, -1       ) );
      quats.push_back( gmtl::Quat<float>( -0, -0.173648, -0, -0.984808) );
      quats.push_back( gmtl::Quat<float>( -0, -0.34202, -0, -0.939693 ) );
      quats.push_back( gmtl::Quat<float>( -0, -0.5, -0, -0.866025     ) );
      quats.push_back( gmtl::Quat<float>( -0, -0.642788, -0, -0.766044) );
      quats.push_back( gmtl::Quat<float>( -0, -0.766044, -0, -0.642788) );
      quats.push_back( gmtl::Quat<float>( -0, -0.866025, -0, -0.5     ) );
      quats.push_back( gmtl::Quat<float>( -0, -0.939693, -0, -0.34202 ) );
      quats.push_back( gmtl::Quat<float>( -0, -0.984808, -0, -0.173648) );
      quats.push_back( gmtl::Quat<float>( -0, -1, -0, 0    ) );
      quats.push_back( gmtl::Quat<float>( -0, -0.984808, -0, 0.173648 ) );
      quats.push_back( gmtl::Quat<float>( -0, -0.939693, -0, 0.34202  ) );
      quats.push_back( gmtl::Quat<float>( -0, -0.866025, -0, 0.5      ) );
      quats.push_back( gmtl::Quat<float>( -0, -0.766044, -0, 0.642788 ) );
      quats.push_back( gmtl::Quat<float>( -0, -0.642788, -0, 0.766044 ) );
      quats.push_back( gmtl::Quat<float>( -0, -0.5, -0, 0.866025      ) );
      quats.push_back( gmtl::Quat<float>( -0, -0.34202, -0, 0.939693  ) );
      quats.push_back( gmtl::Quat<float>( -0, -0.173648, -0, 0.984808 ) );
      quats.push_back( gmtl::Quat<float>( 0, 0, 0, 1                  ) );
      quats.push_back( gmtl::Quat<float>( 0, 0.173648, 0, 0.984808    ) );
      quats.push_back( gmtl::Quat<float>( 0, 0.34202, 0, 0.939693     ) );
      quats.push_back( gmtl::Quat<float>( 0, 0.5, 0, 0.866025         ) );
      quats.push_back( gmtl::Quat<float>( 0, 0.642788, 0, 0.766044    ) );
      quats.push_back( gmtl::Quat<float>( 0, 0.766044, 0, 0.642788    ) );
      quats.push_back( gmtl::Quat<float>( 0, 0.866025, 0, 0.5         ) );
      quats.push_back( gmtl::Quat<float>( 0, 0.939693, 0, 0.34202     ) );
      quats.push_back( gmtl::Quat<float>( 0, 0.984808, 0, 0.173648    ) );
      quats.push_back( gmtl::Quat<float>( 0, 1, 0, 0       ) );
      quats.push_back( gmtl::Quat<float>( 0, 0.984808, 0, -0.173648   ) );
      quats.push_back( gmtl::Quat<float>( 0, 0.939693, 0, -0.34202    ) );
      quats.push_back( gmtl::Quat<float>( 0, 0.866025, 0, -0.5        ) );
      quats.push_back( gmtl::Quat<float>( 0, 0.766044, 0, -0.642788   ) );
      quats.push_back( gmtl::Quat<float>( 0, 0.642788, 0, -0.766044   ) );
      quats.push_back( gmtl::Quat<float>( 0, 0.5, 0, -0.866025        ) );
      quats.push_back( gmtl::Quat<float>( 0, 0.34202, 0, -0.939693    ) );
      quats.push_back( gmtl::Quat<float>( 0, 0.173648, 0, -0.984808   ) );
      quats.push_back( gmtl::Quat<float>( -0, 0, -0, -1    ) );
      
      // @todo check this against another math lib other than VR Juggler...
      int count = 0;
      for (int x = -360; x <= 360; x += 20)
      {
         gmtl::Quat<float> q3;
         CPPUNIT_ASSERT( count >= 0 );
         gmtl::makeRot( q2, gmtl::Math::deg2Rad( float(x) ), 0.0f, 1.0f, 0.0f );
         gmtl::makeRot( q3, gmtl::Math::deg2Rad( float(x) ), gmtl::Vec3f( 0.0f, 1.0f, 0.0f ) );
         CPPUNIT_ASSERT( gmtl::isEqual( quats[count], q2, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( q3, q2, eps ) );
         count++;
      }
   }

   void testQuatGetRot()
   {
      const float eps = 0.0001f;
      std::vector<gmtl::Vec4f> quats;
      quats.push_back( gmtl::Vec4f( 6.28319, 2, 0, 0           ) );
      quats.push_back( gmtl::Vec4f( 5.93412, -0, -1, -0        ) );
      quats.push_back( gmtl::Vec4f( 5.58505, -0, -1, -0        ) );
      quats.push_back( gmtl::Vec4f( 5.23599, -0, -1, -0        ) );
      quats.push_back( gmtl::Vec4f( 4.88692, -0, -1, -0        ) );
      quats.push_back( gmtl::Vec4f( 4.53786, -0, -1, -0        ) );
      quats.push_back( gmtl::Vec4f( 4.18879, -0, -1, -0        ) );
      quats.push_back( gmtl::Vec4f( 3.83972, -0, -1, -0        ) );
      quats.push_back( gmtl::Vec4f( 3.49066, -0, -1, -0        ) );
      quats.push_back( gmtl::Vec4f( 3.14159, -0, -1, -0        ) );
      quats.push_back( gmtl::Vec4f( 2.79253, -0, -1, -0        ) );
      quats.push_back( gmtl::Vec4f( 2.44346, -0, -1, -0        ) );
      quats.push_back( gmtl::Vec4f( 2.0944, -0, -1, -0         ) );
      quats.push_back( gmtl::Vec4f( 1.74533, -0, -1, -0        ) );
      quats.push_back( gmtl::Vec4f( 1.39626, -0, -1, -0        ) );
      quats.push_back( gmtl::Vec4f( 1.0472, -0, -1, -0         ) );
      quats.push_back( gmtl::Vec4f( 0.698132, -0, -1, -0       ) );
      quats.push_back( gmtl::Vec4f( 0.349066, -0, -0.999999, -0 ) );
      quats.push_back( gmtl::Vec4f( 0, 0, 0, 0                 ) );
      quats.push_back( gmtl::Vec4f( 0.349066, 0, 0.999999, 0   ) );
      quats.push_back( gmtl::Vec4f( 0.698132, 0, 1, 0          ) );
      quats.push_back( gmtl::Vec4f( 1.0472, 0, 1, 0            ) );
      quats.push_back( gmtl::Vec4f( 1.39626, 0, 1, 0           ) );
      quats.push_back( gmtl::Vec4f( 1.74533, 0, 1, 0           ) );
      quats.push_back( gmtl::Vec4f( 2.0944, 0, 1, 0            ) );
      quats.push_back( gmtl::Vec4f( 2.44346, 0, 1, 0           ) );
      quats.push_back( gmtl::Vec4f( 2.79253, 0, 1, 0           ) );
      quats.push_back( gmtl::Vec4f( 3.14159, 0, 1, 0           ) );
      quats.push_back( gmtl::Vec4f( 3.49066, 0, 1, 0           ) );
      quats.push_back( gmtl::Vec4f( 3.83972, 0, 1, 0           ) );
      quats.push_back( gmtl::Vec4f( 4.18879, 0, 1, 0           ) );
      quats.push_back( gmtl::Vec4f( 4.53786, 0, 1, 0           ) );
      quats.push_back( gmtl::Vec4f( 4.88692, 0, 1, 0           ) );
      quats.push_back( gmtl::Vec4f( 5.23599, 0, 1, 0           ) );
      quats.push_back( gmtl::Vec4f( 5.58505, 0, 1, 0           ) );
      quats.push_back( gmtl::Vec4f( 5.93412, 0, 1, 0           ) );
      quats.push_back( gmtl::Vec4f( 6.28319, 2, 0, 0           ) );
      
      // @todo check this against another math lib other than VR Juggler...
      //   (all the vals above look sane, but... )
      float a, b, c, fg;
      gmtl::Quat<float> q2;
      int count = 0;
      for (int x = -360; x <= 360; x += 20)
      {
         gmtl::makeRot( q2, gmtl::Math::deg2Rad( float(x) ), 0.0f, 1.0f, 0.0f );
         gmtl::getRot( q2, fg, a, b, c );
         CPPUNIT_ASSERT( gmtl::isEqual( quats[count], gmtl::Vec4f( fg, a, b, c ), eps ) );
         ++count;
      }
   }
   
   void testQuatMakeGetMakeRot()
   {
      const float eps = 0.0001f;
      gmtl::Quat<float> q2, q3;
      float fg, a, b, c, fg1, a1, b1, c1;
      for (int x = -360; x <= 360; x += 20)
      {
         gmtl::makeRot( q2, gmtl::Math::deg2Rad( float(x) ), 0.0f, 1.0f, 0.0f );
         gmtl::getRot( q2, fg, a, b, c );
         gmtl::makeRot( q3, fg, a, b, c );
         gmtl::getRot( q3, fg1, a1, b1, c1 );
         CPPUNIT_ASSERT( gmtl::isEqual( q3, q2, eps ) );
         
         CPPUNIT_ASSERT( gmtl::Math::isEqual( fg1, fg, eps ) );
         CPPUNIT_ASSERT( gmtl::Math::isEqual( a1, a, eps ) );
         CPPUNIT_ASSERT( gmtl::Math::isEqual( b1, b, eps ) );
         CPPUNIT_ASSERT( gmtl::Math::isEqual( c1, c, eps ) );
      }
   }

   /** @todo implement quat makeRot Euler */
   static CppUnit::Test* suite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite( "GenerateTest" );
      test_suite->addTest( new CppUnit::TestCaller<GenerateTest>( "testMakeVecFromQuat", &GenerateTest::testMakeVecFromQuat ) );
      test_suite->addTest( new CppUnit::TestCaller<GenerateTest>( "testQuatMakePure", &GenerateTest::testQuatMakePure ) );
      test_suite->addTest( new CppUnit::TestCaller<GenerateTest>( "testQuatMakeConj", &GenerateTest::testQuatMakeConj ) );
      test_suite->addTest( new CppUnit::TestCaller<GenerateTest>( "testQuatMakeInvert", &GenerateTest::testQuatMakeInvert ) );
      test_suite->addTest( new CppUnit::TestCaller<GenerateTest>( "testQuatMakeRot", &GenerateTest::testQuatMakeRot ) );
      test_suite->addTest( new CppUnit::TestCaller<GenerateTest>( "testQuatGetRot", &GenerateTest::testQuatGetRot ) );
      test_suite->addTest( new CppUnit::TestCaller<GenerateTest>( "testQuatMakeGetMakeRot", &GenerateTest::testQuatMakeGetMakeRot ) );
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
