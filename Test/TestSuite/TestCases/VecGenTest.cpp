/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: VecGenTest.cpp,v $
 * Date modified: $Date: 2003-02-06 01:39:50 $
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
#include "VecGenTest.h"
#include "../Suites.h"
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/MetricRegistry.h>

#include <gmtl/Vec.h>
#include <gmtl/VecOps.h>
#include <gmtl/Quat.h>
#include <gmtl/QuatOps.h>
#include <gmtl/Generate.h>

namespace gmtlTest
{
   CPPUNIT_TEST_SUITE_REGISTRATION(VecGenTest);
   CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(VecGenMetricTest, Suites::metric());

   //-- vec tests --//

   void VecGenTest::testMakeVecFromQuat()
   {
      gmtl::Quat<float> quat( 0.0f,21.0f,31.0f,1234.0f );
      gmtl::Vec<float, 3> vec( gmtl::makeVec( quat ) );
      CPPUNIT_ASSERT( vec[0] == 0.0f );
      CPPUNIT_ASSERT( vec[1] == 21.0f );
      CPPUNIT_ASSERT( vec[2] == 31.0f );
   }
   
   void VecGenTest::testMakeNormalVecFromVec()
   {
      {
         const float eps = 0.001f;
         const gmtl::Vec<float, 3> vec( 0.1f, 0.0f, 0.0f ), expected( 1, 0, 0 );
         gmtl::Vec<float, 3> result( gmtl::makeNormal( vec ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result, eps ) );
      }
      
      {
         const float eps = 0.001f;
         const gmtl::Vec<float, 3> vec( 0.1f, 128943139.0f, 0.0f ), expected( 0, 1, 0 );
         gmtl::Vec<float, 3> result( gmtl::makeNormal( vec ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result, eps ) );
      }
      
      {
         const float eps = 0.001f;
         const gmtl::Vec<float, 3> vec( 0.0f, 0.0f, 0.001f ), expected( 0, 0, 1 );
         gmtl::Vec<float, 3> result( gmtl::makeNormal( vec ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result, eps ) );
      }
   }
   
   
   
   //-- timing tests --//
   
   
   void VecGenMetricTest::testGenTimingMakeNormalVec1()
   {
      gmtl::Vec<double, 4> vec4d;
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         vec4d = gmtl::makeNormal( vec4d );
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE( "VecGenTest/makeNormal(vec4d)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // force intelligent compilers to do all the iterations (ie. to not optimize them out), 
      // by using the variables computed...
      CPPUNIT_ASSERT( vec4d[0] != 10000.0f && vec4d[1] != 10000.0f && vec4d[2] != 10000.0f );
   }
   
   void VecGenMetricTest::testGenTimingMakeNormalVec2()
   {
      gmtl::Vec<float, 4> vec4f;
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         vec4f = gmtl::makeNormal( vec4f );
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE( "VecGenTest/makeNormal(vec4f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   
      // force intelligent compilers to do all the iterations (ie. to not optimize them out), 
      // by using the variables computed...
      CPPUNIT_ASSERT( vec4f[0] != 10000.0f && vec4f[1] != 10000.0f && vec4f[2] != 10000.0f );
   }
   void VecGenMetricTest::testGenTimingMakeNormalVec3()
   {
      gmtl::Vec<double, 3> vec3d;
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         vec3d = gmtl::makeNormal( vec3d );
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE( "VecGenTest/makeNormal(vec3d)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      // force intelligent compilers to do all the iterations (ie. to not optimize them out), 
      // by using the variables computed...
      CPPUNIT_ASSERT( vec3d[0] != 10000.0f && vec3d[1] != 10000.0f && vec3d[2] != 10000.0f );
   }
   
   void VecGenMetricTest::testGenTimingMakeNormalVec4()
   {
      gmtl::Vec<float, 3> vec3f;
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         vec3f = gmtl::makeNormal( vec3f );
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE( "VecGenTest/makeNormal(vec3f)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   
      
      // force intelligent compilers to do all the iterations (ie. to not optimize them out), 
      // by using the variables computed...
      CPPUNIT_ASSERT( vec3f[0] != 10000.0f && vec3f[1] != 10000.0f && vec3f[2] != 10000.0f );
   }
   
   void VecGenMetricTest::testGenTimingMakeVec()
   {
      gmtl::Quat<double> q1;
      gmtl::Vec<double, 3> v1;
      const long iters(25000);
      CPPUNIT_METRIC_START_TIMING();
      
      for (long iter = 0; iter < iters; ++iter)
      {
         v1 = gmtl::makeVec( q1 );
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE( "VecGenTest/makeVec(quatd)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

      gmtl::Quat<float> q2;
      gmtl::Vec<float, 3> v2;
      CPPUNIT_METRIC_START_TIMING();
      for (long iter = 0; iter < iters; ++iter)
      {
         v2 = gmtl::makeVec( q2 );
      }
      CPPUNIT_METRIC_STOP_TIMING();
      CPPUNIT_ASSERT_METRIC_TIMING_LE( "VecGenTest/makeVec(quatf)", iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
   
      // force intelligent compilers to do all the iterations (ie. to not optimize them out), 
      // by using the variables computed...
      CPPUNIT_ASSERT( v2[0] != 10000.0f );
      CPPUNIT_ASSERT( v1[0] != 10000.0f );
   }
}
