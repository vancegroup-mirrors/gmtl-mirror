/*************** <auto-copyright.pl BEGIN do not edit this line> **************
 *
 * PyJuggler is (C) Copyright 2002, 2003 by Patrick Hartling
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: _gmtl_functions_h.cpp,v $
 * Date modified: $Date: 2003-08-17 06:32:59 $
 * Version:       $Revision: 1.3 $
 * -----------------------------------------------------------------
 *
 *************** <auto-copyright.pl END do not edit this line> ***************/


// Includes ====================================================================
#include <boost/python.hpp>
#include <gmtl-functions.h>

// Using =======================================================================
using namespace boost::python;

// Declarations ================================================================


namespace  {


BOOST_PYTHON_FUNCTION_OVERLOADS(isEqual_overloads_2_3, gmtl::isEqual, 2, 3)


}// namespace 


// Module ======================================================================
void _Export_gmtl_functions_h()
{
    def("distance", (float (*)(const gmtl::LineSeg<float> &, const gmtl::Point<float,3> &))&gmtl::distance);
    def("distance", (double (*)(const gmtl::LineSeg<double> &, const gmtl::Point<double,3> &))&gmtl::distance);
    def("distance", (double (*)(const gmtl::Plane<double> &, const gmtl::Point<double,3> &))&gmtl::distance);
    def("distance", (float (*)(const gmtl::Plane<float> &, const gmtl::Point<float,3> &))&gmtl::distance);
    def("findNearestPt", (gmtl::Point<float,3> (*)(const gmtl::LineSeg<float> &, const gmtl::Point<float,3> &))&gmtl::findNearestPt);
    def("findNearestPt", (gmtl::Point<double,3> (*)(const gmtl::LineSeg<double> &, const gmtl::Point<double,3> &))&gmtl::findNearestPt);
    def("findNearestPt", (float (*)(const gmtl::Plane<float> &, const gmtl::Point<float,3> &, gmtl::Point<float,3> &))&gmtl::findNearestPt);
    def("findNearestPt", (double (*)(const gmtl::Plane<double> &, const gmtl::Point<double,3> &, gmtl::Point<double,3> &))&gmtl::findNearestPt);
    def("isEqual", (bool (*)(const gmtl::Coord<gmtl::Vec<double, 3>,gmtl::EulerAngle<double, gmtl::XYZ> > &, const gmtl::Coord<gmtl::Vec<double, 3>,gmtl::EulerAngle<double, gmtl::XYZ> > &, double))&gmtl::isEqual, isEqual_overloads_2_3());
    def("isEqual", (bool (*)(const gmtl::Coord<gmtl::Vec<double, 4>,gmtl::AxisAngle<double> > &, const gmtl::Coord<gmtl::Vec<double, 4>,gmtl::AxisAngle<double> > &, double))&gmtl::isEqual, isEqual_overloads_2_3());
    def("isEqual", (bool (*)(const gmtl::Coord<gmtl::Vec<float, 4>,gmtl::AxisAngle<float> > &, const gmtl::Coord<gmtl::Vec<float, 4>,gmtl::AxisAngle<float> > &, float))&gmtl::isEqual, isEqual_overloads_2_3());
    def("isEqual", (bool (*)(const gmtl::Coord<gmtl::Vec<double, 4>,gmtl::Quat<double> > &, const gmtl::Coord<gmtl::Vec<double, 4>,gmtl::Quat<double> > &, double))&gmtl::isEqual, isEqual_overloads_2_3());
    def("isEqual", (bool (*)(const gmtl::Coord<gmtl::Vec<float, 4>,gmtl::Quat<float> > &, const gmtl::Coord<gmtl::Vec<float, 4>,gmtl::Quat<float> > &, float))&gmtl::isEqual, isEqual_overloads_2_3());
    def("isEqual", (bool (*)(const gmtl::Tri<float> &, const gmtl::Tri<float> &, const float &))&gmtl::isEqual);
    def("isEqual", (bool (*)(const gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::ZYX> > &, const gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::ZYX> > &, float))&gmtl::isEqual, isEqual_overloads_2_3());
    def("isEqual", (bool (*)(const gmtl::VecBase<float,3> &, const gmtl::VecBase<float,3> &, const float &))&gmtl::isEqual);
    def("isEqual", (bool (*)(const gmtl::VecBase<double,3> &, const gmtl::VecBase<double,3> &, const double &))&gmtl::isEqual);
    def("isEqual", (bool (*)(const gmtl::Coord<gmtl::Vec<double, 3>,gmtl::EulerAngle<double, gmtl::ZXY> > &, const gmtl::Coord<gmtl::Vec<double, 3>,gmtl::EulerAngle<double, gmtl::ZXY> > &, double))&gmtl::isEqual, isEqual_overloads_2_3());
    def("isEqual", (bool (*)(const gmtl::Coord<gmtl::Vec<double, 3>,gmtl::EulerAngle<double, gmtl::ZYX> > &, const gmtl::Coord<gmtl::Vec<double, 3>,gmtl::EulerAngle<double, gmtl::ZYX> > &, double))&gmtl::isEqual, isEqual_overloads_2_3());
    def("isEqual", (bool (*)(const gmtl::Coord<gmtl::Vec<double, 3>,gmtl::Quat<double> > &, const gmtl::Coord<gmtl::Vec<double, 3>,gmtl::Quat<double> > &, double))&gmtl::isEqual, isEqual_overloads_2_3());
    def("isEqual", (bool (*)(const gmtl::Coord<gmtl::Vec<float, 3>,gmtl::Quat<float> > &, const gmtl::Coord<gmtl::Vec<float, 3>,gmtl::Quat<float> > &, float))&gmtl::isEqual, isEqual_overloads_2_3());
    def("isEqual", (bool (*)(const gmtl::Coord<gmtl::Vec<double, 4>,gmtl::EulerAngle<double, gmtl::ZXY> > &, const gmtl::Coord<gmtl::Vec<double, 4>,gmtl::EulerAngle<double, gmtl::ZXY> > &, double))&gmtl::isEqual, isEqual_overloads_2_3());
    def("isEqual", (bool (*)(const gmtl::Coord<gmtl::Vec<double, 4>,gmtl::EulerAngle<double, gmtl::ZYX> > &, const gmtl::Coord<gmtl::Vec<double, 4>,gmtl::EulerAngle<double, gmtl::ZYX> > &, double))&gmtl::isEqual, isEqual_overloads_2_3());
    def("isEqual", (bool (*)(const gmtl::Coord<gmtl::Vec<double, 4>,gmtl::EulerAngle<double, gmtl::XYZ> > &, const gmtl::Coord<gmtl::Vec<double, 4>,gmtl::EulerAngle<double, gmtl::XYZ> > &, double))&gmtl::isEqual, isEqual_overloads_2_3());
    def("isEqual", (bool (*)(const gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::ZXY> > &, const gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::ZXY> > &, float))&gmtl::isEqual, isEqual_overloads_2_3());
    def("isEqual", (bool (*)(const gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::ZYX> > &, const gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::ZYX> > &, float))&gmtl::isEqual, isEqual_overloads_2_3());
    def("isEqual", (bool (*)(const gmtl::Quat<float> &, const gmtl::Quat<float> &, float))&gmtl::isEqual, isEqual_overloads_2_3());
    def("isEqual", (bool (*)(const gmtl::Quat<double> &, const gmtl::Quat<double> &, double))&gmtl::isEqual, isEqual_overloads_2_3());
    def("isEqual", (bool (*)(const gmtl::VecBase<float,4> &, const gmtl::VecBase<float,4> &, const float &))&gmtl::isEqual);
    def("isEqual", (bool (*)(const gmtl::VecBase<double,4> &, const gmtl::VecBase<double,4> &, const double &))&gmtl::isEqual);
    def("isEqual", (bool (*)(const gmtl::Matrix<float,4,4> &, const gmtl::Matrix<float,4,4> &, const float &))&gmtl::isEqual, isEqual_overloads_2_3());
    def("isEqual", (bool (*)(const gmtl::Matrix<float,3,3> &, const gmtl::Matrix<float,3,3> &, const float &))&gmtl::isEqual, isEqual_overloads_2_3());
    def("isEqual", (bool (*)(const gmtl::Coord<gmtl::Vec<double, 3>,gmtl::AxisAngle<double> > &, const gmtl::Coord<gmtl::Vec<double, 3>,gmtl::AxisAngle<double> > &, double))&gmtl::isEqual, isEqual_overloads_2_3());
    def("isEqual", (bool (*)(const gmtl::Coord<gmtl::Vec<float, 3>,gmtl::AxisAngle<float> > &, const gmtl::Coord<gmtl::Vec<float, 3>,gmtl::AxisAngle<float> > &, float))&gmtl::isEqual, isEqual_overloads_2_3());
    def("isEqual", (bool (*)(const gmtl::AxisAngle<float> &, const gmtl::AxisAngle<float> &, const float &))&gmtl::isEqual, isEqual_overloads_2_3());
    def("isEqual", (bool (*)(const gmtl::AxisAngle<double> &, const gmtl::AxisAngle<double> &, const double &))&gmtl::isEqual, isEqual_overloads_2_3());
    def("isEqual", (bool (*)(const gmtl::EulerAngle<float,gmtl::ZXY> &, const gmtl::EulerAngle<float,gmtl::ZXY> &, const float &))&gmtl::isEqual, isEqual_overloads_2_3());
    def("isEqual", (bool (*)(const gmtl::EulerAngle<float,gmtl::ZYX> &, const gmtl::EulerAngle<float,gmtl::ZYX> &, const float &))&gmtl::isEqual, isEqual_overloads_2_3());
    def("isEqual", (bool (*)(const gmtl::EulerAngle<double,gmtl::XYZ> &, const gmtl::EulerAngle<double,gmtl::XYZ> &, const double &))&gmtl::isEqual, isEqual_overloads_2_3());
    def("isEqual", (bool (*)(const gmtl::EulerAngle<double,gmtl::ZYX> &, const gmtl::EulerAngle<double,gmtl::ZYX> &, const double &))&gmtl::isEqual, isEqual_overloads_2_3());
    def("isEqual", (bool (*)(const gmtl::EulerAngle<double,gmtl::ZXY> &, const gmtl::EulerAngle<double,gmtl::ZXY> &, const double &))&gmtl::isEqual, isEqual_overloads_2_3());
    def("isEqual", (bool (*)(const gmtl::EulerAngle<float,gmtl::XYZ> &, const gmtl::EulerAngle<float,gmtl::XYZ> &, const float &))&gmtl::isEqual, isEqual_overloads_2_3());
    def("isEqual", (bool (*)(const gmtl::AABox<double> &, const gmtl::AABox<double> &, const double &))&gmtl::isEqual);
    def("isEqual", (bool (*)(const gmtl::AABox<float> &, const gmtl::AABox<float> &, const float &))&gmtl::isEqual);
    def("isEqual", (bool (*)(const gmtl::Sphere<float> &, const gmtl::Sphere<float> &, const float &))&gmtl::isEqual);
    def("isEqual", (bool (*)(const gmtl::Sphere<double> &, const gmtl::Sphere<double> &, const double &))&gmtl::isEqual);
    def("isEqual", (bool (*)(const gmtl::Tri<double> &, const gmtl::Tri<double> &, const double &))&gmtl::isEqual);
    def("isEqual", (bool (*)(const gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::XYZ> > &, const gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::XYZ> > &, float))&gmtl::isEqual, isEqual_overloads_2_3());
    def("isEqual", (bool (*)(const gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::ZXY> > &, const gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::ZXY> > &, float))&gmtl::isEqual, isEqual_overloads_2_3());
    def("isEqual", (bool (*)(const gmtl::Plane<float> &, const gmtl::Plane<float> &, const float &))&gmtl::isEqual);
    def("isEqual", (bool (*)(const gmtl::Plane<double> &, const gmtl::Plane<double> &, const double &))&gmtl::isEqual);
    def("isEqual", (bool (*)(const gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::XYZ> > &, const gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::XYZ> > &, float))&gmtl::isEqual, isEqual_overloads_2_3());
}
