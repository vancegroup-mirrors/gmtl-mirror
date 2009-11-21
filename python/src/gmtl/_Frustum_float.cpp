/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: _Frustum_float.cpp,v $
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
void _Export_Frustum_float()
{
    scope* gmtl_Frustum_float_scope = new scope(
    class_< gmtl::Frustum<float> >("Frustumf", init<  >())
        .def(init< const gmtl::Frustum<float> & >())
        .def(init< const gmtl::Matrix44f & >())
        .def(init< const gmtl::Matrix44f &, const gmtl::Matrix44f & >())
        .add_property("planes",
                      (tuple (*)(gmtl::Frustum<float>*)) &gmtlWrappers::Frustum_getPlanes)
        .def("extractPlanes",
             (void(gmtl::Frustum<float>::*)(const gmtl::Matrix44f&, const gmtl::Matrix44f&)) &gmtl::Frustum<float>::extractPlanes)
        .def("extractPlanes",
             (void(gmtl::Frustum<float>::*)(const gmtl::Matrix44f&)) &gmtl::Frustum<float>::extractPlanes)
        .def_pickle(gmtlPickle::Frustum_pickle<float>())
    );

    enum_< gmtl::Frustum<float>::PlaneNames >("PlaneNames")
        .value("LEFT", gmtl::Frustum<float>::PLANE_LEFT)
        .value("RIGHT", gmtl::Frustum<float>::PLANE_RIGHT)
        .value("BOTTOM", gmtl::Frustum<float>::PLANE_BOTTOM)
        .value("TOP", gmtl::Frustum<float>::PLANE_TOP)
        .value("NEAR", gmtl::Frustum<float>::PLANE_NEAR)
        .value("FAR", gmtl::Frustum<float>::PLANE_FAR)
    ;

    delete gmtl_Frustum_float_scope;

}
