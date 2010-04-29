/** @file    host.c
 ** @author  Andrea Vedaldi
 ** @brief   Host - Definition
 **/

/* AUTORIGHTS
Copyright (C) 2007-09 Andrea Vedaldi and Brian Fulkerson

This file is part of VLFeat, available under the terms of the
GNU GPLv2, or (at your option) any later version.
*/

#include "host.h"
#include "generic.h"

/**
 @file host.h

 This module provides functionalities to identify the
 host operating system, C compiler,
 and CPU architecture. It also provides a few features
 to abstract from such details.

 - @ref host-os "Host operating system"
 - @ref host-compiler "Host compiler"
   - @ref host-compiler-data-model "Data models"
   - @ref host-compiler-other      "Oter compiler specific features"
 - @ref host-arch "Host CPU architecture"
   - @ref host-arch-endianness "Endianness"

 @see http://predef.sourceforge.net/index.php

 @section host-os Host operating system

 The module defines a symbol to identify the host operating system:
 ::VL_OS_WIN for Windows, ::VL_OS_LINUX for Linux, ::VL_OS_MACOSX for
 Mac OS X, and so on.

 @section host-compiler Host compiler

 The module defines a symbol to identify the host compiler:
 ::VL_COMPILER_MSC for Microsoft Visual C++, ::VL_COMPILER_GNUC for
 GNU C, and so on. The (integer) value of such symbols corresponds the
 version of the compiler.

 The module defines a symbol to identify the data model of the
 compiler: ::VL_COMPILER_ILP32, ::VL_COMPILER_LP32, or
 ::VL_COMPILER_LP64 (see Sect. @ref host-compiler-data-model).  For
 convenience, it also defines a number of atomic types of prescribed
 width (::vl_int8, ::vl_int16, ::vl_int32, etc.).

 @remark While some of such functionalities are provided by the
 standard header @c stdint.h, the latter is not supported by all
 platforms.

 @subsection host-compiler-data-model Data models

 The C language defines a number of atomic data types (such as @c
 char, @c short, @c int and so on). The number of bits (width) used to
 represent each data type depends on the compiler data model.  The
 following table summarizes the relevant conventions:

 <table><caption><b>Compiler data models.</b> The table shows
 how many bits are allocated to each atomic data type according to
 each model.</caption>
 <tr style="font-weight:bold;">
 <td>Data model</td>
 <td><code>short</code></td>
 <td><code>int</code></td>
 <td><code>long</code></td>
 <td><code>long long</code></td>
 <td><code>void*</code></td>
 <td>Compiler</td>
 </tr>
 <tr>
 <td>ILP32</td>
 <td style="background-color:#ffa;">16</td>
 <td style="background-color:#afa;">32</td>
 <td style="background-color:#afa;">32</td>
 <td >64</td>
 <td style="background-color:#afa;">32</td>
 <td>common 32 bit architectures</td>
 </tr>
 <tr>
 <td>LP64</td>
 <td style="background-color:#ffa;">16</td>
 <td style="background-color:#afa;">32</td>
 <td>64</td>
 <td>64</td>
 <td>64</td>
 <td>UNIX-64 (Linux, Mac OS X)</td>
 </tr>
 <tr>
 <td>ILP64</td>
 <td style="background-color:#ffa;">16</td>
 <td>64</td>
 <td>64</td>
 <td>64</td>
 <td>64</td>
 <td>Alpha, Cray</td>
 </tr>
 <tr>
 <td>SLIP64</td>
 <td>64</td>
 <td>64</td>
 <td>64</td>
 <td>64</td>
 <td>64</td>
 <td></td>
 </tr>
 <tr>
 <td>LLP64</td>
 <td style="background-color:#ffa;">16</td>
 <td style="background-color:#afa;">32</td>
 <td style="background-color:#afa;">32</td>
 <td>64</td>
 <td>64</td>
 <td>Windows-64</td>
 </tr>
 </table>

 @subsection host-compiler-other Other compiler-specific features

 The module provides the macro ::VL_EXPORT to declare symbols exported
 from the library and the macro ::VL_INLINE to declare inline
 functions.  Such features are not part of the C89 standard, and
 change depending on the compiler.

 @par "Example:"
 The following header file declares a function @c f that
 should be visible from outside the library.
 @code
 #include <vl/generic.h>
 VL_EXPORT void f () ;
 VL_EXPORT int i ;
 @endcode
 Notice that the macro ::VL_EXPORT needs not to be included again
 when the function is defined.

 @par "Example:"
 The following header file declares an inline function @c f:
 @code
 #include <vl/generic.h>
 VL_INLINE int f() ;

 VL_INLINE int f() { return 1 ; }
 @endcode

 Here the first instruction defines the function @c f, where the
 second declares it. Notice that since this is an inline function, its
 definition must be found in the header file rather than in an
 implementation file.  Notice also that definition and declaration can
 be merged.

 These macros translate according to the following tables:

 <table style="font-size:70%;">
 <caption>Macros for exporting library symbols</caption>
 <tr>
 <td>Platform</td>
 <td>Macro name</td>
 <td>Value when building the library</td>
 <td>Value when importing the library</td>
 </tr>
 <tr>
 <td>Unix/GCC</td>
 <td>::VL_EXPORT</td>
 <td>empty (assumes <c>-visibility=hidden</c> GCC option)</td>
 <td><c>__attribute__((visibility ("default")))</c></td>
 </tr>
 <tr>
 <td>Win/Visual C++</td>
 <td>::VL_EXPORT</td>
 <td>@c __declspec(dllexport)</td>
 <td>@c __declspec(dllimport)</td>
 </tr>
 </table>

 <table style="font-size:70%;">
 <caption>Macros for declaring inline functions</caption>
 <tr>
 <td>Platform</td>
 <td>Macro name</td>
 <td>Value</td>
 </tr>
 <tr>
 <td>Unix/GCC</td>
 <td>::VL_INLINE</td>
 <td>static inline</td>
 </tr>
 <tr>
 <td>Win/Visual C++</td>
 <td>::VL_INLINE</td>
 <td>static __inline</td>
 </tr>
 </table>

 @section host-arch Host CPU architecture

 The module defines a symbol to identify the host CPU architecture:
 ::VL_ARCH_IX86 for Intel x86, ::VL_ARCH_IA64 for Intel 64, and so on.

 @subsection host-arch-endianness Endianness

 The module defines a symbol to identify the host CPU endianness:
 ::VL_ARCH_BIG_ENDIAN for big endian and ::VL_ARCH_LITTLE_ENDIAN for
 little endian. The functions ::vl_swap_host_big_endianness_8(),
 ::vl_swap_host_big_endianness_4(), ::vl_swap_host_big_endianness_2()
 to change the endianness of data (from/to host and network order).

 Recall that <em>endianness</em> concerns the way multi-byte data
 types (such as 16, 32 and 64 bits integers) are stored into the
 addressable memory.  All CPUs uses a contiguous address range to
 store atomic data types (e.g. a 16-bit integer could be assigned to
 the addresses <c>0x10001</c> and <c>0x10002</c>), but the order may
 differ.

 - The convention is <em>big endian</em>, or in <em>network
   order</em>, if the most significant byte of the multi-byte data
   types is assigned to the smaller memory address. This is the
   convention used for instance by the PPC architecture.

 - The convention is <em>little endian</em> if the least significant
   byte is assigned to the smaller memory address. This is the
   convention used for instance by the x86 architecture.

 @remark The names &ldquo;big endian&rdquo; and &ldquo;little
 endian&rdquo; are a little confusing. &ldquo;Big endian&rdquo; means
 &ldquo;big endian first&rdquo;, i.e.  the address of the most
 significant byte comes first. Similarly, &ldquo;little endian&rdquo;
 means &ldquo;little endian first&rdquo;, in the sense that the
 address of the least significant byte comes first.

 Endianness is a concern when data is either exchanged with processors
 that use different conventions, transmitted over a network, or stored
 to a file. For the latter two cases, one usually saves data in big
 endian (network) order regardless of the host CPU.

@section Multi-threading host-threads

The file defines ::VL_THREADS_WIN if multi-threading support is
enabled and the host supports Windows threads and ::VL_THREAD_POSIX if
it supports POSIX threads.

 **/

/** @def VL_OS_LINUX
 ** @brief Defined if the host operating system is Linux.
 **/

/** @def VL_OS_MACOSX
 ** @brief Defined if the host operating system is Mac OS X.
 **/

/** @def VL_OS_WIN
 ** @brief Defined if the host operating system is Windows (32 or 64)
 **/

/** @def VL_OS_WIN64
 ** @brief Defined if the host operating system is Windows-64.
 **/

/** @def VL_COMPILER_GNUC
 ** @brief Defined if the host compiler is GNU C.
 **
 ** This macro is defined if the compiler is GNUC.
 ** Its value is calculated as
 ** @code
 ** 10000 * MAJOR + 100 * MINOR + PATCHLEVEL
 ** @endcode
 ** @see @ref host-compiler
 **/

/** @def VL_COMPILER_MSC
 ** @brief Defined if the host compiler is Microsoft Visual C++.
 ** @see @ref host-compiler
 **/

/** @def VL_COMPILER_LLP64
 ** @brief Defined if the host compiler data model is LLP64.
 ** @see @ref host-compiler-data-model
 **/

/** @def VL_COMPILER_LP64
 ** @brief Defined if the host compiler data model is LP64.
 ** @see @ref host-compiler-data-model
 **/

/** @def VL_COMPILER_ILP32
 ** @brief Defined if the host compiler data model is ILP32.
 ** @see @ref host-compiler-data-model
 **/

/** @def VL_ARCH_IX86
 ** @brief Defined if the host CPU is of the Intel x86 family.
 ** @see @ref host-arch
 **/

/** @def VL_ARCH_IA64
 ** @brief Defined if the host CPU is of the Intel Architecture-64 family.
 ** @see @ref host-arch
 **/

/** @def VL_ARCH_LITTLE_ENDIAN
 ** @brief Defined if the host CPU is little endian
 ** @see @ref host-arch-endianness
 **/

/** @def VL_ARCH_BIG_ENDIAN
 ** @brief Defined if the host CPU is big endian
 ** @see @ref host-arch-endianness
 **/

/** @def VL_INLINE
 ** @brief Adds appropriate inline function qualifier
 ** @see @ref host-compiler-others
 **/

/** @def VL_EXPORT
 ** @brief Declares a DLL exported symbol
 ** @see @ref host-compiler-others
 **/

/** @def VL_ENABLE_THREADS
 ** @brief Defined if multi-threading support is enabled
 **
 ** Define this symbol to enable multi-threading support.
 **/

#ifdef __DOXYGEN__
#define VL_ENABLE_THREADS
#endif

/** @def VL_THREADS_WIN
 ** @biref Defined if the host uses Windows threads.
 **/

/** @def VL_THREADS_POSIX
 ** @brief Defiend if the host uses POISX threads.
 **/

/** --------------------------------------------------------------- */

#if defined(VL_ARCH_IX86) || defined(VL_ARCH_IA64) || defined(VL_ARCH_X64)
#define HAS_CPUID
#else
#undef HAS_CPUID
#endif

#if defined(HAS_CPUID) & defined(VL_COMPILER_MSC)
#include <intrin.h>
VL_INLINE void
_vl_cpuid (vl_int32* info, int function)
{
  __cpuid(info, function) ;
}
#endif

#if defined(HAS_CPUID) & defined(VL_COMPILER_GNUC)
VL_INLINE void
_vl_cpuid (vl_int32* info, int function)
{
#if defined(VL_ARCH_IX86) && (defined(__PIC__) || defined(__pic__))
  /* This version is compatible with -fPIC on x386 targets. This special
   * case is required becaus
   * on such platform -fPIC alocates ebx as global offset table pointer.
   * Note that =r below will be mapped to a register different from ebx,
   * so the code is sound. */
  __asm__ __volatile__
  ("pushl %%ebx      \n" /* save %ebx */
   "cpuid            \n"
   "movl %%ebx, %1   \n" /* save what cpuid just put in %ebx */
   "popl %%ebx       \n" /* restore the old %ebx */
   : "=a"(info[0]), "=r"(info[1]), "=c"(info[2]), "=d"(info[3])
   : "a"(function)
   : "cc") ; /* clobbered (cc=condition codes) */
#else /* no -fPIC or -fPIC with a 64-bit target */
  __asm__ __volatile__
  ("cpuid"
   : "=a"(info[0]), "=b"(info[1]), "=c"(info[2]), "=d"(info[3])
   : "a"(function)
   : "cc") ;
#endif
}

#endif

void
_vl_x86cpu_info_init (VlX86CpuInfo *self)
{
  vl_int32 info [4] ;
  int max_func = 0 ;
  _vl_cpuid(info, 0) ;
  max_func = info[0] ;
  *((vl_int32*)self->vendorString+0) = info[1] ;
  *((vl_int32*)self->vendorString+1) = info[3] ;
  *((vl_int32*)self->vendorString+2) = info[2] ;

  if (max_func >= 1) {
    _vl_cpuid(info, 1) ;
    self->hasMMX   = info[3] & (1 << 23) ;
    self->hasSSE   = info[3] & (1 << 25) ;
    self->hasSSE2  = info[3] & (1 << 26) ;
    self->hasSSE3  = info[2] & (1 <<  0) ;
    self->hasSSE41 = info[2] & (1 << 19) ;
    self->hasSSE42 = info[2] & (1 << 20) ;
  }
}

void
_vl_x86cpu_info_print (VlX86CpuInfo const *self)
{
  VL_PRINTF(" CPU %s", self->vendorString) ;
  VL_PRINTF(": MMX:%s",           VL_YESNO(self->hasMMX)) ;
  VL_PRINTF(", SSE:%s",           VL_YESNO(self->hasSSE)) ;
  VL_PRINTF(", SSE2:%s",          VL_YESNO(self->hasSSE2)) ;
  VL_PRINTF(", SSE3:%s",          VL_YESNO(self->hasSSE3)) ;
  VL_PRINTF(", SSE4.1:%s",        VL_YESNO(self->hasSSE41)) ;
  VL_PRINTF(", SSE4.2:%s\n",      VL_YESNO(self->hasSSE42)) ;
}

/** ------------------------------------------------------------------
 ** @brief Print compiler information
 **
 ** Print compiler, host, and configuration information. These
 ** parameters are static and set at compile time.
 **/

VL_EXPORT void
vl_print_compiler_info ()
{
  char const *arch = 0, *endian = 0, *comp = 0, *dm = 0, *th = 0 ;
  int compver ;
#ifdef VL_ARCH_X64
  arch = "X64" ;
#endif
#ifdef VL_ARCH_IA64
  arch = "IA64" ;
#endif
#ifdef VL_ARCH_IX86
  arch = "IX86" ;
#endif
#ifdef VL_ARCH_PPC
  arch = "PPC" ;
#endif

#ifdef VL_ARCH_BIG_ENDIAN
  endian = "big endian" ;
#endif
#ifdef VL_ARCH_LITTLE_ENDIAN
  endian = "little endian" ;
#endif

#ifdef VL_COMPILER_MSC
  comp = "Microsoft Visual C++" ;
  compver = VL_COMPILER_MSC ;
#endif
#ifdef VL_COMPILER_GNUC
  comp = "GNU C" ;
  compver = VL_COMPILER_GNUC ;
#endif

#ifdef VL_COMPILER_LP64
  dm = "LP64" ;
#endif
#ifdef VL_COMPILER_LLP64
  dm = "LP64" ;
#endif
#ifdef VL_COMPILER_ILP32
  dm = "ILP32" ;
#endif

#ifdef VL_ENABLE_THREADS
#ifdef VL_THREADS_WIN
  th = "Windows" ;
#elif VL_THREADS_POSIX
  th = "Posix" ;
#endif
#else
  th = "None" ;
#endif

  VL_PRINTF(" Static config: %s %d, %s, %s, %s, threads:%s\n",
            comp, compver, dm, arch, endian, th) ;
}



