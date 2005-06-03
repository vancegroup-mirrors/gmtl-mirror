/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: _gmtl_Generate_h.cpp,v $
 * Date modified: $Date: 2005-06-03 22:51:40 $
 * Version:       $Revision: 1.5 $
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
#include <gmtl-Generate.h>

// Using =======================================================================
using namespace boost::python;

// Declarations ================================================================


namespace gmtlWrappers
{

// These wrappers around gmtl::setDirCos() are needed because we lose the
// ability to have default function arguments otherwise.  When defining the
// functions below, we would have to use casting to distinguish between the
// different overloads of gmtl::setDirCos(), but in so doing, we lose the
// default function arguments.  These thin wrappers allow gmtl::setDirCos()
// to be used from Python with its default arguments as intended.
gmtl::Matrix33f& setDirCosMatrix33f(gmtl::Matrix33f& m, const gmtl::Vec3f& v0,
                                    const gmtl::Vec3f& v1,
                                    const gmtl::Vec3f& v2,
                                    const gmtl::Vec3f& v3 = gmtl::Vec3f(1.0f, 0.0f, 0.0f),
                                    const gmtl::Vec3f& v4 = gmtl::Vec3f(0.0f, 1.0f, 0.0f),
                                    const gmtl::Vec3f& v5 = gmtl::Vec3f(0.0f, 0.0f, 1.0f))
{
   return gmtl::setDirCos(m, v0, v1, v2, v3, v4, v5);
}

gmtl::Matrix33d& setDirCosMatrix33d(gmtl::Matrix33d& m, const gmtl::Vec3d& v0,
                                    const gmtl::Vec3d& v1,
                                    const gmtl::Vec3d& v2,
                                    const gmtl::Vec3d& v3 = gmtl::Vec3d(1.0f, 0.0f, 0.0f),
                                    const gmtl::Vec3d& v4 = gmtl::Vec3d(0.0f, 1.0f, 0.0f),
                                    const gmtl::Vec3d& v5 = gmtl::Vec3d(0.0f, 0.0f, 1.0f))
{
   return gmtl::setDirCos(m, v0, v1, v2, v3, v4, v5);
}

gmtl::Matrix44f& setDirCosMatrix44f(gmtl::Matrix44f& m, const gmtl::Vec3f& v0,
                                    const gmtl::Vec3f& v1,
                                    const gmtl::Vec3f& v2,
                                    const gmtl::Vec3f& v3 = gmtl::Vec3f(1.0f, 0.0f, 0.0f),
                                    const gmtl::Vec3f& v4 = gmtl::Vec3f(0.0f, 1.0f, 0.0f),
                                    const gmtl::Vec3f& v5 = gmtl::Vec3f(0.0f, 0.0f, 1.0f))
{
   return gmtl::setDirCos(m, v0, v1, v2, v3, v4, v5);
}

gmtl::Matrix44d& setDirCosMatrix44d(gmtl::Matrix44d& m, const gmtl::Vec3d& v0,
                                    const gmtl::Vec3d& v1,
                                    const gmtl::Vec3d& v2,
                                    const gmtl::Vec3d& v3 = gmtl::Vec3d(1.0f, 0.0f, 0.0f),
                                    const gmtl::Vec3d& v4 = gmtl::Vec3d(0.0f, 1.0f, 0.0f),
                                    const gmtl::Vec3d& v5 = gmtl::Vec3d(0.0f, 0.0f, 1.0f))
{
   return gmtl::setDirCos(m, v0, v1, v2, v3, v4, v5);
}

}


namespace  {


BOOST_PYTHON_FUNCTION_OVERLOADS(setDirCosMatrix33f_overloads_4_7,
                                gmtlWrappers::setDirCosMatrix33f, 4, 7)
BOOST_PYTHON_FUNCTION_OVERLOADS(setDirCosMatrix33d_overloads_4_7,
                                gmtlWrappers::setDirCosMatrix33d, 4, 7)
BOOST_PYTHON_FUNCTION_OVERLOADS(setDirCosMatrix44f_overloads_4_7,
                                gmtlWrappers::setDirCosMatrix44f, 4, 7)
BOOST_PYTHON_FUNCTION_OVERLOADS(setDirCosMatrix44d_overloads_4_7,
                                gmtlWrappers::setDirCosMatrix44d, 4, 7)


}// namespace 


// Module ======================================================================
void _Export_gmtl_Generate_h()
{
    def("makeConj", (gmtl::Quat<double> (*)(const gmtl::Quat<double> &))&gmtl::makeConj);
    def("makeConj", (gmtl::Quat<float> (*)(const gmtl::Quat<float> &))&gmtl::makeConj);
    def("makeCross", (gmtl::Vec<int,3> (*)(const gmtl::Vec<int,3> &, const gmtl::Vec<int,3> &))&gmtl::makeCross);
    def("makeCross", (gmtl::Vec<float,3> (*)(const gmtl::Vec<float,3> &, const gmtl::Vec<float,3> &))&gmtl::makeCross);
    def("makeCross", (gmtl::Vec<double,3> (*)(const gmtl::Vec<double,3> &, const gmtl::Vec<double,3> &))&gmtl::makeCross);
    def("makeInvert", (gmtl::Quat<float> (*)(const gmtl::Quat<float> &))&gmtl::makeInvert);
    def("makeInvert", (gmtl::Quat<double> (*)(const gmtl::Quat<double> &))&gmtl::makeInvert);
    def("makeInvert", (gmtl::Matrix<double,4,4> (*)(const gmtl::Matrix<double,4,4> &))&gmtl::makeInvert);
    def("makeInvert", (gmtl::Matrix<float,3,3> (*)(const gmtl::Matrix<float,3,3> &))&gmtl::makeInvert);
    def("makeInvert", (gmtl::Matrix<float,4,4> (*)(const gmtl::Matrix<float,4,4> &))&gmtl::makeInvert);
    def("makeInvert", (gmtl::Matrix<double,3,3> (*)(const gmtl::Matrix<double,3,3> &))&gmtl::makeInvert);
    def("makeNormal", (gmtl::Quat<float> (*)(const gmtl::Quat<float> &))&gmtl::makeNormal);
    def("makeNormal", (gmtl::Quat<double> (*)(const gmtl::Quat<double> &))&gmtl::makeNormal);
    def("makeNormal", (gmtl::Vec<float,4> (*)(gmtl::Vec<float,4>))&gmtl::makeNormal);
    def("makeNormal", (gmtl::Vec<float,3> (*)(gmtl::Vec<float,3>))&gmtl::makeNormal);
    def("makeNormal", (gmtl::Vec<double,3> (*)(gmtl::Vec<double,3>))&gmtl::makeNormal);
    def("makeNormal", (gmtl::AxisAngle<float> (*)(const gmtl::AxisAngle<float> &))&gmtl::makeNormal);
    def("makeNormal", (gmtl::AxisAngle<double> (*)(const gmtl::AxisAngle<double> &))&gmtl::makeNormal);
    def("makePure", (gmtl::Quat<float> (*)(const gmtl::Vec<float,3> &))&gmtl::makePure);
    def("makePure", (gmtl::Quat<double> (*)(const gmtl::Vec<double,3> &))&gmtl::makePure);
    def("makeTranspose", (gmtl::Matrix<float,3,3> (*)(const gmtl::Matrix<float,3,3> &))&gmtl::makeTranspose);
    def("makeTranspose", (gmtl::Matrix<float,4,4> (*)(const gmtl::Matrix<float,4,4> &))&gmtl::makeTranspose);
    def("makeTranspose", (gmtl::Matrix<double,3,3> (*)(const gmtl::Matrix<double,3,3> &))&gmtl::makeTranspose);
    def("makeTranspose", (gmtl::Matrix<double,4,4> (*)(const gmtl::Matrix<double,4,4> &))&gmtl::makeTranspose);
    def("makeVec", (gmtl::Vec<float,3> (*)(const gmtl::Quat<float> &))&gmtl::makeVec);
    def("makeVec", (gmtl::Vec<double,3> (*)(const gmtl::Quat<double> &))&gmtl::makeVec);
    def("makeXRot", (float (*)(const gmtl::Matrix<float,3,3> &))&gmtl::makeXRot);
    def("makeXRot", (float (*)(const gmtl::Matrix<float,4,4> &))&gmtl::makeXRot);
    def("makeXRot", (double (*)(const gmtl::Matrix<double,3,3> &))&gmtl::makeXRot);
    def("makeXRot", (double (*)(const gmtl::Matrix<double,4,4> &))&gmtl::makeXRot);
    def("makeYRot", (float (*)(const gmtl::Matrix<float,4,4> &))&gmtl::makeYRot);
    def("makeYRot", (double (*)(const gmtl::Matrix<double,3,3> &))&gmtl::makeYRot);
    def("makeYRot", (float (*)(const gmtl::Matrix<float,3,3> &))&gmtl::makeYRot);
    def("makeYRot", (double (*)(const gmtl::Matrix<double,4,4> &))&gmtl::makeYRot);
    def("makeZRot", (float (*)(const gmtl::Matrix<float,3,3> &))&gmtl::makeZRot);
    def("makeZRot", (double (*)(const gmtl::Matrix<double,3,3> &))&gmtl::makeZRot);
    def("makeZRot", (float (*)(const gmtl::Matrix<float,4,4> &))&gmtl::makeZRot);
    def("makeZRot", (double (*)(const gmtl::Matrix<double,4,4> &))&gmtl::makeZRot);
    def("set", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::ZYX> > &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::XYZ> > &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::ZXY> > &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::ZYX> > &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::ZXY> > &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::ZYX> > &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::XYZ> > &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::ZXY> > &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::XYZ> > &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::XYZ> > &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::ZYX> > &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Coord<gmtl::Vec<float, 3>,gmtl::Quat<float> > & (*)(gmtl::Coord<gmtl::Vec<float, 3>,gmtl::Quat<float> > &, const gmtl::Matrix<float,4,4> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::ZXY> > & (*)(gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::ZXY> > &, const gmtl::Matrix<float,3,3> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::ZYX> > & (*)(gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::ZYX> > &, const gmtl::Matrix<float,3,3> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::XYZ> > & (*)(gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::XYZ> > &, const gmtl::Matrix<float,3,3> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<double,4,4> & (*)(gmtl::Matrix<double,4,4> &, const gmtl::Quat<double> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::Quat<float> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::Coord<gmtl::Vec<float, 4>,gmtl::AxisAngle<float> > &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::Quat<float> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::ZYX> > & (*)(gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::ZYX> > &, const gmtl::Matrix<float,3,3> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::XYZ> > & (*)(gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::XYZ> > &, const gmtl::Matrix<float,3,3> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::ZXY> > & (*)(gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::ZXY> > &, const gmtl::Matrix<float,3,3> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::XYZ> > & (*)(gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::XYZ> > &, const gmtl::Matrix<float,4,4> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Coord<gmtl::Vec<float, 3>,gmtl::Quat<float> > & (*)(gmtl::Coord<gmtl::Vec<float, 3>,gmtl::Quat<float> > &, const gmtl::Matrix<float,3,3> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Coord<gmtl::Vec<float, 4>,gmtl::Quat<float> > & (*)(gmtl::Coord<gmtl::Vec<float, 4>,gmtl::Quat<float> > &, const gmtl::Matrix<float,4,4> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::Coord<gmtl::Vec<float, 4>,gmtl::AxisAngle<float> > &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::Coord<gmtl::Vec<float, 3>,gmtl::AxisAngle<float> > &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::Coord<gmtl::Vec<float, 4>,gmtl::Quat<float> > &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::Coord<gmtl::Vec<float, 3>,gmtl::AxisAngle<float> > &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::Coord<gmtl::Vec<float, 4>,gmtl::Quat<float> > &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::Coord<gmtl::Vec<float, 3>,gmtl::Quat<float> > &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::ZXY> > &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::Coord<gmtl::Vec<float, 3>,gmtl::Quat<float> > &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<double,3,3> & (*)(gmtl::Matrix<double,3,3> &, const gmtl::Quat<double> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::EulerAngle<float,gmtl::ZXY> & (*)(gmtl::EulerAngle<float,gmtl::ZXY> &, const gmtl::Matrix<float,3,3> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::EulerAngle<float,gmtl::ZXY> & (*)(gmtl::EulerAngle<float,gmtl::ZXY> &, const gmtl::Matrix<float,4,4> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::EulerAngle<float,gmtl::ZYX> & (*)(gmtl::EulerAngle<float,gmtl::ZYX> &, const gmtl::Matrix<float,4,4> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::EulerAngle<float,gmtl::ZYX> & (*)(gmtl::EulerAngle<float,gmtl::ZYX> &, const gmtl::Matrix<float,3,3> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::EulerAngle<float,gmtl::XYZ> & (*)(gmtl::EulerAngle<float,gmtl::XYZ> &, const gmtl::Matrix<float,3,3> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::EulerAngle<float,gmtl::XYZ> & (*)(gmtl::EulerAngle<float,gmtl::XYZ> &, const gmtl::Matrix<float,4,4> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Quat<float> & (*)(gmtl::Quat<float> &, const gmtl::Matrix<float,4,4> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Quat<double> & (*)(gmtl::Quat<double> &, const gmtl::Matrix<double,4,4> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Quat<float> & (*)(gmtl::Quat<float> &, const gmtl::Matrix<float,3,3> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::AxisAngle<float> & (*)(gmtl::AxisAngle<float> &, gmtl::Quat<float>))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::AxisAngle<double> & (*)(gmtl::AxisAngle<double> &, gmtl::Quat<double>))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::XYZ> > & (*)(gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::XYZ> > &, const gmtl::Matrix<float,4,4> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::ZYX> > & (*)(gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::ZYX> > &, const gmtl::Matrix<float,4,4> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::ZXY> > & (*)(gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::ZXY> > &, const gmtl::Matrix<float,4,4> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::ZYX> > & (*)(gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::ZYX> > &, const gmtl::Matrix<float,4,4> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::ZXY> > & (*)(gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::ZXY> > &, const gmtl::Matrix<float,4,4> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Coord<gmtl::Vec<float, 4>,gmtl::Quat<float> > & (*)(gmtl::Coord<gmtl::Vec<float, 4>,gmtl::Quat<float> > &, const gmtl::Matrix<float,3,3> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Quat<float> & (*)(gmtl::Quat<float> &, const gmtl::AxisAngle<float> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Quat<float> & (*)(gmtl::Quat<float> &, const gmtl::EulerAngle<float,gmtl::ZXY> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Quat<float> & (*)(gmtl::Quat<float> &, const gmtl::EulerAngle<float,gmtl::ZYX> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Quat<float> & (*)(gmtl::Quat<float> &, const gmtl::EulerAngle<float,gmtl::XYZ> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Quat<double> & (*)(gmtl::Quat<double> &, const gmtl::AxisAngle<double> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::EulerAngle<float,gmtl::ZXY> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::EulerAngle<float,gmtl::ZYX> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::EulerAngle<float,gmtl::XYZ> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<double,4,4> & (*)(gmtl::Matrix<double,4,4> &, const gmtl::AxisAngle<double> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::AxisAngle<float> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<double,4,4> & (*)(gmtl::Matrix<double,4,4> &, const gmtl::EulerAngle<double,gmtl::XYZ> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<double,4,4> & (*)(gmtl::Matrix<double,4,4> &, const gmtl::EulerAngle<double,gmtl::ZYX> &))&gmtl::set, return_internal_reference< 1 >());
    def("set", (gmtl::Matrix<double,4,4> & (*)(gmtl::Matrix<double,4,4> &, const gmtl::EulerAngle<double,gmtl::ZXY> &))&gmtl::set, return_internal_reference< 1 >());
    def("setAxes", (gmtl::Matrix<double,3,3> & (*)(gmtl::Matrix<double,3,3> &, const gmtl::Vec<double,3> &, const gmtl::Vec<double,3> &, const gmtl::Vec<double,3> &))&gmtl::setAxes, return_internal_reference< 1 >());
    def("setAxes", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::Vec<float,3> &, const gmtl::Vec<float,3> &, const gmtl::Vec<float,3> &))&gmtl::setAxes, return_internal_reference< 1 >());
    def("setAxes", (gmtl::Matrix<double,4,4> & (*)(gmtl::Matrix<double,4,4> &, const gmtl::Vec<double,3> &, const gmtl::Vec<double,3> &, const gmtl::Vec<double,3> &))&gmtl::setAxes, return_internal_reference< 1 >());
    def("setAxes", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::Vec<float,3> &, const gmtl::Vec<float,3> &, const gmtl::Vec<float,3> &))&gmtl::setAxes, return_internal_reference< 1 >());
    def("setDirCos", &gmtlWrappers::setDirCosMatrix33f,
        return_internal_reference<1>(), setDirCosMatrix33f_overloads_4_7());
    def("setDirCos", &gmtlWrappers::setDirCosMatrix33d,
        return_internal_reference<1>(), setDirCosMatrix33d_overloads_4_7());
    def("setDirCos", &gmtlWrappers::setDirCosMatrix44f,
        return_internal_reference<1>(), setDirCosMatrix44f_overloads_4_7());
    def("setDirCos", &gmtlWrappers::setDirCosMatrix44d,
        return_internal_reference<1>(), setDirCosMatrix44d_overloads_4_7());
    def("setFrustum", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, float, float, float, float, float, float))&gmtl::setFrustum, return_internal_reference< 1 >());
    def("setFrustum", (gmtl::Matrix<double,4,4> & (*)(gmtl::Matrix<double,4,4> &, double, double, double, double, double, double))&gmtl::setFrustum, return_internal_reference< 1 >());
    def("setPerspective", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, float, float, float, float))&gmtl::setPerspective, return_internal_reference< 1 >());
    def("setPerspective", (gmtl::Matrix<double,4,4> & (*)(gmtl::Matrix<double,4,4> &, double, double, double, double))&gmtl::setPerspective, return_internal_reference< 1 >());
    def("setPure", (gmtl::Quat<float> & (*)(gmtl::Quat<float> &, const gmtl::Vec<float,3> &))&gmtl::setPure, return_internal_reference< 1 >());
    def("setPure", (gmtl::Quat<double> & (*)(gmtl::Quat<double> &, const gmtl::Vec<double,3> &))&gmtl::setPure, return_internal_reference< 1 >());
    def("setRot", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::Vec<float,3> &, const gmtl::Vec<float,3> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Coord<gmtl::Vec<float, 4>,gmtl::Quat<float> > & (*)(gmtl::Coord<gmtl::Vec<float, 4>,gmtl::Quat<float> > &, const gmtl::Matrix<float,4,4> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Coord<gmtl::Vec<float, 3>,gmtl::Quat<float> > & (*)(gmtl::Coord<gmtl::Vec<float, 3>,gmtl::Quat<float> > &, const gmtl::Matrix<float,4,4> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Coord<gmtl::Vec<float, 4>,gmtl::Quat<float> > & (*)(gmtl::Coord<gmtl::Vec<float, 4>,gmtl::Quat<float> > &, const gmtl::Matrix<float,3,3> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::ZYX> > & (*)(gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::ZYX> > &, const gmtl::Matrix<float,4,4> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::XYZ> > & (*)(gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::XYZ> > &, const gmtl::Matrix<float,4,4> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Matrix<double,4,4> & (*)(gmtl::Matrix<double,4,4> &, const gmtl::Quat<double> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::XYZ> > & (*)(gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::XYZ> > &, const gmtl::Matrix<float,3,3> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::ZXY> > & (*)(gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::ZXY> > &, const gmtl::Matrix<float,4,4> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::ZYX> > & (*)(gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::ZYX> > &, const gmtl::Matrix<float,4,4> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::XYZ> > & (*)(gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::XYZ> > &, const gmtl::Matrix<float,4,4> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::ZXY> > & (*)(gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::ZXY> > &, const gmtl::Matrix<float,3,3> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::ZYX> > & (*)(gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::ZYX> > &, const gmtl::Matrix<float,3,3> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::XYZ> > & (*)(gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::XYZ> > &, const gmtl::Matrix<float,3,3> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::ZXY> > & (*)(gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::ZXY> > &, const gmtl::Matrix<float,3,3> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Quat<float> & (*)(gmtl::Quat<float> &, const gmtl::Vec<float,3> &, const gmtl::Vec<float,3> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Coord<gmtl::Vec<float, 3>,gmtl::Quat<float> > & (*)(gmtl::Coord<gmtl::Vec<float, 3>,gmtl::Quat<float> > &, const gmtl::Matrix<float,3,3> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::ZXY> > & (*)(gmtl::Coord<gmtl::Vec<float, 4>,gmtl::EulerAngle<float, gmtl::ZXY> > &, const gmtl::Matrix<float,4,4> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::EulerAngle<float,gmtl::XYZ> & (*)(gmtl::EulerAngle<float,gmtl::XYZ> &, const gmtl::Matrix<float,4,4> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::EulerAngle<float,gmtl::ZXY> & (*)(gmtl::EulerAngle<float,gmtl::ZXY> &, const gmtl::Matrix<float,4,4> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::EulerAngle<float,gmtl::ZYX> & (*)(gmtl::EulerAngle<float,gmtl::ZYX> &, const gmtl::Matrix<float,4,4> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Quat<float> & (*)(gmtl::Quat<float> &, const gmtl::Matrix<float,4,4> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Quat<double> & (*)(gmtl::Quat<double> &, const gmtl::Matrix<double,4,4> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::AxisAngle<float> & (*)(gmtl::AxisAngle<float> &, gmtl::Quat<float>))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::AxisAngle<double> & (*)(gmtl::AxisAngle<double> &, gmtl::Quat<double>))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Quat<float> & (*)(gmtl::Quat<float> &, const gmtl::EulerAngle<float,gmtl::ZXY> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Quat<float> & (*)(gmtl::Quat<float> &, const gmtl::EulerAngle<float,gmtl::ZYX> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Quat<float> & (*)(gmtl::Quat<float> &, const gmtl::EulerAngle<float,gmtl::XYZ> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Quat<float> & (*)(gmtl::Quat<float> &, const gmtl::AxisAngle<float> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::AxisAngle<float> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Matrix<double,4,4> & (*)(gmtl::Matrix<double,4,4> &, const gmtl::AxisAngle<double> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::AxisAngle<float> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::EulerAngle<float,gmtl::XYZ> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::EulerAngle<float,gmtl::ZYX> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::EulerAngle<float,gmtl::ZXY> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Matrix<double,4,4> & (*)(gmtl::Matrix<double,4,4> &, const gmtl::EulerAngle<double,gmtl::XYZ> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::EulerAngle<float,gmtl::ZXY> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::EulerAngle<float,gmtl::ZYX> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::EulerAngle<float,gmtl::XYZ> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Matrix<double,4,4> & (*)(gmtl::Matrix<double,4,4> &, const gmtl::EulerAngle<double,gmtl::ZXY> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Matrix<double,4,4> & (*)(gmtl::Matrix<double,4,4> &, const gmtl::EulerAngle<double,gmtl::ZYX> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::ZYX> > & (*)(gmtl::Coord<gmtl::Vec<float, 3>,gmtl::EulerAngle<float, gmtl::ZYX> > &, const gmtl::Matrix<float,3,3> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::Quat<float> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::Quat<float> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setRot", (gmtl::Matrix<double,3,3> & (*)(gmtl::Matrix<double,3,3> &, const gmtl::Quat<double> &))&gmtl::setRot, return_internal_reference< 1 >());
    def("setScale", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::Vec<float,2> &))&gmtl::setScale, return_internal_reference< 1 >());
    def("setScale", (gmtl::Matrix<double,3,3> & (*)(gmtl::Matrix<double,3,3> &, const double))&gmtl::setScale, return_internal_reference< 1 >());
    def("setScale", (gmtl::Matrix<double,3,3> & (*)(gmtl::Matrix<double,3,3> &, const gmtl::Vec<double,2> &))&gmtl::setScale, return_internal_reference< 1 >());
    def("setScale", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const float))&gmtl::setScale, return_internal_reference< 1 >());
    def("setScale", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::Vec<float,3> &))&gmtl::setScale, return_internal_reference< 1 >());
    def("setScale", (gmtl::Matrix<double,4,4> & (*)(gmtl::Matrix<double,4,4> &, const double))&gmtl::setScale, return_internal_reference< 1 >());
    def("setScale", (gmtl::Matrix<double,4,4> & (*)(gmtl::Matrix<double,4,4> &, const gmtl::Vec<double,3> &))&gmtl::setScale, return_internal_reference< 1 >());
    def("setScale", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const float))&gmtl::setScale, return_internal_reference< 1 >());
    def("setTrans", (gmtl::Vec<float,4> & (*)(gmtl::Vec<float,4> &, const gmtl::Matrix<float,4,4> &))&gmtl::setTrans, return_internal_reference< 1 >());
    def("setTrans", (gmtl::Vec<float,3> & (*)(gmtl::Vec<float,3> &, const gmtl::Matrix<float,3,3> &))&gmtl::setTrans, return_internal_reference< 1 >());
    def("setTrans", (gmtl::Vec<double,3> & (*)(gmtl::Vec<double,3> &, const gmtl::Matrix<double,4,4> &))&gmtl::setTrans, return_internal_reference< 1 >());
    def("setTrans", (gmtl::Vec<float,3> & (*)(gmtl::Vec<float,3> &, const gmtl::Matrix<float,4,4> &))&gmtl::setTrans, return_internal_reference< 1 >());
    def("setTrans", (gmtl::Vec<float,4> & (*)(gmtl::Vec<float,4> &, const gmtl::Matrix<float,3,3> &))&gmtl::setTrans, return_internal_reference< 1 >());
    def("setTrans", (gmtl::Vec<float,2> & (*)(gmtl::Vec<float,2> &, const gmtl::Matrix<float,3,3> &))&gmtl::setTrans, return_internal_reference< 1 >());
    def("setTrans", (gmtl::Vec<double,2> & (*)(gmtl::Vec<double,2> &, const gmtl::Matrix<double,3,3> &))&gmtl::setTrans, return_internal_reference< 1 >());
    def("setTrans", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::VecBase<float,4> &))&gmtl::setTrans, return_internal_reference< 1 >());
    def("setTrans", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::VecBase<float,3> &))&gmtl::setTrans, return_internal_reference< 1 >());
    def("setTrans", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::VecBase<float,4> &))&gmtl::setTrans, return_internal_reference< 1 >());
    def("setTrans", (gmtl::Matrix<float,4,4> & (*)(gmtl::Matrix<float,4,4> &, const gmtl::VecBase<float,3> &))&gmtl::setTrans, return_internal_reference< 1 >());
    def("setTrans", (gmtl::Matrix<double,4,4> & (*)(gmtl::Matrix<double,4,4> &, const gmtl::VecBase<double,3> &))&gmtl::setTrans, return_internal_reference< 1 >());
    def("setTrans", (gmtl::Matrix<float,3,3> & (*)(gmtl::Matrix<float,3,3> &, const gmtl::VecBase<float,2> &))&gmtl::setTrans, return_internal_reference< 1 >());
    def("setTrans", (gmtl::Matrix<double,3,3> & (*)(gmtl::Matrix<double,3,3> &, const gmtl::VecBase<double,2> &))&gmtl::setTrans, return_internal_reference< 1 >());
    def("setRow", (void (*)(gmtl::Vec<float, 3>&, const gmtl::Matrix<float, 3, 3>&, unsigned))&gmtl::setRow);
    def("setRow", (void (*)(gmtl::Vec<double, 3>&, const gmtl::Matrix<double, 3, 3>&, unsigned))&gmtl::setRow);
    def("setRow", (void (*)(gmtl::Vec<float, 4>&, const gmtl::Matrix<float, 4, 4>&, unsigned))&gmtl::setRow);
    def("setRow", (void (*)(gmtl::Vec<double, 4>&, const gmtl::Matrix<double, 4, 4>&, unsigned))&gmtl::setRow);
    def("makeRow", (gmtl::Vec<float, 3> (*)(const gmtl::Matrix<float, 3, 3>&, unsigned))&gmtl::makeRow);
    def("makeRow", (gmtl::Vec<double, 3> (*)(const gmtl::Matrix<double, 3, 3>&, unsigned))&gmtl::makeRow);
    def("makeRow", (gmtl::Vec<float, 4> (*)(const gmtl::Matrix<float, 4, 4>&, unsigned))&gmtl::makeRow);
    def("makeRow", (gmtl::Vec<double, 4> (*)(const gmtl::Matrix<double, 4, 4>&, unsigned))&gmtl::makeRow);
    def("setColumn", (void (*)(gmtl::Vec<float, 3>&, const gmtl::Matrix<float, 3, 3>&, unsigned))&gmtl::setColumn);
    def("setColumn", (void (*)(gmtl::Vec<double, 3>&, const gmtl::Matrix<double, 3, 3>&, unsigned))&gmtl::setColumn);
    def("setColumn", (void (*)(gmtl::Vec<float, 4>&, const gmtl::Matrix<float, 4, 4>&, unsigned))&gmtl::setColumn);
    def("setColumn", (void (*)(gmtl::Vec<double, 4>&, const gmtl::Matrix<double, 4, 4>&, unsigned))&gmtl::setColumn);
    def("makeColumn", (gmtl::Vec<float, 3> (*)(const gmtl::Matrix<float, 3, 3>&, unsigned))&gmtl::makeColumn);
    def("makeColumn", (gmtl::Vec<double, 3> (*)(const gmtl::Matrix<double, 3, 3>&, unsigned))&gmtl::makeColumn);
    def("makeColumn", (gmtl::Vec<float, 4> (*)(const gmtl::Matrix<float, 4, 4>&, unsigned))&gmtl::makeColumn);
    def("makeColumn", (gmtl::Vec<double, 4> (*)(const gmtl::Matrix<double, 4, 4>&, unsigned))&gmtl::makeColumn);
}
