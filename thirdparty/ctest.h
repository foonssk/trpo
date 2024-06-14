/* Copyright 2011-2023 Bas van den Berg
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef CTEST_H
#define CTEST_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __GNUC__
#define CTEST_IMPL_FORMAT_PRINTF(a, b) __attribute__ ((format (printf, a, b)))
#else
#define CTEST_IMPL_FORMAT_PRINTF(a, b)
#endif

#include <inttypes.h> /* intmax_t, uintmax_t, PRI* */
#include <stdbool.h>  /* bool, true, false */
#include <stddef.h>   /* size_t */

typedef void (*ctest_nullary_run_func) (void);
typedef void (*ctest_unary_run_func) (void *);
typedef void (*ctest_setup_func) (void *);
typedef void (*ctest_teardown_func) (void *);

union ctest_run_func_union {
    ctest_nullary_run_func nullary;
    ctest_unary_run_func unary;
};

#define CTEST_IMPL_PRAGMA(x) _Pragma (#x)

#if defined(__GNUC__)
#if defined(__clang__) || __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)
/* the GCC argument will work for both gcc and clang  */
#define CTEST_IMPL_DIAG_PUSH_IGNORED(w) \
  CTEST_IMPL_PRAGMA (GCC diagnostic push) \
  CTEST_IMPL_PRAGMA (GCC diagnostic ignored "-W" #w)
#define CTEST_IMPL_DIAG_POP() CTEST_IMPL_PRAGMA (GCC diagnostic pop)
#else
/* the push/pop functionality wasn't in gcc until 4.6, fallback to "ignored" */
#define CTEST_IMPL_DIAG_PUSH_IGNORED(w) \
  CTEST_IMPL_PRAGMA (GCC diagnostic ignored "-W" #w)
#define CTEST_IMPL_DIAG_POP()
#endif
#else
/* leave them out entirely for non-GNUC compilers  */
#define CTEST_IMPL_DIAG_PUSH_IGNORED(w)
#define CTEST_IMPL_DIAG_POP()
#endif

struct ctest {
    const char *ssname; // suite name
    const char *ttname; // test name
    union ctest_run_func_union run;

    void *data;
    ctest_setup_func *setup;
    ctest_teardown_func *teardown;

    int skip;

    unsigned int magic;
};

#define CTEST_IMPL_NAME(name) ctest_##name
#define CTEST_IMPL_FNAME(sname, tname) CTEST_IMPL_NAME (sname##_##tname##_run)
#define CTEST_IMPL_TNAME(sname, tname) CTEST_IMPL_NAME (sname##_##tname)
#define CTEST_IMPL_DATA_SNAME(sname) CTEST_IMPL_NAME (sname##_data)
#define CTEST_IMPL_DATA_TNAME(sname, tname) CTEST_IMPL_NAME (sname##_##tname##_data)
#define CTEST_IMPL_SETUP_FNAME(sname) CTEST_IMPL_NAME (sname##_setup)
#define CTEST_IMPL_SETUP_FPNAME(sname) CTEST_IMPL_NAME (sname##_setup_ptr)
#define CTEST_IMPL_SETUP_TPNAME(sname, tname) CTEST_IMPL_NAME (sname##_##tname##_setup_ptr)
#define CTEST_IMPL_TEARDOWN_FNAME(sname) CTEST_IMPL_NAME (sname##_teardown)
#define CTEST_IMPL_TEARDOWN_FPNAME(sname) CTEST_IMPL_NAME (sname##_teardown_ptr)
#define CTEST_IMPL_TEARDOWN_TPNAME(sname, tname) CTEST_IMPL_NAME (sname##_##tname##_teardown_ptr)

#define CTEST_IMPL_MAGIC (0xdeadbeef)
#ifdef __APPLE__
#define CTEST_IMPL_SECTION \
  __attribute__ ((used, section ("__DATA, .ctest"), aligned (1)))
#else
#define CTEST_IMPL_SECTION \
  __attribute__ ((used, section (".ctest"), aligned (1)))
#endif

#define CTEST_IMPL_STRUCT(sname, tname, tskip, tdata, tsetup, tteardown)      \
  static struct ctest CTEST_IMPL_TNAME (sname, tname) CTEST_IMPL_SECTION = {  \
    #sname,                                                                   \
    #tname,                                                                   \
    { (ctest_nullary_run_func)CTEST_IMPL_FNAME (sname, tname) },              \
    tdata,                                                                    \
    (ctest_setup_func *)tsetup,                                               \
    (ctest_teardown_func *)tteardown,                                         \
    tskip,                                                                    \
    CTEST_IMPL_MAGIC,                                                         \
  }

#ifdef __cplusplus

#define CTEST_SETUP(sname) \
  template <> \
  void CTEST_IMPL_SETUP_FNAME (sname) (struct CTEST_IMPL_DATA_SNAME (sname) * data)

#define CTEST_TEARDOWN(sname) \
  template <> \
  void CTEST_IMPL_TEARDOWN_FNAME (sname) (struct CTEST_IMPL_DATA_SNAME (sname) * data)

#define CTEST_DATA(sname) \
  template <typename T> void CTEST_IMPL_SETUP_FNAME (sname) (T * data) {} \
  template <typename T> void CTEST_IMPL_TEARDOWN_FNAME (sname) (T * data) {}  \
  struct CTEST_IMPL_DATA_SNAME (sname)

#define CTEST_IMPL_CTEST(sname, tname, tskip) \
  static void CTEST_IMPL_FNAME (sname, tname) (void); \
  CTEST_IMPL_STRUCT (sname, tname, tskip, NULL, NULL, NULL); \
  static void CTEST_IMPL_FNAME (sname, tname) (void)

#define CTEST_IMPL_CTEST2(sname, tname, tskip) \
  static struct CTEST_IMPL_DATA_SNAME (sname) \
      CTEST_IMPL_DATA_TNAME (sname, tname); \
  static void CTEST_IMPL_FNAME (sname, tname) ( \
      struct CTEST_IMPL_DATA_SNAME (sname) * data); \
  static void (*CTEST_IMPL_SETUP_TPNAME (sname, tname)) ( \
      struct CTEST_IMPL_DATA_SNAME (sname) *) \
      = &CTEST_IMPL_SETUP_FNAME ( \
          sname)<struct CTEST_IMPL_DATA_SNAME (sname)>; \
  static void (*CTEST_IMPL_TEARDOWN_TPNAME (sname, tname)) ( \
      struct CTEST_IMPL_DATA_SNAME (sname) *) \
      = &CTEST_IMPL_TEARDOWN_FNAME ( \
          sname)<struct CTEST_IMPL_DATA_SNAME (sname)>; \
  CTEST_IMPL_STRUCT (sname, tname, tskip, \
                     &CTEST_IMPL_DATA_TNAME (sname, tname), \
                     (ctest_setup_func *) &CTEST_IMPL_SETUP_TPNAME (sname, tname), \
                     (ctest_teardown_func *) &CTEST_IMPL_TEARDOWN_TPNAME (sname, tname)); \
  static void CTEST_IMPL_FNAME (sname, tname) ( \
      struct CTEST_IMPL_DATA_SNAME (sname) * data)

#else

#define CTEST_SETUP(sname) \
  static void CTEST_IMPL_SETUP_FNAME (sname) ( \
      struct CTEST_IMPL_DATA_SNAME (sname) * data); \
  static void (*CTEST_IMPL_SETUP_FPNAME (sname)) ( \
      struct CTEST_IMPL_DATA_SNAME (sname) *) \
      = &CTEST_IMPL_SETUP_FNAME (sname); \
  static void CTEST_IMPL_SETUP_FNAME (sname) ( \
      struct CTEST_IMPL_DATA_SNAME (sname) * data)

#define CTEST_TEARDOWN(sname) \
  static void CTEST_IMPL_TEARDOWN_FNAME (sname) ( \
      struct CTEST_IMPL_DATA_SNAME (sname) * data); \
  static void (*CTEST_IMPL_TEARDOWN_FPNAME (sname)) ( \
      struct CTEST_IMPL_DATA_SNAME (sname) *) \
      = &CTEST_IMPL_TEARDOWN_FNAME (sname); \
  static void CTEST_IMPL_TEARDOWN_FNAME (sname) ( \
      struct CTEST_IMPL_DATA_SNAME (sname) * data)

#define CTEST_DATA(sname) \
  struct CTEST_IMPL_DATA_SNAME (sname); \
  static void (*CTEST_IMPL_SETUP_FPNAME (sname)) ( \
      struct CTEST_IMPL_DATA_SNAME (sname) *); \
  static void (*CTEST_IMPL_TEARDOWN_FPNAME (sname)) ( \
      struct CTEST_IMPL_DATA_SNAME (sname) *); \
  struct CTEST_IMPL_DATA_SNAME (sname)

#define CTEST_IMPL_CTEST(sname, tname, tskip) \
  static void CTEST_IMPL_FNAME (sname, tname) (void); \
  CTEST_IMPL_STRUCT (sname, tname, tskip, NULL, NULL, NULL); \
  static void CTEST_IMPL_FNAME (sname, tname) (void)

#define CTEST_IMPL_CTEST2(sname, tname, tskip) \
  static struct CTEST_IMPL_DATA_SNAME (sname) \
      CTEST_IMPL_DATA_TNAME (sname, tname); \
  static void CTEST_IMPL_FNAME (sname, tname) ( \
      struct CTEST_IMPL_DATA_SNAME (sname) * data); \
  CTEST_IMPL_STRUCT (sname, tname, tskip, \
                     &CTEST_IMPL_DATA_TNAME (sname, tname), \
                     (ctest_setup_func *) &CTEST_IMPL_SETUP_FPNAME (sname), \
                     (ctest_teardown_func *) &CTEST_IMPL_TEARDOWN_FPNAME (sname)); \
  static void CTEST_IMPL_FNAME (sname, tname) ( \
      struct CTEST_IMPL_DATA_SNAME (sname) * data)

#endif

#define CTEST(sname, tname) CTEST_IMPL_CTEST (sname, tname, 0)
#define CTEST_SKIP(sname, tname) CTEST_IMPL_CTEST (sname, tname, 1)
#define CTEST2(sname, tname) CTEST_IMPL_CTEST2 (sname, tname, 0)
#define CTEST2_SKIP(sname, tname) CTEST_IMPL_CTEST2 (sname, tname, 1)

int ctest_main (int argc, const char *argv[]);

#ifdef __cplusplus
}
#endif

#endif
