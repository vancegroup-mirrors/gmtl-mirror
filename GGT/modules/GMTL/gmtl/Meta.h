/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Meta.h,v $
 * Date modified: $Date: 2002-05-10 05:38:47 $
 * Version:       $Revision: 1.4 $
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
#ifndef _GMTL_METAPROGRAMMING_H
#define _GMTL_METAPROGRAMMING_H

/** @defgroup Meta Template Metaprogramming Utilities */

namespace gmtl
{  
   /** @addtogroup Meta */
   //@{
   
   /** A lightweight identifier you can pass to overloaded functions 
    *  to typefy them.
    *
    *  Type2Type lets you transport the type information about T to functions
    */
   template <typename T>
   struct Type2Type
   {
      typedef T OriginalType;
   };
   
   //@}

   /** @addtogroup Helper Meta */
   //@{
   template <class T> inline void ignore_unused_variable_warning(const T&) { }

   //@}

} // end namespace
#endif
