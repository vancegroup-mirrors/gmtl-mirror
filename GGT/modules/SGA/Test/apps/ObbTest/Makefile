# =============================================================================
# Advanced template makefile for VR Juggler applications.  This is intended
# for "power users" who really know what they are doing and want to abuse
# Doozer's flexibility.  :)
# $Id: Makefile,v 1.1.1.1 2002-01-18 20:43:10 allenb Exp $
#
# *** IMPORTANT NOTES -- READ THESE FIRST ***
#     1) This file _requires_ the use of GNU make (gmake).
# =============================================================================

# Nothing but comments should come before this line.
default: all

# -----------------------------------------------------------------------------
# Application-specific variable settings.  It is safe to modify these.
# -----------------------------------------------------------------------------

# The application name that is built.  A value must be set for this!
APP_NAME	= pfObbTestApp

# The directory where the source files for this application are located.
srcdir  	= $(shell pwd)
srcdir_down = $(srcdir)/..
OBJDIR    = $(srcdir)/obj
GFX_BUILD_ROOT  = ${HOME}/Source/gfx/build
GFX_INC_ROOT = ${HOME}/Source/gfx

# -----------------------------------------------------------------------------
# Early information acquisition.  Before actually loading the Doozer
# application .mk file, individual internal files can be loaded here to get
# values that they set before Doozer puts all the pieces together.
#
# *** Be very careful with this section! ***
# -----------------------------------------------------------------------------
# Specify the directory containing the Doozer .mk files that will be used.
mk_basedir = $(HOME)/Source/mk


# Get the name of the host platform early.
include $(mk_basedir)/vrac.hosttype.mk

# Compiler flags needed for this application.  They are used as follows:
#
#    DEBUG_APP         - If set to TRUE, this application will be compiled with
#                        debugging symbols and no optimized symbols
#    OPTIM_APP         - If set to TRUE, this application will be compiled with
#                        optimized symbols and no debugging symbols
#    DEBUG_FLAGS       - Debugging flags passed to the compiler.  Settings this
#                        completely overrides what Doozer uses internally.
#    OPTIM_FLAGS       - Optimization flags passed to the compiler.  Settings
#                        this completely overrides what Doozer uses internally.
#    VJ_LIB_TYPE       - Specify the type of VR Juggler library used for
#                        linking.  The possibilities are debug or opt.
#    EXTRA_CFLAGS      - Extra application-specific C compiler flags
#    EXTRA_CXXFLAGS    - Extra application-specific C++ compiler flags
#    EXTRA_DEBUG_FLAGS - Extra application-specific compiler debugging flags
#    EXTRA_INCLUDES    - Extra include paths (-I... options) for the compilers
#    EXTRA_OPTIM_FLAGS - Extra application-specific compiler optimization flags
#    PF_PATH           - Path (including -L option) to the Performer libraries
#

DEBUG_APP		= TRUE
OPTIM_APP		= FALSE
#DEBUG_FLAGS		=
#OPTIM_FLAGS		= -O3
VJ_LIB_TYPE		= debug
EXTRA_CFLAGS		=
EXTRA_CXXFLAGS		=
EXTRA_INCLUDES		= -I${NSPR_BASE_DIR}/include -I/usr/include \
                      -I${GFX_INC_ROOT}/apps \
                      -I${GFX_INC_ROOT} -I${GFX_BUILD_ROOT}
#PF_PATH		=


ifeq ($(HOSTTYPE), IRIX64)
EXTRA_DEBUG_FLAGS = -D_DEBUG
EXTRA_OPTIM_FLAGS = -O2
OPTIM_FLAGS = -O2
endif

ifeq ($(HOSTTYPE), Linux)
#EXTRA_DEBUG_FLAGS	=
EXTRA_DEBUG_FLAGS = -pg -D_DEBUG
OPTIM_FLAGS	= -g -O2
EXTRA_LDFLAGS = -Wl,-noinhibit-exec
endif


#CXX = insure

# The list of all source files needed for this application.  Based on this,
# a list of object files is put in $(OBJS) automatically.
APP_SRCS	 = pfObbTestApp.cpp

PF_CORE_SRCS = pfAppCore.cpp \
               pfAppBase.cpp

SRCS = $(PF_CORE_SRCS) $(APP_SRCS)

# This is for extra libraries needed specfically for your application.  The
# general libraries needed for applications are in $(LIBS).
#EXTRA_LIBS	= -L$(HOME)/Source/gfx/build/lib -lgfx

ifeq ($(HOSTTYPE), IRIX64)
EXTRA_LIBS += -L${GFX_BUILD_ROOT}/lib32 -lgfx -L${NSPR_BASE_DIR}/lib/ -lnspr4 -lpthread
endif

ifeq ($(HOSTTYPE), Linux)
EXTRA_LIBS += -L${GFX_BUILD_ROOT}/lib -lgfx -L${NSPR_BASE_DIR}/lib/ -lnspr4 -lpthread
endif

# This is for extra system libraries (-lpthread for example) needed
# specifically for this application.  These are added to the linker command
# after all the basic libraries and all the system libraries.
EXTRA_SYS_LIBS	=

# Extend this as necessary to find source files that are not in the current
# directory.  Set EXTRA_PATH_FOR_SOURCES to all the directories that you
# have sources in. (current dir is already included by default)
EXTRA_PATH_FOR_SOURCES = $(srcdir_down)/pfCore

# Additional files and directories besides the standard ones that need to be
# removed by the 'clean' target.
CLEAN_FILES	=
CLEAN_DIRS	=

# The following include line MUST COME BEFORE the targets for compiling the
# application.
#
# To build an application, include one of the following basic files:
#
#     vrac.glapp.mk         - An ordinary OpenGL app
#     vrac.pfapp.mk         - An ordinary Performer app
#     vrac.juggler.glapp.mk - An ordinary VR Juggler OpenGL app
#     vrac.juggler.pfapp.mk - An ordinary VR Juggler Performer app
#
include $(mk_basedir)/vrac.pfapp.mk

# For additional features, include one or more of the following extra files:
#
#     vrac.aw.mk       - Add sound using AudioWorks
#     vrac.sl.mk       - Add sound using SL
#     vrac.switcher.mk - Add capabilities to get this application compiled
#                        into a VR Juggler switcher
#
#include /home/vr/apps/mk/...

# To modify various variables set internally by Doozer, make changes here.
# If a variable's value needs to be extended in some way, it can be done
# using += or := as follows:
#
#     VAR += <new settings>
#
#   or
#
#     VAR := <new settings> $(VAR) <more new settings>
#CXX = insure
#OS_LDFLAGS = -LANG:std -J2 -all

# -----------------------------------------------------------------------------
# Targets.
# -----------------------------------------------------------------------------
all: $(APP_NAME)

test_it:
	@echo "Src dir: " ${srcdir}
	@echo "Src down: " ${srcdir_down}
	@echo "Srcs: " ${SRCS}
	@touch test_it
	rm test_it

# Target for the application to be built.
$(APP_NAME): $(OBJS)    
	$(LINK) -o $@ $(OBJS) $(EXTRA_LIBS) $(LIBS)
