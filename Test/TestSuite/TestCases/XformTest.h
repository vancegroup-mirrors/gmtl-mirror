/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: XformTest.h,v $
 * Date modified: $Date: 2002-03-08 17:29:44 $
 * Version:       $Revision: 1.10 $
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

#include <gmtl/gmtlConfig.h>
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
         T bok = 88;
         std::string n = "XformTest/operator*(quat4,vec3)";
         n += name;
         gmtl::Quatf<T> q1( (T)1, (T)2, (T)3, (T)4 );
         gmtl::Vec<T, 3> v2;
         v2[0] = (T)1;
         const long iters(50000);
         CPPUNIT_METRIC_START_TIMING();
         bool result = false;
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
         CPPUNIT_ASSERT( v2[0] != 0.0 );
      }
   };

   void xformQuatVec3()
   {
      XformQuatVec3<float>::go( "f" );
      XformQuatVec3<double>::go( "d" );
      XformQuatVec3<short>::go( "s" );
      XformQuatVec3<int>::go( "i" );
      XformQuatVec3<long>::go( "l" );
   }   
   
   
   template <typename T, unsigned ROWS, unsigned COLS>
   class XformMatVecComplete
   {
   public:
      static void go( char* name )
      {
         char buf[20]; int rows( ROWS ), cols( COLS );
         std::string n = "XformTest/operator*(mat";
         sprintf( buf, "%d", rows ); n += buf;
         sprintf( buf, "%d", cols ); n += buf;
         n += ",vec";
         sprintf( buf, "%d", cols ); n += buf;
         n += ")";
         //n += name;
         gmtl::Matrix<T, ROWS, COLS> q1;
         gmtl::Vec<T, COLS> v2; // last component is 0.0 by definition
         v2[0] = (T)1;
         const long iters(50000);
         CPPUNIT_METRIC_START_TIMING();
         bool result = false;
         for (long iter = 0; iter < iters; ++iter)
         {
            v2 = q1 * v2;
         }
         CPPUNIT_METRIC_STOP_TIMING();
         CPPUNIT_ASSERT_METRIC_TIMING_LE( n.c_str(), iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
         CPPUNIT_ASSERT( v2[0] != 0.0 );
      }   
   };
   void xformMatVecComplete()
   {
      XformMatVecComplete<float, 2, 2>::go( "f" );
      XformMatVecComplete<double, 2, 2>::go( "d" );
      XformMatVecComplete<float, 2, 3>::go( "f" );
      XformMatVecComplete<double, 2, 3>::go( "d" );
      XformMatVecComplete<float, 3, 3>::go( "f" );
      XformMatVecComplete<double, 3, 3>::go( "d" );
      XformMatVecComplete<float, 3, 4>::go( "f" );
      XformMatVecComplete<double, 3, 4>::go( "d" );
      XformMatVecComplete<float, 4, 4>::go( "f" );
      XformMatVecComplete<double, 4, 4>::go( "d" );
      XformMatVecComplete<short, 4, 4>::go( "s" );
      XformMatVecComplete<int, 4, 4>::go( "i" );
      XformMatVecComplete<long, 4, 4>::go( "l" );
   }

   
   template <typename T, unsigned ROWS, unsigned COLS>
   class XformMatVecPartial
   {
   public:
      static void go( char* name )
      {
         char buf[20];
         std::string n = "XformTest/operator*(mat";
         sprintf( buf, "%d", ROWS ); n += buf;
         sprintf( buf, "%d", COLS ); n += buf;
         n += ",vec";
         sprintf( buf, "%d", COLS-1 ); n += buf;
         n += ")";
         n += name;
         gmtl::Matrix<T, ROWS, COLS> q1;
         gmtl::Vec<T, COLS-1> v2; 
         v2[0] = (T)1;
         const long iters(50000);
         CPPUNIT_METRIC_START_TIMING();
         bool result = false;
         for (long iter = 0; iter < iters; ++iter)
         {
            v2 = q1 * v2;
         }
         CPPUNIT_METRIC_STOP_TIMING();
         CPPUNIT_ASSERT_METRIC_TIMING_LE( n.c_str(), iters, 0.075f, 0.1f );  // warn at 7.5%, error at 10%
         CPPUNIT_ASSERT( v2[0] != 0.0 );
      }
   };
   void xformMatVecPartial() 
   {
      XformMatVecPartial<float, 2, 3>::go( "f" );
      XformMatVecPartial<double, 2, 3>::go( "d" );
      XformMatVecPartial<float, 3, 3>::go( "f" );
      XformMatVecPartial<double, 3, 3>::go( "d" );
      XformMatVecPartial<float, 3, 4>::go( "f" );
      XformMatVecPartial<double, 3, 4>::go( "d" );
      XformMatVecPartial<float, 4, 4>::go( "f" );
      XformMatVecPartial<double, 4, 4>::go( "d" );
      XformMatVecPartial<short, 4, 4>::go( "s" );
      XformMatVecPartial<int, 4, 4>::go( "i" );
      XformMatVecPartial<long, 4, 4>::go( "l" );
   }
   
   
   
   
   template <typename T, unsigned ROWS, unsigned COLS>
   class XformMatPointComplete
   {
   public:
      static void go( char* name )
      {
         char buf[20]; int rows( ROWS ), cols( COLS );
         std::string n = "XformTest/operator*(mat";
         sprintf( buf, "%d", rows ); n += buf;
         sprintf( buf, "%d", cols ); n += buf;
         n += ",pnt";
         sprintf( buf, "%d", cols ); n += buf;
         n += ")";
         n += name;
         gmtl::Matrix<T, ROWS, COLS> q1;
         gmtl::Point<T, COLS> v2; // last component is 1.0 by definition
         v2[0] = (T)1;
         const long iters(50000);
         CPPUNIT_METRIC_START_TIMING();
         bool result = false;
         for (long iter = 0; iter < iters; ++iter)
         {
            v2 = q1 * v2;
         }
         CPPUNIT_METRIC_STOP_TIMING();
         CPPUNIT_ASSERT_METRIC_TIMING_LE( n.c_str(), iters, 0.075f, 0.1f);  // warn at 7.5%, error at 10%
         CPPUNIT_ASSERT( v2[0] != 0.0 );
      }   
   };
   void xformMatPointComplete()
   {
      XformMatPointComplete<float, 2, 2>::go( "f" );
      XformMatPointComplete<double, 2, 2>::go( "d" );
      XformMatPointComplete<float, 2, 3>::go( "f" );
      XformMatPointComplete<double, 2, 3>::go( "d" );
      XformMatPointComplete<float, 3, 3>::go( "f" );
      XformMatPointComplete<double, 3, 3>::go( "d" );
      XformMatPointComplete<float, 3, 4>::go( "f" );
      XformMatPointComplete<double, 3, 4>::go( "d" );
      XformMatPointComplete<float, 4, 4>::go( "f" );
      XformMatPointComplete<double, 4, 4>::go( "d" );
      XformMatPointComplete<short, 4, 4>::go( "s" );
      XformMatPointComplete<int, 4, 4>::go( "i" );
      XformMatPointComplete<long, 4, 4>::go( "l" );
   }
   
   template <typename T, unsigned ROWS, unsigned COLS>
   class XformMatPointPartial
   {
   public:
      static void go( std::string name )
      {
         char buf[20];
         std::string n = "XformTest/operator*(mat";
         sprintf( buf, "%d", ROWS ); n += buf;
         sprintf( buf, "%d", COLS ); n += buf;
         n += ",vec";
         sprintf( buf, "%d", COLS-1 ); n += buf;
         n += ")";
         n += name;
         gmtl::Matrix<T, ROWS, COLS> q1;
         gmtl::Point<T, COLS-1> v2;
         v2[0] = (T)1;
         const long iters(50000);
         CPPUNIT_METRIC_START_TIMING();
         bool result = false;
         for (long iter = 0; iter < iters; ++iter)
         {
            v2 = q1 * v2;
         }
         CPPUNIT_METRIC_STOP_TIMING();
         CPPUNIT_ASSERT_METRIC_TIMING_LE( n.c_str(), iters, 0.075f, 0.1f );  // warn at 7.5%, error at 10%
         CPPUNIT_ASSERT( v2[0] != 0.0 );
      }
   };
   void xformMatPointPartial()
   {
      XformMatPointPartial<float, 2, 2>::go( "f" );
      XformMatPointPartial<double, 2, 2>::go( "d" );
      XformMatPointPartial<float, 2, 3>::go( "f" );
      XformMatPointPartial<double, 2, 3>::go( "d" );
      XformMatPointPartial<float, 3, 3>::go( "f" );
      XformMatPointPartial<double, 3, 3>::go( "d" );
      XformMatPointPartial<float, 3, 4>::go( "f" );
      XformMatPointPartial<double, 3, 4>::go( "d" );
      XformMatPointPartial<float, 4, 4>::go( "f" );
      XformMatPointPartial<double, 4, 4>::go( "d" );
      XformMatPointPartial<short, 4, 4>::go( "s" );
      XformMatPointPartial<int, 4, 4>::go( "i" );
      XformMatPointPartial<long, 4, 4>::go( "l" );
   }
   
   
   
   
   
   
   
   
   
   
   
   
   
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
   
   void testQuatVecXform()
   {
      // xform a vector by a quat.  verify the rotation worked...
      const float eps = 0.0001f;
      gmtl::Quat<float> q1, q2, q3, qident;
      gmtl::Vec<float, 3> vec( 0.0f, 0.0f, 1.0f ), res1, res2, res3, resi;
      gmtl::makeRot( q1, gmtl::Math::deg2Rad( 90.0f ), 0.0f, 1.0f, 0.0f );
      gmtl::makeRot( q2, gmtl::Math::deg2Rad( 90.0f ), 1.0f, 0.0f, 0.0f );
      gmtl::makeRot( q3, gmtl::Math::deg2Rad( 35.0f ), 1.0f, 1.0f, 0.0f );
      gmtl::xform( res1, q1, vec );
      gmtl::xform( res2, q2, vec );
      gmtl::xform( res3, q3, vec );
      gmtl::xform( resi, qident, vec );
      
      gmtl::Vec<float, 3> ex1( 1.0f, 0.0f, 0.0f );
      gmtl::Vec<float, 3> ex2( 0.0f, -1.0f, 0.0f );
      gmtl::Vec<float, 3> ex3( 0.286788f, -0.286788f, 0.864364f );

      CPPUNIT_ASSERT( gmtl::isEqual( ex1, res1, eps ) );
      CPPUNIT_ASSERT( gmtl::isEqual( ex2, res2, eps ) );
      CPPUNIT_ASSERT( gmtl::isEqual( ex3, res3, eps ) );
      CPPUNIT_ASSERT( gmtl::isEqual( vec, resi, eps ) );
      
      // operator* should be same
      gmtl::Vec<float, 3> res4, res5, res6;
      res4 = q1 * vec;
      res5 = q2 * vec;
      res6 = q3 * vec;
      resi = qident * vec;
      CPPUNIT_ASSERT( gmtl::isEqual( ex1, res4, eps ) );
      CPPUNIT_ASSERT( gmtl::isEqual( ex2, res5, eps ) );
      CPPUNIT_ASSERT( gmtl::isEqual( ex3, res6, eps ) );
      CPPUNIT_ASSERT( gmtl::isEqual( vec, resi, eps ) );
   }


   static CppUnit::Test* suite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("Vec3Test");
      //test_suite->addTest( new CppUnit::TestCaller<XformTest>("testVec4_Mat_Xform", &XformTest::testVec4_Mat_Xform));
      //test_suite->addTest( new CppUnit::TestCaller<XformTest>("testVec3_Mat_Xform", &XformTest::testVec3_Mat_Xform));
      //test_suite->addTest( new CppUnit::TestCaller<XformTest>("testPoint3_Mat_Xform", &XformTest::testPoint3_Mat_Xform));
      
      test_suite->addTest( new CppUnit::TestCaller<XformTest>("xformMatPointComplete", &XformTest::xformMatPointComplete));
      test_suite->addTest( new CppUnit::TestCaller<XformTest>("xformMatPointPartial", &XformTest::xformMatPointPartial));
      test_suite->addTest( new CppUnit::TestCaller<XformTest>("xformMatVecComplete", &XformTest::xformMatVecComplete));
      test_suite->addTest( new CppUnit::TestCaller<XformTest>("xformMatVecPartial", &XformTest::xformMatVecPartial));
      test_suite->addTest( new CppUnit::TestCaller<XformTest>("testQuatVecXform", &XformTest::testQuatVecXform));
      test_suite->addTest( new CppUnit::TestCaller<XformTest>("xformQuatVec3", &XformTest::xformQuatVec3));

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
