/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: OptTest.h,v $
 * Date modified: $Date: 2002-02-11 18:20:00 $
 * Version:       $Revision: 1.6 $
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

   ArrayVec3& operator+=( ArrayVec3& lhs, const ArrayVec3& rhs )
   {
      lhs.vec[0] += rhs.vec[0];
      lhs.vec[1] += rhs.vec[1];
      lhs.vec[2] += rhs.vec[2];
      return lhs;
   }  
   ArrayVec3& inplaceModify( ArrayVec3& lhs )
   {
      lhs.vec[0] += lhs.vec[0];
      lhs.vec[1] += lhs.vec[1];
      lhs.vec[2] += lhs.vec[2];
      return lhs;
   }
   ArrayVec3& setEqual( ArrayVec3& lhs, const ArrayVec3& rhs )
   {
      lhs.vec[0] = rhs.vec[0];
      lhs.vec[1] = rhs.vec[1];
      lhs.vec[2] = rhs.vec[2];
      return lhs;
   }
   ArrayVec3& setEqualConst( ArrayVec3& lhs )
   {
      lhs.vec[0] = 0.0f;
      lhs.vec[1] = 0.0f;
      lhs.vec[2] = 0.0f;
      return lhs;
   }  
   ArrayVec3 retvalopt( const ArrayVec3& lhs, const ArrayVec3& rhs )
   {
      return ArrayVec3( lhs.vec[0] + rhs.vec[0], lhs.vec[1] + rhs.vec[1], lhs.vec[2] + rhs.vec[2] );
   }
   ArrayVec3 noretvalopt( const ArrayVec3& lhs, const ArrayVec3& rhs )
   {
      ArrayVec3 temporary;
      temporary.vec[0] = lhs.vec[0] + rhs.vec[0];
      temporary.vec[1] = lhs.vec[1] + rhs.vec[1];
      temporary.vec[2] = lhs.vec[2] + rhs.vec[2];
      return temporary;
   }
   void retbyref( ArrayVec3& result, const ArrayVec3& lhs, const ArrayVec3& rhs )
   {
      result.vec[0] = lhs.vec[0] + rhs.vec[0];
      result.vec[1] = lhs.vec[1] + rhs.vec[1];
      result.vec[2] = lhs.vec[2] + rhs.vec[2];
   }
   ArrayVec3 retvalInternalTemporary( const ArrayVec3& lhs, const ArrayVec3& rhs )
   {
      ArrayVec3 temporary;
      temporary.vec[0] = lhs.vec[0] + rhs.vec[0];
      temporary.vec[1] = lhs.vec[1] + rhs.vec[1];
      temporary.vec[2] = lhs.vec[2] + rhs.vec[2];
      return temporary;
   }
   
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

   SeparateVec3& setEqual( SeparateVec3& lhs, const SeparateVec3& rhs )
   {
      lhs.vec0 = rhs.vec0;
      lhs.vec1 = rhs.vec1;
      lhs.vec2 = rhs.vec2;
      return lhs;
   }  
   SeparateVec3& setEqualConst( SeparateVec3& lhs )
   {
      lhs.vec0 = 0.0f;
      lhs.vec1 = 0.0f;
      lhs.vec2 = 0.0f;
      return lhs;
   }  
   SeparateVec3& inplaceModify( SeparateVec3& lhs )
   {
      lhs.vec0 += lhs.vec0;
      lhs.vec1 += lhs.vec1;
      lhs.vec2 += lhs.vec2;
      return lhs;
   }
   SeparateVec3& operator+=( SeparateVec3& lhs, const SeparateVec3& rhs )
   {
      lhs.vec0 += rhs.vec0;
      lhs.vec1 += rhs.vec1;
      lhs.vec2 += rhs.vec2;
      return lhs;
   }   
   SeparateVec3 retvalopt( const SeparateVec3& lhs, const SeparateVec3& rhs )
   {
      return SeparateVec3( lhs.vec0 + rhs.vec0, lhs.vec1 + rhs.vec1, lhs.vec2 + rhs.vec2 );
   }
   SeparateVec3 retvalInternalTemporary( const SeparateVec3& lhs, const SeparateVec3& rhs )
   {
      SeparateVec3 temporary;
      temporary.vec0 = lhs.vec0 + rhs.vec0;
      temporary.vec1 = lhs.vec1 + rhs.vec1;
      temporary.vec2 = lhs.vec2 + rhs.vec2;
      return temporary;
   }
   void retbyref( SeparateVec3& result, const SeparateVec3& lhs, const SeparateVec3& rhs )
   {
      result.vec0 = lhs.vec0 + rhs.vec0;
      result.vec1 = lhs.vec1 + rhs.vec1;
      result.vec2 = lhs.vec2 + rhs.vec2;
   }
   const int TIMES_TO_RUN = 9999999;
      
   // this might be better, but it wont compile... :(
   //   SeparateVec3 retvalopt2( const SeparateVec3& lhs, const SeparateVec3& rhs )
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

   // this simulates the invert or normalize func
   // two possibilities:
   //    invert( srcAndResult )
   //    invert( result, source )
   // 
   void testInPlace()
   {
      SeparateVec3 destvec;
      std::cout << std::endl << "test perf of in-place modification of destvec param (no temporary)" << std::endl;

      // operate on some value in place (uses = and +
      // inplaceModify( result );
      {
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            inplaceModify( destvec );
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         std::cout << "\n[s]testInPlace (inplaceModify( destvec );): " << end_t - start_t << std::endl;
      }
      {
         ArrayVec3 destvec;
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            inplaceModify( destvec );
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         std::cout << "[a]testInPlace (inplaceModify( destvec );): " << end_t - start_t << std::endl;
      }
      
      // do operation to temp
      // operator+=( result, v1 );
      {
         SeparateVec3 srcvec;
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            operator+=( destvec, srcvec );
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         std::cout << "\n[s]testInPlace (operator+=( destvec, srcvec );): " << end_t - start_t << std::endl;
      }
      {
         ArrayVec3 destvec;
         ArrayVec3 srcvec;
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            operator+=( destvec, srcvec );
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         std::cout << "[a]testInPlace (operator+=( destvec, srcvec );): " << end_t - start_t << std::endl;
      }
   }
   
   // test perf of copy ops
   void testSetEqual()
   {
      SeparateVec3 destvec;
      SeparateVec3 srcvec1, srcvec2;
      std::cout << std::endl << "test perf of copy ops" << std::endl;

      // set destvec from const values
      // setEqualConst( result );
      {
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            setEqualConst( destvec );
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         std::cout << "\n[s]testSetEqual (setEqualConst( destvec );): " << end_t - start_t << std::endl;
      }
      {
         ArrayVec3 destvec;
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            setEqualConst( destvec );
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         std::cout << "[a]testSetEqual (setEqualConst( destvec );): " << end_t - start_t << std::endl;
      }
      
      // use our setEqual func to copy
      // setEqual( result, v1 )
      {
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            setEqual( destvec, srcvec1 );
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         std::cout << "\n[s]testSetEqual (setEqual( destvec, srcvec1 ) ): " << end_t - start_t << std::endl;
      }
      {
         ArrayVec3 destvec;
         ArrayVec3 srcvec1, srcvec2;
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            setEqual( destvec, srcvec1 );
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         std::cout << "[a]testSetEqual (setEqual( destvec, srcvec1 )): " << end_t - start_t << std::endl;
      }
      
      // let compiler make the operator=
      {
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            destvec = srcvec1;
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         std::cout << "\n[s]testSetEqual (destvec = srcvec1 from compiler): " << end_t - start_t << std::endl;
      }
      {
         ArrayVec3 destvec;
         ArrayVec3 srcvec1, srcvec2;
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            destvec = srcvec1;
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         std::cout << "[a]testSetEqual (destvec = srcvec1 from compiler): " << end_t - start_t << std::endl;
      }
   }
   
   // test perf of returning result by reference (no temporary)
   void testRetByReference()
   {
      SeparateVec3 destvec;
      SeparateVec3 srcvec1, srcvec2;
      std::cout << std::endl << "test perf of returning result by reference (no temporary)" << std::endl;

      {
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            destvec += srcvec1;
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         std::cout << "\n[s]testRetValOpt (destvec += srcvec1): " << end_t - start_t << std::endl;
      }
      {
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            destvec = srcvec1; destvec += srcvec2;
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         std::cout << "[s]testRetValOpt (destvec = srcvec1; destvec += srcvec2): " << end_t - start_t << std::endl;
      }
      {
         ArrayVec3 destvec;
         ArrayVec3 srcvec1, srcvec2;
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            destvec = srcvec1; destvec += srcvec2;
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         std::cout << "[a]testRetValOpt (destvec = srcvec1; destvec += srcvec2): " << end_t - start_t << std::endl;
      }
   }
   
   // test perf of returning internal temporary by value
   void testRetValOptUsingInternalTemporary()
   {
      SeparateVec3 destvec;
      SeparateVec3 srcvec1, srcvec2;
      std::cout << std::endl << "test perf of returning internal temporary by value" << std::endl;

      {
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            destvec = retvalInternalTemporary( srcvec1, srcvec2 );
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         std::cout << "\n[s]testRetValOpt (destvec = srcvec1 + srcvec2 with noretvalopt): " << end_t - start_t << std::endl;
      }
      {
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            destvec = retvalInternalTemporary( destvec, destvec );
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         std::cout << "[s]testRetValOpt (destvec = destvec + srcvec2 with noretvalopt): " << end_t - start_t << std::endl;
      }
      {
         ArrayVec3 destvec;
         ArrayVec3 srcvec1, srcvec2;
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            destvec = retvalInternalTemporary( destvec, srcvec2 );
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         std::cout << "[a]testRetValOpt (destvec = destvec + srcvec2 with noretvalopt): " << end_t - start_t << std::endl;
      }
   }
   
   // test perf of the the return value optimization when returning a temporary by value
   void testRetValOpt()
   {
      SeparateVec3 destvec;
      SeparateVec3 srcvec1, srcvec2;
      std::cout << std::endl << "test perf of ret val opt when returning a temporary by value" << std::endl;

      // return by reference
      // retbyref( result, v1, v2 );
      {
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            retbyref( destvec, srcvec1, srcvec2 );
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         std::cout << "\n[s]testRetValOpt (destvec = srcvec1 + srcvec2 with retbyref): " << end_t - start_t << std::endl;
      }
      {
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            retbyref( destvec, destvec, destvec );
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         std::cout << "[s]testRetValOpt (destvec = destvec + srcvec2 with retbyref): " << end_t - start_t << std::endl;
      }
      {
         ArrayVec3 destvec;
         ArrayVec3 srcvec1, srcvec2;
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            retbyref( destvec, destvec, srcvec2 );
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         std::cout << "[a]testRetValOpt (destvec = destvec + srcvec2 with retbyref): " << end_t - start_t << std::endl;
      }
      
      // return by reference
      // result = retvalopt( v1, v2 );
      {
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            destvec = retvalopt( srcvec1, srcvec2 );
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         std::cout << "\n[s]testRetValOpt (destvec = srcvec1 + srcvec2 with retvalopt): " << end_t - start_t << std::endl;
      }
      {
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            destvec = retvalopt( destvec, destvec );
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         std::cout << "[s]testRetValOpt (destvec = destvec + srcvec2 with retvalopt): " << end_t - start_t << std::endl;
      }
      {
         ArrayVec3 destvec;
         ArrayVec3 srcvec1, srcvec2;
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            destvec = retvalopt( destvec, srcvec2 );
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         std::cout << "[a]testRetValOpt (destvec = destvec + srcvec2 with retvalopt): " << end_t - start_t << std::endl;
      }
   }
   
   
   
   // test performance of loop unrolling
   void testLoopUnrolling()
   {
      ArrayVec3 destvec;
      ArrayVec3 srcvec;
      std::cout << std::endl << "test performance of manual loop unrolling" << std::endl;

      {
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            for (int y = 0; y < 3; ++y)
            {
               destvec.vec[y] += srcvec.vec[y];
            }
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         std::cout << "\n[a]testLoopUnrolling (forloop ++y): " << end_t - start_t << std::endl;
      }
      
      {
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            for (int y = 0; y < 3; y++)
            {
               destvec.vec[y] += srcvec.vec[y];
            }
         }
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         std::cout << "[a]testLoopUnrolling (forloop y++): " << end_t - start_t << std::endl;
      }
      
      {
         CppUnit::MetricRegistry::TimeStamp start_t = CppUnit::MetricRegistry::instance()->getCurTime();
         for (int x = 0; x < TIMES_TO_RUN; ++x)
         {
            destvec.vec[0] += srcvec.vec[0];
            destvec.vec[1] += srcvec.vec[1];
            destvec.vec[2] += srcvec.vec[2];
         }  
         CppUnit::MetricRegistry::TimeStamp end_t = CppUnit::MetricRegistry::instance()->getCurTime();
         std::cout << "[a]testLoopUnrolling (unrolled): " << end_t - start_t << std::endl;
      }
   }
   
   

   static Test* suite()
   {
      CppUnit::TestSuite* test_suite = new CppUnit::TestSuite ("OptTest");
      test_suite->addTest( new CppUnit::TestCaller<OptTest>("testInPlace", &OptTest::testInPlace));
      test_suite->addTest( new CppUnit::TestCaller<OptTest>("testSetEqual", &OptTest::testSetEqual));
      test_suite->addTest( new CppUnit::TestCaller<OptTest>("testRetByReference", &OptTest::testRetByReference));
      test_suite->addTest( new CppUnit::TestCaller<OptTest>("testRetValOptUsingInternalTemporary", &OptTest::testRetValOptUsingInternalTemporary));
      test_suite->addTest( new CppUnit::TestCaller<OptTest>("testRetValOpt", &OptTest::testRetValOpt));
      test_suite->addTest( new CppUnit::TestCaller<OptTest>("testLoopUnrolling", &OptTest::testLoopUnrolling));
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
