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
   if profile:
      CXXFLAGS.extend(['-pg'])
      LINKFLAGS.extend(['-pg'])

   # Debug or optimize build?
   if optimize:
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
   if profile:
      CXXFLAGS.extend([])
      LINKFLAGS.extend([])

   # Debug or optimize build?
   if optimize:
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

# Check for optimize
optimize = 0
if ARGUMENTS.get('opt', 0):
   optimize = 1

# Check for profiling
profile = 0
if ARGUMENTS.get('profile', 0):
   profile = 1

# Check for an install prefix
PREFIX = '/usr/local'
if ARGUMENTS.get('prefix'):
   PREFIX = ARGUMENTS['prefix']
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

# Process subdirectories
subdirs = Split("""
   gmtl
   Test
""")

for s in subdirs:
   SConscript(dirs = s)

# install target
baseEnv.Alias("install", PREFIX)

# Build everything by default
Default('.')
