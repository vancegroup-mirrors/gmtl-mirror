/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: VecBaseTest.h,v $
 * Date modified: $Date: 2002-03-18 18:25:14 $
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

#include <gmtl/VecBase.h>

namespace gmtlTest
{

class VecBaseTest : public CppUnit::TestCase
{
public:
   VecBaseTest( std::string name = "VecBaseTest" )
   : CppUnit::TestCase (name)
   {;}

   virtual ~VecBaseTest()
   {}

   virtual void setUp()
   {;}

   virtual void tearDown()
   {
   }

   void testVecBaseCreation()
   {
      gmtl::VecBase<double, 3> vec;
      vec[0] = 0.0f; // use the var

      /*
      CPPUNIT_ASSERT( vec[0] == 0.0f);
      CPPUNIT_ASSERT( vec[1] == 0.0f);
      CPPUNIT_ASSERT( vec[2] == 0.0f);
      */

      // Test overhead of creation
      const long iters(400000);
      float use_value(0);
      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         gmtl::VecBase<float, 2> test_vec2;
         test_vec2[0] = 1.0f;
         gmtl::VecBase<float, 3> test_vec3;
         test_vec3[0] = 2.0f;
         gmtl::VecBase<float, 4> test_vec4;
         test_vec4[0] = 3.0f;

         use_value = use_value + test_vec2[0] + test_vec3[0] + test_vec4[0];
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("VecBaseTest/VecCreationOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT( use_value > 0.0f );
   }

   void testCopyConstruct()
   {
      gmtl::VecBase<double, 3> test_vec;

      test_vec[0] = 2.0f;
      test_vec[1] = 4.0f;
      test_vec[2] = 8.0f;

      gmtl::VecBase<double, 3> test_vec_copy(test_vec);

      CPPUNIT_ASSERT( test_vec_copy[0] == 2.0f);
      CPPUNIT_ASSERT( test_vec_copy[1] == 4.0f);
      CPPUNIT_ASSERT( test_vec_copy[2] == 8.0f);

      // Test copy construction overhead
      const long iters(400000);
      gmtl::VecBase<float, 2> test_vec2;
      test_vec2[0] = 2.0f;
      gmtl::VecBase<float, 3> test_vec3;
      test_vec2[0] = 3.0f;
      gmtl::VecBase<float, 4> test_vec4;
      test_vec2[0] = 4.0f;
      float use_value;     // A temp just here to use the objs so the copiler (hopefully) does not opt them out

      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         gmtl::VecBase<float, 2> test_vec2_copy(test_vec2);
         use_value += test_vec2_copy[0];
         gmtl::VecBase<float, 3> test_vec3_copy(test_vec3);
         use_value += test_vec3_copy[0];
         gmtl::VecBase<float, 4> test_vec4_copy(test_vec4);
         use_value += test_vec4_copy[0];
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("VecBaseTest/CopyConstructOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }


   void testConstructors()
   {
      gmtl::VecBase<float, 4> test_vec4(1.0f, 2.0f, 3.0f, 4.0f);
      CPPUNIT_ASSERT( test_vec4[0] == 1.0f);
      CPPUNIT_ASSERT( test_vec4[1] == 2.0f);
      CPPUNIT_ASSERT( test_vec4[2] == 3.0f);
      CPPUNIT_ASSERT( test_vec4[3] == 4.0f);

      gmtl::VecBase<float, 3> test_vec3(1.0f, 2.0f, 3.0f);
      CPPUNIT_ASSERT( test_vec3[0] == 1.0f);
      CPPUNIT_ASSERT( test_vec3[1] == 2.0f);
      CPPUNIT_ASSERT( test_vec3[2] == 3.0f);

      gmtl::VecBase<float, 2> test_vec2(1.0f, 2.0f);
      CPPUNIT_ASSERT( test_vec2[0] == 1.0f);
      CPPUNIT_ASSERT( test_vec2[1] == 2.0f);

      gmtl::VecBase<float, 1> test_vec1(1.0f);
      CPPUNIT_ASSERT( test_vec1[0] == 1.0f);

      // Test constructor
      const long iters(400000);
      float use_value(0.0f);     // A temp just here to use the objs so the copiler (hopefully) does not opt them out

      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         gmtl::VecBase<float, 4> test_vec4(1.0f, 2.0f, 3.0f, 4.0f);
         gmtl::VecBase<float, 3> test_vec3(1.0f, 2.0f, 3.0f);
         gmtl::VecBase<float, 2> test_vec2(1.0f, 2.0f);
         gmtl::VecBase<float, 1> test_vec1(1.0f);

         use_value = use_value + test_vec4[3] + test_vec3[2] + test_vec2[1] + test_vec1[0];
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("VecBaseTest/ConstructorsOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void testSet()
   {
      gmtl::VecBase<float, 4> test_vec4;
      test_vec4.set(1.0f, 2.0f, 3.0f, 4.0f);
      CPPUNIT_ASSERT( test_vec4[0] == 1.0f);
      CPPUNIT_ASSERT( test_vec4[1] == 2.0f);
      CPPUNIT_ASSERT( test_vec4[2] == 3.0f);
      CPPUNIT_ASSERT( test_vec4[3] == 4.0f);

      gmtl::VecBase<float, 3> test_vec3;
      test_vec3.set(1.0f, 2.0f, 3.0f);
      CPPUNIT_ASSERT( test_vec3[0] == 1.0f);
      CPPUNIT_ASSERT( test_vec3[1] == 2.0f);
      CPPUNIT_ASSERT( test_vec3[2] == 3.0f);

      gmtl::VecBase<float, 2> test_vec2;
      test_vec2.set(1.0f, 2.0f);
      CPPUNIT_ASSERT( test_vec2[0] == 1.0f);
      CPPUNIT_ASSERT( test_vec2[1] == 2.0f);

      gmtl::VecBase<float, 1> test_vec1;
      test_vec1.set(1.0f);
      CPPUNIT_ASSERT( test_vec1[0] == 1.0f);

      // Test constructor
      const float iters(400000);
      float use_value(0.0f);     // A temp just here to use the objs so the copiler (hopefully) does not opt them out

      CPPUNIT_METRIC_START_TIMING();

      for( float iter=0;iter<iters; ++iter)
      {
         test_vec4.set(iters+0, iters+1, iters+2, iters+3);
         test_vec3.set(iters+0, iters+1, iters+2);
         test_vec2.set(iters+0, iters+1);
         test_vec1.set(iters+0);

         use_value = use_value + test_vec4[3] + test_vec3[2] + test_vec2[1] + test_vec1[0];
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("VecBaseTest/SetOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT( use_value > 0.0f );
   }

   void testSetPtr()
   {
      float data[4] = {1.0f, 2.0f, 3.0f, 4.0f};

      gmtl::VecBase<float, 4> test_vec4;
      test_vec4.set(data);
      CPPUNIT_ASSERT( test_vec4[0] == 1.0f);
      CPPUNIT_ASSERT( test_vec4[1] == 2.0f);
      CPPUNIT_ASSERT( test_vec4[2] == 3.0f);
      CPPUNIT_ASSERT( test_vec4[3] == 4.0f);

      gmtl::VecBase<float, 3> test_vec3;
      test_vec3.set(data);
      CPPUNIT_ASSERT( test_vec3[0] == 1.0f);
      CPPUNIT_ASSERT( test_vec3[1] == 2.0f);
      CPPUNIT_ASSERT( test_vec3[2] == 3.0f);

      gmtl::VecBase<float, 2> test_vec2;
      test_vec2.set(data);
      CPPUNIT_ASSERT( test_vec2[0] == 1.0f);
      CPPUNIT_ASSERT( test_vec2[1] == 2.0f);

      gmtl::VecBase<float, 1> test_vec1;
      test_vec1.set(data);
      CPPUNIT_ASSERT( test_vec1[0] == 1.0f);

      // Test constructor
      const float iters(400000);
      float use_value(0.0f);     // A temp just here to use the objs so the copiler (hopefully) does not opt them out

      CPPUNIT_METRIC_START_TIMING();

      for( float iter=0;iter<iters; ++iter)
      {
         data[0] += 1.0f; data[1] += 2.0f; data[2] += 4.0f; data[3] += 8.0f;    // Just make sure data changes
         test_vec4.set(data);
         test_vec3.set(data);
         test_vec2.set(data);
         test_vec1.set(data);

         use_value = use_value + test_vec4[3] + test_vec3[2] + test_vec2[1] + test_vec1[0];
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("VecBaseTest/SetPtrOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      CPPUNIT_ASSERT( use_value > 0.0f );
   }


   void testGetData()
   {
      float* data;
      gmtl::VecBase<float, 4> test_vec4(1.0f, 2.0f, 3.0f, 4.0f);
      data = test_vec4.getData();
      CPPUNIT_ASSERT( data[0] == 1.0f);
      CPPUNIT_ASSERT( data[1] == 2.0f);
      CPPUNIT_ASSERT( data[2] == 3.0f);
      CPPUNIT_ASSERT( data[3] == 4.0f);

      gmtl::VecBase<float, 3> test_vec3(1.0f, 2.0f, 3.0f);
      data = test_vec3.getData();
      CPPUNIT_ASSERT( data[0] == 1.0f);
      CPPUNIT_ASSERT( data[1] == 2.0f);
      CPPUNIT_ASSERT( data[2] == 3.0f);

      gmtl::VecBase<float, 2> test_vec2(1.0f, 2.0f);
      data = test_vec2.getData();
      CPPUNIT_ASSERT( data[0] == 1.0f);
      CPPUNIT_ASSERT( data[1] == 2.0f);
   }

   static CppUnit::Test* suite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("VecBaseTest");
      test_suite->addTest( new CppUnit::TestCaller<VecBaseTest>("testVecBaseCreation", &VecBaseTest::testVecBaseCreation));
      test_suite->addTest( new CppUnit::TestCaller<VecBaseTest>("testCopyConstruct", &VecBaseTest::testCopyConstruct));
      test_suite->addTest( new CppUnit::TestCaller<VecBaseTest>("testConstructors", &VecBaseTest::testConstructors));
      test_suite->addTest( new CppUnit::TestCaller<VecBaseTest>("testSet", &VecBaseTest::testSet));
      test_suite->addTest( new CppUnit::TestCaller<VecBaseTest>("testSetPtr", &VecBaseTest::testSetPtr));
      test_suite->addTest( new CppUnit::TestCaller<VecBaseTest>("testGetData", &VecBaseTest::testGetData));

      return test_suite;
   }

   static CppUnit::Test* interactiveSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("InteractiveVecBaseTest");
      //test_suite->addTest( new CppUnit::TestCaller<ThreadTest>("interactiveCPUGrind", &ThreadTest::interactiveTestCPUGrind));
      return test_suite;
   }

protected:

};

};
