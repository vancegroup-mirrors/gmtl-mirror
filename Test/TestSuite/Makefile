# Generated automatically from Makefile.advanced-template.in by configure.
# ************** <auto-copyright.pl BEGIN do not edit this line> **************
# Doozer
#
# Original Authors:
#   Patrick Hartling, Kevin Meinert
# -----------------------------------------------------------------------------
# VR Juggler is (C) Copyright 1998, 1999, 2000, 2001 by Iowa State University
#
# Original Authors:
#   Allen Bierbaum, Christopher Just,
#   Patrick Hartling, Kevin Meinert,
#   Carolina Cruz-Neira, Albert Baker
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Library General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Library General Public License for more details.
#
# You should have received a copy of the GNU Library General Public
# License along with this library; if not, write to the
# Free Software Foundation, Inc., 59 Temple Place - Suite 330,
# Boston, MA 02111-1307, USA.
#
# -----------------------------------------------------------------
# File:          $RCSfile: Makefile,v $
# Date modified: $Date: 2002-06-30 17:31:24 $
# Version:       $Revision: 1.40 $
# -----------------------------------------------------------------
# *************** <auto-copyright.pl END do not edit this line> ***************

# =============================================================================
# Advanced template makefile for VR Juggler applications.  This is intended
# for "power users" who really know what they are doing and want to abuse
# Doozer's flexibility.  :)
# $Id: Makefile,v 1.40 2002-06-30 17:31:24 allenb Exp $
#
# *** IMPORTANT NOTES -- READ THESE FIRST ***
#     1) This file _requires_ the use of GNU make (gmake).
# =============================================================================

# Nothing but comments should come before this line.
default: all

# -----------------------------------------------------------------------------
# Early information acquisition.  Before actually loading the Doozer
# application .mk file, individual internal files can be loaded here to get
# values that they set before Doozer puts all the pieces together.
#
# *** Be very careful with this section! ***
# -----------------------------------------------------------------------------
GGT_ROOT	= ../../../../
GMTL_ROOT   = ../../
CPPUNIT_DIR = $(GGT_ROOT)/external/cppunit

# Specify the directory containing the Doozer .mk files that will be used.
# Users are encouraged to include files relative to this variable in this file
# so that the include path can be changed easily.
DZR_BASE_DIR	= $(GGT_ROOT)/Doozer

# Get the name of the host platform early.
include $(DZR_BASE_DIR)/mk/dzr.hosttype.mk

# -----------------------------------------------------------------------------
# Application-specific variable settings.  It is safe to modify these.
# -----------------------------------------------------------------------------

# The application name that is built.  A value must be set for this!
APP_NAME	= runner

# The directory where the source files for this application are located.
srcdir  	= $(shell pwd)


# Test suite stuff

# Compiler flags needed for this application.  They are used as follows:
#
#    DEBUG_APP         - If set to TRUE, this application will be compiled with
#                        debugging symbols and no optimized symbols
#    OPTIM_APP         - If set to TRUE, this application will be compiled with
#                        optimized symbols and no debugging symbols
#    DEBUG_FLAGS       - Debugging flags passed to the compiler.  Settings this
#                        completely overrides what Doozer uses internally.
#    OPTIM_FLAGS       - Optimization f[click on a class for detailed information] lags passed to the compiler.  Settings
#                        this completely overrides what Doozer uses internally.
#    EXTRA_CFLAGS      - Extra application-specific C compiler flags
#    EXTRA_CXXFLAGS    - Extra application-specific C++ compiler flags
#    EXTRA_DEBUG_FLAGS - Extra application-specific compiler debugging flags
#    EXTRA_INCLUDES    - Extra include paths (-I... options) for the compilers
#    EXTRA_OPTIM_FLAGS - Extra application-specific compiler optimization flags
#    EXTRA_UI_LIBS     - Extra user interface libraries needed for linking.
#    PF_PATH           - Path (including -L option) to the Performer libraries
#
ifeq ($(HOSTTYPE), Linux)
	# Require gcc3 on linux
	CXX              = g++3
endif
USE_OPT?=           N
#DEBUG_FLAGS      =
OPTIM_FLAGS       = -O3 $(EXTRA_OPTIM_FLAGS)
EXTRA_CFLAGS      =
ifeq ($(HOSTTYPE), Linux)
   EXTRA_CXXFLAGS = -Wall -fexceptions
else
   EXTRA_CXXFLAGS =
endif
#EXTRA_CXXFLAGS    = -pipe
EXTRA_DEBUG_FLAGS	= -D_DEBUG
EXTRA_OPTIM_FLAGS	= -D_OPT
ifeq (${USE_OPT},Y)
   DEBUG_APP		= FALSE
   OPTIM_APP		= TRUE
endif
ifneq (${USE_OPT},Y)
   DEBUG_APP		= TRUE
   OPTIM_APP		= FALSE
endif


GMTL_INCLUDES  = -I$(GMTL_ROOT) -I$(GGT_ROOT)/
SUITE_INCLUDES = -I$(CPPUNIT_DIR)/include
EXTRA_INCLUDES = $(GMTL_INCLUDES) $(SUITE_INCLUDES)

# Platform-specific settings.
ifeq ($(HOSTTYPE), IRIX)
   EXTRA_INCLUDES += -I$(GGT_ROOT)/external/boost/boost/compatibility/cpp_c_headers
endif

EXTRA_UI_FLAGS =

# The list of all source files needed for this application.  Based on this,
# a list of object files is put in $(OBJS) automatically.
#
# For multiple sets of source files, individual lists of object files can
# be generated using the makeobjs function.  It works as follows:
#
#    MY_OBJS = $(call makeobjs, $(MY_SRCS))
#
# This can be done for as many lists of object files as necessary.
# This is helpful for compiling multiple applications.
TEST_SRCS = ConvertTest.cpp \
            LineSegTest.cpp \
            MatrixClassTest.cpp \
            MatrixCompareTest.cpp \
            MatrixGenTest.cpp \
            MatrixOpsTest.cpp \
            OptTest.cpp \
            OutputTest.cpp \
            PlaneTest.cpp \
            PointTest.cpp \
            AABoxTest.cpp \
				AABoxContainTest.cpp \
            CoordClassTest.cpp \
            CoordCompareTest.cpp \
            CoordGenTest.cpp \
            QuatClassTest.cpp \
            QuatCompareTest.cpp \
            QuatOpsTest.cpp \
            QuatGenTest.cpp \
            QuatStuffTest.cpp \
            SphereTest.cpp \
            TriTest.cpp \
            VecBaseTest.cpp \
            EulerAngleClassTest.cpp \
            EulerAngleCompareTest.cpp \
            AxisAngleClassTest.cpp \
            AxisAngleCompareTest.cpp \
            VecGenTest.cpp \
            VecTest.cpp \
            XformTest.cpp \
            testSuite.cpp
CPPUNIT_UI_SRCS	= TextTestProgressListener.cpp	\
                  TextOutputter.cpp		\
                  TestRunner.cpp
CPPUNIT_EXTS	= MetricRegistry.cpp
CPPUNIT_SRCS	= Asserter.cpp			\
                  Exception.cpp			\
                  NotEqualException.cpp		\
                  SourceLine.cpp		\
                  SynchronizedObject.cpp	\
                  TestAssert.cpp		\
                  TestCase.cpp			\
                  TestFailure.cpp		\
                  TestResult.cpp		\
                  TestResultCollector.cpp	\
                  TestSucessListener.cpp	\
                  TestSuite.cpp			\
                  $(CPPUNIT_UI_SRCS)		\
                  $(CPPUNIT_EXTS)             

EXTRA_CPPUNIT_SRCS_PATH	= $(CPPUNIT_DIR)/src/cppunit $(CPPUNIT_DIR)/src/cppunit/extensions

SRCS = $(TEST_SRCS) $(CPPUNIT_SRCS)
OBJDIR = $(DZR_HOSTTYPE).obj
DEPDIR = $(DZR_HOSTTYPE).obj

ifneq ($(HOSTTYPE), Win32)
# This is for extra libraries needed specfically for your application.  The
# general libraries needed for applications are in $(LIBS).
EXTRA_LIBS	= -lm
endif

# This is for extra system libraries (-lpthread for example) needed
# specifically for this application.  These are added to the linker command
# after all the basic libraries and all the system libraries.
EXTRA_SYS_LIBS	=

# Extend this as necessary to find source files that are not in the current
# directory.  Set EXTRA_PATH_FOR_SOURCES to all the directories that you
# have sources in. (current dir is already included by default)
EXTRA_PATH_FOR_SOURCES = $(EXTRA_CPPUNIT_SRCS_PATH):TestCases:TestCases/InfoTests

# Additional files and directories besides the standard ones that need to be
# removed by the 'clean' target.
CLEAN_FILES	=
CLEAN_DIRS	=

# The following include line MUST COME BEFORE the targets for compiling the
# application.
include $(DZR_BASE_DIR)/mk/dzr.basicapp.mk
#include $(DZR_BASE_DIR)/ext/...

# To modify various variables set internally by Doozer, make changes here.
# If a variable's value needs to be extended in some way, it can be done
# using += or := as follows:
#
#     VAR += <new settings>
#
#   or
#
#     VAR := <new settings> $(VAR) <more new settings>

# -----------------------------------------------------------------------------
# Targets.
# -----------------------------------------------------------------------------
all: $(APP_NAME)

# Target for the application to be built.
$(APP_NAME): $(OBJS)
	$(LINK) -o $@ $(OBJS) $(EXTRA_LIBS) $(LIBS)
