/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: MatrixClassTest.h,v $
 * Date modified: $Date: 2002-02-12 16:17:16 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 *********************************************************** ggt-head end */
/*************************************************************** ggt-cpr beg
*
* GGT: The Generic Graphics Toolkit
* Copyright (C) 2001, 2002 Allen Bierbaum
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

#include <gmtl/Matrix.h>

namespace gmtlTest
{

class MatrixClassTest : public CppUnit::TestCase
{
public:
   MatrixClassTest( std::string name = "MatrixClassTest" )
   : TestCase (name)
   {;}

   virtual ~MatrixClassTest()
   {}

   virtual void setUp()
   {;}

   virtual void tearDown()
   {
   }

   // test out operations using identity matrix
   void testMatrixIdentity()
   {
      // make sure identity constants are set up correctly.
      {
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY44F( 0, 0  ) == 1.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY44F( 1, 1  ) == 1.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY44F( 2, 2  ) == 1.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY44F( 3, 3  ) == 1.0f );
         
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY44F( 1, 0  ) == 0.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY44F( 2, 0  ) == 0.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY44F( 3, 0  ) == 0.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY44F( 0, 1  ) == 0.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY44F( 2, 1  ) == 0.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY44F( 3, 1  ) == 0.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY44F( 0, 2  ) == 0.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY44F( 1, 2  ) == 0.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY44F( 3, 2  ) == 0.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY44F( 0, 3  ) == 0.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY44F( 1, 3  ) == 0.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY44F( 2, 3  ) == 0.0f );
      }
      
      {
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY34F( 0, 0 ) == 1.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY34F( 1, 1 ) == 1.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY34F( 2, 2 ) == 1.0f );
 
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY34F( 1, 0 ) == 0.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY34F( 2, 0 ) == 0.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY34F( 0, 1 ) == 0.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY34F( 2, 1 ) == 0.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY34F( 0, 2 ) == 0.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY34F( 1, 2 ) == 0.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY34F( 0, 3 ) == 0.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY34F( 1, 3 ) == 0.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY34F( 2, 3 ) == 0.0f );
      }
      
      {
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY33F( 0, 0 ) == 1.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY33F( 1, 1 ) == 1.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY33F( 2, 2 ) == 1.0f );
 
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY33F( 1, 0 ) == 0.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY33F( 2, 0 ) == 0.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY33F( 0, 1 ) == 0.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY33F( 2, 1 ) == 0.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY33F( 0, 2 ) == 0.0f );
         CPPUNIT_ASSERT( gmtl::MAT_IDENTITY33F( 1, 2 ) == 0.0f );
      }
      
      // make sure default constructor inits to ident
      {
         gmtl::Matrix44f test_mat;
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 2, 2 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 3, 3 ) == 1.0f );
 
         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 3, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 3, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 2 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 1, 2 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 3, 2 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 3 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 1, 3 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 3 ) == 0.0f );
      }
 
      {
         gmtl::Matrix34f test_mat;
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 2, 2 ) == 1.0f );
 
         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 2 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 1, 2 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 3 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 1, 3 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 3 ) == 0.0f );
      }
 
      {
         gmtl::Matrix33f test_mat;
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 2, 2 ) == 1.0f );
 
         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 2 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 1, 2 ) == 0.0f );
      }
      
      // make sure copy constructor works.
      {
         gmtl::Matrix44f test_mat( gmtl::MAT_IDENTITY44F );
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 2, 2 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 3, 3 ) == 1.0f );
 
         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 3, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 3, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 2 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 1, 2 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 3, 2 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 3 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 1, 3 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 3 ) == 0.0f );
      }
      
      {
         gmtl::Matrix34f test_mat( gmtl::MAT_IDENTITY34F );
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 2, 2 ) == 1.0f );
 
         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 2 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 1, 2 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 3 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 1, 3 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 3 ) == 0.0f );
      }
      
      {
         gmtl::Matrix33f test_mat( gmtl::MAT_IDENTITY33F );
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 2, 2 ) == 1.0f );
 
         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 2 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 1, 2 ) == 0.0f );
      }
      
      // make sure operator= works:
      {
         gmtl::Matrix44f test_mat;
         test_mat = gmtl::MAT_IDENTITY44F;
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 2, 2 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 3, 3 ) == 1.0f );
 
         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 3, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 3, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 2 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 1, 2 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 3, 2 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 3 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 1, 3 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 3 ) == 0.0f );
      }
      
      {
         gmtl::Matrix34f test_mat;
         test_mat = gmtl::MAT_IDENTITY34F;
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 2, 2 ) == 1.0f );
 
         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 2 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 1, 2 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 3 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 1, 3 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 3 ) == 0.0f );
      }
      
      {
         gmtl::Matrix33f test_mat( gmtl::MAT_IDENTITY33F );
         test_mat = gmtl::MAT_IDENTITY33F;
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 2, 2 ) == 1.0f );
 
         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 2 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 1, 2 ) == 0.0f );
      }
   }
   
   // make sure set( float* ) works
   void testMatrixSetFloat()
   {   
      {
         float mat44[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 };
         gmtl::Matrix44f test_mat;
         test_mat.set( mat44 );
         
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 0  );
         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 1  );
         CPPUNIT_ASSERT( test_mat( 2, 0 ) == 2  );
         CPPUNIT_ASSERT( test_mat( 3, 0 ) == 3  );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 4  );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 5  );
         CPPUNIT_ASSERT( test_mat( 2, 1 ) == 6  );
         CPPUNIT_ASSERT( test_mat( 3, 1 ) == 7  );
         CPPUNIT_ASSERT( test_mat( 0, 2 ) == 8  );
         CPPUNIT_ASSERT( test_mat( 1, 2 ) == 9  );
         CPPUNIT_ASSERT( test_mat( 2, 2 ) == 10 );
         CPPUNIT_ASSERT( test_mat( 3, 2 ) == 11 );
         CPPUNIT_ASSERT( test_mat( 0, 3 ) == 12 );
         CPPUNIT_ASSERT( test_mat( 1, 3 ) == 13 );
         CPPUNIT_ASSERT( test_mat( 2, 3 ) == 14 );
         CPPUNIT_ASSERT( test_mat( 3, 3 ) == 15 );
      }
      
      {
         float mat34[] = { 0,1,2,3,4,5,6,7,8,9,10,11 };
         gmtl::Matrix34f test_mat;
         test_mat.set( mat34 );
         
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 0 );
         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 1 );
         CPPUNIT_ASSERT( test_mat( 2, 0 ) == 2 );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 3 );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 4 );
         CPPUNIT_ASSERT( test_mat( 2, 1 ) == 5 );
         CPPUNIT_ASSERT( test_mat( 0, 2 ) == 6 );
         CPPUNIT_ASSERT( test_mat( 1, 2 ) == 7 );
         CPPUNIT_ASSERT( test_mat( 2, 2 ) == 8 );
         CPPUNIT_ASSERT( test_mat( 0, 3 ) == 9 );
         CPPUNIT_ASSERT( test_mat( 1, 3 ) == 10 );
         CPPUNIT_ASSERT( test_mat( 2, 3 ) == 11 );
      }
      
      {
         float mat33[] = { 0,1,2,3,4,5,6,7,8 };
         gmtl::Matrix33f test_mat( gmtl::MAT_IDENTITY33F );
         test_mat.set( mat33 );
         
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 0 );
         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 1 );
         CPPUNIT_ASSERT( test_mat( 2, 0 ) == 2 );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 3 );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 4 );
         CPPUNIT_ASSERT( test_mat( 2, 1 ) == 5 );
         CPPUNIT_ASSERT( test_mat( 0, 2 ) == 6 );
         CPPUNIT_ASSERT( test_mat( 1, 2 ) == 7 );
         CPPUNIT_ASSERT( test_mat( 2, 2 ) == 8 );
      }
      
      {
         float mat22[] = { 0,1,2,3 };
         gmtl::Matrix22f test_mat( gmtl::MAT_IDENTITY22F );
         test_mat.set( mat22 );
         
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 0 );
         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 1 );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 2 );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 3 );
      }
   }
   
   // more general creation tests..
   // tests default constructor, copy constructor, set()
   //       operator() operator[]
   void testMatrix44Creation()
   {
      // make sure setter and getters work (float* setter tested in a different test)
      gmtl::Matrix44f src_mat;
      src_mat.set( 0.0f,  1.0f,  2.0f,  3.0f, 
                   4.0f,  5.0f,  6.0f,  7.0f, 
                   8.0f,  9.0f,  10.0f, 11.0f, 
                   12.0f, 13.0f, 14.0f, 15.0f);

      // test that operator[] is sane
      {
         CPPUNIT_ASSERT( src_mat[0]   == 0 );
         CPPUNIT_ASSERT( src_mat[1]   == 4 );
         CPPUNIT_ASSERT( src_mat[2]   == 8 );
         CPPUNIT_ASSERT( src_mat[3]   == 12 );
         CPPUNIT_ASSERT( src_mat[4]   == 1 );
         CPPUNIT_ASSERT( src_mat[5]   == 5 );
         CPPUNIT_ASSERT( src_mat[6]   == 9 );
         CPPUNIT_ASSERT( src_mat[7]   == 13 );
         CPPUNIT_ASSERT( src_mat[8]   == 2 );
         CPPUNIT_ASSERT( src_mat[9]   == 6 );
         CPPUNIT_ASSERT( src_mat[10]  == 10 );
         CPPUNIT_ASSERT( src_mat[11]  == 14 );
         CPPUNIT_ASSERT( src_mat[12]  == 3 );
         CPPUNIT_ASSERT( src_mat[13]  == 7 );
         CPPUNIT_ASSERT( src_mat[14]  == 11 );
         CPPUNIT_ASSERT( src_mat[15]  == 15 );
      }
      // test that operator() is sane (points to what we expect)
      {
         CPPUNIT_ASSERT( src_mat( 0, 0 ) == 0 );
         CPPUNIT_ASSERT( src_mat( 1, 0 ) == 4 );
         CPPUNIT_ASSERT( src_mat( 2, 0 ) == 8 );
         CPPUNIT_ASSERT( src_mat( 3, 0 ) == 12 );
         CPPUNIT_ASSERT( src_mat( 0, 1 ) == 1 );
         CPPUNIT_ASSERT( src_mat( 1, 1 ) == 5 );
         CPPUNIT_ASSERT( src_mat( 2, 1 ) == 9 );
         CPPUNIT_ASSERT( src_mat( 3, 1 ) == 13 );
         CPPUNIT_ASSERT( src_mat( 0, 2 ) == 2 );
         CPPUNIT_ASSERT( src_mat( 1, 2 ) == 6 );
         CPPUNIT_ASSERT( src_mat( 2, 2 ) == 10 );
         CPPUNIT_ASSERT( src_mat( 3, 2 ) == 14 );
         CPPUNIT_ASSERT( src_mat( 0, 3 ) == 3 );
         CPPUNIT_ASSERT( src_mat( 1, 3 ) == 7 );
         CPPUNIT_ASSERT( src_mat( 2, 3 ) == 11 );
         CPPUNIT_ASSERT( src_mat( 3, 3 ) == 15 );
      }

      // test that operator() and operator[] are equivelent
      {
         gmtl::Matrix44f src_mat( gmtl::MAT_IDENTITY44F );
         CPPUNIT_ASSERT( src_mat( 0, 0 ) == src_mat[0] );
         CPPUNIT_ASSERT( src_mat( 1, 0 ) == src_mat[1] );
         CPPUNIT_ASSERT( src_mat( 2, 0 ) == src_mat[2] );
         CPPUNIT_ASSERT( src_mat( 3, 0 ) == src_mat[3] );
         CPPUNIT_ASSERT( src_mat( 0, 1 ) == src_mat[4] );
         CPPUNIT_ASSERT( src_mat( 1, 1 ) == src_mat[5] );
         CPPUNIT_ASSERT( src_mat( 2, 1 ) == src_mat[6] );
         CPPUNIT_ASSERT( src_mat( 3, 1 ) == src_mat[7] );
         CPPUNIT_ASSERT( src_mat( 0, 2 ) == src_mat[8] );
         CPPUNIT_ASSERT( src_mat( 1, 2 ) == src_mat[9] );
         CPPUNIT_ASSERT( src_mat( 2, 2 ) == src_mat[10] );
         CPPUNIT_ASSERT( src_mat( 3, 2 ) == src_mat[11] );
         CPPUNIT_ASSERT( src_mat( 0, 3 ) == src_mat[12] );
         CPPUNIT_ASSERT( src_mat( 1, 3 ) == src_mat[13] );
         CPPUNIT_ASSERT( src_mat( 2, 3 ) == src_mat[14] );
         CPPUNIT_ASSERT( src_mat( 3, 3 ) == src_mat[15] );
      }
      // make sure copy constructor works.
      {
         gmtl::Matrix44f test_mat( src_mat );
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 0 );
         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 4 );
         CPPUNIT_ASSERT( test_mat( 2, 0 ) == 8 );
         CPPUNIT_ASSERT( test_mat( 3, 0 ) == 12 );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 1 );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 5 );
         CPPUNIT_ASSERT( test_mat( 2, 1 ) == 9 );
         CPPUNIT_ASSERT( test_mat( 3, 1 ) == 13 );
         CPPUNIT_ASSERT( test_mat( 0, 2 ) == 2 );
         CPPUNIT_ASSERT( test_mat( 1, 2 ) == 6 );
         CPPUNIT_ASSERT( test_mat( 2, 2 ) == 10 );
         CPPUNIT_ASSERT( test_mat( 3, 2 ) == 14 );
         CPPUNIT_ASSERT( test_mat( 0, 3 ) == 3 );
         CPPUNIT_ASSERT( test_mat( 1, 3 ) == 7 );
         CPPUNIT_ASSERT( test_mat( 2, 3 ) == 11 );
         CPPUNIT_ASSERT( test_mat( 3, 3 ) == 15 );
      }
      // make sure operator= works
      {
         gmtl::Matrix44f test_mat;
         // it is identity matrix now...
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 2, 2 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 3, 3 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 3, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 3, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 2 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 1, 2 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 3, 2 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 3 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 1, 3 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 3 ) == 0.0f );
         test_mat = src_mat;
         // it should have changed...
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 0 );
         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 4 );
         CPPUNIT_ASSERT( test_mat( 2, 0 ) == 8 );
         CPPUNIT_ASSERT( test_mat( 3, 0 ) == 12 );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 1 );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 5 );
         CPPUNIT_ASSERT( test_mat( 2, 1 ) == 9 );
         CPPUNIT_ASSERT( test_mat( 3, 1 ) == 13 );
         CPPUNIT_ASSERT( test_mat( 0, 2 ) == 2 );
         CPPUNIT_ASSERT( test_mat( 1, 2 ) == 6 );
         CPPUNIT_ASSERT( test_mat( 2, 2 ) == 10 );
         CPPUNIT_ASSERT( test_mat( 3, 2 ) == 14 );
         CPPUNIT_ASSERT( test_mat( 0, 3 ) == 3 );
         CPPUNIT_ASSERT( test_mat( 1, 3 ) == 7 );
         CPPUNIT_ASSERT( test_mat( 2, 3 ) == 11 );
         CPPUNIT_ASSERT( test_mat( 3, 3 ) == 15 );
      }
   }
   void testMatrix34Creation()
   {
      // make sure setter and getters work (float* setter tested in a different test)
      gmtl::Matrix34f src_mat;
      src_mat.set( 0, 1, 2, 3, 
                   4, 5, 6, 7, 
                   8, 9, 10, 11);

      // test that operator[] is sane
      {
         CPPUNIT_ASSERT( src_mat[0]  == 0 );
         CPPUNIT_ASSERT( src_mat[1]  == 4 );
         CPPUNIT_ASSERT( src_mat[2]  == 8 );
         CPPUNIT_ASSERT( src_mat[3]  == 1 );
         CPPUNIT_ASSERT( src_mat[4]  == 5 );
         CPPUNIT_ASSERT( src_mat[5]  == 9 );
         CPPUNIT_ASSERT( src_mat[6]  == 2 );
         CPPUNIT_ASSERT( src_mat[7]  == 6 );
         CPPUNIT_ASSERT( src_mat[8]  == 10 );
         CPPUNIT_ASSERT( src_mat[9]  == 3 );
         CPPUNIT_ASSERT( src_mat[10] == 7 );
         CPPUNIT_ASSERT( src_mat[11] == 11 );
      }
      // test that operator() is sane (points to what we expect)
      {
         CPPUNIT_ASSERT( src_mat( 0, 0 ) == 0 );
         CPPUNIT_ASSERT( src_mat( 1, 0 ) == 4 );
         CPPUNIT_ASSERT( src_mat( 2, 0 ) == 8 );
         CPPUNIT_ASSERT( src_mat( 0, 1 ) == 1 );
         CPPUNIT_ASSERT( src_mat( 1, 1 ) == 5 );
         CPPUNIT_ASSERT( src_mat( 2, 1 ) == 9 );
         CPPUNIT_ASSERT( src_mat( 0, 2 ) == 2 );
         CPPUNIT_ASSERT( src_mat( 1, 2 ) == 6 );
         CPPUNIT_ASSERT( src_mat( 2, 2 ) == 10 );
         CPPUNIT_ASSERT( src_mat( 0, 3 ) == 3 );
         CPPUNIT_ASSERT( src_mat( 1, 3 ) == 7 );
         CPPUNIT_ASSERT( src_mat( 2, 3 ) == 11 );
      }

      // test that operator() and operator[] are equivelent
      {
         gmtl::Matrix34f src_mat( gmtl::MAT_IDENTITY34F );
         CPPUNIT_ASSERT( src_mat( 0, 0 ) == src_mat[0] );
         CPPUNIT_ASSERT( src_mat( 1, 0 ) == src_mat[1] );
         CPPUNIT_ASSERT( src_mat( 2, 0 ) == src_mat[2] );
         CPPUNIT_ASSERT( src_mat( 0, 1 ) == src_mat[3] );
         CPPUNIT_ASSERT( src_mat( 1, 1 ) == src_mat[4] );
         CPPUNIT_ASSERT( src_mat( 2, 1 ) == src_mat[5] );
         CPPUNIT_ASSERT( src_mat( 0, 2 ) == src_mat[6] );
         CPPUNIT_ASSERT( src_mat( 1, 2 ) == src_mat[7] );
         CPPUNIT_ASSERT( src_mat( 2, 2 ) == src_mat[8] );
         CPPUNIT_ASSERT( src_mat( 0, 3 ) == src_mat[9] );
         CPPUNIT_ASSERT( src_mat( 1, 3 ) == src_mat[10] );
         CPPUNIT_ASSERT( src_mat( 2, 3 ) == src_mat[11] );
      }
      // make sure copy constructor works.
      {
         gmtl::Matrix34f test_mat( src_mat );
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 0 );
         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 4 );
         CPPUNIT_ASSERT( test_mat( 2, 0 ) == 8 );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 1 );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 5 );
         CPPUNIT_ASSERT( test_mat( 2, 1 ) == 9 );
         CPPUNIT_ASSERT( test_mat( 0, 2 ) == 2 );
         CPPUNIT_ASSERT( test_mat( 1, 2 ) == 6 );
         CPPUNIT_ASSERT( test_mat( 2, 2 ) == 10 );
         CPPUNIT_ASSERT( test_mat( 0, 3 ) == 3 );
         CPPUNIT_ASSERT( test_mat( 1, 3 ) == 7 );
         CPPUNIT_ASSERT( test_mat( 2, 3 ) == 11 );
      }
      // make sure operator= works
      {
         gmtl::Matrix34f test_mat;
         // it is identity matrix now...
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 2, 2 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 2 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 1, 2 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 3 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 1, 3 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 3 ) == 0.0f );
         test_mat = src_mat;
         // it should have changed...
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 0 );
         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 4 );
         CPPUNIT_ASSERT( test_mat( 2, 0 ) == 8 );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 1 );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 5 );
         CPPUNIT_ASSERT( test_mat( 2, 1 ) == 9 );
         CPPUNIT_ASSERT( test_mat( 0, 2 ) == 2 );
         CPPUNIT_ASSERT( test_mat( 1, 2 ) == 6 );
         CPPUNIT_ASSERT( test_mat( 2, 2 ) == 10 );
         CPPUNIT_ASSERT( test_mat( 0, 3 ) == 3 );
         CPPUNIT_ASSERT( test_mat( 1, 3 ) == 7 );
         CPPUNIT_ASSERT( test_mat( 2, 3 ) == 11 );
      }
   }
   void testMatrix33Creation()
   {
      // make sure setter and getters work (float* setter tested in a different test)
      gmtl::Matrix33f src_mat;
      src_mat.set( 0, 1, 2, 
                   3, 4, 5, 
                   6, 7, 8);

      // test that operator[] is sane
      {
         CPPUNIT_ASSERT( src_mat[0] == 0 );
         CPPUNIT_ASSERT( src_mat[1] == 3 );
         CPPUNIT_ASSERT( src_mat[2] == 6 );
         CPPUNIT_ASSERT( src_mat[3] == 1 );
         CPPUNIT_ASSERT( src_mat[4] == 4 );
         CPPUNIT_ASSERT( src_mat[5] == 7 );
         CPPUNIT_ASSERT( src_mat[6] == 2 );
         CPPUNIT_ASSERT( src_mat[7] == 5 );
         CPPUNIT_ASSERT( src_mat[8] == 8 );
      }

      // test that operator() is sane (points to what we expect)
      {
         CPPUNIT_ASSERT( src_mat( 0, 0 ) == 0 );
         CPPUNIT_ASSERT( src_mat( 1, 0 ) == 3 );
         CPPUNIT_ASSERT( src_mat( 2, 0 ) == 6 );
         CPPUNIT_ASSERT( src_mat( 0, 1 ) == 1 );
         CPPUNIT_ASSERT( src_mat( 1, 1 ) == 4 );
         CPPUNIT_ASSERT( src_mat( 2, 1 ) == 7 );
         CPPUNIT_ASSERT( src_mat( 0, 2 ) == 2 );
         CPPUNIT_ASSERT( src_mat( 1, 2 ) == 5 );
         CPPUNIT_ASSERT( src_mat( 2, 2 ) == 8 );
      }

      // test that operator() and operator[] are equivelent
      {
         CPPUNIT_ASSERT( src_mat( 0, 0 ) == src_mat[0] );
         CPPUNIT_ASSERT( src_mat( 1, 0 ) == src_mat[1] );
         CPPUNIT_ASSERT( src_mat( 2, 0 ) == src_mat[2] );
         CPPUNIT_ASSERT( src_mat( 0, 1 ) == src_mat[3] );
         CPPUNIT_ASSERT( src_mat( 1, 1 ) == src_mat[4] );
         CPPUNIT_ASSERT( src_mat( 2, 1 ) == src_mat[5] );
         CPPUNIT_ASSERT( src_mat( 0, 2 ) == src_mat[6] );
         CPPUNIT_ASSERT( src_mat( 1, 2 ) == src_mat[7] );
         CPPUNIT_ASSERT( src_mat( 2, 2 ) == src_mat[8] );
      }
      // make sure copy constructor works.
      {
         gmtl::Matrix33f test_mat( src_mat );
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 0 );
         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 3 );
         CPPUNIT_ASSERT( test_mat( 2, 0 ) == 6 );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 1 );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 4 );
         CPPUNIT_ASSERT( test_mat( 2, 1 ) == 7 );
         CPPUNIT_ASSERT( test_mat( 0, 2 ) == 2 );
         CPPUNIT_ASSERT( test_mat( 1, 2 ) == 5 );
         CPPUNIT_ASSERT( test_mat( 2, 2 ) == 8 );
      }
      // make sure operator= works
      {
         gmtl::Matrix33f test_mat;
         // it is identity matrix now...
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 2, 2 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 2, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 2 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 1, 2 ) == 0.0f );
         test_mat = src_mat;
         // it should have changed...
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 0 );
         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 3 );
         CPPUNIT_ASSERT( test_mat( 2, 0 ) == 6 );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 1 );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 4 );
         CPPUNIT_ASSERT( test_mat( 2, 1 ) == 7 );
         CPPUNIT_ASSERT( test_mat( 0, 2 ) == 2 );
         CPPUNIT_ASSERT( test_mat( 1, 2 ) == 5 );
         CPPUNIT_ASSERT( test_mat( 2, 2 ) == 8 );
      }
   }
   
   void testMatrix22Creation()
   {
      // make sure setter and getters work (float* setter tested in a different test)
      gmtl::Matrix22f src_mat;
      src_mat.set( 0, 1,  
                   2, 3 );

      // test that operator[] is sane
      {
         CPPUNIT_ASSERT( src_mat[0] == 0 );
         CPPUNIT_ASSERT( src_mat[1] == 2 );
         CPPUNIT_ASSERT( src_mat[2] == 1 );
         CPPUNIT_ASSERT( src_mat[3] == 3 );
      }

      // test that operator() is sane (points to what we expect)
      {
         CPPUNIT_ASSERT( src_mat( 0, 0 ) == 0 );
         CPPUNIT_ASSERT( src_mat( 1, 0 ) == 2 );
         CPPUNIT_ASSERT( src_mat( 0, 1 ) == 1 );
         CPPUNIT_ASSERT( src_mat( 1, 1 ) == 3 );
      }

      // test that operator() and operator[] are equivelent
      {
         CPPUNIT_ASSERT( src_mat( 0, 0 ) == src_mat[0] );
         CPPUNIT_ASSERT( src_mat( 1, 0 ) == src_mat[1] );
         CPPUNIT_ASSERT( src_mat( 0, 1 ) == src_mat[2] );
         CPPUNIT_ASSERT( src_mat( 1, 1 ) == src_mat[3] );
      }
      // make sure copy constructor works.
      {
         gmtl::Matrix22f test_mat( src_mat );
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 0 );
         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 2 );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 1 );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 3 );
      }
      // make sure operator= works
      {
         gmtl::Matrix22f test_mat;
         // it is identity matrix now...
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 1.0f );
         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 0.0f );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 1.0f );
         test_mat = src_mat;
         // it should have changed...
         CPPUNIT_ASSERT( test_mat( 0, 0 ) == 0 );
         CPPUNIT_ASSERT( test_mat( 1, 0 ) == 2 );
         CPPUNIT_ASSERT( test_mat( 0, 1 ) == 1 );
         CPPUNIT_ASSERT( test_mat( 1, 1 ) == 3 );
      }
   }
   
   static Test* suite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("MatrixClassTest");
      test_suite->addTest( new CppUnit::TestCaller<MatrixClassTest>("testMatrixIdentity", &MatrixClassTest::testMatrixIdentity));
      test_suite->addTest( new CppUnit::TestCaller<MatrixClassTest>("testMatrixSetFloat", &MatrixClassTest::testMatrixSetFloat));
      test_suite->addTest( new CppUnit::TestCaller<MatrixClassTest>("testMatrix44Creation", &MatrixClassTest::testMatrix44Creation));
      test_suite->addTest( new CppUnit::TestCaller<MatrixClassTest>("testMatrix34Creation", &MatrixClassTest::testMatrix34Creation));
      test_suite->addTest( new CppUnit::TestCaller<MatrixClassTest>("testMatrix33Creation", &MatrixClassTest::testMatrix33Creation));
      return test_suite;
   }

   static Test* interactiveSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("InteractiveThreadTest");
      //test_suite->addTest( new CppUnit::TestCaller<ThreadTest>("interactiveCPUGrind", &ThreadTest::interactiveTestCPUGrind));
      return test_suite;
   }

protected:

};

};
