dnl ************************************************************** ggt-head beg
dnl
dnl GGT: Generic Graphics Toolkit
dnl
dnl Original Authors:
dnl   Allen Bierbaum
dnl
dnl -----------------------------------------------------------------
dnl File:          $RCSfile: gmtl.m4,v $
dnl Date modified: $Date: 2007-07-15 19:26:23 $
dnl Version:       $Revision: 1.19 $
dnl -----------------------------------------------------------------
dnl
dnl ************************************************************** ggt-head end

dnl *************************************************************** ggt-cpr beg
dnl GGT: The Generic Graphics Toolkit
dnl Copyright (C) 2001,2002 Allen Bierbaum 
dnl
dnl This library is free software; you can redistribute it and/or
dnl modify it under the terms of the GNU Lesser General Public
dnl License as published by the Free Software Foundation; either
dnl version 2.1 of the License, or (at your option) any later version.
dnl
dnl This library is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
dnl Lesser General Public License for more details.
dnl
dnl You should have received a copy of the GNU Lesser General Public
dnl License along with this library; if not, write to the Free Software
dnl Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
dnl
dnl *************************************************************** ggt-cpr end

dnl ---------------------------------------------------------------------------
dnl Test for GMTL and then define GMTL_CXXFLAGS, GMTL_INCLUDES, and
dnl GMTL_VERSION.
dnl
dnl Usage:
dnl    GMTL_PATH(version , gmtl-root [, include-path [, action-if-found [, action-if-not-found]]])
dnl
dnl Arguments:
dnl    version             - The minimum required version.
dnl    action-if-found     - The action to take if a GMTL implementation is
dnl                          found.  This argument is optional.
dnl    action-if-not-found - The action to take if a GMTL implementation is
dnl                          not found.  This argument is optional.
dnl ---------------------------------------------------------------------------
AC_DEFUN([GMTL_PATH],
[
   AM_PATH_FLAGPOLL([0.8.1], ,
                    [AC_MSG_ERROR(*** Flagpoll required for GMTL flags ***)])

   min_gmtl_version=ifelse([$1], ,0.4.11,$1)
   AC_MSG_CHECKING([for GMTL version >= $min_gmtl_version])

   GMTL_VERSION=`$FLAGPOLL gmtl --modversion`
   if $FLAGPOLL gmtl --atleast-version=$min_gmtl_version >/dev/null 2>&1
   then
      :
   else
      no_gmtl='yes'
   fi

   if test "x$no_gmtl" = "xyes" ; then
      AC_MSG_RESULT([no ($GMTL_VERSION)])

      ifelse([$3], , :, [$3])
   else
      AC_MSG_RESULT([yes ($GMTL_VERSION)])

      GMTL_CXXFLAGS=`$FLAGPOLL gmtl --cflags`
      GMTL_INCLUDES=`$FLAGPOLL gmtl --cflags-only-I`

      ifelse([$2], , :, [$2])
   fi

   AC_SUBST(GMTL_CXXFLAGS)
   AC_SUBST(GMTL_INCLUDES)
   AC_SUBST(GMTL_VERSION)
])
