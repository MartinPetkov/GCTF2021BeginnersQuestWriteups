#ifndef _HASHCLASHLIB_HASHCLASH_CONFIG_H
#define _HASHCLASHLIB_HASHCLASH_CONFIG_H 1
 
/* lib/hashclash/config.h. Generated automatically at end of configure. */
/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */

/* Define to 1 to support Advanced Bit Manipulation */
#ifndef HASHCLASH_HAVE_ABM
#define HASHCLASH_HAVE_ABM 1
#endif

/* Define to 1 to support Multi-Precision Add-Carry Instruction Extensions */
#ifndef HASHCLASH_HAVE_ADX
#define HASHCLASH_HAVE_ADX 1
#endif

/* Define to 1 to support Advanced Encryption Standard New Instruction Set
   (AES-NI) */
#ifndef HASHCLASH_HAVE_AES
#define HASHCLASH_HAVE_AES 1
#endif

/* Support Altivec instructions */
/* #undef HAVE_ALTIVEC */

/* Define to 1 to support Advanced Vector Extensions */
#ifndef HASHCLASH_HAVE_AVX
#define HASHCLASH_HAVE_AVX 1
#endif

/* Define to 1 to support Advanced Vector Extensions 2 */
#ifndef HASHCLASH_HAVE_AVX2
#define HASHCLASH_HAVE_AVX2 1
#endif

/* Define to 1 to support AVX-512 Byte and Word Instructions */
#ifndef HASHCLASH_HAVE_AVX512_BW
#define HASHCLASH_HAVE_AVX512_BW 1
#endif

/* Define to 1 to support AVX-512 Conflict Detection Instructions */
#ifndef HASHCLASH_HAVE_AVX512_CD
#define HASHCLASH_HAVE_AVX512_CD 1
#endif

/* Define to 1 to support AVX-512 Doubleword and Quadword Instructions */
#ifndef HASHCLASH_HAVE_AVX512_DQ
#define HASHCLASH_HAVE_AVX512_DQ 1
#endif

/* Define to 1 to support AVX-512 Exponential & Reciprocal Instructions */
/* #undef HAVE_AVX512_ER */

/* Define to 1 to support AVX-512 Foundation Extensions */
#ifndef HASHCLASH_HAVE_AVX512_F
#define HASHCLASH_HAVE_AVX512_F 1
#endif

/* Define to 1 to support AVX-512 Integer Fused Multiply Add Instructions */
/* #undef HAVE_AVX512_IFMA */

/* Define to 1 to support AVX-512 Conflict Prefetch Instructions */
/* #undef HAVE_AVX512_PF */

/* Define to 1 to support AVX-512 Vector Byte Manipulation Instructions */
/* #undef HAVE_AVX512_VBMI */

/* Define to 1 to support AVX-512 Vector Length Extensions */
#ifndef HASHCLASH_HAVE_AVX512_VL
#define HASHCLASH_HAVE_AVX512_VL 1
#endif

/* Define to 1 to support Bit Manipulation Instruction Set 1 */
#ifndef HASHCLASH_HAVE_BMI1
#define HASHCLASH_HAVE_BMI1 1
#endif

/* Define to 1 to support Bit Manipulation Instruction Set 2 */
#ifndef HASHCLASH_HAVE_BMI2
#define HASHCLASH_HAVE_BMI2 1
#endif

/* define if the Boost library is available */
#ifndef HASHCLASH_HAVE_BOOST
#define HASHCLASH_HAVE_BOOST /**/
#endif

/* define if the Boost::Filesystem library is available */
#ifndef HASHCLASH_HAVE_BOOST_FILESYSTEM
#define HASHCLASH_HAVE_BOOST_FILESYSTEM /**/
#endif

/* define if the Boost::IOStreams library is available */
#ifndef HASHCLASH_HAVE_BOOST_IOSTREAMS
#define HASHCLASH_HAVE_BOOST_IOSTREAMS /**/
#endif

/* define if the Boost::PROGRAM_OPTIONS library is available */
#ifndef HASHCLASH_HAVE_BOOST_PROGRAM_OPTIONS
#define HASHCLASH_HAVE_BOOST_PROGRAM_OPTIONS /**/
#endif

/* define if the Boost::Serialization library is available */
#ifndef HASHCLASH_HAVE_BOOST_SERIALIZATION
#define HASHCLASH_HAVE_BOOST_SERIALIZATION /**/
#endif

/* define if the Boost::System library is available */
#ifndef HASHCLASH_HAVE_BOOST_SYSTEM
#define HASHCLASH_HAVE_BOOST_SYSTEM /**/
#endif

/* define if the Boost::Thread library is available */
#ifndef HASHCLASH_HAVE_BOOST_THREAD
#define HASHCLASH_HAVE_BOOST_THREAD /**/
#endif

/* define if CUDA is available */
/* #undef HAVE_CUDA */

/* define if the compiler supports basic C++11 syntax */
#ifndef HASHCLASH_HAVE_CXX11
#define HASHCLASH_HAVE_CXX11 1
#endif

/* Define to 1 if you have the <dlfcn.h> header file. */
#ifndef HASHCLASH_HAVE_DLFCN_H
#define HASHCLASH_HAVE_DLFCN_H 1
#endif

/* Define to 1 to support Fused Multiply-Add Extensions 3 */
#ifndef HASHCLASH_HAVE_FMA3
#define HASHCLASH_HAVE_FMA3 1
#endif

/* Define to 1 to support Fused Multiply-Add Extensions 4 */
/* #undef HAVE_FMA4 */

/* Define to 1 if you have the <inttypes.h> header file. */
#ifndef HASHCLASH_HAVE_INTTYPES_H
#define HASHCLASH_HAVE_INTTYPES_H 1
#endif

/* Define to 1 if you have the `bz2' library (-lbz2). */
#ifndef HASHCLASH_HAVE_LIBBZ2
#define HASHCLASH_HAVE_LIBBZ2 1
#endif

/* Define to 1 if you have the `z' library (-lz). */
#ifndef HASHCLASH_HAVE_LIBZ
#define HASHCLASH_HAVE_LIBZ 1
#endif

/* Define to 1 if you have the <memory.h> header file. */
#ifndef HASHCLASH_HAVE_MEMORY_H
#define HASHCLASH_HAVE_MEMORY_H 1
#endif

/* Define to 1 to support Multimedia Extensions */
#ifndef HASHCLASH_HAVE_MMX
#define HASHCLASH_HAVE_MMX 1
#endif

/* Define to 1 to support Memory Protection Extensions */
#ifndef HASHCLASH_HAVE_MPX
#define HASHCLASH_HAVE_MPX 1
#endif

/* Define to 1 to support Prefetch Vector Data Into Caches WT1 */
/* #undef HAVE_PREFETCHWT1 */

/* Define if you have POSIX threads libraries and header files. */
#ifndef HASHCLASH_HAVE_PTHREAD
#define HASHCLASH_HAVE_PTHREAD 1
#endif

/* Have PTHREAD_PRIO_INHERIT. */
#ifndef HASHCLASH_HAVE_PTHREAD_PRIO_INHERIT
#define HASHCLASH_HAVE_PTHREAD_PRIO_INHERIT 1
#endif

/* Define to 1 to support Digital Random Number Generator */
#ifndef HASHCLASH_HAVE_RDRND
#define HASHCLASH_HAVE_RDRND 1
#endif

/* Define to 1 to support Secure Hash Algorithm Extension */
/* #undef HAVE_SHA */

/* Define to 1 to support Streaming SIMD Extensions */
#ifndef HASHCLASH_HAVE_SSE
#define HASHCLASH_HAVE_SSE 1
#endif

/* Define to 1 to support Streaming SIMD Extensions */
#ifndef HASHCLASH_HAVE_SSE2
#define HASHCLASH_HAVE_SSE2 1
#endif

/* Define to 1 to support Streaming SIMD Extensions 3 */
#ifndef HASHCLASH_HAVE_SSE3
#define HASHCLASH_HAVE_SSE3 1
#endif

/* Define to 1 to support Streaming SIMD Extensions 4.1 */
#ifndef HASHCLASH_HAVE_SSE4_1
#define HASHCLASH_HAVE_SSE4_1 1
#endif

/* Define to 1 to support Streaming SIMD Extensions 4.2 */
#ifndef HASHCLASH_HAVE_SSE4_2
#define HASHCLASH_HAVE_SSE4_2 1
#endif

/* Define to 1 to support AMD Streaming SIMD Extensions 4a */
/* #undef HAVE_SSE4a */

/* Define to 1 to support Supplemental Streaming SIMD Extensions 3 */
#ifndef HASHCLASH_HAVE_SSSE3
#define HASHCLASH_HAVE_SSSE3 1
#endif

/* Define to 1 if you have the <stdint.h> header file. */
#ifndef HASHCLASH_HAVE_STDINT_H
#define HASHCLASH_HAVE_STDINT_H 1
#endif

/* Define to 1 if you have the <stdlib.h> header file. */
#ifndef HASHCLASH_HAVE_STDLIB_H
#define HASHCLASH_HAVE_STDLIB_H 1
#endif

/* Define to 1 if you have the <strings.h> header file. */
#ifndef HASHCLASH_HAVE_STRINGS_H
#define HASHCLASH_HAVE_STRINGS_H 1
#endif

/* Define to 1 if you have the <string.h> header file. */
#ifndef HASHCLASH_HAVE_STRING_H
#define HASHCLASH_HAVE_STRING_H 1
#endif

/* Define to 1 if you have the <sys/stat.h> header file. */
#ifndef HASHCLASH_HAVE_SYS_STAT_H
#define HASHCLASH_HAVE_SYS_STAT_H 1
#endif

/* Define to 1 if you have the <sys/types.h> header file. */
#ifndef HASHCLASH_HAVE_SYS_TYPES_H
#define HASHCLASH_HAVE_SYS_TYPES_H 1
#endif

/* Define to 1 if you have the <unistd.h> header file. */
#ifndef HASHCLASH_HAVE_UNISTD_H
#define HASHCLASH_HAVE_UNISTD_H 1
#endif

/* Support VSX instructions */
/* #undef HAVE_VSX */

/* Define to 1 to support eXtended Operations Extensions */
/* #undef HAVE_XOP */

/* Define to the sub-directory where libtool stores uninstalled libraries. */
#ifndef HASHCLASH_LT_OBJDIR
#define HASHCLASH_LT_OBJDIR ".libs/"
#endif

/* Name of package */
#ifndef HASHCLASH_PACKAGE
#define HASHCLASH_PACKAGE "hashclash"
#endif

/* Define to the address where bug reports for this package should be sent. */
#ifndef HASHCLASH_PACKAGE_BUGREPORT
#define HASHCLASH_PACKAGE_BUGREPORT "marc@marc-stevens.nl"
#endif

/* Define to the full name of this package. */
#ifndef HASHCLASH_PACKAGE_NAME
#define HASHCLASH_PACKAGE_NAME "HashClash"
#endif

/* Define to the full name and version of this package. */
#ifndef HASHCLASH_PACKAGE_STRING
#define HASHCLASH_PACKAGE_STRING "HashClash 1.0.0"
#endif

/* Define to the one symbol short name of this package. */
#ifndef HASHCLASH_PACKAGE_TARNAME
#define HASHCLASH_PACKAGE_TARNAME "hashclash"
#endif

/* Define to the home page for this package. */
#ifndef HASHCLASH_PACKAGE_URL
#define HASHCLASH_PACKAGE_URL "https://github.com/cr-marcstevens/hashclash"
#endif

/* Define to the version of this package. */
#ifndef HASHCLASH_PACKAGE_VERSION
#define HASHCLASH_PACKAGE_VERSION "1.0.0"
#endif

/* Define to necessary symbol if this constant uses a non-standard name on
   your system. */
/* #undef PTHREAD_CREATE_JOINABLE */

/* Define to 1 if you have the ANSI C header files. */
#ifndef HASHCLASH_STDC_HEADERS
#define HASHCLASH_STDC_HEADERS 1
#endif

/* Version number of package */
#ifndef HASHCLASH_VERSION
#define HASHCLASH_VERSION "1.0.0"
#endif

/* Define for Solaris 2.5.1 so the uint32_t typedef from <sys/synch.h>,
   <pthread.h>, or <semaphore.h> is not used. If the typedef were allowed, the
   #define below would cause a syntax error. */
/* #undef _UINT32_T */

/* Define for Solaris 2.5.1 so the uint64_t typedef from <sys/synch.h>,
   <pthread.h>, or <semaphore.h> is not used. If the typedef were allowed, the
   #define below would cause a syntax error. */
/* #undef _UINT64_T */

/* Define for Solaris 2.5.1 so the uint8_t typedef from <sys/synch.h>,
   <pthread.h>, or <semaphore.h> is not used. If the typedef were allowed, the
   #define below would cause a syntax error. */
/* #undef _UINT8_T */

/* Define to `unsigned int' if <sys/types.h> does not define. */
/* #undef size_t */

/* Define to the type of an unsigned integer type of width exactly 16 bits if
   such a type exists and the standard includes do not define it. */
/* #undef uint16_t */

/* Define to the type of an unsigned integer type of width exactly 32 bits if
   such a type exists and the standard includes do not define it. */
/* #undef uint32_t */

/* Define to the type of an unsigned integer type of width exactly 64 bits if
   such a type exists and the standard includes do not define it. */
/* #undef uint64_t */

/* Define to the type of an unsigned integer type of width exactly 8 bits if
   such a type exists and the standard includes do not define it. */
/* #undef uint8_t */
 
/* once: _HASHCLASHLIB_HASHCLASH_CONFIG_H */
#endif
