/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: XformTest.h,v $
 * Date modified: $Date: 2002-05-20 22:39:23 $
 * Version:       $Revision: 1.23 $
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
#include <iostream>
#include <stdio.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/extensions/MetricRegistry.h>

#include <gmtl/Xforms.h>
//#include <gmtl/gmtlOutput.h>

namespace gmtlTest
{

class XformTest : public CppUnit::TestCase
{
public:
   XformTest( std::string name = "XformTest")
   : CppUnit::TestCase (name)
   {;}

   virtual ~XformTest()
   {}

   virtual void setUp()
   {;}

   virtual void tearDown()
   {
   }

   template <typename T>
   class XformQuatVec3
   {
   public:
      static void go( char* name )
      {
         std::string n = "XformTest/operator*(quat4,vec3)";
         n += name;
         gmtl::Quat<T> q1( gmtl::makeNormal( gmtl::Quat<T>( (T)1, (T)2, (T)3, (T)4 ) ) );
         gmtl::Vec<T, 3> v2;
         v2[0] = (T)1;
         const long iters(25000);
         CPPUNIT_METRIC_START_TIMING();
         for (long iter = 0; iter < iters; ++iter)
         {
            v2 = q1 * v2;
         }
         CPPUNIT_METRIC_STOP_TIMING();
         CPPUNIT_ASSERT_METRIC_TIMING_LE( n.c_str(), iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

         n = "XformTest/xform(vec,quat4,vec3)";
         n += name;
         CPPUNIT_METRIC_START_TIMING();
         for (long iter = 0; iter < iters; ++iter)
         {
            gmtl::xform( v2, q1, v2 );
         }
         CPPUNIT_METRIC_STOP_TIMING();
         CPPUNIT_ASSERT_METRIC_TIMING_LE( n.c_str(), iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
         CPPUNIT_ASSERT( v2[0] != 13.045 );
      }
   };

   void testTimingXformQuatVec3();


// mips pro and VC7 can't handle template template params
#ifdef __GNUC__
   /** @todo Get XformMatByVecType to work outside gcc */
   template <
         template <typename, unsigned> class VEC_TYPE,
         typename T,
         unsigned VEC_SIZE,
         unsigned ROWS,
         unsigned COLS
   >
   class XformMatByVecType
   {
   public:
      static void go( char* vectype  )
      {
         char buf[20]; int rows( ROWS ), cols( COLS ), vecsize( VEC_SIZE );
         std::string n = "XformTest/operator*(mat";
         sprintf( buf, "%d", rows ); n += buf;
         sprintf( buf, "%d", cols ); n += buf;
         n += ",";
         n += vectype;
         sprintf( buf, "%d", vecsize ); n += buf;
         n += ")";
         n += typeid( T ).name();
         gmtl::Matrix<T, ROWS, COLS> q1;
         VEC_TYPE<T, VEC_SIZE> v2;
         const long iters(25000);
         CPPUNIT_METRIC_START_TIMING();
         for (long iter = 0; iter < iters; ++iter)
         {
            v2 = q1 * v2;
         }
         CPPUNIT_METRIC_STOP_TIMING();
         CPPUNIT_ASSERT_METRIC_TIMING_LE( n.c_str(), iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

         n = "XformTest/xform(";
         n += vectype;
         sprintf( buf, "%d", vecsize ); n += buf;
         n += ",mat";
         sprintf( buf, "%d", rows ); n += buf;
         sprintf( buf, "%d", cols ); n += buf;
         n += ",";
         n += vectype;
         sprintf( buf, "%d", vecsize ); n += buf;
         n += ")";
         n += typeid( T ).name();
         CPPUNIT_METRIC_START_TIMING();
         for (long iter = 0; iter < iters; ++iter)
         {
            gmtl::xform( v2, q1, v2 );
         }
         CPPUNIT_METRIC_STOP_TIMING();
         CPPUNIT_ASSERT_METRIC_TIMING_LE( n.c_str(), iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%

         CPPUNIT_ASSERT( v2[0] != 1.0 );
      }
   };
#endif // __GNUC__

   void testTimingXformMatVecComplete();
   void testTimingXformMatVecPartial();
   void testTimingXformMatPointComplete();
   void testTimingXformMatPointPartial();


   ///  old tests....

   /*
   void testVec4_Mat_Xform()
   {
      gmtl::Vec4  v1, v1_trans, v1_trans_ans;
      v1.set(1.1,-2.2,3.3,1.0);
      gmtl::Matrix rot_mat;
      rot_mat.makeXYZEuler(20.0f, -30.0f, 40.0f);
      v1_trans_ans.set(0.30443, -2.28262, 3.41130, 1.0);
      v1_trans = rot_mat * v1;

      CPPUNIT_ASSERT(v1_trans.equal(v1_trans_ans,0.0001));

   }

   void testVec3_Mat_Xform()
   {
      // Vector, so translation should not affect it

      gmtl::Vec3  v1, v1_xform, v1_xform_ans;
      v1.set(1.1,-2.2,3.3);
      gmtl::Matrix xform_mat;
      xform_mat.makeXYZEuler(20.0f, -30.0f, 40.0f);
      xform_mat.setTrans(10.0, 1.0, -13.0f);
      //std::cout << "xform_mat: " << xform_mat << std::endl;

      v1_xform_ans.set(0.30443, -2.28262, 3.41130);
      v1_xform = xform_mat * v1;

      CPPUNIT_ASSERT(v1_xform.equal(v1_xform_ans,0.0001));
   }

   void testPoint3_Mat_Xform()
   {
      // Vector, so translation should not affect it

      gmtl::Point3  p1, p1_xform, p1_xform_ans;
      p1.set(1.1,-2.2,3.3);
      gmtl::Matrix xform_mat;
      xform_mat.makeXYZEuler(20.0f, -30.0f, 40.0f);
      xform_mat.setTrans(10.0, 1.0, -13.0f);
      //std::cout << "p1: " << p1 << std::endl;
      //std::cout << "xform_mat: " << xform_mat << std::endl;

      p1_xform_ans.set(10.30443, -1.28262, -9.5887);
      p1_xform = xform_mat * p1;
      //std::cout << "point_p1_xform: " << p1_xform << std::endl;

      CPPUNIT_ASSERT(p1_xform.equal(p1_xform_ans,0.0001));
   }
   */

   void output( gmtl::Quat<float> q )
   {
      std::cout<<q[0]<<" "<<q[1]<<" "<<q[2]<<" "<<q[3]<<std::endl;
   }

   void output( gmtl::Vec<float, 3> q )
   {
      std::cout<<q[0]<<" "<<q[1]<<" "<<q[2]<<std::endl;
   }

   void testQuatVecXform();
   void weird_XformQuatVec_InvConj_SanityCheck();
   void testMatVecXform();
   void testMatPointXform();

   static CppUnit::Test* suite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("Vec3Test");
      //test_suite->addTest( new CppUnit::TestCaller<XformTest>("testVec4_Mat_Xform", &XformTest::testVec4_Mat_Xform));
      //test_suite->addTest( new CppUnit::TestCaller<XformTest>("testVec3_Mat_Xform", &XformTest::testVec3_Mat_Xform));
      //test_suite->addTest( new CppUnit::TestCaller<XformTest>("testPoint3_Mat_Xform", &XformTest::testPoint3_Mat_Xform));

      test_suite->addTest( new CppUnit::TestCaller<XformTest>("testTimingXformQuatVec3", &XformTest::testTimingXformQuatVec3));
      test_suite->addTest( new CppUnit::TestCaller<XformTest>("testTimingXformMatPointComplete", &XformTest::testTimingXformMatPointComplete));
      test_suite->addTest( new CppUnit::TestCaller<XformTest>("testTimingXformMatPointPartial", &XformTest::testTimingXformMatPointPartial));
      test_suite->addTest( new CppUnit::TestCaller<XformTest>("testTimingXformMatVecComplete", &XformTest::testTimingXformMatVecComplete));
      test_suite->addTest( new CppUnit::TestCaller<XformTest>("testTimingXformMatVecPartial", &XformTest::testTimingXformMatVecPartial));


      test_suite->addTest( new CppUnit::TestCaller<XformTest>("testQuatVecXform", &XformTest::testQuatVecXform));
      test_suite->addTest( new CppUnit::TestCaller<XformTest>("weird_XformQuatVec_InvConj_SanityCheck", &XformTest::weird_XformQuatVec_InvConj_SanityCheck));
      test_suite->addTest( new CppUnit::TestCaller<XformTest>("testMatVecXform", &XformTest::testMatVecXform));
      test_suite->addTest( new CppUnit::TestCaller<XformTest>("testMatPointXform", &XformTest::testMatPointXform));

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
