#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

/* FIXME: 
   Check these declarations against the C/Fortran source code.
*/

/* .Call calls */
extern SEXP C_fullocate(SEXP);

static const R_CallMethodDef CallEntries[] = {
    {"C_fullocate", (DL_FUNC) &C_fullocate, 1},
    {NULL, NULL, 0}
};

void R_init_testpkg(DllInfo *dll)
{
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
