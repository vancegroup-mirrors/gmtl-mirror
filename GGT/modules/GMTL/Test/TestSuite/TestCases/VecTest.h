/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: VecTest.h,v $
 * Date modified: $Date: 2002-02-11 18:56:00 $
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

#include <gmtl/Vec.h>
#include <gmtl/Compare.h>

namespace gmtlTest
{

class VecTest : public CppUnit::TestCase
{
public:
   VecTest( std::string name = "VecTest" )
   : TestCase (name)
   {;}

   virtual ~VecTest()
   {}

   virtual void setUp()
   {;}

   virtual void tearDown()
   {
   }

   void testCreation()
   {
      gmtl::Vec<double, 3> vec;

      CPPUNIT_ASSERT( vec[0] == 0.0f);
      CPPUNIT_ASSERT( vec[1] == 0.0f);
      CPPUNIT_ASSERT( vec[2] == 0.0f);

      // Test overhead of creation
      const long iters(400000);
      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         gmtl::Vec<float, 2> test_vec2;
         test_vec2[0] = 1.0f;
         gmtl::Vec<float, 3> test_vec3;
         test_vec3[0] = 2.0f;
         gmtl::Vec<float, 4> test_vec4;
         test_vec4[0] = 3.0f;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("VecTest/VecCreationOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void testCopyConstruct()
   {
      gmtl::Vec<double, 3> test_vec;

      test_vec[0] = 2.0f;
      test_vec[1] = 4.0f;
      test_vec[2] = 8.0f;

      gmtl::Vec<double, 3> test_vec_copy(test_vec);

      CPPUNIT_ASSERT( test_vec_copy[0] == 2.0f);
      CPPUNIT_ASSERT( test_vec_copy[1] == 4.0f);
      CPPUNIT_ASSERT( test_vec_copy[2] == 8.0f);

      // Test copy construction overhead
      const long iters(400000);
      gmtl::Vec<float, 2> test_vec2;
      test_vec2[0] = 2.0f;
      gmtl::Vec<float, 3> test_vec3;
      test_vec2[0] = 3.0f;
      gmtl::Vec<float, 4> test_vec4;
      test_vec2[0] = 4.0f;
      float use_value;     // A temp just here to use the objs so the copiler (hopefully) does not opt them out

      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         gmtl::Vec<float, 2> test_vec2_copy(test_vec2);
         use_value += test_vec2_copy[0];
         gmtl::Vec<float, 3> test_vec3_copy(test_vec3);
         use_value += test_vec3_copy[0];
         gmtl::Vec<float, 4> test_vec4_copy(test_vec4);
         use_value += test_vec4_copy[0];
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("VecTest/CopyConstructOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }


   void testConstructors()
   {
      gmtl::Vec<float, 4> test_vec4(1.0f, 2.0f, 3.0f, 4.0f);
      CPPUNIT_ASSERT( test_vec4[0] == 1.0f);
      CPPUNIT_ASSERT( test_vec4[1] == 2.0f);
      CPPUNIT_ASSERT( test_vec4[2] == 3.0f);
      CPPUNIT_ASSERT( test_vec4[3] == 4.0f);

      gmtl::Vec<float, 3> test_vec3(1.0f, 2.0f, 3.0f);
      CPPUNIT_ASSERT( test_vec3[0] == 1.0f);
      CPPUNIT_ASSERT( test_vec3[1] == 2.0f);
      CPPUNIT_ASSERT( test_vec3[2] == 3.0f);

      gmtl::Vec<float, 2> test_vec2(1.0f, 2.0f);
      CPPUNIT_ASSERT( test_vec2[0] == 1.0f);
      CPPUNIT_ASSERT( test_vec2[1] == 2.0f);

      gmtl::Vec<float, 1> test_vec1(1.0f);
      CPPUNIT_ASSERT( test_vec1[0] == 1.0f);

      // Test constructor
      const long iters(400000);
      float use_value(0.0f);     // A temp just here to use the objs so the copiler (hopefully) does not opt them out

      CPPUNIT_METRIC_START_TIMING();

      for( long iter=0;iter<iters; ++iter)
      {
         gmtl::Vec<float, 4> test_vec4(1.0f, 2.0f, 3.0f, 4.0f);
         gmtl::Vec<float, 3> test_vec3(1.0f, 2.0f, 3.0f);
         gmtl::Vec<float, 2> test_vec2(1.0f, 2.0f);
         gmtl::Vec<float, 1> test_vec1(1.0f);

         use_value = use_value + test_vec4[3] + test_vec3[2] + test_vec2[1] + test_vec1[0];
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("VecTest/ConstructorsOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void testSet()
   {
      gmtl::Vec<float, 4> test_vec4;
      test_vec4.set(1.0f, 2.0f, 3.0f, 4.0f);
      CPPUNIT_ASSERT( test_vec4[0] == 1.0f);
      CPPUNIT_ASSERT( test_vec4[1] == 2.0f);
      CPPUNIT_ASSERT( test_vec4[2] == 3.0f);
      CPPUNIT_ASSERT( test_vec4[3] == 4.0f);

      gmtl::Vec<float, 3> test_vec3;
      test_vec3.set(1.0f, 2.0f, 3.0f);
      CPPUNIT_ASSERT( test_vec3[0] == 1.0f);
      CPPUNIT_ASSERT( test_vec3[1] == 2.0f);
      CPPUNIT_ASSERT( test_vec3[2] == 3.0f);

      gmtl::Vec<float, 2> test_vec2;
      test_vec2.set(1.0f, 2.0f);
      CPPUNIT_ASSERT( test_vec2[0] == 1.0f);
      CPPUNIT_ASSERT( test_vec2[1] == 2.0f);

      gmtl::Vec<float, 1> test_vec1;
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
      CPPUNIT_ASSERT_METRIC_TIMING_LE("VecTest/SetOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }

   void testSetPtr()
   {
      float data[4] = {1.0f, 2.0f, 3.0f, 4.0f};

      gmtl::Vec<float, 4> test_vec4;
      test_vec4.set(data);
      CPPUNIT_ASSERT( test_vec4[0] == 1.0f);
      CPPUNIT_ASSERT( test_vec4[1] == 2.0f);
      CPPUNIT_ASSERT( test_vec4[2] == 3.0f);
      CPPUNIT_ASSERT( test_vec4[3] == 4.0f);

      gmtl::Vec<float, 3> test_vec3;
      test_vec3.set(data);
      CPPUNIT_ASSERT( test_vec3[0] == 1.0f);
      CPPUNIT_ASSERT( test_vec3[1] == 2.0f);
      CPPUNIT_ASSERT( test_vec3[2] == 3.0f);

      gmtl::Vec<float, 2> test_vec2;
      test_vec2.set(data);
      CPPUNIT_ASSERT( test_vec2[0] == 1.0f);
      CPPUNIT_ASSERT( test_vec2[1] == 2.0f);

      gmtl::Vec<float, 1> test_vec1;
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
      CPPUNIT_ASSERT_METRIC_TIMING_LE("VecTest/SetPtrOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   }


   void testGetData()
   {
      float* data;
      gmtl::Vec<float, 4> test_vec4(1.0f, 2.0f, 3.0f, 4.0f);
      data = test_vec4.getData();
      CPPUNIT_ASSERT( data[0] == 1.0f);
      CPPUNIT_ASSERT( data[1] == 2.0f);
      CPPUNIT_ASSERT( data[2] == 3.0f);
      CPPUNIT_ASSERT( data[3] == 4.0f);

      gmtl::Vec<float, 3> test_vec3(1.0f, 2.0f, 3.0f);
      data = test_vec3.getData();
      CPPUNIT_ASSERT( data[0] == 1.0f);
      CPPUNIT_ASSERT( data[1] == 2.0f);
      CPPUNIT_ASSERT( data[2] == 3.0f);

      gmtl::Vec<float, 2> test_vec2(1.0f, 2.0f);
      data = test_vec2.getData();
      CPPUNIT_ASSERT( data[0] == 1.0f);
      CPPUNIT_ASSERT( data[1] == 2.0f);
   }


   // -- Test comparison -- //
   void testEqualityCompare()
   {
      gmtl::Vec<float, 4> test_vec1(1.0f, 2.0f, 3.0f, 4.0f);
      gmtl::Vec<float, 4> test_vec2(test_vec1);

      CPPUNIT_ASSERT( test_vec1 == test_vec2);
      CPPUNIT_ASSERT(! (test_vec1 != test_vec2));

      test_vec2 = test_vec1;     // Set equal, vary elt 0
      test_vec2[0] = 21.10f;
      CPPUNIT_ASSERT( test_vec1 != test_vec2);
      CPPUNIT_ASSERT(! (test_vec1 == test_vec2));

      test_vec2 = test_vec1;     // Set equal, vary elt 0
      test_vec2[1] = 21.10f;
      CPPUNIT_ASSERT( test_vec1 != test_vec2);
      CPPUNIT_ASSERT(! (test_vec1 == test_vec2));

      test_vec2 = test_vec1;     // Set equal, vary elt 0
      test_vec2[2] = 21.10f;
      CPPUNIT_ASSERT( test_vec1 != test_vec2);
      CPPUNIT_ASSERT(! (test_vec1 == test_vec2));

      test_vec2 = test_vec1;     // Set equal, vary elt 0
      test_vec2[3] = 21.10f;
      CPPUNIT_ASSERT( test_vec1 != test_vec2);
      CPPUNIT_ASSERT(! (test_vec1 == test_vec2));

      // Test comparison performance
      // Test constructor
      const float iters(400000);
      unsigned true_count(0);
      unsigned false_count(0);
      
      // -- Equality
      CPPUNIT_METRIC_START_TIMING();
      test_vec1.set(0.0f, 0.0f, 0.0f, 2000.0f);
      test_vec2.set(0.0f, 0.0f, 0.0f, 1000.0f);
      
      for( float iter=0;iter<iters; ++iter)
      {
         test_vec1[3] += 1.0f;
         test_vec2[3] += 2.0f;
         if(test_vec1 == test_vec2)
            true_count++;         
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("VecTest/EqualityCompareOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // -- Inequality
      CPPUNIT_METRIC_START_TIMING();
      test_vec1.set(0.0f, 0.0f, 0.0f, 2000.0f);
      test_vec2.set(0.0f, 0.0f, 0.0f, 1000.0f);
      
      for( float iter=0;iter<iters; ++iter)
      {
         test_vec1[3] += 1.0f;
         test_vec2[3] += 2.0f;
         if(test_vec1 != test_vec2)
            false_count++;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("VecTest/InequalityCompareOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

   }

   // -- Test comparison -- //
   void testIsEqual()
   {
      gmtl::Vec<float, 4> test_vec1(1.0f, 2.0f, 3.0f, 4.0f);
      gmtl::Vec<float, 4> test_vec2(test_vec1);
      float eps(0.0f);

      for(eps=0.0f;eps<10.0f;eps += 0.05f)
      {
         CPPUNIT_ASSERT( gmtl::isEqual(test_vec1, test_vec2, eps) );                     
      }

      test_vec1.set(1.0f, 1.0f, 1.0f, 1.0f);
      for(unsigned elt=0; elt<4; elt++)
      {
         test_vec2 = test_vec1;     // Set equal, vary elt 0
         test_vec2[elt] = 21.0f;
         CPPUNIT_ASSERT( !gmtl::isEqual(test_vec1, test_vec2, 10.0f) );
         CPPUNIT_ASSERT( !gmtl::isEqual(test_vec1, test_vec2, 19.9f) );
         CPPUNIT_ASSERT( gmtl::isEqual(test_vec1, test_vec2, 20.1f) );
         CPPUNIT_ASSERT( gmtl::isEqual(test_vec1, test_vec2, 22.0f) );
      }

      // Test comparison performance
      // Test constructor
      const float iters(400000);
      unsigned true_count(0);
      unsigned false_count(0);
      
      // -- Equality
      CPPUNIT_METRIC_START_TIMING();
      test_vec1.set(0.0f, 0.0f, 0.0f, 2000.0f);
      test_vec2.set(0.0f, 0.0f, 0.0f, 1000.0f);
      
      for( float iter=0;iter<iters; ++iter)
      {
         test_vec1[3] += 1.0f;
         test_vec2[3] += 2.0f;
         if(gmtl::isEqual(test_vec1, test_vec2, 1.0f) )
            true_count++;
         if(gmtl::isEqual(test_vec1, test_vec2, 0.1f) )
            true_count++;
         if(gmtl::isEqual(test_vec1, test_vec2, 100000.0f) )
            true_count++;
      }

      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE("VecTest/isEqualOverhead", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
      
   }


   static Test* suite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("VecTest");
      test_suite->addTest( new CppUnit::TestCaller<VecTest>("testCreation", &VecTest::testCreation));
      test_suite->addTest( new CppUnit::TestCaller<VecTest>("testCopyConstruct", &VecTest::testCopyConstruct));
      test_suite->addTest( new CppUnit::TestCaller<VecTest>("testConstructors", &VecTest::testConstructors));
      test_suite->addTest( new CppUnit::TestCaller<VecTest>("testSet", &VecTest::testSet));
      test_suite->addTest( new CppUnit::TestCaller<VecTest>("testSetPtr", &VecTest::testSetPtr));
      test_suite->addTest( new CppUnit::TestCaller<VecTest>("testGetData", &VecTest::testGetData));
      test_suite->addTest( new CppUnit::TestCaller<VecTest>("testEqualityCompare", &VecTest::testEqualityCompare));
      test_suite->addTest( new CppUnit::TestCaller<VecTest>("testIsEqual", &VecTest::testIsEqual));
      
      return test_suite;
   }

   static Test* interactiveSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("InteractiveVecTest");
      //test_suite->addTest( new CppUnit::TestCaller<ThreadTest>("interactiveCPUGrind", &ThreadTest::interactiveTestCPUGrind));
      return test_suite;
   }

protected:

};

};
