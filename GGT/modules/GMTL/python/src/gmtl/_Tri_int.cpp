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
 * File:          $RCSfile: _Tri_int.cpp,v $
 * Date modified: $Date: 2003-08-15 22:01:57 $
 * Version:       $Revision: 1.2 $
 * -----------------------------------------------------------------
 *
 *************** <auto-copyright.pl END do not edit this line> ***************/


// Includes ====================================================================
#include <boost/python.hpp>
#include <gmtl/Tri.h>
#include <gmtl/TriOps.h>
#include <gmtl/Output.h>

// Using =======================================================================
using namespace boost::python;

// Module ======================================================================
void _Export_Tri_int()
{
    class_< gmtl::Tri<int> >("Trii", init<  >())
        .def(init< const gmtl::Point<int,3> &, const gmtl::Point<int,3> &, const gmtl::Point<int,3> & >())
        .def(init< const gmtl::Tri<int> & >())
        .def("edge", (gmtl::Vec<int, 3> (gmtl::Tri<int>::*)(int) const) &gmtl::Tri<int>::edge)
        .def("edge", (gmtl::Vec<int, 3> (gmtl::Tri<int>::*)(int, int) const) &gmtl::Tri<int>::edge)
        .def("set", &gmtl::Tri<int>::set)
        .def(self == self)
        .def(self != self)
        .def(self_ns::str(self))
    ;

}
