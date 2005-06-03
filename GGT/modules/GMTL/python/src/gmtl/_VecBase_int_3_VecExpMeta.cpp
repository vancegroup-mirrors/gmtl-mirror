/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: _VecBase_int_3_VecExpMeta.cpp,v $
 * Date modified: $Date: 2005-06-03 15:13:04 $
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
#include <gmtl/VecBase.h>
#include <gmtl/Output.h>
#include <gmtl-wrappers.h>
#include <gmtl-getData-wrappers.h>
#include <gmtl-pickle.h>

// Using =======================================================================
using namespace boost::python;

// Module ======================================================================
void _VecBase_int_3_VecExpMeta()
{
   typedef gmtl::VecBase<int, 3,
                         gmtl::meta::VecBinaryExpr<gmtl::VecBase<int,3>,
                                                   gmtl::VecBase<int,3>,
                                                   gmtl::meta::VecPlusBinary>
                        > VecBase_VecPlusBinary_t;

   scope* gmtl_VecBase_int_3_VecBinaryExpr_VecPlusBinary_scope = new scope(
   class_<VecBase_VecPlusBinary_t>("VecBase3iPlusBinary",
                                   init<const VecBase_VecPlusBinary_t&>())
      .def("__getitem__",
           (int (VecBase_VecPlusBinary_t::*)(const unsigned)) &VecBase_VecPlusBinary_t::operator[])
   );

   enum_< VecBase_VecPlusBinary_t::Params >("Params")
      .value("Size", VecBase_VecPlusBinary_t::Size)
   ;

   delete gmtl_VecBase_int_3_VecBinaryExpr_VecPlusBinary_scope;

   typedef gmtl::VecBase<int, 3,
                         gmtl::meta::VecBinaryExpr<gmtl::VecBase<int,3>,
                                                   gmtl::VecBase<int,3>,
                                                   gmtl::meta::VecMinusBinary>
                        > VecBase_VecMinusBinary_t;

   scope* gmtl_VecBase_int_3_VecBinaryExpr_VecMinusBinary_scope = new scope(
   class_<VecBase_VecMinusBinary_t>("VecBase3iMinusBinary",
                                    init<const VecBase_VecMinusBinary_t&>())
      .def("__getitem__",
           (int (VecBase_VecMinusBinary_t::*)(const unsigned)) &VecBase_VecMinusBinary_t::operator[])
   );

   enum_<VecBase_VecMinusBinary_t::Params>("Params")
      .value("Size", VecBase_VecMinusBinary_t::Size)
   ;

   delete gmtl_VecBase_int_3_VecBinaryExpr_VecMinusBinary_scope;

   typedef gmtl::VecBase<int, 3,
                         gmtl::meta::VecBinaryExpr<gmtl::VecBase<int,3>,
                                                   gmtl::VecBase<int,3>,
                                                   gmtl::meta::VecMultBinary>
                        > VecBase_VecMultBinary_t;

   scope* gmtl_VecBase_int_3_VecBinaryExpr_VecMultBinary_scope = new scope(
   class_<VecBase_VecMultBinary_t>("VecBase3iMultBinary",
                                   init<const VecBase_VecMultBinary_t&>())
      .def("__getitem__",
           (int (VecBase_VecMultBinary_t::*)(const unsigned)) &VecBase_VecMultBinary_t::operator[])
   );

   enum_<VecBase_VecMultBinary_t::Params>("Params")
      .value("Size", VecBase_VecMultBinary_t::Size)
   ;

   delete gmtl_VecBase_int_3_VecBinaryExpr_VecMultBinary_scope;

   typedef gmtl::VecBase<int, 3,
                         gmtl::meta::VecBinaryExpr<gmtl::VecBase<int,3>,
                                                   gmtl::VecBase<int,3>,
                                                   gmtl::meta::VecDivBinary>
                        > VecBase_VecDivBinary_t;

   scope* gmtl_VecBase_int_3_VecBinaryExpr_VecDivBinary_scope = new scope(
   class_<VecBase_VecDivBinary_t>("VecBase3iDivBinary",
                                   init<const VecBase_VecDivBinary_t&>())
      .def("__getitem__",
           (int (VecBase_VecDivBinary_t::*)(const unsigned)) &VecBase_VecDivBinary_t::operator[])
   );

   enum_<VecBase_VecDivBinary_t::Params>("Params")
      .value("Size", VecBase_VecDivBinary_t::Size)
   ;

   delete gmtl_VecBase_int_3_VecBinaryExpr_VecDivBinary_scope;

   typedef gmtl::VecBase<int, 3,
                         gmtl::meta::VecUnaryExpr<gmtl::VecBase<int,3>,
                                                  gmtl::meta::VecNegUnary>
                        > VecBase_VecNegUnary_t;

   scope* gmtl_VecBase_int_3_VecUnaryExpr_VecNegUnary_scope = new scope(
   class_<VecBase_VecNegUnary_t>("VecBase3iNegUnary",
                                 init<const VecBase_VecNegUnary_t&>())
      .def("__getitem__",
           (int (VecBase_VecNegUnary_t::*)(const unsigned)) &VecBase_VecNegUnary_t::operator[])
   );

   enum_<VecBase_VecNegUnary_t::Params>("Params")
      .value("Size", VecBase_VecNegUnary_t::Size)
   ;

   delete gmtl_VecBase_int_3_VecUnaryExpr_VecNegUnary_scope;

}
