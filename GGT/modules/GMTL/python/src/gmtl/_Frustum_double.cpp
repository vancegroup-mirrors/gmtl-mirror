/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: _Frustum_double.cpp,v $
 * Date modified: $Date: 2007-06-13 23:17:26 $
 * Version:       $Revision: 1.1 $
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
#include <gmtl/Frustum.h>
#include <gmtl-getData-wrappers.h>
#include <gmtl-pickle.h>

// Using =======================================================================
using namespace boost::python;

// Module ======================================================================
void _Export_Frustum_double()
{
    scope* gmtl_Frustum_double_scope = new scope(
    class_< gmtl::Frustum<double> >("Frustumd", init<  >())
        .def(init< const gmtl::Frustum<double> & >())
        .def(init< const gmtl::Matrix44d & >())
        .def(init< const gmtl::Matrix44d &, const gmtl::Matrix44d & >())
        .add_property("planes",
                      (tuple (*)(gmtl::Frustum<double>*)) &gmtlWrappers::Frustum_getPlanes)
        .def("extractPlanes",
             (void(gmtl::Frustum<double>::*)(const gmtl::Matrix44d&, const gmtl::Matrix44d&)) &gmtl::Frustum<double>::extractPlanes)
        .def("extractPlanes",
             (void(gmtl::Frustum<double>::*)(const gmtl::Matrix44d&)) &gmtl::Frustum<double>::extractPlanes)
        .def_pickle(gmtlPickle::Frustum_pickle<double>())
    );

    enum_< gmtl::Frustum<double>::PlaneNames >("PlaneNames")
        .value("LEFT", gmtl::Frustum<double>::PLANE_LEFT)
        .value("RIGHT", gmtl::Frustum<double>::PLANE_RIGHT)
        .value("BOTTOM", gmtl::Frustum<double>::PLANE_BOTTOM)
        .value("TOP", gmtl::Frustum<double>::PLANE_TOP)
        .value("NEAR", gmtl::Frustum<double>::PLANE_NEAR)
        .value("FAR", gmtl::Frustum<double>::PLANE_FAR)
    ;

    delete gmtl_Frustum_double_scope;

}
