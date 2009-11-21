/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: gmtl-containment-wrappers.h,v $
 * Date modified: $Date: 2007-06-13 23:17:25 $
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

#ifndef _PYGMTL_GMTL_CONTAINMENT_WRAPPERS_H_
#define _PYGMTL_GMTL_CONTAINMENT_WRAPPERS_H_

// This file makes declarations of the templated function instantiations
// needed for Boost.Python to do its thing.  More specifically, the functions
// defined here wrap instantiations of gmtl::intersect() and change the return
// type to be a Python tuple.

#include <boost/python/tuple.hpp>

#include <gmtl/Containment.h>


namespace gmtlWrappers
{
   using namespace boost::python;

   template<typename T>
   tuple isInVolume(const gmtl::Frustum<T>& frustum,
                    const gmtl::Point<T, 3>& point)
   {
      unsigned int index;
      bool result = gmtl::isInVolume(frustum, point, index);
      return make_tuple(result, index);
   }
}

#if ! defined(__APPLE__)
namespace gmtlWrappers
{
   template tuple isInVolume(const gmtl::Frustumf&, const gmtl::Point3f&);
   template tuple isInVolume(const gmtl::Frustumd&, const gmtl::Point3d&);
}
#endif


#endif /* _PYGMTL_GMTL_CONTAINMENT_WRAPPERS_H_ */
