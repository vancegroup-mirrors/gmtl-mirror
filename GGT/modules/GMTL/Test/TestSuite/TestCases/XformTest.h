/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: XformTest.h,v $
 * Date modified: $Date: 2002-03-09 23:34:59 $
 * Version:       $Revision: 1.14 $
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
         CPPUNIT_ASSERT( v2[0] != 13.045 );
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
         const long iters(50000);
         CPPUNIT_METRIC_START_TIMING();
         bool result = false;
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
   void xformMatVecComplete()
   {
      XformMatByVecType<gmtl::Vec, float, 2, 2, 2>::go( "vec" );
      XformMatByVecType<gmtl::Vec, float, 3, 2, 3>::go( "vec" );
      XformMatByVecType<gmtl::Vec, float, 3, 3, 3>::go( "vec" );
      XformMatByVecType<gmtl::Vec, float, 4, 3, 4>::go( "vec" );
      XformMatByVecType<gmtl::Vec, float, 4, 4, 4>::go( "vec" );

      XformMatByVecType<gmtl::Vec, double, 2, 2, 2>::go( "vec" );
      XformMatByVecType<gmtl::Vec, double, 3, 2, 3>::go( "vec" );
      XformMatByVecType<gmtl::Vec, double, 3, 3, 3>::go( "vec" );
      XformMatByVecType<gmtl::Vec, double, 4, 3, 4>::go( "vec" );
      XformMatByVecType<gmtl::Vec, double, 4, 4, 4>::go( "vec" );
      
      XformMatByVecType<gmtl::Vec, short, 4, 4, 4>::go( "vec" );
      XformMatByVecType<gmtl::Vec, int, 4, 4, 4>::go( "vec" );
      XformMatByVecType<gmtl::Vec, long, 4, 4, 4>::go( "vec" );
   }

   void xformMatVecPartial() 
   {
      XformMatByVecType<gmtl::Vec, float, 2, 2, 3>::go( "vec" );
      XformMatByVecType<gmtl::Vec, float, 2, 3, 3>::go( "vec" );
      XformMatByVecType<gmtl::Vec, float, 3, 3, 4>::go( "vec" );
      XformMatByVecType<gmtl::Vec, float, 3, 4, 4>::go( "vec" );

      XformMatByVecType<gmtl::Vec, double, 2, 2, 3>::go( "vec" );
      XformMatByVecType<gmtl::Vec, double, 2, 3, 3>::go( "vec" );
      XformMatByVecType<gmtl::Vec, double, 3, 3, 4>::go( "vec" );
      XformMatByVecType<gmtl::Vec, double, 3, 4, 4>::go( "vec" );

      XformMatByVecType<gmtl::Vec, short, 3, 4, 4>::go( "vec" );
      XformMatByVecType<gmtl::Vec, int, 3, 4, 4>::go( "vec" );
      XformMatByVecType<gmtl::Vec, long, 3, 4, 4>::go( "vec" );
   }
   void xformMatPointComplete()
   {
      XformMatByVecType<gmtl::Point, float, 2, 2, 2>::go( "pnt" );
      XformMatByVecType<gmtl::Point, float, 3, 2, 3>::go( "pnt" );
      XformMatByVecType<gmtl::Point, float, 3, 3, 3>::go( "pnt" );
      XformMatByVecType<gmtl::Point, float, 4, 3, 4>::go( "pnt" );
      XformMatByVecType<gmtl::Point, float, 4, 4, 4>::go( "pnt" );
      
      XformMatByVecType<gmtl::Point, double, 2, 2, 2>::go( "pnt" );
      XformMatByVecType<gmtl::Point, double, 3, 2, 3>::go( "pnt" );
      XformMatByVecType<gmtl::Point, double, 3, 3, 3>::go( "pnt" );
      XformMatByVecType<gmtl::Point, double, 4, 3, 4>::go( "pnt" );
      XformMatByVecType<gmtl::Point, double, 4, 4, 4>::go( "pnt" );
      
      XformMatByVecType<gmtl::Point, short, 4, 4, 4>::go( "pnt" );
      XformMatByVecType<gmtl::Point, int, 4, 4, 4>::go( "pnt" );
      XformMatByVecType<gmtl::Point, long, 4, 4, 4>::go( "pnt" );
   }
   void xformMatPointPartial()
   {
      XformMatByVecType<gmtl::Point, float, 2, 2, 3>::go( "pnt" );
      XformMatByVecType<gmtl::Point, float, 2, 3, 3>::go( "pnt" );
      XformMatByVecType<gmtl::Point, float, 3, 3, 4>::go( "pnt" );
      XformMatByVecType<gmtl::Point, float, 3, 4, 4>::go( "pnt" );
      
      XformMatByVecType<gmtl::Point, double, 2, 2, 3>::go( "pnt" );
      XformMatByVecType<gmtl::Point, double, 2, 3, 3>::go( "pnt" );
      XformMatByVecType<gmtl::Point, double, 3, 3, 4>::go( "pnt" );
      XformMatByVecType<gmtl::Point, double, 3, 4, 4>::go( "pnt" );
      
      XformMatByVecType<gmtl::Point, short, 3, 4, 4>::go( "pnt" );
      XformMatByVecType<gmtl::Point, int, 3, 4, 4>::go( "pnt" );
      XformMatByVecType<gmtl::Point, long, 3, 4, 4>::go( "pnt" );
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
      {
         // xform() vector quat.  verify xform works...
         const float eps = 0.0001f;
         gmtl::Quat<float> q1, q2, q3, qident;
         gmtl::Vec<float, 3> vec( 0.0f, 0.0f, 1.0f ), res1, res2, res3, res4, resi, vec2( 2.0f, 5.0f, 10.0f );
         gmtl::makeRot( q1, gmtl::Math::deg2Rad( 90.0f ), 0.0f, 1.0f, 0.0f );
         gmtl::makeRot( q2, gmtl::Math::deg2Rad( 90.0f ), 1.0f, 0.0f, 0.0f );
         gmtl::makeRot( q3, gmtl::Math::deg2Rad( 35.0f ), 1.0f, 1.0f, 0.0f );

         gmtl::Vec<float, 3> ex1( 1.0f, 0.0f, 0.0f );
         gmtl::Vec<float, 3> ex2( 0.0f, -1.0f, 0.0f );
         gmtl::Vec<float, 3> ex3( 0.40558f, -0.40558f, 0.819152f ); // this also matches xform(mat,vec)
         gmtl::Vec<float, 3> ex4( 6.32707f, 0.67293f, 9.40826f ); // this also matches xform(mat,vec)

         gmtl::xform( res1, q1, vec );
         gmtl::xform( res2, q2, vec );
         gmtl::xform( res3, q3, vec );
         gmtl::xform( res4, q3, vec2 );
         gmtl::xform( resi, qident, vec );

         CPPUNIT_ASSERT( gmtl::isEqual( vec, resi, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex1, res1, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex2, res2, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex3, res3, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex4, res4, eps ) );

         // operator*() should be same as xform()
         gmtl::Vec<float, 3> res5, res6, res7, res8;
         res5 = q1 * vec;
         res6 = q2 * vec;
         res7 = q3 * vec;
         res8 = q3 * vec2;
         resi = qident * vec;
         CPPUNIT_ASSERT( gmtl::isEqual( vec, resi, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex1, res5, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex2, res6, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex3, res7, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex4, res8, eps ) );

         // make sure that xform(quat) yields same result as xform(mat).
         gmtl::Matrix<float, 4,4> mat;
         gmtl::makeRot( mat, gmtl::Math::deg2Rad( 35.0f ), 1.0f, 1.0f, 0.0f );
         res8 = mat * vec2;
         CPPUNIT_ASSERT( gmtl::isEqual( ex4, res8, eps ) );
      }

      // make sure non unit length vectors work...
      {   
         float eps = 0.001f;
         const gmtl::Vec3f vec( 10,100,200 ), expected( 10, -200, 100 );
         gmtl::Quatf rot;
         gmtl::makeRot( rot, gmtl::Math::deg2Rad( 90.0f ), gmtl::makeNormal( gmtl::Vec3f( 1,0,0 ) ) );
         
         gmtl::Vec3f result;
         gmtl::xform( result, rot, vec );
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result, eps ) );
      }
   }
   
   void weird_XformQuatVec_InvConj_SanityCheck()
   {
      // just for sanity check, inv and conj should both work 
      // for the implementation of quat*vec (but conj is actually faster so we usually choose that.)
      {   
         float eps = 0.001f;
         const gmtl::Vec3f vec( 10,-100,-2000 ), expected( 10, 2000, -100 );
         gmtl::Quatf rot;
         gmtl::makeRot( rot, gmtl::Math::deg2Rad( 90.0f ), gmtl::makeNormal( gmtl::Vec3f( 1,0,0 ) ) );
         
         gmtl::Vec3f result1, result2;
         result1 = makeVec( rot * makePure( vec ) * makeConj( rot ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result1, eps ) );
         result2 = makeVec( rot * makePure( vec ) * makeInvert( rot ) );
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result2, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( result1, result2, eps ) );
         //CPPUNIT_ASSERT( !gmtl::isEqual( makeConj( rot ), makeInvert( rot ), eps ) );
      }
      
      // same, but without the expected value (just check that the two are equal)
      {   
         float eps = 0.001f;
         const gmtl::Vec3f vec( 123, -4.56, 78.910 );
         gmtl::Quatf rot;
         gmtl::makeRot( rot, gmtl::Math::deg2Rad( 123.4556f ), gmtl::makeNormal( gmtl::Vec3f( -79,1000,234 ) ) );
         
         gmtl::Vec3f result1, result2;
         result1 = makeVec( rot * makePure( vec ) * makeConj( rot ) );
         result2 = makeVec( rot * makePure( vec ) * makeInvert( rot ) );
         CPPUNIT_ASSERT( gmtl::isEqual( result1, result2, eps ) );
         //CPPUNIT_ASSERT( !gmtl::isEqual( makeConj( rot ), makeInvert( rot ), eps ) );
      }
   }   
   
   void testMatVecXform()
   {
      // really simple mat44*vec4 rotations (hard coded matrix rot)
      {
         // xform a vector by a mat.  verify the rotation worked...
         const float eps = 0.0001f;
         gmtl::Matrix<float, 4, 4> q1, q2, q3, qident;
         q1.set( 0.0f, -1.0f, 0.0f, 0.0f,  // twist 90 about Z
              1.0f, 0.0f, 0.0f, 0.0f,
              0.0f, 0.0f, 1.0f, 0.0f,
              0.0f, 0.0f, 0.0f, 1.0f );
         q2.set( 0.0f, 0.0f, 1.0f, 0.0f,   // twist 90 about Y
              0.0f, 1.0f, 0.0f, 0.0f,
              -1.0f, 0.0f, 0.0f, 0.0f,
              0.0f, 0.0f, 0.0f, 1.0f );
         q3.set( 1.0f, 0.0f, 0.0f, 0.0f,   // twist -90 about X
              0.0f, 0.0f, 1.0f, 0.0f,
              0.0f, -1.0f, 0.0f, 0.0f,
              0.0f, 0.0f, 0.0f, 1.0f );
         gmtl::Vec<float, 4> vec( 0.0f, 0.0f, 1.0f, 0.0f ), res1, res2, res3, res4, resi, vec2( 1.0f, 1.0f, -10.0f, 0.0f );
         gmtl::Vec<float, 4> ex1( 0.0f, 0.0f, 1.0f, 0.0f );
         gmtl::Vec<float, 4> ex2( 1.0f, 0.0f, 0.0f, 0.0f );
         gmtl::Vec<float, 4> ex3( 0.0f, 1.0f, 0.0f, 0.0f );
         gmtl::Vec<float, 4> ex4( 1.0f, -10.0f, -1.0f, 0.0f );
         
         gmtl::xform( resi, qident, vec );
         gmtl::xform( res1, q1, vec );
         gmtl::xform( res2, q2, vec );
         gmtl::xform( res3, q3, vec );
         gmtl::xform( res4, q3, vec2 );
         
         CPPUNIT_ASSERT( gmtl::isEqual( vec, resi, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex1, res1, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex2, res2, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex3, res3, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex4, res4, eps ) );
         
         resi = qident * vec;
         res1 = q1 * vec;
         res2 = q2 * vec;
         res3 = q3 * vec;
         res4 = q3 * vec2;
         
         CPPUNIT_ASSERT( gmtl::isEqual( vec, resi, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex1, res1, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex2, res2, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex3, res3, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex4, res4, eps ) );
      }
      
      // really simple mat44*vec3 rotations (hard coded matrix rot)
      {
         // xform a vector by a mat.  verify the rotation worked...
         const float eps = 0.0001f;
         gmtl::Matrix<float, 4, 4> q1, q2, q3, qident;
         q1.set( 0.0f, -1.0f, 0.0f, 0.0f,  // twist 90 about Z
              1.0f, 0.0f, 0.0f, 0.0f,
              0.0f, 0.0f, 1.0f, 0.0f,
              0.0f, 0.0f, 0.0f, 1.0f );
         q2.set( 0.0f, 0.0f, 1.0f, 0.0f,   // twist 90 about Y
              0.0f, 1.0f, 0.0f, 0.0f,
              -1.0f, 0.0f, 0.0f, 0.0f,
              0.0f, 0.0f, 0.0f, 1.0f );
         q3.set( 1.0f, 0.0f, 0.0f, 0.0f,   // twist -90 about X
              0.0f, 0.0f, 1.0f, 0.0f,
              0.0f, -1.0f, 0.0f, 0.0f,
              0.0f, 0.0f, 0.0f, 1.0f );
         gmtl::Vec<float, 3> vec( 0.0f, 0.0f, 1.0f ), res1, res2, res3, res4, resi, vec2( 1.0f, 1.0f, -10.0f );
         gmtl::Vec<float, 3> ex1( 0.0f, 0.0f, 1.0f );
         gmtl::Vec<float, 3> ex2( 1.0f, 0.0f, 0.0f );
         gmtl::Vec<float, 3> ex3( 0.0f, 1.0f, 0.0f );
         gmtl::Vec<float, 3> ex4( 1.0f, -10.0f, -1.0f );
         
         gmtl::xform( resi, qident, vec );
         gmtl::xform( res1, q1, vec );
         gmtl::xform( res2, q2, vec );
         gmtl::xform( res3, q3, vec );
         gmtl::xform( res4, q3, vec2 );
         
         CPPUNIT_ASSERT( gmtl::isEqual( vec, resi, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex1, res1, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex2, res2, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex3, res3, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex4, res4, eps ) );
         
         resi = qident * vec;
         res1 = q1 * vec;
         res2 = q2 * vec;
         res3 = q3 * vec;
         res4 = q3 * vec2;
         
         CPPUNIT_ASSERT( gmtl::isEqual( vec, resi, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex1, res1, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex2, res2, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex3, res3, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex4, res4, eps ) );
      }
      
      // really simple mat44*pnt4 rotations (hard coded matrix rot)
      {
         // xform a vector by a mat.  verify the rotation worked...
         const float eps = 0.0001f;
         gmtl::Matrix<float, 4, 4> q1, q2, q3, qident;
         q1.set( 0.0f, -1.0f, 0.0f, 0.0f,  // twist 90 about Z
              1.0f, 0.0f, 0.0f, 0.0f,
              0.0f, 0.0f, 1.0f, 0.0f,
              0.0f, 0.0f, 0.0f, 1.0f );
         q2.set( 0.0f, 0.0f, 1.0f, 0.0f,   // twist 90 about Y
              0.0f, 1.0f, 0.0f, 0.0f,
              -1.0f, 0.0f, 0.0f, 0.0f,
              0.0f, 0.0f, 0.0f, 1.0f );
         q3.set( 1.0f, 0.0f, 0.0f, 0.0f,   // twist -90 about X
              0.0f, 0.0f, 1.0f, 0.0f,
              0.0f, -1.0f, 0.0f, 0.0f,
              0.0f, 0.0f, 0.0f, 1.0f );
         gmtl::Point<float, 4> vec( 0.0f, 0.0f, 1.0f, 1.0f ), res1, res2, res3, res4, resi, vec2( 1.0f, 1.0f, -10.0f, 1.0f );
         gmtl::Point<float, 4> ex1( 0.0f, 0.0f, 1.0f, 1.0f );
         gmtl::Point<float, 4> ex2( 1.0f, 0.0f, 0.0f, 1.0f );
         gmtl::Point<float, 4> ex3( 0.0f, 1.0f, 0.0f, 1.0f );
         gmtl::Point<float, 4> ex4( 1.0f, -10.0f, -1.0f, 1.0f );
         
         gmtl::xform( resi, qident, vec );
         gmtl::xform( res1, q1, vec );
         gmtl::xform( res2, q2, vec );
         gmtl::xform( res3, q3, vec );
         gmtl::xform( res4, q3, vec2 );
         
         CPPUNIT_ASSERT( gmtl::isEqual( vec, resi, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex1, res1, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex2, res2, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex3, res3, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex4, res4, eps ) );
         
         resi = qident * vec;
         res1 = q1 * vec;
         res2 = q2 * vec;
         res3 = q3 * vec;
         res4 = q3 * vec2;
         
         CPPUNIT_ASSERT( gmtl::isEqual( vec, resi, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex1, res1, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex2, res2, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex3, res3, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex4, res4, eps ) );
      }
      
      // really simple mat44*pnt3 rotations (hard coded matrix rot)
      {
         // xform a vector by a mat.  verify the rotation worked...
         const float eps = 0.0001f;
         gmtl::Matrix<float, 4, 4> q1, q2, q3, qident;
         q1.set( 0.0f, -1.0f, 0.0f, 0.0f,  // twist 90 about Z
              1.0f, 0.0f, 0.0f, 0.0f,
              0.0f, 0.0f, 1.0f, 0.0f,
              0.0f, 0.0f, 0.0f, 1.0f );
         q2.set( 0.0f, 0.0f, 1.0f, 0.0f,   // twist 90 about Y
              0.0f, 1.0f, 0.0f, 0.0f,
              -1.0f, 0.0f, 0.0f, 0.0f,
              0.0f, 0.0f, 0.0f, 1.0f );
         q3.set( 1.0f, 0.0f, 0.0f, 0.0f,   // twist -90 about X
              0.0f, 0.0f, 1.0f, 0.0f,
              0.0f, -1.0f, 0.0f, 0.0f,
              0.0f, 0.0f, 0.0f, 1.0f );
         gmtl::Point<float, 3> vec( 0.0f, 0.0f, 1.0f ), res1, res2, res3, res4, resi, vec2( 1.0f, 1.0f, -10.0f );
         gmtl::Point<float, 3> ex1( 0.0f, 0.0f, 1.0f );
         gmtl::Point<float, 3> ex2( 1.0f, 0.0f, 0.0f );
         gmtl::Point<float, 3> ex3( 0.0f, 1.0f, 0.0f );
         gmtl::Point<float, 3> ex4( 1.0f, -10.0f, -1.0f );
         
         gmtl::xform( resi, qident, vec );
         gmtl::xform( res1, q1, vec );
         gmtl::xform( res2, q2, vec );
         gmtl::xform( res3, q3, vec );
         gmtl::xform( res4, q3, vec2 );
         
         CPPUNIT_ASSERT( gmtl::isEqual( vec, resi, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex1, res1, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex2, res2, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex3, res3, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex4, res4, eps ) );
         
         resi = qident * vec;
         res1 = q1 * vec;
         res2 = q2 * vec;
         res3 = q3 * vec;
         res4 = q3 * vec2;
         
         CPPUNIT_ASSERT( gmtl::isEqual( vec, resi, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex1, res1, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex2, res2, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex3, res3, eps ) );
         CPPUNIT_ASSERT( gmtl::isEqual( ex4, res4, eps ) );
      }
      
      // more "interesting" rotations...
      {
         const float eps = 0.0001f;
         const gmtl::Vec<float, 3> vec( 2.0f, 5.0f, 10.0f ), expected( 6.32707, 0.67293, 9.40826 );
         gmtl::Matrix<float, 4, 4> mat;
         gmtl::makeRot( mat, gmtl::Math::deg2Rad( 35.0f ), 1.0f, 1.0f, 0.0f );
         
         // xform a vector by a mat.  verify the rotation worked...
         gmtl::Vec<float, 3> result1;
         gmtl::xform( result1, mat, vec );
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result1, eps ) );

         // operator* should be same
         gmtl::Vec<float, 3> result2;
         result2 = mat * vec;
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result2, eps ) );
         
         // make sure that xform by quat yields same result as xform by mat.
         gmtl::Quat<float> quat;
         gmtl::makeRot( quat, gmtl::Math::deg2Rad( 35.0f ), 1.0f, 1.0f, 0.0f );
         
         gmtl::Vec<float, 3> result3;
         gmtl::xform( result3, quat, vec );
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result3, eps ) );
         
         gmtl::Vec<float, 3> result4;
         result4 = quat * vec;
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result4, eps ) );
      }
      
      
      
      // 4x4 matrix: test out complete transforms with a weird vector
      {
         const float eps = 0.0001f;
         const gmtl::Vec<float, 4> vec( -100, 334, 455, -568 ), expected( -339, 145, 629, 1113 );
         gmtl::Matrix<float, 4, 4> mat;
         mat.set( 1, 2, 3, 4, 
                  5, 6, 7, 8,
                  9, 10, 11, 12,
                  13, 14, 15, 16 );
         
         // xform a vector by a mat.  verify the xform worked...
         gmtl::Vec<float, 4> result1;
         gmtl::xform( result1, mat, vec );
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result1, eps ) );

         // operator* should be same
         gmtl::Vec<float, 4> result2;
         result2 = mat * vec;
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result2, eps ) );
      }
      
      // 3x4 matrix: test out complete transforms with a weird vector
      // @todo: maybe change this to return size 3: todo, xform doesn't support uneven matrices, but should it??? need to resolve.. 
      {
         const float eps = 0.0001f;
         const gmtl::Vec<float, 4> vec( -100, 334, 455, -568 );
         const gmtl::Vec<float, 4> expected( -339, 145, 629, 0.0f );
         gmtl::Matrix<float, 3, 4> mat;
         mat.set( 1, 2, 3, 4, 
                  5, 6, 7, 8,
                  9, 10, 11, 12 );
         
         // xform a vector by a mat.  verify the xform worked...
         gmtl::Vec<float, 4> result1;
         gmtl::xform( result1, mat, vec );
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result1, eps ) );

         // operator* should be same
         gmtl::Vec<float, 4> result2;
         result2 = mat * vec;
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result2, eps ) );
      }
      
      
      // 3x3 matrix: test out complete transforms with a weird vector
      {
         const float eps = 0.0001f;
         const gmtl::Vec<float, 3> vec( -100.0f, 334.0f, 455.0f ), expected( 1933, 4689, 7445 );
         gmtl::Matrix<float, 3, 3> mat;
         mat.set( 1, 2, 3, 
                  5, 6, 7,
                  9, 10, 11 );
         
         // xform a vector by a mat.  verify the xform worked...
         gmtl::Vec<float, 3> result1;
         gmtl::xform( result1, mat, vec );
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result1, eps ) );

         // operator* should be same
         gmtl::Vec<float, 3> result2;
         result2 = mat * vec;
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result2, eps ) );
      }
      
      // 4x4 matrix: test out complete transforms with standard vector
      {
         const float eps = 0.0001f;
         const gmtl::Vec<float, 4> vec( -100.0f, 334.0f, 455.0f, 0.0f ), expected( 1933.0f, 4689.0f, 7445.0f, 10201.0f );
         const gmtl::Vec<float, 3> partial_vec( -100.0f, 334.0f, 455.0f ), expected2( 1933.0f/10201.0f, 4689.0f/10201.0f, 7445.0f/10201.0f );
         gmtl::Matrix<float, 4, 4> mat;
         mat.set( 1, 2, 3, 4, 
                  5, 6, 7, 8,
                  9, 10, 11, 12,
                  13, 14, 15, 16 );
         
         // xform a vector by a mat.  verify the xform worked...
         gmtl::Vec<float, 4> result1;
         gmtl::xform( result1, mat, vec );
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result1, eps ) );

         // operator* should be same
         gmtl::Vec<float, 4> result2;
         result2 = mat * vec;
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result2, eps ) );
         
         // xform a partially specified vector by a mat.  verify the xform worked...
         gmtl::Vec<float, 3> result3;
         gmtl::xform( result3, mat, partial_vec );
         CPPUNIT_ASSERT( gmtl::isEqual( expected2, result3, eps ) );

         // operator* should be same
         gmtl::Vec<float, 3> result4;
         result4 = mat * partial_vec;
         CPPUNIT_ASSERT( gmtl::isEqual( expected2, result4, eps ) );
      }
      
      // 3x4 matrix: test out complete transforms with standard vector
      // @todo: maybe change this to return size 3: todo, xform doesn't support uneven matrices, but should it??? need to resolve.. 
      {
         const float eps = 0.0001f;
         const gmtl::Vec<float, 4> vec( -100, 334, 455, 0.0f ), expected( 1933, 4689, 7445, 0.0f );
         const gmtl::Vec<float, 3> partial_vec( -100, 334, 455 ), expected2( 1933, 4689, 7445 );
         gmtl::Matrix<float, 3, 4> mat;
         mat.set( 1, 2, 3, 4, 
                  5, 6, 7, 8,
                  9, 10, 11, 12 );
         
         // xform a vector by a mat.  verify the xform worked...
         gmtl::Vec<float, 4> result1;
         gmtl::xform( result1, mat, vec );
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result1, eps ) );

         // operator* should be same
         gmtl::Vec<float, 4> result2;
         result2 = mat * vec;
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result2, eps ) );
         
         // xform a partially specified vector by a mat.  verify the xform worked...
         gmtl::Vec<float, 3> result3;
         gmtl::xform( result3, mat, partial_vec );
         CPPUNIT_ASSERT( gmtl::isEqual( expected2, result3, eps ) );

         // operator* should be same
         gmtl::Vec<float, 3> result4;
         result4 = mat * partial_vec;
         CPPUNIT_ASSERT( gmtl::isEqual( expected2, result4, eps ) );
      }

      // 3x3 matrix: test out complete transforms with standard vector
      {
         const float eps = 0.0001f;
         const gmtl::Vec<float, 3> vec( -100, 334, 0.0f ), expected( 568, 1504, 2440 );
         const gmtl::Vec<float, 2> partial_vec( -100, 334 ), expected2( 568.0f/2440.0f, 1504.0f/2440.0f );
         gmtl::Matrix<float, 3, 3> mat;
         mat.set( 1, 2, 3, 
                  5, 6, 7,
                  9, 10, 11 );
         
         // xform a vector by a mat.  verify the xform worked...
         gmtl::Vec<float, 3> result1;
         gmtl::xform( result1, mat, vec );
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result1, eps ) );

         // operator* should be same
         gmtl::Vec<float, 3> result2;
         result2 = mat * vec;
         CPPUNIT_ASSERT( gmtl::isEqual( expected, result2, eps ) );
         
         // xform a partially specified vector by a mat.  verify the xform worked...
         gmtl::Vec<float, 2> result3;
         gmtl::xform( result3, mat, partial_vec );
         CPPUNIT_ASSERT( gmtl::isEqual( expected2, result3, eps ) );

         // operator* should be same
         gmtl::Vec<float, 2> result4;
         result4 = mat * partial_vec;
         CPPUNIT_ASSERT( gmtl::isEqual( expected2, result4, eps ) );
      }
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
      test_suite->addTest( new CppUnit::TestCaller<XformTest>("weird_XformQuatVec_InvConj_SanityCheck", &XformTest::weird_XformQuatVec_InvConj_SanityCheck));
      test_suite->addTest( new CppUnit::TestCaller<XformTest>("testMatVecXform", &XformTest::testMatVecXform));
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
