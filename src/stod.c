#include <Rinternals.h>


SEXP C_int_mat_nth_row_nrnc(int *int_mat_int, int nr, int nc, int n) {
  SEXP out = PROTECT(Rf_allocVector(INTSXP, nc));
  int *out_int = INTEGER(out);
  if (n <= 0 | n > nr) {
    for (int i = 0; i != nc; ++i) {
      out_int[i] = NA_INTEGER;
    }
  } else {
    for (int i = 0; i != nr; ++i) {
      out_int[i] = int_mat_int[n - 1 + i * nr];
    }
  }
  UNPROTECT(1);
  return out;
}

SEXP C_make_len2_int_vec(int first, int second) {
  SEXP out = PROTECT(Rf_allocVector(INTSXP, 2));
  int *out_int = INTEGER(out);
  out_int[0] = first;
  out_int[1] = second;
  UNPROTECT(1);
  return out;
}

SEXP C_fullocate(SEXP int_mat) {
  int nr = Rf_nrows(int_mat), *int_mat_int = INTEGER(int_mat);
  int last, row_num;  // row_num will be 1-indexed
  SEXP prlst0cdr = PROTECT(C_int_mat_nth_row_nrnc(int_mat_int, nr, 2, 1));
  SEXP prlst = PROTECT(Rf_list1(prlst0cdr));
  SEXP prlst_tail = prlst;
  last = INTEGER(prlst0cdr)[1];
  row_num = 2;
  while (row_num <= nr) {
    Rprintf("row_num: %i\n", row_num);
    SEXP row = PROTECT(C_int_mat_nth_row_nrnc(int_mat_int, nr, 2, row_num));
    Rf_PrintValue(prlst);
    int *row_int = INTEGER(row);
    if (row_int[0] == last + 1) {
      Rprintf("here1");
      SEXP next = PROTECT(Rf_list1(row));
      prlst_tail = SETCDR(prlst_tail, next);
      last = row_int[1];
      UNPROTECT(1);
      ++row_num;
    } else {
      Rprintf("here2");
      SEXP next_car = PROTECT(C_make_len2_int_vec(last + 1, row_int[0] - 1));
      SEXP next = PROTECT(Rf_list1(next_car));
      prlst_tail = SETCDR(prlst_tail, next);
      last = row_int[0] - 1;
      UNPROTECT(2);
    }
    UNPROTECT(1);
  }
  SEXP out = PROTECT(Rf_PairToVectorList(prlst));
  UNPROTECT(3);
  return out;
}

