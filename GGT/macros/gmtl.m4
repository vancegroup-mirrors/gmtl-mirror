dnl ************************************************************** ggt-head beg
dnl
dnl GGT: Generic Graphics Toolkit
dnl
dnl Original Authors:
dnl   Allen Bierbaum
dnl
dnl -----------------------------------------------------------------
dnl File:          $RCSfile: gmtl.m4,v $
dnl Date modified: $Date: 2002-04-24 15:10:52 $
dnl Version:       $Revision: 1.5 $
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
dnl Test for GMTL and then define GMTL_CXXFLAGS and GMTL_VERSION.
dnl ---------------------------------------------------------------------------
AC_DEFUN(GMTL_PATH,
[
   dnl Get the cflags and libraries from the gmtl-config script
   AC_ARG_WITH(gmtl-prefix,
               [  --with-gmtl-prefix=<PATH>
                          Prefix where GMTL is installed
                          (optional)                      [No default]],
               gmtl_config_prefix="$withval", gmtl_config_prefix="")
   AC_ARG_WITH(gmtl-exec-prefix,
               [  --with-gmtl-exec-prefix=<PATH>
                          Exec prefix where GMTL is
                          installed (optional)            [No default]],
               gmtl_config_exec_prefix="$withval", gmtl_config_exec_prefix="")
dnl   AC_ARG_ENABLE(gmtltest,
dnl                 [  --disable-gmtltest       Do not try to compile and run a
dnl                         test GMTL program], , enable_gmtltest=yes)

   if test "x$gmtl_config_exec_prefix" != "x" ; then
      gmtl_config_args="$gmtl_config_args --exec-prefix=$gmtl_config_exec_prefix"

      if test x${GMTL_CONFIG+set} != xset ; then
         GMTL_CONFIG="$gmtl_config_exec_prefix/bin/gmtl-config"
      fi
   fi

   if test "x$gmtl_config_prefix" != "x" ; then
      gmtl_config_args="$gmtl_config_args --prefix=$gmtl_config_prefix"

      if test x${GMTL_CONFIG+set} != xset ; then
         GMTL_CONFIG="$gmtl_config_prefix/bin/gmtl-config"
      fi
   fi

   if test "x$GMTL_BASE_DIR" != "x" ; then
      gmtl_config_args="$gmtl_config_args --prefix=$GMTL_BASE_DIR"

      if test x${GMTL_CONFIG+set} != xset ; then
         GMTL_CONFIG="$GMTL_BASE_DIR/bin/gmtl-config"
      fi
   fi

   AC_PATH_PROG(GMTL_CONFIG, gmtl-config, no)
   min_gmtl_version=ifelse([$1], ,0.0.1,$1)

   dnl Do a sanity check to ensure that $GMTL_CONFIG actually works.
   if ! (eval $GMTL_CONFIG --cxxflags >/dev/null 2>&1) 2>&1 ; then
      GMTL_CONFIG='no'
   fi

   GMTL_CXXFLAGS=''

   no_gmtl='no'
   if test "x$GMTL_CONFIG" = "xno" ; then
      no_gmtl='yes'
   else
      GMTL_CXXFLAGS=`$GMTL_CONFIG $gmtl_config_args --cxxflags`
   fi

   if test "x$no_gmtl" = "xyes" ; then
      if test "$GMTL_CONFIG" = "no" ; then
         echo "*** The gmtl-config script installed by GMTL could not be found"
         echo "*** If GMTL was installed in PREFIX, make sure"
         ehco "*** PREFIX/include/gmtl exists." 
      fi
      GMTL_VERSION='-1'
      ifelse([$3], , :, [$3])
   fi

   AC_SUBST(GMTL_CXXFLAGS)
   AC_SUBST(GMTL_VERSION)
])
