/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */

/* Define to 1 to support Advanced Bit Manipulation */
#define HAVE_ABM 1

/* Define to 1 to support Multi-Precision Add-Carry Instruction Extensions */
#define HAVE_ADX 1

/* Define to 1 to support Advanced Encryption Standard New Instruction Set
   (AES-NI) */
#define HAVE_AES 1

/* Support Altivec instructions */
/* #undef HAVE_ALTIVEC */

/* Define to 1 to support Advanced Vector Extensions */
#define HAVE_AVX 1

/* Define to 1 to support Advanced Vector Extensions 2 */
#define HAVE_AVX2 1

/* Define to 1 to support AVX-512 Byte and Word Instructions */
#define HAVE_AVX512_BW 1

/* Define to 1 to support AVX-512 Conflict Detection Instructions */
#define HAVE_AVX512_CD 1

/* Define to 1 to support AVX-512 Doubleword and Quadword Instructions */
#define HAVE_AVX512_DQ 1

/* Define to 1 to support AVX-512 Exponential & Reciprocal Instructions */
/* #undef HAVE_AVX512_ER */

/* Define to 1 to support AVX-512 Foundation Extensions */
#define HAVE_AVX512_F 1

/* Define to 1 to support AVX-512 Integer Fused Multiply Add Instructions */
/* #undef HAVE_AVX512_IFMA */

/* Define to 1 to support AVX-512 Conflict Prefetch Instructions */
/* #undef HAVE_AVX512_PF */

/* Define to 1 to support AVX-512 Vector Byte Manipulation Instructions */
/* #undef HAVE_AVX512_VBMI */

/* Define to 1 to support AVX-512 Vector Length Extensions */
#define HAVE_AVX512_VL 1

/* Define to 1 to support Bit Manipulation Instruction Set 1 */
#define HAVE_BMI1 1

/* Define to 1 to support Bit Manipulation Instruction Set 2 */
#define HAVE_BMI2 1

/* define if the Boost library is available */
#define HAVE_BOOST /**/

/* define if the Boost::Filesystem library is available */
#define HAVE_BOOST_FILESYSTEM /**/

/* define if the Boost::IOStreams library is available */
#define HAVE_BOOST_IOSTREAMS /**/

/* define if the Boost::PROGRAM_OPTIONS library is available */
#define HAVE_BOOST_PROGRAM_OPTIONS /**/

/* define if the Boost::Serialization library is available */
#define HAVE_BOOST_SERIALIZATION /**/

/* define if the Boost::System library is available */
#define HAVE_BOOST_SYSTEM /**/

/* define if the Boost::Thread library is available */
#define HAVE_BOOST_THREAD /**/

/* define if CUDA is available */
/* #undef HAVE_CUDA */

/* define if the compiler supports basic C++11 syntax */
#define HAVE_CXX11 1

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Define to 1 to support Fused Multiply-Add Extensions 3 */
#define HAVE_FMA3 1

/* Define to 1 to support Fused Multiply-Add Extensions 4 */
/* #undef HAVE_FMA4 */

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the `bz2' library (-lbz2). */
#define HAVE_LIBBZ2 1

/* Define to 1 if you have the `z' library (-lz). */
#define HAVE_LIBZ 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 to support Multimedia Extensions */
#define HAVE_MMX 1

/* Define to 1 to support Memory Protection Extensions */
#define HAVE_MPX 1

/* Define to 1 to support Prefetch Vector Data Into Caches WT1 */
/* #undef HAVE_PREFETCHWT1 */

/* Define if you have POSIX threads libraries and header files. */
#define HAVE_PTHREAD 1

/* Have PTHREAD_PRIO_INHERIT. */
#define HAVE_PTHREAD_PRIO_INHERIT 1

/* Define to 1 to support Digital Random Number Generator */
#define HAVE_RDRND 1

/* Define to 1 to support Secure Hash Algorithm Extension */
/* #undef HAVE_SHA */

/* Define to 1 to support Streaming SIMD Extensions */
#define HAVE_SSE 1

/* Define to 1 to support Streaming SIMD Extensions */
#define HAVE_SSE2 1

/* Define to 1 to support Streaming SIMD Extensions 3 */
#define HAVE_SSE3 1

/* Define to 1 to support Streaming SIMD Extensions 4.1 */
#define HAVE_SSE4_1 1

/* Define to 1 to support Streaming SIMD Extensions 4.2 */
#define HAVE_SSE4_2 1

/* Define to 1 to support AMD Streaming SIMD Extensions 4a */
/* #undef HAVE_SSE4a */

/* Define to 1 to support Supplemental Streaming SIMD Extensions 3 */
#define HAVE_SSSE3 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Support VSX instructions */
/* #undef HAVE_VSX */

/* Define to 1 to support eXtended Operations Extensions */
/* #undef HAVE_XOP */

/* Define to the sub-directory where libtool stores uninstalled libraries. */
#define LT_OBJDIR ".libs/"

/* Name of package */
#define PACKAGE "hashclash"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "marc@marc-stevens.nl"

/* Define to the full name of this package. */
#define PACKAGE_NAME "HashClash"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "HashClash 1.0.0"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "hashclash"

/* Define to the home page for this package. */
#define PACKAGE_URL "https://github.com/cr-marcstevens/hashclash"

/* Define to the version of this package. */
#define PACKAGE_VERSION "1.0.0"

/* Define to necessary symbol if this constant uses a non-standard name on
   your system. */
/* #undef PTHREAD_CREATE_JOINABLE */

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Version number of package */
#define VERSION "1.0.0"

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
