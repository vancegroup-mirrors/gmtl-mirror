/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: OptTest.h,v $
 * Date modified: $Date: 2002-02-10 04:38:07 $
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
#include <cppunit/extensions/MetricRegistry.h>

#include <gmtl/Vec3.h>
#include <gmtl/matVecFuncs.h>

namespace gmtlTest
{
class ArrayVec3
   {
   public:
      ArrayVec3() 
      {
         vec[0] = 0.0f;
         vec[1] = 0.0f;
         vec[2] = 0.0f;
      }
      ArrayVec3( const ArrayVec3& v )
      {
         vec[0] = v.vec[0];
         vec[1] = v.vec[1];
         vec[2] = v.vec[2];
      }
      ArrayVec3( float x, float y, float z )
      {
         vec[0] = x;
         vec[1] = y;
         vec[2] = z;
      }
      float vec[3];
   };
   
   class SeparateVec3
   {
   public:
      SeparateVec3() 
      {
         vec1 = 0.0f;
         vec2 = 0.0f;
         vec0 = 0.0f;
      }
      SeparateVec3( const SeparateVec3& v )
      {
         vec0 = v.vec0;
         vec1 = v.vec1;
         vec2 = v.vec2;
      }
      SeparateVec3( float x, float y, float z )
      {
         vec0 = x;
         vec1 = y;
         vec2 = z;
      }
      float vec0, vec1, vec2;
   };
   
   SeparateVec3& operator+=( SeparateVec3& lhs, const SeparateVec3& rhs )
   {
      lhs.vec0 = rhs.vec0;
      lhs.vec1 = rhs.vec1;
      lhs.vec2 = rhs.vec2;
      return lhs;
   }   
   SeparateVec3 operator+( const SeparateVec3& lhs, const SeparateVec3& rhs )
   {
      return SeparateVec3( lhs.vec0 + rhs.vec0, lhs.vec1 + rhs.vec1, lhs.vec2 + rhs.vec2 );
   }
//   SeparateVec3 addOpt( const SeparateVec3& lhs, const SeparateVec3& rhs )
//   {
//      return SeparateVec3( lhs ) += rhs;
//   }
class OptTest : public CppUnit::TestCase
{
public:
   OptTest( std::string name = "OptTest" )
   : TestCase (name)
   {;}

   virtual ~OptTest()
   {}

   virtual void setUp()
   {;}

   virtual void tearDown()
   {
   }

   void testRetValOpt()
   {
      
   }
   
   void testLoopUnrolling()
   {
      
   }
   
   void testRetValOptUsingInternalTemporary()
   {
      
   }

   static Test* suite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("OptTest");
      test_suite->addTest( new CppUnit::TestCaller<OptTest>("testRetValOpt", &OptTest::testRetValOpt));
      return test_suite;
   }

   static Test* interactiveSuite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("InteractiveThreadTest");
      //test_suite->addTest( new CppUnit::TestCaller<ThreadTest>("interactiveCPUGrind", &ThreadTest::interactiveTestCPUGrind));
      return test_suite;
   }
private:
   
};

};
