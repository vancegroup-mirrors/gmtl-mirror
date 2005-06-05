/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: _VecBase_double_4_VecExpMeta.cpp,v $
 * Date modified: $Date: 2005-06-05 00:47:19 $
 * Version:       $Revision: 1.3 $
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
void _VecBase_double_4_VecExpMeta()
{
   typedef gmtl::VecBase<double, 4,
                         gmtl::meta::VecBinaryExpr<gmtl::VecBase<double,4>,
                                                   gmtl::VecBase<double,4>,
                                                   gmtl::meta::VecPlusBinary>
                        > VecBase_VecPlusBinary_t;

   scope* gmtl_VecBase_double_4_VecBinaryExpr_VecPlusBinary_scope = new scope(
   class_<VecBase_VecPlusBinary_t>("VecBase4dPlusBinary",
                                   init<const VecBase_VecPlusBinary_t&>())
      .def("__getitem__",
           (double (VecBase_VecPlusBinary_t::*)(const unsigned)) &VecBase_VecPlusBinary_t::operator[])
   );

   enum_< VecBase_VecPlusBinary_t::Params >("Params")
      .value("Size", VecBase_VecPlusBinary_t::Size)
   ;

   delete gmtl_VecBase_double_4_VecBinaryExpr_VecPlusBinary_scope;

   typedef gmtl::VecBase<double, 4,
                         gmtl::meta::VecBinaryExpr<gmtl::VecBase<double,4>,
                                                   gmtl::VecBase<double,4>,
                                                   gmtl::meta::VecMinusBinary>
                        > VecBase_VecMinusBinary_t;

   scope* gmtl_VecBase_double_4_VecBinaryExpr_VecMinusBinary_scope = new scope(
   class_<VecBase_VecMinusBinary_t>("VecBase4dMinusBinary",
                                    init<const VecBase_VecMinusBinary_t&>())
      .def("__getitem__",
           (double (VecBase_VecMinusBinary_t::*)(const unsigned)) &VecBase_VecMinusBinary_t::operator[])
   );

   enum_<VecBase_VecMinusBinary_t::Params>("Params")
      .value("Size", VecBase_VecMinusBinary_t::Size)
   ;

   delete gmtl_VecBase_double_4_VecBinaryExpr_VecMinusBinary_scope;

   typedef gmtl::VecBase<double, 4,
                         gmtl::meta::VecBinaryExpr<gmtl::VecBase<double,4>,
                                                   gmtl::VecBase<double,4>,
                                                   gmtl::meta::VecMultBinary>
                        > VecBase_VecMultBinary_t;

   scope* gmtl_VecBase_double_4_VecBinaryExpr_VecMultBinary_scope = new scope(
   class_<VecBase_VecMultBinary_t>("VecBase4dMultBinary",
                                   init<const VecBase_VecMultBinary_t&>())
      .def("__getitem__",
           (double (VecBase_VecMultBinary_t::*)(const unsigned)) &VecBase_VecMultBinary_t::operator[])
   );

   enum_<VecBase_VecMultBinary_t::Params>("Params")
      .value("Size", VecBase_VecMultBinary_t::Size)
   ;

   delete gmtl_VecBase_double_4_VecBinaryExpr_VecMultBinary_scope;

   typedef gmtl::VecBase<double, 4,
                         gmtl::meta::VecBinaryExpr<gmtl::VecBase<double,4>,
                                                   gmtl::VecBase<double,4>,
                                                   gmtl::meta::VecDivBinary>
                        > VecBase_VecDivBinary_t;

   scope* gmtl_VecBase_double_4_VecBinaryExpr_VecDivBinary_scope = new scope(
   class_<VecBase_VecDivBinary_t>("VecBase4dDivBinary",
                                   init<const VecBase_VecDivBinary_t&>())
      .def("__getitem__",
           (double (VecBase_VecDivBinary_t::*)(const unsigned)) &VecBase_VecDivBinary_t::operator[])
   );

   enum_<VecBase_VecDivBinary_t::Params>("Params")
      .value("Size", VecBase_VecDivBinary_t::Size)
   ;

   delete gmtl_VecBase_double_4_VecBinaryExpr_VecDivBinary_scope;

   typedef gmtl::VecBase<double, 4,
                         gmtl::meta::VecBinaryExpr<gmtl::VecBase<double,4>,
                                                   gmtl::VecBase<double,
                                                                 4,
                                                                 gmtl::meta::ScalarArg<double>
                                                                >,
                                                   gmtl::meta::VecMultBinary>
                        > VecBase_ScalarArg_VecMultBinary_t;

   scope* gmtl_VecBase_double_4_VecBinaryExpr_ScalarArg_VecMultBinary_scope = new scope(
   class_<VecBase_ScalarArg_VecMultBinary_t>("VecBase4dScalarArgMultBinary",
                                             init<const VecBase_ScalarArg_VecMultBinary_t&>())
      .def("__getitem__",
           (double (VecBase_ScalarArg_VecMultBinary_t::*)(const unsigned)) &VecBase_ScalarArg_VecMultBinary_t::operator[])
   );

   enum_<VecBase_ScalarArg_VecMultBinary_t::Params>("Params")
      .value("Size", VecBase_ScalarArg_VecMultBinary_t::Size)
   ;

   delete gmtl_VecBase_double_4_VecBinaryExpr_ScalarArg_VecMultBinary_scope;

   typedef gmtl::VecBase<double, 4,
                         gmtl::meta::VecBinaryExpr<gmtl::VecBase<double,4>,
                                                   gmtl::VecBase<double,
                                                                 4,
                                                                 gmtl::meta::ScalarArg<double>
                                                                >,
                                                   gmtl::meta::VecDivBinary>
                        > VecBase_ScalarArg_VecDivBinary_t;

   scope* gmtl_VecBase_double_4_VecBinaryExpr_ScalarArg_VecDivBinary_scope = new scope(
   class_<VecBase_ScalarArg_VecDivBinary_t>("VecBase4dScalarArgDivBinary",
                                            init<const VecBase_ScalarArg_VecDivBinary_t&>())
      .def("__getitem__",
           (double (VecBase_ScalarArg_VecDivBinary_t::*)(const unsigned)) &VecBase_ScalarArg_VecDivBinary_t::operator[])
   );

   enum_<VecBase_ScalarArg_VecDivBinary_t::Params>("Params")
      .value("Size", VecBase_ScalarArg_VecDivBinary_t::Size)
   ;

   delete gmtl_VecBase_double_4_VecBinaryExpr_ScalarArg_VecDivBinary_scope;

   typedef gmtl::VecBase<double, 4,
                         gmtl::meta::VecUnaryExpr<gmtl::VecBase<double,4>,
                                                  gmtl::meta::VecNegUnary>
                        > VecBase_VecNegUnary_t;

   scope* gmtl_VecBase_double_4_VecUnaryExpr_VecNegUnary_scope = new scope(
   class_<VecBase_VecNegUnary_t>("VecBase4dNegUnary",
                                 init<const VecBase_VecNegUnary_t&>())
      .def("__getitem__",
           (double (VecBase_VecNegUnary_t::*)(const unsigned)) &VecBase_VecNegUnary_t::operator[])
   );

   enum_<VecBase_VecNegUnary_t::Params>("Params")
      .value("Size", VecBase_VecNegUnary_t::Size)
   ;

   delete gmtl_VecBase_double_4_VecUnaryExpr_VecNegUnary_scope;

}
