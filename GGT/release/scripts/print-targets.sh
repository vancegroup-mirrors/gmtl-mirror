#!/bin/sh

# -----------------------------------------------------------------------------
# Print out the target information for the build system.  These come directly
# from the comments at the top of the top-level Makefile.in.  Doing this in a
# shell script is a few orders of magnitude faster than echoing each line
# individually in the Makefile.
#
#	$Id: print-targets.sh,v 1.1.1.1 2002-01-18 20:43:12 allenb Exp $
# -----------------------------------------------------------------------------

cat <<EOF

Primary build/install targets are:
    world        - Build and install everything.
    buildworld   - Build everything (same as 'all').
    installworld - Install everything (same as 'install-all').  This
                   requires that 'buildworld' be successfully completed
                   beforehand.

Build targets are:
    all          - Build everything.
    debug        - Build the VR Juggler libraries (dynamic and static) with
                   debugging symbols turned on.
    dbg          - Build the debugging, static copy of the libraries.
    ddso         - Build the debugging, dynamic shared object version of
                   the libraries.
    optim        - Build the VR Juggler libraries (dynamic and static) with
                   optimization flags enabled.
    opt          - Build the optimized, static version of the libraries.
    dso          - Build the dynamic shared object version of the
                   libraries.

Library type targets are:
    static-libs  - Build the static versions of the libraries.  This target
                   depends on a correct value for \$(LIBDIR) (that does not
                   have a default value).
    shared-libs  - Build the dynamic shared versions of the libraries.
                   This target depends on a correct value for \$(LIBDIR)
                   (that does not have a default value).

Clean-up targets are:
    clean        - Clean up everything (uses common 'clean' target).
    cleandepend  - Clean up the dependency files (uses common 'cleandepend'
                   target).
    clobber      - Clean up everything and remove the directories containing
                   the compiled libraries and its object files.

The default target is 'debug'.

EOF
