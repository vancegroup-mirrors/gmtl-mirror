import os, string, sys
import re
pj = os.path.join

# Bring in the AutoDist build helper
sys.path.append('tools/build')
from AutoDist import *

enable_python = False
have_cppunit  = False

#------------------------------------------------------------------------------
# Define some generally useful functions
#------------------------------------------------------------------------------
def GetGMTLVersion():
   "Gets the GMTL version from the gmtl/Version.h header"
   import re

   contents = open('gmtl/Version.h', 'r').read()
   major = re.compile('.*(#define *GMTL_VERSION_MAJOR *(\d+)).*', re.DOTALL).sub(r'\2', contents)
   minor = re.compile('.*(#define *GMTL_VERSION_MINOR *(\d+)).*', re.DOTALL).sub(r'\2', contents)
   patch = re.compile('.*(#define *GMTL_VERSION_PATCH *(\d+)).*', re.DOTALL).sub(r'\2', contents)
   return (int(major), int(minor), int(patch))

def GetPlatform():
   "Determines what platform this build is being run on."
   if string.find(sys.platform, 'irix') != -1:
      return 'irix'
   elif string.find(sys.platform, 'linux') != -1:
      return 'linux'
   elif string.find(sys.platform, 'cygwin') != -1:
      return 'win32'
   elif string.find(os.name, 'win32') != -1:
      return 'win32'
   else:
      return sys.platform
Export('GetPlatform')

def CreateConfig(target, source, env):
   "Creates the xxx-config file users use to compile against this library"
   import re

   targets = map(lambda x: str(x), target)
   sources = map(lambda x: str(x), source)

   submap = env['submap']

   # Build each target from its source
   for i in range(len(targets)):
      print "Generating config file " + targets[i]
      contents = open(sources[i], 'r').read()

      # Go through the substitution dictionary and modify the contents read in
      # from the source file
      for key, value in submap.items():
         contents = re.sub(re.escape(key), re.escape(value), contents)

      # Write out the target file with the new contents
      open(targets[0], 'w').write(contents)
      os.chmod(targets[0], 0755)
   return 0

def BuildLinuxEnvironment():
   "Builds a base environment for other modules to build on set up for linux"
   global optimize, profile, builders

   CXX = WhereIs('g++3') or 'g++'
   LINK = CXX
   CXXFLAGS = ['-Wall', '-pipe']
   LINKFLAGS = []

   # Enable profiling?
   if profile != 'no':
      CXXFLAGS.extend(['-pg'])
      LINKFLAGS.extend(['-pg'])

   # Debug or optimize build?
   if optimize != 'no':
      CXXFLAGS.extend(['-DNDEBUG', '-g', '-O2'])
   else:
      CXXFLAGS.extend(['-D_DEBUG', '-g'])

   return Environment(
      ENV         = os.environ,

      CXX         = CXX,
      CXXFLAGS    = CXXFLAGS,
      LINK        = LINK,
      LINKFLAGS   = LINKFLAGS,
      CPPPATH     = [],
      LIBPATH     = [],
      LIBS        = [],
   )

def BuildIRIXEnvironment():
   "Builds a base environment for other modules to build on set up for IRIX"
   global optimize, profile, builders

   CXX = 'CC'
   LINK = 'CC'
   CXXFLAGS = ['-n32', '-mips3', '-LANG:std', '-w2']
   LINKFLAGS = CXXFLAGS

   # Enable profiling?
   if profile != 'no':
      CXXFLAGS.extend([])
      LINKFLAGS.extend([])

   # Debug or optimize build?
   if optimize != 'no':
      CXXFLAGS.extend(['-DNDEBUG', '-O2'])
   else:
      CXXFLAGS.extend(['-D_DEBUG', '-g', '-gslim'])

   return Environment(
      ENV         = os.environ,
      CXX         = CXX,
      CXXFLAGS    = CXXFLAGS,
      LINK        = LINK,
      LINKFLAGS   = LINKFLAGS,
      CPPPATH     = [],
      LIBPATH     = [],
      LIBS        = [],
   )

def BuildWin32Environment():
   env = Environment(ENV = os.environ)
   for t in ['msvc', 'mslink']:
      Tool(t)(env)

   # We need exception handling support turned on for Boost.Python.
   env['CXXFLAGS'] += '/EHsc'

   return env

# ########################################
# Options
# ########################################
def ValidateBoostOption(key, value, environ):
   "Validate the boost option settings"
   global enable_python
   req_boost_version = 103000
   sys.stdout.write("checking for %s [%s]...\n" % (key, value))

   if "BoostPythonDir" == key:
      # Get the boost version
      boost_ver_filename = pj(value, 'include', 'boost', 'version.hpp')
      if not os.path.isfile(boost_ver_filename):
         sys.stdout.write("[%s] not found.\n" % boost_ver_filename)
         Exit()
         return False
      ver_file = file(boost_ver_filename)

      # Matches 103000
      ver_num = int(re.search("define\s+?BOOST_VERSION\s+?(\d*)",
                              ver_file.read()).group(1))
      sys.stdout.write("found version: %s\n" % ver_num)

      if ver_num < req_boost_version:
         print "   Boost version to old: required version:%s\n" % req_boost_version
         Exit()
         return False

      # Check on the libraries that I need to use
      if enable_python:
         if GetPlatform() == 'win32':
            boost_python_lib_name = pj(value, 'lib', 'boost_python.dll')
         else:
            boost_python_lib_name = pj(value, 'lib', 'libboost_python.a')

         if not os.path.isfile(boost_python_lib_name):
            print "[%s] not found."%boost_python_lib_name
            Exit()
            return False

         if GetPlatform() == 'irix':
            environ.Append(BoostCPPPATH = [pj(value, 'include'), pj(value, 'include', 'boost', 'compatibility', 'cpp_c_headers')])
         else:
            environ.Append(BoostCPPPATH = [pj(value, 'include')])

         environ.Append(BoostLIBPATH = [pj(value, 'lib')])
         environ.Append(BoostLIBS = ['boost_python'])

   else:
      assert False, "Invalid Boost key"

def ApplyBoostOptions(env):
   global enable_python
   if enable_python:
      env.Append(CPPPATH = env["BoostCPPPATH"])
      env.Append(LIBPATH = env["BoostLIBPATH"])
      env.Append(LIBS = env["BoostLIBS"])

def AddBoostOptions(opts):
   opts.Add('BoostPythonDir',
            help = 'Boost.Python installation directory (boost dir must exist under this directory": default: BoostPythonDir="/usr/local/include"',
            default = '/usr/local/include', validator = ValidateBoostOption)

def ValidatePythonOption(key, value, environ):
   "Validate the Python option settings"
   global enable_python
   sys.stdout.write("checking for %s [%s]...\n" % (key, value))

   if "EnablePython" == key:
      enable_python = value

      if enable_python:
         required_version = 2.2
         python = WhereIs('python')
         if not python:
            enable_python = False
            print 'WARNING: Can\'t find python executable'
            return False

         py_cmd = python + ' -c \'import sys; print sys.prefix; print sys.version[:3]\''
         prefix = ''
         py_ver = ''

         # XXX: Something is broken with trying to use os.popen() on Windows.
         # This is a hack to work around that until something real can be
         # found to fix it.  Basically, this makes the assumption that the
         # Python installation being used to invoke scons is the same as the
         # one against which PyGMTL will be compiled.
         if GetPlatform() == 'win32':
            (prefix, py_ver) = (sys.prefix, sys.version[:3])
         else:
            (prefix, py_ver) = string.split(os.popen(py_cmd).read())

         # Version must match
         if float(py_ver) < required_version:
            print 'WARNING: Python version ' + py_ver + ' != ' + str(required_version)
            enable_python = False
         else:
            # Build up the env information
            if GetPlatform() == 'win32':
               environ.Append(PythonCPPPATH = [pj(prefix, 'include')])
            else:
               environ.Append(PythonCPPPATH = [pj(prefix, 'include', 'python'+py_ver)])
   else:
      assert False, "Invalid Python key"

   return enable_python

def ApplyPythonOptions(env):
   env.Append(CPPPATH = env["PythonCPPPATH"])

def AddPythonOptions(opts):
   opts.Add('EnablePython',
            help = 'Enable compilation of PyGMTL; default: EnablePython=False',
            default = False, validator = ValidatePythonOption)

def ValidateCppUnitOption(key, value, environ):
   "Validate the CppUnit option settings"
   global have_cppunit
   sys.stdout.write("checking for %s [%s]...\n" % (key, value))

   if "CppUnitDir" == key:
      cfg = os.path.join(environ['CppUnitDir'], 'bin', 'cppunit-config')
      found = os.path.isfile(cfg)

      if found:
         sys.stdout.write('yes\n')
         have_cppunit = True
      else:
         sys.stdout.write('no\n')
         have_cppunit = False
   else:
      assert False, "Invalid CppUnit key"
      found = 0

   return found

def ApplyCppUnitOptions(env):
   global have_cppunit
   if have_cppunit:
      cfg = pj(env['CppUnitDir'], 'bin', 'cppunit-config')
      ParseConfig(env, cfg + ' --cflags --libs')

def AddCppUnitOptions(opts):
   opts.Add('CppUnitDir',
            help = 'CppUnit installation directory (cppunit dir must exist under this directory": default: CppUnitDir="/usr/local/include"',
            default = '/usr/local/include', validator = ValidateCppUnitOption)

Export('ApplyBoostOptions ApplyPythonOptions ApplyCppUnitOptions')

#------------------------------------------------------------------------------
# Grok the arguments to this build
#------------------------------------------------------------------------------
EnsureSConsVersion(0,91)

# Figure out what version of GMTL we're building
GMTL_VERSION = GetGMTLVersion()
print 'Building GMTL Version: %i.%i.%i' % GMTL_VERSION

help_text = "\n---- GMTL Build System ----\n"

# Get command-line arguments
optimize = ARGUMENTS.get('optimize', 'no')
profile = ARGUMENTS.get('profile', 'no')
PREFIX = ARGUMENTS.get('prefix', '/usr/local')
Prefix(PREFIX)
Export('PREFIX')

# Create the extra builders
# Define a builder for the gmtl-config script
builders = {
   'ConfigBuilder'   : Builder(action = CreateConfig)
}

# Create and export the base environment
if GetPlatform() == 'irix':
   baseEnv = BuildIRIXEnvironment()
elif GetPlatform() == 'linux' or GetPlatform()[:7] == 'freebsd':
   baseEnv = BuildLinuxEnvironment()
elif GetPlatform() == 'win32':
   baseEnv = BuildWin32Environment()
else:
   print 'Unsupported build environment: ' + GetPlatform()
   sys.exit(-1)
baseEnv['enable_python'] = False
Export('baseEnv')

opts = Options('config.cache')
AddCppUnitOptions(opts)
AddPythonOptions(opts)
AddBoostOptions(opts)

if not SCons.Script.options.help_msg:
   opts.Update(baseEnv);
   opts.Save('options.cache', baseEnv);

help_text += "Platform: " + GetPlatform() + "\n";
help_text += str(baseEnv["TOOLS"]) + "\n";
help_text += opts.GenerateHelpText(baseEnv);
help_text += """
You can store configuration options in the file: options.custom
This file will be loaded each time.  Note: Options are cached in the file: options.cache.
"""

if not SCons.Script.options.help_msg:
   print "Preparing build settings...\n"

   # Create the GMTL package
   pkg = Package('gmtl', '%i.%i.%i' % GMTL_VERSION)
   pkg.addExtraDist(Split("""
      AUTHORS
      ChangeLog
      COPYING
      gmtl-config.in
      SConstruct
      docs/Makefile
      docs/docbook.mk
      docs/gmtl.doxy
      docs/gmtl.latex.doxy
      docs/gmtl.man.doxy
      docs/version.mk.doxy
      docs/programmer.guide/Makefile
      docs/programmer.guide/guide.xml
      gmtl/gmtl.doxygen
      gmtl/SConscript
      gmtl/External/SConscript
      gmtl/Util/SConscript
      python/SConscript
      Test/SConscript
      Test/TestSuite/SConscript
      Test/TestSuite/TestCases/SConscript
      Test/TestSuite/TestCases/InfoTests/SConscript
      tools/build/AutoDist.py
   """))
   Export('pkg')

   # Process subdirectories
   subdirs = Split('gmtl')
   if enable_python:
      subdirs.append('python')
   if have_cppunit:
      subdirs.append('Test')
   SConscript(dirs = subdirs)

   # Setup the builder for gmtl-config
   env = baseEnv.Copy(BUILDERS = builders)
   env.ConfigBuilder('gmtl-config','gmtl-config.in',
      submap = {
         '@prefix@'                    : PREFIX,
         '@exec_prefix@'               : '${prefix}',
         '@gmtl_cxxflags@'             : '',
         '@includedir@'                : pj(PREFIX, 'include'),
         '@gmtl_extra_cxxflags@'       : '',
         '@gmtl_extra_include_dirs@'   : '',
         '@VERSION_MAJOR@'             : str(GMTL_VERSION[0]),
         '@VERSION_MINOR@'             : str(GMTL_VERSION[1]),
         '@VERSION_PATCH@'             : str(GMTL_VERSION[2]),
      }
   )
   env.Depends('gmtl-config', 'gmtl/Version.h')
   env.Install(pj(PREFIX, 'bin'), 'gmtl-config')

   pkg.build()
   MakeSourceDist(pkg, env)

# Build everything by default
Default('.')
