/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: testSuite.cpp,v $
 * Date modified: $Date: 2002-06-10 20:16:39 $
 * Version:       $Revision: 1.47 $
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

#include <gmtl/Version.h>

// GMTL tests
#include <TestCases/MathTest.h>

#include <TestCases/VecBaseTest.h>
#include <TestCases/VecTest.h>
#include <TestCases/PointTest.h>
#include <TestCases/SphereTest.h>
#include <TestCases/TriTest.h>
#include <TestCases/PlaneTest.h>
#include <TestCases/LineSegTest.h>

#include <TestCases/MatrixClassTest.h>
#include <TestCases/MatrixCompareTest.h>
#include <TestCases/MatrixOpsTest.h>
#include <TestCases/MatrixGenTest.h>
#include <TestCases/QuatGenTest.h>
#include <TestCases/VecGenTest.h>

#include <TestCases/CoordClassTest.h>
#include <TestCases/CoordCompareTest.h>
#include <TestCases/CoordGenTest.h>


#include <TestCases/QuatClassTest.h>
#include <TestCases/QuatCompareTest.h>
#include <TestCases/QuatStuffTest.h>
#include <TestCases/QuatOpsTest.h>

#include <TestCases/ConvertTest.h>
#include <TestCases/XformTest.h>

#include <TestCases/OutputTest.h>
#include <TestCases/EulerAngleClassTest.h>
#include <TestCases/EulerAngleCompareTest.h>
#include <TestCases/AxisAngleClassTest.h>
//#include <TestCases/AxisAngleCompareTest.h>

#include <TestCases/AABoxTest.h>


#include <TestCases/InfoTests/OptTest.h>

// old tests
//#include <TestCases/Vec3Test.h>
//#include <TestCases/MatrixTest.h>
//#include <TestCases/Point3Test.h>
//#include <TestCases/OOBoxTest.h>
//#include <TestCases/PlaneTest.h>
//#include <TestCases/ContainmentTest.h>
//#include <TestCases/IntersectionTest.h>
//#include <TestCases/TriTest.h>

std::string getHostname(void);

void usage( char** av )
{
   std::cout << "\n\nusage: " << av[0] << " [gmtl|perf|info|all]\n\n" << std::endl;
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

   // Print out what version of GMTL we're testing.
   std::cout<<std::endl;
   std::cout<<"GMTL Version: "<<gmtl::version<<std::endl;
   std::cout<<std::endl;

   //------------------------------------
   //  GMTL Tests
   //------------------------------------
   CppUnit::TextTestRunner runner;


   // Create the tests
   CppUnit::TestSuite* gmtl_suite = new CppUnit::TestSuite("gmtl_suite");

   gmtl_suite->addTest( gmtlTest::MathTest::suite() );
	
   gmtl_suite->addTest( gmtlTest::VecBaseTest::suite() );
   gmtl_suite->addTest( gmtlTest::VecTest::suite() );
   gmtl_suite->addTest( gmtlTest::PointTest::suite() );

   gmtl_suite->addTest( gmtlTest::SphereTest::suite() );
   gmtl_suite->addTest( gmtlTest::TriTest::suite() );
   gmtl_suite->addTest( gmtlTest::PlaneTest::suite() );
   gmtl_suite->addTest( gmtlTest::LineSegTest::suite() );

   gmtl_suite->addTest( gmtlTest::MatrixClassTest::suite() );
   gmtl_suite->addTest( gmtlTest::MatrixCompareTest::suite() );
   gmtl_suite->addTest( gmtlTest::MatrixOpsTest::suite() );
   gmtl_suite->addTest( gmtlTest::MatrixGenTest::suite() );
   gmtl_suite->addTest( gmtlTest::QuatGenTest::suite() );
   gmtl_suite->addTest( gmtlTest::VecGenTest::suite() );

   gmtl_suite->addTest( gmtlTest::CoordClassTest::suite() );
   gmtl_suite->addTest( gmtlTest::CoordCompareTest::suite() );
   gmtl_suite->addTest( gmtlTest::CoordGenTest::suite() );

   gmtl_suite->addTest( gmtlTest::QuatClassTest::suite() );
   gmtl_suite->addTest( gmtlTest::QuatCompareTest::suite() );
   gmtl_suite->addTest( gmtlTest::QuatOpsTest::suite() );
   gmtl_suite->addTest( gmtlTest::QuatStuffTest::suite() );

   gmtl_suite->addTest( gmtlTest::XformTest::suite() );
   gmtl_suite->addTest( gmtlTest::ConvertTest::suite() );

   gmtl_suite->addTest( gmtlTest::OutputTest::suite() );
   gmtl_suite->addTest( gmtlTest::AABoxTest::suite() );
   gmtl_suite->addTest( gmtlTest::EulerAngleClassTest::suite() );
   gmtl_suite->addTest( gmtlTest::EulerAngleCompareTest::suite() );
   gmtl_suite->addTest( gmtlTest::AxisAngleClassTest::suite() );
   //gmtl_suite->addTest( gmtlTest::AxisAngleCompareTest::suite() );

   /*
   gmtl_suite->addTest( gmtlTest::Point3Test::suite() );
   gmtl_suite->addTest( gmtlTest::Vec3Test::suite() );
   gmtl_suite->addTest( gmtlTest::OOBoxTest::suite() );
   gmtl_suite->addTest( gmtlTest::PlaneTest::suite() );
   gmtl_suite->addTest( gmtlTest::ContainmentTest::suite() );
   gmtl_suite->addTest( gmtlTest::IntersectionTest::suite() );
   gmtl_suite->addTest( gmtlTest::TriTest::suite() );
   */

   // setup the perf suite
   CppUnit::TestSuite* perf_suite = new CppUnit::TestSuite( "perf_suite" );
   perf_suite->addTest( gmtlTest::VecBaseTest::perfSuite() );

   perf_suite->addTest( gmtlTest::MatrixClassTest::perfSuite() );
   perf_suite->addTest( gmtlTest::MatrixCompareTest::perfSuite() );
   perf_suite->addTest( gmtlTest::MatrixOpsTest::perfSuite() );
   perf_suite->addTest( gmtlTest::MatrixGenTest::perfSuite() );


   perf_suite->addTest( gmtlTest::CoordClassTest::perfSuite() );
   perf_suite->addTest( gmtlTest::CoordCompareTest::perfSuite() );
   perf_suite->addTest( gmtlTest::CoordGenTest::perfSuite() );

   perf_suite->addTest( gmtlTest::AABoxTest::perfSuite() );

   CppUnit::TestSuite* info_suite = new CppUnit::TestSuite( "info_suite" );
   info_suite->addTest( gmtlTest::OptTest::suite() );

   // Add the tests
   runner.addTest( gmtl_suite );
   runner.addTest( perf_suite );
   runner.addTest( info_suite );

   // --- RUN THEM --- //
   if (ac > 1)
   {
      std::string arg = av[1];
      if (arg.size() > 0 && (arg[0] == 'g' || arg[0] == 'a'))
      {
         std::cout << "running gmtl_suite" << std::endl;
         runner.run( "gmtl_suite" );
      }
      if (arg.size() > 0 && (arg[0] == 'p' || arg[0] == 'a'))
      {
         std::cout << "running perf_suite" << std::endl;
         runner.run( "perf_suite" );
      }
      if (arg.size() > 0 && (arg[0] == 'i' || arg[0] == 'a'))
      {
         std::cout << "running info_suite" << std::endl;
         runner.run( "info_suite" );
      }
   }
   else
   {
      usage( av );
         std::cout << "running gmtl_suite" << std::endl;
      runner.run( "gmtl_suite" );
         std::cout << "running perf_suite" << std::endl;
      runner.run( "perf_suite" );
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
