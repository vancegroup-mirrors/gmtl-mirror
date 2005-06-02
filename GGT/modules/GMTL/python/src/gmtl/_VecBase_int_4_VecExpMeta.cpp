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
 * File:          $RCSfile: _VecBase_int_4_VecExpMeta.cpp,v $
 * Date modified: $Date: 2005-06-02 21:22:35 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 *************** <auto-copyright.pl END do not edit this line> ***************/

// Includes ====================================================================
#include <boost/python.hpp>
#include <gmtl/VecBase.h>
#include <gmtl/Output.h>
#include <gmtl-wrappers.h>
#include <gmtl-getData-wrappers.h>
#include <gmtl-pickle.h>

// Using =======================================================================
using namespace boost::python;

// Module ======================================================================
void _VecBase_int_4_VecExpMeta()
{
   typedef gmtl::VecBase<int, 4,
                         gmtl::meta::VecBinaryExpr<gmtl::VecBase<int,4>,
                                                   gmtl::VecBase<int,4>,
                                                   gmtl::meta::VecPlusBinary>
                        > VecBase_VecPlusBinary_t;

   scope* gmtl_VecBase_int_4_VecBinaryExpr_VecPlusBinary_scope = new scope(
   class_<VecBase_VecPlusBinary_t>("VecBase4iPlusBinary",
                                   init<const VecBase_VecPlusBinary_t&>())
      .def("__getitem__",
           (int (VecBase_VecPlusBinary_t::*)(const unsigned)) &VecBase_VecPlusBinary_t::operator[])
   );

   enum_< VecBase_VecPlusBinary_t::Params >("Params")
      .value("Size", VecBase_VecPlusBinary_t::Size)
   ;

   delete gmtl_VecBase_int_4_VecBinaryExpr_VecPlusBinary_scope;

   typedef gmtl::VecBase<int, 4,
                         gmtl::meta::VecBinaryExpr<gmtl::VecBase<int,4>,
                                                   gmtl::VecBase<int,4>,
                                                   gmtl::meta::VecMinusBinary>
                        > VecBase_VecMinusBinary_t;

   scope* gmtl_VecBase_int_4_VecBinaryExpr_VecMinusBinary_scope = new scope(
   class_<VecBase_VecMinusBinary_t>("VecBase4iMinusBinary",
                                    init<const VecBase_VecMinusBinary_t&>())
      .def("__getitem__",
           (int (VecBase_VecMinusBinary_t::*)(const unsigned)) &VecBase_VecMinusBinary_t::operator[])
   );

   enum_<VecBase_VecMinusBinary_t::Params>("Params")
      .value("Size", VecBase_VecMinusBinary_t::Size)
   ;

   delete gmtl_VecBase_int_4_VecBinaryExpr_VecMinusBinary_scope;

   typedef gmtl::VecBase<int, 4,
                         gmtl::meta::VecBinaryExpr<gmtl::VecBase<int,4>,
                                                   gmtl::VecBase<int,4>,
                                                   gmtl::meta::VecMultBinary>
                        > VecBase_VecMultBinary_t;

   scope* gmtl_VecBase_int_4_VecBinaryExpr_VecMultBinary_scope = new scope(
   class_<VecBase_VecMultBinary_t>("VecBase4iMultBinary",
                                   init<const VecBase_VecMultBinary_t&>())
      .def("__getitem__",
           (int (VecBase_VecMultBinary_t::*)(const unsigned)) &VecBase_VecMultBinary_t::operator[])
   );

   enum_<VecBase_VecMultBinary_t::Params>("Params")
      .value("Size", VecBase_VecMultBinary_t::Size)
   ;

   delete gmtl_VecBase_int_4_VecBinaryExpr_VecMultBinary_scope;

   typedef gmtl::VecBase<int, 4,
                         gmtl::meta::VecBinaryExpr<gmtl::VecBase<int,4>,
                                                   gmtl::VecBase<int,4>,
                                                   gmtl::meta::VecDivBinary>
                        > VecBase_VecDivBinary_t;

   scope* gmtl_VecBase_int_4_VecBinaryExpr_VecDivBinary_scope = new scope(
   class_<VecBase_VecDivBinary_t>("VecBase4iDivBinary",
                                   init<const VecBase_VecDivBinary_t&>())
      .def("__getitem__",
           (int (VecBase_VecDivBinary_t::*)(const unsigned)) &VecBase_VecDivBinary_t::operator[])
   );

   enum_<VecBase_VecDivBinary_t::Params>("Params")
      .value("Size", VecBase_VecDivBinary_t::Size)
   ;

   delete gmtl_VecBase_int_4_VecBinaryExpr_VecDivBinary_scope;

   typedef gmtl::VecBase<int, 4,
                         gmtl::meta::VecUnaryExpr<gmtl::VecBase<int,4>,
                                                  gmtl::meta::VecNegUnary>
                        > VecBase_VecNegUnary_t;

   scope* gmtl_VecBase_int_4_VecUnaryExpr_VecNegUnary_scope = new scope(
   class_<VecBase_VecNegUnary_t>("VecBase4iNegUnary",
                                 init<const VecBase_VecNegUnary_t&>())
      .def("__getitem__",
           (int (VecBase_VecNegUnary_t::*)(const unsigned)) &VecBase_VecNegUnary_t::operator[])
   );

   enum_<VecBase_VecNegUnary_t::Params>("Params")
      .value("Size", VecBase_VecNegUnary_t::Size)
   ;

   delete gmtl_VecBase_int_4_VecUnaryExpr_VecNegUnary_scope;

}
