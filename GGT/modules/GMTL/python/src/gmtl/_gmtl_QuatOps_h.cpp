/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: _gmtl_QuatOps_h.cpp,v $
 * Date modified: $Date: 2003-08-30 17:22:10 $
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

// Includes ====================================================================
#include <boost/python.hpp>
#include <gmtl-QuatOps.h>

// Using =======================================================================
using namespace boost::python;

// Declarations ================================================================


namespace  {


BOOST_PYTHON_FUNCTION_OVERLOADS(isEquiv_overloads_2_3, gmtl::isEquiv, 2, 3)
BOOST_PYTHON_FUNCTION_OVERLOADS(slerp_overloads_4_5, gmtl::slerp, 4, 5)
BOOST_PYTHON_FUNCTION_OVERLOADS(isEqual_overloads_2_3, gmtl::isEqual, 2, 3)


}// namespace 


// Module ======================================================================
void _Export_gmtl_QuatOps_h()
{
    def("conj", (gmtl::Quat<float> & (*)(gmtl::Quat<float> &))&gmtl::conj, return_internal_reference< 1 >());
    def("conj", (gmtl::Quat<double> & (*)(gmtl::Quat<double> &))&gmtl::conj, return_internal_reference< 1 >());
    def("div", (gmtl::Quat<float> & (*)(gmtl::Quat<float> &, const gmtl::Quat<float> &, gmtl::Quat<float>))&gmtl::div, return_internal_reference< 1 >());
    def("div", (gmtl::Quat<float> & (*)(gmtl::Quat<float> &, const gmtl::Quat<float> &, float))&gmtl::div, return_internal_reference< 1 >());
    def("div", (gmtl::Quat<double> & (*)(gmtl::Quat<double> &, const gmtl::Quat<double> &, gmtl::Quat<double>))&gmtl::div, return_internal_reference< 1 >());
    def("div", (gmtl::Quat<double> & (*)(gmtl::Quat<double> &, const gmtl::Quat<double> &, double))&gmtl::div, return_internal_reference< 1 >());
    def("exp", (gmtl::Quat<float> & (*)(gmtl::Quat<float> &))&gmtl::exp, return_internal_reference< 1 >());
    def("exp", (gmtl::Quat<double> & (*)(gmtl::Quat<double> &))&gmtl::exp, return_internal_reference< 1 >());
    def("invert", (gmtl::Quat<double> & (*)(gmtl::Quat<double> &))&gmtl::invert, return_internal_reference< 1 >());
    def("invert", (gmtl::Quat<float> & (*)(gmtl::Quat<float> &))&gmtl::invert, return_internal_reference< 1 >());
    def("isEquiv", (bool (*)(const gmtl::Quat<double> &, const gmtl::Quat<double> &, double))&gmtl::isEquiv, isEquiv_overloads_2_3());
    def("isEquiv", (bool (*)(const gmtl::Quat<float> &, const gmtl::Quat<float> &, float))&gmtl::isEquiv, isEquiv_overloads_2_3());
    def("log", (gmtl::Quat<double> & (*)(gmtl::Quat<double> &))&gmtl::log, return_internal_reference< 1 >());
    def("log", (gmtl::Quat<float> & (*)(gmtl::Quat<float> &))&gmtl::log, return_internal_reference< 1 >());
    def("negate", (gmtl::Quat<float> & (*)(gmtl::Quat<float> &))&gmtl::negate, return_internal_reference< 1 >());
    def("negate", (gmtl::Quat<double> & (*)(gmtl::Quat<double> &))&gmtl::negate, return_internal_reference< 1 >());
    def("slerp", (gmtl::Quat<double> & (*)(gmtl::Quat<double> &, const double, const gmtl::Quat<double> &, const gmtl::Quat<double> &, bool))&gmtl::slerp, return_internal_reference< 1 >(), slerp_overloads_4_5());
    def("slerp", (gmtl::Quat<float> & (*)(gmtl::Quat<float> &, const float, const gmtl::Quat<float> &, const gmtl::Quat<float> &, bool))&gmtl::slerp, return_internal_reference< 1 >(), slerp_overloads_4_5());
    def("squad", (void (*)(gmtl::Quat<float> &, float, const gmtl::Quat<float> &, const gmtl::Quat<float> &, const gmtl::Quat<float> &, const gmtl::Quat<float> &))&gmtl::squad, return_internal_reference< 1 >());
    def("squad", (void (*)(gmtl::Quat<double> &, double, const gmtl::Quat<double> &, const gmtl::Quat<double> &, const gmtl::Quat<double> &, const gmtl::Quat<double> &))&gmtl::squad, return_internal_reference< 1 >());
    def("isEqual", (bool (*)(const gmtl::Quat<float> &, const gmtl::Quat<float> &, float))&gmtl::isEqual, isEqual_overloads_2_3());
    def("isEqual", (bool (*)(const gmtl::Quat<double> &, const gmtl::Quat<double> &, double))&gmtl::isEqual, isEqual_overloads_2_3());
}
