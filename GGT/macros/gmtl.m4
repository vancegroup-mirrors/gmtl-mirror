dnl ************************************************************** ggt-head beg
dnl
dnl GGT: Generic Graphics Toolkit
dnl
dnl Original Authors:
dnl   Allen Bierbaum
dnl
dnl -----------------------------------------------------------------
dnl File:          $RCSfile: gmtl.m4,v $
dnl Date modified: $Date: 2002-04-04 22:44:12 $
dnl Version:       $Revision: 1.4 $
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
dnl GMTL_PATH([MINIMUM-VERSION, [ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND [, MODULES]]]])
dnl
dnl Test for GMTL and then define GMTL_CXXFLAGS, GMTL_INCLUDES, and
dnl GMTL_VERSION.
dnl ---------------------------------------------------------------------------
AC_DEFUN(GMTL_PATH,
[
   dnl Get the cflags and libraries from the gmtl-config script
   AC_ARG_WITH(gmtl-include,
               [  --with-gmtl-include=<PATH>
                          Path to GMTL headers (optional) [No default]],
               gmtl_include="$withval", gmtl_include="")
dnl   AC_ARG_WITH(gmtl-exec-prefix,
dnl               [  --with-gmtl-exec-prefix=<PATH>
dnl                          Exec prefix where GMTL is
dnl                          installed (optional)            [No default]],
dnl               gmtl_config_exec_prefix="$withval", gmtl_config_exec_prefix="")
dnl   AC_ARG_ENABLE(gmtltest,
dnl                 [  --disable-gmtltest       Do not try to compile and run a
dnl                         test GMTL program], , enable_gmtltest=yes)

   if test "x$GMTL_BASE_DIR" != "x" ; then
      gmtl_include="$GMTL_BASE_DIR/include"
   fi

   no_gmtl=''
   GMTL_INCLUDES=''

   if test "x$gmtl_include" != "x" ; then
      gmtl_save_CPPFLAGS="$CPPFLAGS"
      CPPFLAGS="$CPPFLAGS -I$gmtl_include"

      AC_LANG_SAVE
      AC_LANG_CPLUSPLUS
      AC_CHECK_HEADER(gmtl/Tri.h,
         GMTL_INCLUDES="-I$gmtl_include"
         no_gmtl='no')
      AC_LANG_RESTORE

      CPPFLAGS="$gmtl_save_CPPFLAGS"
   fi

   if test "x$no_gmtl" = "x" ; then
      if test "$GMTL_CONFIG" = "no" ; then
         echo "*** The gmtl-config script installed by GMTL could not be found"
         echo "*** If GMTL was installed in PREFIX, make sure"
         ehco "*** PREFIX/include/gmtl exists." 
      fi
      GMTL_CXXFLAGS=''
      GMTL_VERSION='-1'
      ifelse([$3], , :, [$3])
   fi

   AC_SUBST(GMTL_CXXFLAGS)
   AC_SUBST(GMTL_INCLUDES)
   AC_SUBST(GMTL_VERSION)
])
