#ifndef _BSYS_CFG_H_
#define _BSYS_CFG_H_

/*
 * ----------------------------------------------------------------------------
 * Generated from acconfig.h.
 * ----------------------------------------------------------------------------
 */

@TOP@

/* Define if building on FreeBSD. */
#undef BSYS_OS_FreeBSD

/* Define if building on IRIX. */
#undef BSYS_OS_IRIX
#undef _BSD_TYPES

/* Define if building on Linux. */
#undef BSYS_OS_Linux

/* Define if building on a Win32 platform. */
#undef BSYS_OS_Win32
#undef WIN32
#undef _MBCS

/* Define all of the following if POSIX threads are needed. */
#undef BSYS_THREAD_SCOPE
#undef BSYS_POSIX_C_SOURCE
#undef _THREAD_SAFE
#undef RWSTD_MULTI_THREAD
#undef RW_MULTI_THREAD
#undef _REENTRANT

/* Define if using POSIX threads Draft 4. */
#undef _PTHREADS_DRAFT_4

/* Define if using POSIX threads Draft 10 (the "final" draft). */
#undef _PTHREADS_DRAFT_10

@BOTTOM@

#endif	/* _BSYS_CFG_H_ */
