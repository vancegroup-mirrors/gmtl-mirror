/************************************************************** ggt-head beg
 *
 * GGT: Generic Graphics Toolkit
 *
 * Original Authors:
 *   Allen Bierbaum
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Types.h,v $
 * Date modified: $Date: 2002-05-21 14:58:55 $
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
#ifndef _GMTL_TYPES_H_
#define _GMTL_TYPES_H_

//#include <prtypes.h>

namespace gmtl
{
   /*
   typedef PRUint8   Uint8;
   typedef PRUint16  Uint16;
   typedef PRUint32  Uint32;
   typedef PRInt8    Int8;
   typedef PRInt16   Int16;
   typedef PRInt32   Int32;
   typedef float     Float;
   typedef double    Double;
   */

   /** @todo Fix so that type are actually accurate */

   typedef unsigned char   Uint8;
   typedef unsigned short Uint16;
   typedef unsigned int  Uint32;
   typedef char    Int8;
   typedef short   Int16;
   typedef int   Int32;
   typedef float     Float;
   typedef double    Double;

}


#endif
