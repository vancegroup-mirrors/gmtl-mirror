/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: testSuite.cpp,v $
 * Date modified: $Date: 2002-02-21 23:19:14 $
 * Version:       $Revision: 1.20 $
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

//------------------------------------------------------
// Test suite for GMTL
//
// This is designed to test EVERY capability of GMTL
//
//------------------------------------------------------

#include <cppunit/TestSuite.h>
#include <cppunit/TextTestRunner.h>
#include <cppunit/extensions/MetricRegistry.h>

// GMTL tests
#include <gmtl/gmtlConfig.h>
#include <TestCases/VecBaseTest.h>
#include <TestCases/VecTest.h>
#include <TestCases/PointTest.h>
#include <TestCases/SphereTest.h>
#include <TestCases/TriTest.h>
#include <TestCases/PlaneTest.h>

// old tests
#include <TestCases/Vec3Test.h>
//#include <TestCases/MatrixTest.h>
#include <TestCases/MatrixClassTest.h>
#include <TestCases/MatrixCompareTest.h>
#include <TestCases/MatrixOpsTest.h>
#include <TestCases/MatrixGenTest.h>
#include <TestCases/Point3Test.h>
//#include <TestCases/XformTest.h>
//#include <TestCases/OOBoxTest.h>
//#include <TestCases/PlaneTest.h>
//#include <TestCases/ContainmentTest.h>
//#include <TestCases/IntersectionTest.h>
#include <TestCases/QuatClassTest.h>
#include <TestCases/QuatCompareTest.h>
//#include <TestCases/TriTest.h>
#include <TestCases/InfoTests/OptTest.h>

std::string getHostname(void);

void usage( char** av )
{
   std::cout << "\n\nusage: " << av[0] << " [gmtl|info|all]\n\n" << std::endl;
}

int main (int ac, char **av)
{

   // -------- CONFIGURE METRIC REGISTRY ------- //
   CppUnit::MetricRegistry* metric_reg = CppUnit::MetricRegistry::instance();
   std::string metric_prefix;    // Prefix for all metric labels (mode/hostname)

   std::string host_name = getHostname();
   metric_prefix = host_name + "/";
#ifdef _DEBUG
   metric_prefix += "Debug/";
#endif
#ifdef _OPT
   metric_prefix += "Opt/";
#endif

   std::cout << " host: " << host_name << " prefix: "  << metric_prefix << std::endl;

   metric_reg->setPrefix(metric_prefix);
   metric_reg->setFilename("gmtl_metrics.txt");
   metric_reg->setMetric("Main/MetricTest", 1221.75f);


   //------------------------------------
   //  GMTL Tests
   //------------------------------------
   CppUnit::TextTestRunner runner;


   // Create the tests
   CppUnit::TestSuite* gmtl_suite = new CppUnit::TestSuite("gmtl_suite");
	
   gmtl_suite->addTest(gmtlTest::VecBaseTest::suite());
   gmtl_suite->addTest(gmtlTest::VecTest::suite());
   gmtl_suite->addTest(gmtlTest::PointTest::suite());
   gmtl_suite->addTest(gmtlTest::SphereTest::suite());
   gmtl_suite->addTest(gmtlTest::TriTest::suite());
   gmtl_suite->addTest(gmtlTest::PlaneTest::suite());

   gmtl_suite->addTest(gmtlTest::Vec3Test::suite());
   gmtl_suite->addTest(gmtlTest::MatrixClassTest::suite());
   gmtl_suite->addTest(gmtlTest::MatrixCompareTest::suite());
   gmtl_suite->addTest(gmtlTest::MatrixOpsTest::suite());
   gmtl_suite->addTest(gmtlTest::MatrixGenTest::suite());
   gmtl_suite->addTest(gmtlTest::Point3Test::suite());
   gmtl_suite->addTest(gmtlTest::QuatClassTest::suite());
   gmtl_suite->addTest(gmtlTest::QuatCompareTest::suite());
   /*
   gmtl_suite->addTest( gmtlTest::XformTest::suite() );
   gmtl_suite->addTest( gmtlTest::OOBoxTest::suite() );
   gmtl_suite->addTest( gmtlTest::PlaneTest::suite() );
   gmtl_suite->addTest( gmtlTest::ContainmentTest::suite() );
   gmtl_suite->addTest( gmtlTest::IntersectionTest::suite() );
   gmtl_suite->addTest( gmtlTest::TriTest::suite() );
   */
   CppUnit::TestSuite* info_suite = new CppUnit::TestSuite( "info_suite" );
   info_suite->addTest( gmtlTest::OptTest::suite() );

   // Add the tests
   runner.addTest( gmtl_suite );
   runner.addTest( info_suite );

   // --- RUN THEM --- //
   if (ac > 1)
   {
      std::string arg = av[1];
      if (arg.size() > 0 && (arg[0] == 'i' || arg[0] == 'a'))
         runner.run( "info_suite" );
      if (arg.size() > 0 && (arg[0] == 'g' || arg[0] == 'a'))
         runner.run( "gmtl_suite" );
   }
   else
   {
      usage( av );
      runner.run( "gmtl_suite" );
      usage( av );
   }   

   return 0;
}


#include <sys/utsname.h>

std::string getHostname(void)
{
   struct utsname buffer;

   if ( uname(&buffer) == 0 )
   {
      char* temp;
      temp = strchr(buffer.nodename, '.');

      // If the node name contains the full host, dots and all, truncate it
      // at the first dot.
      if ( temp != NULL )
      {
         *temp = '\0';
      }

      return std::string(buffer.nodename);
   }
   else
   {
      return std::string("<hostname-lookup failed>");
   }
}
