import os, string, sys
pj = os.path.join


#------------------------------------------------------------------------------
# Define some generally useful functions
#------------------------------------------------------------------------------
def RequireSConsVersion(minimum):
   "Check the version of SCons being run is at least the given minimum."
   import SCons
   if float(SCons.__version__) < float(minimum):
      print "SCons too old: " + SCons.__version__ + " < " + str(minimum)
      sys.exit(-1)

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

def BuildLinuxEnvironment():
   "Builds a base environment for other modules to build on set up for linux"
   global optimize, profile

   CXX = 'g++3'
   LINK = 'g++3'
   CXXFLAGS = ['-Wall']
   LINKFLAGS = []

   # Enable profiling?
   if profile != 'no':
      CXXFLAGS.extend(['-pg'])
      LINKFLAGS.extend(['-pg'])

   # Debug or optimize build?
   if optimize != 'no':
      CXXFLAGS.extend(['-DNDEBUG', '-O2'])
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
      LIBS        = [])

def BuildIRIXEnvironment():
   "Builds a base environment for other modules to build on set up for IRIX"
   global optimize, profile

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
      LIBS        = [])


#------------------------------------------------------------------------------
# Grok the arguments to this build
#------------------------------------------------------------------------------
RequireSConsVersion(0.08)

# Figure out what version of GMTL we're building
GMTL_VERSION = GetGMTLVersion()
print 'Building GMTL Version: %i.%i.%i' % GMTL_VERSION

# Get command-line arguments
optimize = ARGUMENTS.get('--optimize', 'no')
profile = ARGUMENTS.get('--profile', 'no')
PREFIX = ARGUMENTS.get('--prefix', '/usr/local')
Export('PREFIX')

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


def CreateConfig(target, source, env):
   "Creates the prefix-config file users use to compile against this library"
   global GMTL_VERSION
   import re

   targets = map(lambda x: str(x), target)
   sources = map(lambda x: str(x), source)

   print "Generating " + targets[0]

   contents = open(sources[0], 'r').read()

   contents = re.sub('(%[{}])', r'#\1', contents)
   contents = re.sub('@prefix@', PREFIX, contents)
   contents = re.sub('@exec_prefix@', '${prefix}', contents)
   contents = re.sub('@gmtl_extra_cxxflags@', '', contents)
   contents = re.sub('@gmtl_extra_include_dirs@', '', contents)
   contents = re.sub('@VERSION_MAJOR@', str(GMTL_VERSION[0]), contents)
   contents = re.sub('@VERSION_MINOR@', str(GMTL_VERSION[1]), contents)
   contents = re.sub('@VERSION_PATCH@', str(GMTL_VERSION[2]), contents)
   contents = re.sub('@includedir@', PREFIX+'/include', contents)
   contents = re.sub('@gmtl_cxxflags@', '', contents)

   open(targets[0], 'w').write(contents)
   os.chmod(targets[0], 0755)

   return 0

# Process subdirectories
subdirs = Split("""
   gmtl
   Test
""")

for s in subdirs:
   SConscript(dirs = s)

# install target
baseEnv.Alias('install', PREFIX)

# Define a builder for the gmtl-config script
config_builder = Builder(action = CreateConfig)

# Build everything by default
Default('.')

env = baseEnv.Copy(BUILDERS = {'ConfigBuilder' : config_builder})
env.ConfigBuilder('gmtl-config','gmtl-config.in')
env.Depends('gmtl-config', 'gmtl/Version.h')
env.Install(pj(PREFIX, 'bin'), 'gmtl-config')
