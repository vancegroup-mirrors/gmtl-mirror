/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: gmtl-array-wrappers.h,v $
 * Date modified: $Date: 2005-05-12 19:35:54 $
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

#ifndef _PYGMTL_GMTL_ARRAY_WRAPPERS_H_
#define _PYGMTL_GMTL_ARRAY_WRAPPERS_H_

#include <boost/python/list.hpp>
#include <gmtl/Matrix.h>

namespace gmtlWrappers
{
   template<typename T>
   void Matrix_3_3_set(gmtl::Matrix<T, 3, 3>* m, boost::python::list pyData)
   {
      T gmtl_data[9];

      for ( int i = 0; i < 9; ++i )
      {
         gmtl_data[i] = boost::python::extract<T>(pyData[i]);
      }

      m->set(gmtl_data);
   }

   template void Matrix_3_3_set(gmtl::Matrix<float, 3, 3>*,
                                boost::python::list);

   template<typename T>
   void Matrix_3_3_setTranspose(gmtl::Matrix<T, 3, 3>* m,
                                boost::python::list pyData)
   {
      T gmtl_data[9];

      for ( int i = 0; i < 9; ++i )
      {
         gmtl_data[i] = boost::python::extract<T>(pyData[i]);
      }

      m->setTranspose(gmtl_data);
   }

   template void Matrix_3_3_setTranspose(gmtl::Matrix<float, 3, 3>*,
                                         boost::python::list);

   template<typename T>
   void Matrix_4_4_set(gmtl::Matrix<T, 4, 4>* m, boost::python::list pyData)
   {
      T gmtl_data[16];

      for ( int i = 0; i < 16; ++i )
      {
         gmtl_data[i] = boost::python::extract<T>(pyData[i]);
      }

      m->set(gmtl_data);
   }

   template void Matrix_4_4_set(gmtl::Matrix<float, 4, 4>*,
                                boost::python::list);

   template<typename T>
   void Matrix_4_4_setTranspose(gmtl::Matrix<T, 4, 4>* m,
                                boost::python::list pyData)
   {
      T gmtl_data[16];

      for ( int i = 0; i < 16; ++i )
      {
         gmtl_data[i] = boost::python::extract<T>(pyData[i]);
      }

      m->setTranspose(gmtl_data);
   }

   template void Matrix_4_4_setTranspose(gmtl::Matrix<float, 4, 4>*,
                                         boost::python::list);
}

#endif /* _PYGMTL_GMTL_ARRAY_WRAPPERS_H_ */
