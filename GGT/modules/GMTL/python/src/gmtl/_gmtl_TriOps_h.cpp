/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: _gmtl_TriOps_h.cpp,v $
 * Date modified: $Date: 2003-08-17 06:32:59 $
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
#include <gmtl-TriOps.h>

// Using =======================================================================
using namespace boost::python;

// Module ======================================================================
void _Export_gmtl_TriOps_h()
{
    def("center", (gmtl::Point<double,3> (*)(const gmtl::Tri<double> &))&gmtl::center);
    def("center", (gmtl::Point<int,3> (*)(const gmtl::Tri<int> &))&gmtl::center);
    def("center", (gmtl::Point<float,3> (*)(const gmtl::Tri<float> &))&gmtl::center);
}
