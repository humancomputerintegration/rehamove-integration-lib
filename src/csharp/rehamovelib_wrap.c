/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 4.0.0
 *
 * This file is not intended to be easily readable and contains a number of
 * coding conventions designed to improve portability and efficiency. Do not make
 * changes to this file unless you know what you are doing--modify the SWIG
 * interface file instead.
 * ----------------------------------------------------------------------------- */


#ifndef SWIGCSHARP
#define SWIGCSHARP
#endif


/* -----------------------------------------------------------------------------
 *  This section contains generic SWIG labels for method/variable
 *  declarations/attributes, and other compiler dependent labels.
 * ----------------------------------------------------------------------------- */

/* template workaround for compilers that cannot correctly implement the C++ standard */
#ifndef SWIGTEMPLATEDISAMBIGUATOR
# if defined(__SUNPRO_CC) && (__SUNPRO_CC <= 0x560)
#  define SWIGTEMPLATEDISAMBIGUATOR template
# elif defined(__HP_aCC)
/* Needed even with `aCC -AA' when `aCC -V' reports HP ANSI C++ B3910B A.03.55 */
/* If we find a maximum version that requires this, the test would be __HP_aCC <= 35500 for A.03.55 */
#  define SWIGTEMPLATEDISAMBIGUATOR template
# else
#  define SWIGTEMPLATEDISAMBIGUATOR
# endif
#endif

/* inline attribute */
#ifndef SWIGINLINE
# if defined(__cplusplus) || (defined(__GNUC__) && !defined(__STRICT_ANSI__))
#   define SWIGINLINE inline
# else
#   define SWIGINLINE
# endif
#endif

/* attribute recognised by some compilers to avoid 'unused' warnings */
#ifndef SWIGUNUSED
# if defined(__GNUC__)
#   if !(defined(__cplusplus)) || (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
#     define SWIGUNUSED __attribute__ ((__unused__))
#   else
#     define SWIGUNUSED
#   endif
# elif defined(__ICC)
#   define SWIGUNUSED __attribute__ ((__unused__))
# else
#   define SWIGUNUSED
# endif
#endif

#ifndef SWIG_MSC_UNSUPPRESS_4505
# if defined(_MSC_VER)
#   pragma warning(disable : 4505) /* unreferenced local function has been removed */
# endif
#endif

#ifndef SWIGUNUSEDPARM
# ifdef __cplusplus
#   define SWIGUNUSEDPARM(p)
# else
#   define SWIGUNUSEDPARM(p) p SWIGUNUSED
# endif
#endif

/* internal SWIG method */
#ifndef SWIGINTERN
# define SWIGINTERN static SWIGUNUSED
#endif

/* internal inline SWIG method */
#ifndef SWIGINTERNINLINE
# define SWIGINTERNINLINE SWIGINTERN SWIGINLINE
#endif

/* exporting methods */
#if defined(__GNUC__)
#  if (__GNUC__ >= 4) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4)
#    ifndef GCC_HASCLASSVISIBILITY
#      define GCC_HASCLASSVISIBILITY
#    endif
#  endif
#endif

#ifndef SWIGEXPORT
# if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#   if defined(STATIC_LINKED)
#     define SWIGEXPORT
#   else
#     define SWIGEXPORT __declspec(dllexport)
#   endif
# else
#   if defined(__GNUC__) && defined(GCC_HASCLASSVISIBILITY)
#     define SWIGEXPORT __attribute__ ((visibility("default")))
#   else
#     define SWIGEXPORT
#   endif
# endif
#endif

/* calling conventions for Windows */
#ifndef SWIGSTDCALL
# if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#   define SWIGSTDCALL __stdcall
# else
#   define SWIGSTDCALL
# endif
#endif

/* Deal with Microsoft's attempt at deprecating C standard runtime functions */
#if !defined(SWIG_NO_CRT_SECURE_NO_DEPRECATE) && defined(_MSC_VER) && !defined(_CRT_SECURE_NO_DEPRECATE)
# define _CRT_SECURE_NO_DEPRECATE
#endif

/* Deal with Microsoft's attempt at deprecating methods in the standard C++ library */
#if !defined(SWIG_NO_SCL_SECURE_NO_DEPRECATE) && defined(_MSC_VER) && !defined(_SCL_SECURE_NO_DEPRECATE)
# define _SCL_SECURE_NO_DEPRECATE
#endif

/* Deal with Apple's deprecated 'AssertMacros.h' from Carbon-framework */
#if defined(__APPLE__) && !defined(__ASSERT_MACROS_DEFINE_VERSIONS_WITHOUT_UNDERSCORES)
# define __ASSERT_MACROS_DEFINE_VERSIONS_WITHOUT_UNDERSCORES 0
#endif

/* Intel's compiler complains if a variable which was never initialised is
 * cast to void, which is a common idiom which we use to indicate that we
 * are aware a variable isn't used.  So we just silence that warning.
 * See: https://github.com/swig/swig/issues/192 for more discussion.
 */
#ifdef __INTEL_COMPILER
# pragma warning disable 592
#endif


#include <stdlib.h>
#include <string.h>
#include <stdio.h>


/* Support for throwing C# exceptions from C/C++. There are two types: 
 * Exceptions that take a message and ArgumentExceptions that take a message and a parameter name. */
typedef enum {
  SWIG_CSharpApplicationException,
  SWIG_CSharpArithmeticException,
  SWIG_CSharpDivideByZeroException,
  SWIG_CSharpIndexOutOfRangeException,
  SWIG_CSharpInvalidCastException,
  SWIG_CSharpInvalidOperationException,
  SWIG_CSharpIOException,
  SWIG_CSharpNullReferenceException,
  SWIG_CSharpOutOfMemoryException,
  SWIG_CSharpOverflowException,
  SWIG_CSharpSystemException
} SWIG_CSharpExceptionCodes;

typedef enum {
  SWIG_CSharpArgumentException,
  SWIG_CSharpArgumentNullException,
  SWIG_CSharpArgumentOutOfRangeException
} SWIG_CSharpExceptionArgumentCodes;

typedef void (SWIGSTDCALL* SWIG_CSharpExceptionCallback_t)(const char *);
typedef void (SWIGSTDCALL* SWIG_CSharpExceptionArgumentCallback_t)(const char *, const char *);

typedef struct {
  SWIG_CSharpExceptionCodes code;
  SWIG_CSharpExceptionCallback_t callback;
} SWIG_CSharpException_t;

typedef struct {
  SWIG_CSharpExceptionArgumentCodes code;
  SWIG_CSharpExceptionArgumentCallback_t callback;
} SWIG_CSharpExceptionArgument_t;

static SWIG_CSharpException_t SWIG_csharp_exceptions[] = {
  { SWIG_CSharpApplicationException, NULL },
  { SWIG_CSharpArithmeticException, NULL },
  { SWIG_CSharpDivideByZeroException, NULL },
  { SWIG_CSharpIndexOutOfRangeException, NULL },
  { SWIG_CSharpInvalidCastException, NULL },
  { SWIG_CSharpInvalidOperationException, NULL },
  { SWIG_CSharpIOException, NULL },
  { SWIG_CSharpNullReferenceException, NULL },
  { SWIG_CSharpOutOfMemoryException, NULL },
  { SWIG_CSharpOverflowException, NULL },
  { SWIG_CSharpSystemException, NULL }
};

static SWIG_CSharpExceptionArgument_t SWIG_csharp_exceptions_argument[] = {
  { SWIG_CSharpArgumentException, NULL },
  { SWIG_CSharpArgumentNullException, NULL },
  { SWIG_CSharpArgumentOutOfRangeException, NULL }
};

static void SWIGUNUSED SWIG_CSharpSetPendingException(SWIG_CSharpExceptionCodes code, const char *msg) {
  SWIG_CSharpExceptionCallback_t callback = SWIG_csharp_exceptions[SWIG_CSharpApplicationException].callback;
  if ((size_t)code < sizeof(SWIG_csharp_exceptions)/sizeof(SWIG_CSharpException_t)) {
    callback = SWIG_csharp_exceptions[code].callback;
  }
  callback(msg);
}

static void SWIGUNUSED SWIG_CSharpSetPendingExceptionArgument(SWIG_CSharpExceptionArgumentCodes code, const char *msg, const char *param_name) {
  SWIG_CSharpExceptionArgumentCallback_t callback = SWIG_csharp_exceptions_argument[SWIG_CSharpArgumentException].callback;
  if ((size_t)code < sizeof(SWIG_csharp_exceptions_argument)/sizeof(SWIG_CSharpExceptionArgument_t)) {
    callback = SWIG_csharp_exceptions_argument[code].callback;
  }
  callback(msg, param_name);
}


#ifdef __cplusplus
extern "C" 
#endif
SWIGEXPORT void SWIGSTDCALL SWIGRegisterExceptionCallbacks_rehamovelib(
                                                SWIG_CSharpExceptionCallback_t applicationCallback,
                                                SWIG_CSharpExceptionCallback_t arithmeticCallback,
                                                SWIG_CSharpExceptionCallback_t divideByZeroCallback, 
                                                SWIG_CSharpExceptionCallback_t indexOutOfRangeCallback, 
                                                SWIG_CSharpExceptionCallback_t invalidCastCallback,
                                                SWIG_CSharpExceptionCallback_t invalidOperationCallback,
                                                SWIG_CSharpExceptionCallback_t ioCallback,
                                                SWIG_CSharpExceptionCallback_t nullReferenceCallback,
                                                SWIG_CSharpExceptionCallback_t outOfMemoryCallback, 
                                                SWIG_CSharpExceptionCallback_t overflowCallback, 
                                                SWIG_CSharpExceptionCallback_t systemCallback) {
  SWIG_csharp_exceptions[SWIG_CSharpApplicationException].callback = applicationCallback;
  SWIG_csharp_exceptions[SWIG_CSharpArithmeticException].callback = arithmeticCallback;
  SWIG_csharp_exceptions[SWIG_CSharpDivideByZeroException].callback = divideByZeroCallback;
  SWIG_csharp_exceptions[SWIG_CSharpIndexOutOfRangeException].callback = indexOutOfRangeCallback;
  SWIG_csharp_exceptions[SWIG_CSharpInvalidCastException].callback = invalidCastCallback;
  SWIG_csharp_exceptions[SWIG_CSharpInvalidOperationException].callback = invalidOperationCallback;
  SWIG_csharp_exceptions[SWIG_CSharpIOException].callback = ioCallback;
  SWIG_csharp_exceptions[SWIG_CSharpNullReferenceException].callback = nullReferenceCallback;
  SWIG_csharp_exceptions[SWIG_CSharpOutOfMemoryException].callback = outOfMemoryCallback;
  SWIG_csharp_exceptions[SWIG_CSharpOverflowException].callback = overflowCallback;
  SWIG_csharp_exceptions[SWIG_CSharpSystemException].callback = systemCallback;
}

#ifdef __cplusplus
extern "C" 
#endif
SWIGEXPORT void SWIGSTDCALL SWIGRegisterExceptionArgumentCallbacks_rehamovelib(
                                                SWIG_CSharpExceptionArgumentCallback_t argumentCallback,
                                                SWIG_CSharpExceptionArgumentCallback_t argumentNullCallback,
                                                SWIG_CSharpExceptionArgumentCallback_t argumentOutOfRangeCallback) {
  SWIG_csharp_exceptions_argument[SWIG_CSharpArgumentException].callback = argumentCallback;
  SWIG_csharp_exceptions_argument[SWIG_CSharpArgumentNullException].callback = argumentNullCallback;
  SWIG_csharp_exceptions_argument[SWIG_CSharpArgumentOutOfRangeException].callback = argumentOutOfRangeCallback;
}


/* Callback for returning strings to C# without leaking memory */
typedef char * (SWIGSTDCALL* SWIG_CSharpStringHelperCallback)(const char *);
static SWIG_CSharpStringHelperCallback SWIG_csharp_string_callback = NULL;


#ifdef __cplusplus
extern "C" 
#endif
SWIGEXPORT void SWIGSTDCALL SWIGRegisterStringCallback_rehamovelib(SWIG_CSharpStringHelperCallback callback) {
  SWIG_csharp_string_callback = callback;
}


/* Contract support */

#define SWIG_contract_assert(nullreturn, expr, msg) if (!(expr)) {SWIG_CSharpSetPendingExceptionArgument(SWIG_CSharpArgumentOutOfRangeException, msg, ""); return nullreturn; } else


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "smpt_ll_client.h"

typedef struct {
	char port_name[64];
	Smpt_device device;
} RehamoveDevice;

extern int add(int x, int y);
extern RehamoveDevice * open_port(const char * port_name);
extern void close_port(RehamoveDevice * r);
extern void pulse(RehamoveDevice * r, char * channel, int current, int pulse_width);
extern void custom_pulse(RehamoveDevice * r, char * channel, int num_points, float c0, int w0, float c1, int w1, float c2, int w2, float c3, int w3, float c4, int w4, float c5, int w5, float c6, int w6, float c7, int w7, float c8, int w8, float c9, int w9, float c10, int w10, float c11, int w11, float c12, int w12, float c13, int w13, float c14, int w14, float c15, int w15);
extern int battery(RehamoveDevice * r);


#ifdef __cplusplus
extern "C" {
#endif

SWIGEXPORT void SWIGSTDCALL CSharp_RehamoveDevice_port_name_set(void * jarg1, char * jarg2) {
  RehamoveDevice *arg1 = (RehamoveDevice *) 0 ;
  char *arg2 ;
  
  arg1 = (RehamoveDevice *)jarg1; 
  arg2 = (char *)jarg2; 
  {
    if(arg2) {
      strncpy((char*)arg1->port_name, (const char *)arg2, 64-1);
      arg1->port_name[64-1] = 0;
    } else {
      arg1->port_name[0] = 0;
    }
  }
}


SWIGEXPORT char * SWIGSTDCALL CSharp_RehamoveDevice_port_name_get(void * jarg1) {
  char * jresult ;
  RehamoveDevice *arg1 = (RehamoveDevice *) 0 ;
  char *result = 0 ;
  
  arg1 = (RehamoveDevice *)jarg1; 
  result = (char *)(char *) ((arg1)->port_name);
  jresult = SWIG_csharp_string_callback((const char *)result); 
  return jresult;
}


SWIGEXPORT void SWIGSTDCALL CSharp_RehamoveDevice_device_set(void * jarg1, void * jarg2) {
  RehamoveDevice *arg1 = (RehamoveDevice *) 0 ;
  Smpt_device arg2 ;
  Smpt_device *argp2 ;
  
  arg1 = (RehamoveDevice *)jarg1; 
  argp2 = (Smpt_device *)jarg2; 
  if (!argp2) {
    SWIG_CSharpSetPendingExceptionArgument(SWIG_CSharpArgumentNullException, "Attempt to dereference null Smpt_device", 0);
    return ;
  }
  arg2 = *argp2; 
  if (arg1) (arg1)->device = arg2;
}


SWIGEXPORT void * SWIGSTDCALL CSharp_RehamoveDevice_device_get(void * jarg1) {
  void * jresult ;
  RehamoveDevice *arg1 = (RehamoveDevice *) 0 ;
  Smpt_device result;
  
  arg1 = (RehamoveDevice *)jarg1; 
  result =  ((arg1)->device);
  {
    Smpt_device * resultptr = (Smpt_device *) malloc(sizeof(Smpt_device));
    memmove(resultptr, &result, sizeof(Smpt_device));
    jresult = resultptr;
  }
  return jresult;
}


SWIGEXPORT void * SWIGSTDCALL CSharp_new_RehamoveDevice() {
  void * jresult ;
  RehamoveDevice *result = 0 ;
  
  result = (RehamoveDevice *)calloc(1, sizeof(RehamoveDevice));
  jresult = (void *)result; 
  return jresult;
}


SWIGEXPORT void SWIGSTDCALL CSharp_delete_RehamoveDevice(void * jarg1) {
  RehamoveDevice *arg1 = (RehamoveDevice *) 0 ;
  
  arg1 = (RehamoveDevice *)jarg1; 
  free((char *) arg1);
}


SWIGEXPORT int SWIGSTDCALL CSharp_add(int jarg1, int jarg2) {
  int jresult ;
  int arg1 ;
  int arg2 ;
  int result;
  
  arg1 = (int)jarg1; 
  arg2 = (int)jarg2; 
  result = (int)add(arg1,arg2);
  jresult = result; 
  return jresult;
}


SWIGEXPORT void * SWIGSTDCALL CSharp_open_port(char * jarg1) {
  void * jresult ;
  char *arg1 = (char *) 0 ;
  RehamoveDevice *result = 0 ;
  
  arg1 = (char *)jarg1; 
  result = (RehamoveDevice *)open_port((char const *)arg1);
  jresult = (void *)result; 
  return jresult;
}


SWIGEXPORT void SWIGSTDCALL CSharp_close_port(void * jarg1) {
  RehamoveDevice *arg1 = (RehamoveDevice *) 0 ;
  
  arg1 = (RehamoveDevice *)jarg1; 
  close_port(arg1);
}


SWIGEXPORT void SWIGSTDCALL CSharp_pulse(void * jarg1, char * jarg2, int jarg3, int jarg4) {
  RehamoveDevice *arg1 = (RehamoveDevice *) 0 ;
  char *arg2 = (char *) 0 ;
  int arg3 ;
  int arg4 ;
  
  arg1 = (RehamoveDevice *)jarg1; 
  arg2 = (char *)jarg2; 
  arg3 = (int)jarg3; 
  arg4 = (int)jarg4; 
  pulse(arg1,arg2,arg3,arg4);
}


SWIGEXPORT void SWIGSTDCALL CSharp_custom_pulse(void * jarg1, char * jarg2, int jarg3, float jarg4, int jarg5, float jarg6, int jarg7, float jarg8, int jarg9, float jarg10, int jarg11, float jarg12, int jarg13, float jarg14, int jarg15, float jarg16, int jarg17, float jarg18, int jarg19, float jarg20, int jarg21, float jarg22, int jarg23, float jarg24, int jarg25, float jarg26, int jarg27, float jarg28, int jarg29, float jarg30, int jarg31, float jarg32, int jarg33, float jarg34, int jarg35) {
  RehamoveDevice *arg1 = (RehamoveDevice *) 0 ;
  char *arg2 = (char *) 0 ;
  int arg3 ;
  float arg4 ;
  int arg5 ;
  float arg6 ;
  int arg7 ;
  float arg8 ;
  int arg9 ;
  float arg10 ;
  int arg11 ;
  float arg12 ;
  int arg13 ;
  float arg14 ;
  int arg15 ;
  float arg16 ;
  int arg17 ;
  float arg18 ;
  int arg19 ;
  float arg20 ;
  int arg21 ;
  float arg22 ;
  int arg23 ;
  float arg24 ;
  int arg25 ;
  float arg26 ;
  int arg27 ;
  float arg28 ;
  int arg29 ;
  float arg30 ;
  int arg31 ;
  float arg32 ;
  int arg33 ;
  float arg34 ;
  int arg35 ;
  
  arg1 = (RehamoveDevice *)jarg1; 
  arg2 = (char *)jarg2; 
  arg3 = (int)jarg3; 
  arg4 = (float)jarg4; 
  arg5 = (int)jarg5; 
  arg6 = (float)jarg6; 
  arg7 = (int)jarg7; 
  arg8 = (float)jarg8; 
  arg9 = (int)jarg9; 
  arg10 = (float)jarg10; 
  arg11 = (int)jarg11; 
  arg12 = (float)jarg12; 
  arg13 = (int)jarg13; 
  arg14 = (float)jarg14; 
  arg15 = (int)jarg15; 
  arg16 = (float)jarg16; 
  arg17 = (int)jarg17; 
  arg18 = (float)jarg18; 
  arg19 = (int)jarg19; 
  arg20 = (float)jarg20; 
  arg21 = (int)jarg21; 
  arg22 = (float)jarg22; 
  arg23 = (int)jarg23; 
  arg24 = (float)jarg24; 
  arg25 = (int)jarg25; 
  arg26 = (float)jarg26; 
  arg27 = (int)jarg27; 
  arg28 = (float)jarg28; 
  arg29 = (int)jarg29; 
  arg30 = (float)jarg30; 
  arg31 = (int)jarg31; 
  arg32 = (float)jarg32; 
  arg33 = (int)jarg33; 
  arg34 = (float)jarg34; 
  arg35 = (int)jarg35; 
  custom_pulse(arg1,arg2,arg3,arg4,arg5,arg6,arg7,arg8,arg9,arg10,arg11,arg12,arg13,arg14,arg15,arg16,arg17,arg18,arg19,arg20,arg21,arg22,arg23,arg24,arg25,arg26,arg27,arg28,arg29,arg30,arg31,arg32,arg33,arg34,arg35);
}


SWIGEXPORT int SWIGSTDCALL CSharp_battery(void * jarg1) {
  int jresult ;
  RehamoveDevice *arg1 = (RehamoveDevice *) 0 ;
  int result;
  
  arg1 = (RehamoveDevice *)jarg1; 
  result = (int)battery(arg1);
  jresult = result; 
  return jresult;
}


#ifdef __cplusplus
}
#endif

