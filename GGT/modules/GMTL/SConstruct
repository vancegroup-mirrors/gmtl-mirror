import os, string, sys
pj = os.path.join
import re

# Bring in the AutoDist build helper
sys.path.append('tools/build')
from AutoDist import *

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
   CXXFLAGS = ['-Wall']
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
   return Environment(ENV = os.environ)

def HasCppUnit(env):
   "Tests if the user has CppUnit available"
   sys.stdout.write('checking for cppunit... ')
   if env['with-cppunit'] == None:
      found = 0
   else:
      cfg = os.path.join(env['with-cppunit'], 'bin', 'cppunit-config')
      found = os.path.isfile(cfg)

   if found:
      sys.stdout.write('yes\n')
   else:
      sys.stdout.write('no\n')
   return found

def SetupCppUnit(env):
   "Sets up env for CppUnit"
   if not HasCppUnit(env):
      print 'ERROR: Could not find CppUnit installation.'
      sys.exit(1)
   cfg = pj(env['with-cppunit'], 'bin', 'cppunit-config')
   ParseConfig(env, cfg + ' --cflags --libs')
Export('SetupCppUnit')

def ValidateBoostOption(key, value, environ):
   "Validate the boost option settings"
   req_boost_version = 103000;
   sys.stdout.write("checking for %s [%s]..." % (key, value));

   if "BoostDir" == key:
      # Get the boost version
      boost_ver_filename = pj(value, 'boost', 'version.hpp');
      if not os.path.isfile(boost_ver_filename):
         sys.stdout.write("[%s] not found.\n" % boost_ver_filename);
         return False;
      ver_file = file(boost_ver_filename);
      ver_num = int(re.search("define\s+?BOOST_VERSION\s+?(\d*)", ver_file.read()).group(1));   # Matches 103000
      sys.stdout.write("found version: %s\n" % ver_num);
      if ver_num < req_boost_version:
         print "   Boost version to old: required version:%s\n" % req_boost_version;
         return False;
   elif "BoostVariantDir" == key:
      # Check for boost variant file
      boost_variant_filename = pj(value, 'boost', 'variant.hpp');
      if not os.path.isfile(boost_variant_filename):
         sys.stdout.write("not found.\n");
         return False;
      else:
         sys.stdout.write("found.\n");
   else:
      assert False, "Invalid boost key";


def AddBoostOptions(opts):
   opts.Add('BoostDir',
           help = 'Boost installation directory (boost dir must exhist under this directory": default: CppUnitDir="/usr/local/include"',
           finder = '/usr/local/include',
           validater=ValidateBoostOption);



#------------------------------------------------------------------------------
# Grok the arguments to this build
#------------------------------------------------------------------------------
EnsureSConsVersion(0,10)

# Figure out what version of GMTL we're building
GMTL_VERSION = GetGMTLVersion()
print 'Building GMTL Version: %i.%i.%i' % GMTL_VERSION

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
elif GetPlatform() == 'linux':
   baseEnv = BuildLinuxEnvironment()
elif GetPlatform() == 'win32':
   baseEnv = BuildWin32Environment()
else:
   print 'Unsupported build environment: ' + GetPlatform()
   sys.exit(-1)
Export('baseEnv')

opts = Options('config.cache')
opts.Add('with-cppunit',
         'CppUnit installation directory',
         '/usr/local',
         lambda k,v,env=None: WhereIs(pj(v, 'bin', 'cppunit-config')) != None
        )
AddBoostOptions(opts);   
opts.Update(baseEnv)
Help(opts.GenerateHelpText(baseEnv))


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
   Test/SConscript
   Test/TestSuite/SConscript
   Test/TestSuite/TestCases/SConscript
   Test/TestSuite/TestCases/InfoTests/SConscript
   tools/build/AutoDist.py
"""))
Export('pkg')

# Process subdirectories
subdirs = Split('gmtl')
if HasCppUnit(baseEnv):
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
